/// @file threadmanager.h
#pragma once

#include "def.h"
#include "imonitorclient.h"
#include "types.h"

/// @brief Opaque handle to a job
typedef uint64_t JobHandle;
/// @brief Function pointer type for a job function
typedef void* (*JobFunc)(void* pArg);
/// @brief Function pointer type for a job callback function
typedef void (*JobCb)(void* pUserData);

/// @brief Relative priority of a job submitted
enum struct JobPriority {
    Critical = 0, ///< Critical (highest) priority job in Camx
    High = 1, ///< Next to Critical priority in Camx
    Normal = 2, ///< Next to High priority in Camx
    Invalid = 3 ///< Invalid priority
};

// Invalid thread handle
static const JobHandle InvalidJobHandle = 0;

// Forward declaration of implementation classes
class JobRegistry;
class JobList;
class ThreadCore;
struct RuntimeJob;

/// @brief Thread Library API
class ThreadManager : public IMonitorClient
{
public:
    /// @brief Static method to create an instance of ThreadManager
    static Result Create(
        ThreadManager * *ppInstance,
        const char* pName,
        uint32_t numThreads,
        bool enableHMS = false,
        uint32_t maxDelayedJobCount = DefaultMaxDelayCount);

    /// @brief Method to delete an instance of ThreadManager
    void Destroy();

    /// @brief Register a job family to the thread library. A job family is the set of jobs with the same function name and address, and priority
    Result RegisterJobFamily(
        JobFunc jobFuncAddr,
        const char* pJobFuncName,
        JobCb flushDoneCb,
        JobPriority priority,
        bool isSerialize,
        JobHandle* phJob,
        uint32_t cameraId = InvalidCameraId);

    /// @brief Un-register a job family from the thread library.
    Result UnregisterJobFamily(JobHandle hJob);

    /// @brief Post a job, which may belong to a previously registered family
    Result PostJob(
        JobHandle hJob,
        JobCb stoppedCb,
        void** ppData,
        bool isSplitable,
        bool isBlocking,
        uint64_t maxExecTime = MaxExecutionTimeMilliseconds,
        const char* pJobName = nullptr);

    /// @brief Resume job after flush
    Result ResumeJobFamily(JobHandle hJob);

    /// @brief Flush a registered family of job
    Result FlushJobFamily(
        JobHandle hJob,
        void* pUserData,
        bool isBlocking);

    /// @brief Sync a registered family of job
    Result SyncJobFamily(JobHandle hJob);

    /// @brief Retrieve current job count of a registered job
    uint32_t GetJobCount(JobHandle hJob) const;

    /// @brief Retrieve number of jobs currently executing
    uint32_t GetInFlightCount(JobHandle hJob) const;

    /// @brief  Scan all the jobs of the subscribed client
    Result OnScanAllJobs(std::vector<HMSJobFailedStatus> & rStatus);

    /// @brief  Method to call by HMS to pause the monitoring of a job
    void OnPauseMonitoringJob(void* pJob, uint64_t pauseTime);

    /// @brief  Method to call by HMS to resume the monitoring of a job if paused////////////////////////////////////////////////
    void OnResumeMonitoringJob(void* pJob);

protected:
    uint32_t m_numThreads; ///< suggested number of threads in this pool
    JobRegistry* m_pJobRegistry; ///< Pointer to job registry
    JobList* m_pJobList; ///< Pointer to job list
    ThreadCore* m_pCore; ///< Pointer to thread core
    bool m_enableHealthMonitor; ///< Flag to indicate if health monitor is enabled
    bool m_maxDelayedJobCount; ///< Max delayed job count for HMS

    /// @brief Initialize a newly created ThreadManager object
    Result Initialize(const char* pName);

    /// @brief Constructor for ThreadManager object.
    ThreadManager(
        uint32_t numThreads,
        bool enableHMS,
        uint32_t maxDelayedJobCount);

    /// @brief Default constructor for ThreadManager object.
    ThreadManager();

    /// @brief Destructor for ThreadManager object.
    ~ThreadManager();

    // Disable copy constructor and assignment operator
    ThreadManager(const ThreadManager&) = delete;
    ThreadManager(ThreadManager&&) = delete;
    ThreadManager& operator = (const ThreadManager&) = delete;
    ThreadManager& operator = (ThreadManager&&) = delete;
};