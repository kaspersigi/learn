/// @file threadcore.h
#pragma once
#include "def.h"
#include "imonitorclient.h"
#include "threadcommon.h"
#include <cassert>
#include <sys/types.h>

/// @brief ThreadCore provides the core worker thread functionality
class ThreadCore
{
public:
    /// @brief Constructor for ThreadCore object
    ThreadCore(
        JobRegistry * pJobRegistry,
        JobList * pJobList,
        const char* pName,
        uint32_t numThreads,
        bool enableHMS,
        uint32_t maxDelayedJobCount,
        IMonitorClient* pClientObj);

    /// @brief Destructor for ThreadCore object
    ~ThreadCore();

    Result AcceptNewJob(
        JobHandle hJob,
        JobCb stoppedCb,
        void** ppData,
        bool isSplitable,
        bool isBlocking,
        uint64_t maxExecTime = MaxExecutionTimeMilliseconds,
        const char* pName = nullptr);

    /// @brief Sync/Flush a registered family of job
    Result SyncOrFlushJob(
        JobHandle hJob,
        void* pUserData,
        bool isBlocking,
        FlushStatus flushStatus);

    /// @brief Resume job after flush
    Result ResumeJob(JobHandle hJob);

    /// @brief Retrieve current job count of a registered job
    inline uint32_t GetJobCount(JobHandle hJob) const
    {
        if (!((Initialized == GetStatus()) && m_pJobregistry && (true == m_pJobregistry->ValidateJob(hJob)))) {
            spdlog::error("Cannot get job count");
            assert(false && "Cannot get job count");
        }

        return m_pJobregistry->GetJobCount(hJob);
    }

    /// @brief  Retrieve number of jobs executing currently
    inline uint32_t GetInFlightCount(JobHandle hJob) const
    {
        if (!((Initialized == GetStatus()) && m_pJobregistry && (true == m_pJobregistry->ValidateJob(hJob)))) {
            spdlog::error("Cannot get job count");
            assert(false && "Cannot get job count");
        }

        return m_pJobregistry->GetInflightCount(hJob);
    }

    /// @brief  Initialize a newly created ThreadCore object
    Result Initialize();

    /// @brief  Scan inflight jobs of this module
    Result ScanAllJobs(std::vector<HMSJobFailedStatus> & rStatus);

    /// @brief  Method to call by HMS to pause the monitoring of a job
    void PauseMonitoringJob(void * pJob, u_int64_t pauseTime);

    /// @brief  Method to call by HMS to resume the monitoring of a job if paused
    void ResumeMonitoringJob(void* pJob);

protected:
    // Disable copy constructor and assignment operator
    ThreadCore(const ThreadCore&) = delete;
    ThreadCore(ThreadCore&&) = delete;
    ThreadCore& operator = (const ThreadCore&) = delete;
    ThreadCore& operator = (ThreadCore&&) = delete;

private:
    /// @brief Runtime job execution info
    struct RuntimeJobExecInfo {
        RuntimeJob* pJob; ///< Reference to runtime job
        u_int32_t tid; ///< Thread id of the executing thread
        u_int32_t pid; ///< Process id of the executing thread
        u_int64_t startTime; ///< Execution start time for this job
        u_int32_t delayFactor; ///< Delay factor (of max delaycount) for this job
        u_int64_t pauseTime; ///< Job pause time if job is paused otherwise 0
    };

    /// @brief  Get the current status of the thread library core
    inline CoreStatus GetStatus() const
    {
        return CamxAtomicStoreU8(const_cast<volatile u_int8_t*>(&m_status));
    }

    /// @brief  Set the current status of the thread library core
    inline void SetStatus(CoreStatus status)
    {
        CamxAtomicStoreU8(&m_status, status);
    }

    /// @brief  Static, common landing function for all worker threads after creation
    static void* WorkerThreadBody(void* pArg);

    /// @brief  Actual worker thread routine
    void* DoWork(const u_int32_t threadIndex);

    /// @brief  Main routine for worker threads to look into and execute job queues in order of priority
    Result ProcessJobQueue(const u_int32_t threadIndex);

    /// @brief  Adds a runtime job to one of the job queues, based on priority
    Result AddToPriorityQueue(RuntimeJob * pJob);

    /// @brief  Get the specific job queue based on priority
    JobQueue* GetQueue(JobPriority priority);

    /// @brief  Add a job to monitor and Dispatch a job from the thread pool by calling its function
    void MonitorAndDispatchJob(RuntimeJob * pJob, const u_int32_t threadIndex);

    /// @brief  Dispatch a job from the thread pool by calling its function
    void DispatchJob(RuntimeJob * pJob);

    /// @brief  Trigger threads to process job queues
    void Trigger();

    /// @brief  Call stoppedCb, the job family is being flushed
    void OnJobStopped(RuntimeJob * pJob);

    /// @brief  Go through all registered jobs one by one, and flush them, blocking on each flush
    void FlushAllJobsInternal();

    /// @brief  Create & start worker threads, initialize mutex and conditions
    Result StartThreads();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// StopThreads
    ///
    /// @brief  Stop worker threads, and de-initialize mutex and condition
    ///
    /// @return Success or EFailed
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Result StopThreads();

    /// @brief Max size for a given thread name including instance id
    static const int ThreadNameLength = 255;

    char m_name[ThreadNameLength]; ///< Brief human readable name for the pool
    JobRegistry* m_pJobregistry; ///< Pointer to job registry
    JobList* m_pJobList; ///< Pointer to job list
    u_int32_t m_numThreads; ///< Number of worker threads in the pool
    volatile bool m_stopped; ///< Indicates whether the threads should stop running
    volatile bool m_jobPending; ///< Indicates if a new job is submitted
    JobQueue m_jobQueues[MaxNumQueues]; ///< Priority Job Queues - 0 = critical, 1 = high and 2 = normal

    Mutex* m_pThreadLock; ///< Single lock for all threads, covers m_pReadOK, m_stopped, m_jobPending
    Mutex* m_pInFlightQueueLock; ///< Lock for inflight runtime jobs monitored by HMS
    Condition* m_pReadOK; ///< Single condition for all threads

    CoreStatus m_status; ///< Overall status of the core (one of Error, Inited or Stopped)
    ThreadConfig m_workers[MaxThreadsPerPool]; ///< Actual worker thread configurations
    bool m_enableHealthMonitor; ///< Flag to indicate if healthMonitor is enabled or not
    u_int32_t m_maxDelayedJobCount; ///< Max number of delayed job count
    std::vector<RuntimeJobExecInfo>
        m_inFlightJobs; ///< Inflight job list (for monitoring)
    IMonitorClient* m_pHMSClientObj; ///< Pointer to HMS client object
};