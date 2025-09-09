/// @file threadqueue.h
#pragma once
#include "osutils.h"
#include "threadcommon.h"
#include "threadjoblist.h"
#include "types.h"

/// @brief Job Queue -- A job queue that contains pointers to runtime jobs of a specific logical priority
class JobQueue
{
public:
    /// @brief Constructor for JobQueue object
    JobQueue();

    /// @brief Destructor for JobQueue object
    ~JobQueue();

    /// @brief Enqueue a runtime job
    Result Enqueue(RuntimeJob * pJob, JobRegistry * pJobRegistry);

    /// @brief  Unlock queue
    void UnlockQueue();

    /// @brief Lock queue
    void LockQueue();

    /// @brief Returns if queue has jobs
    bool HasJobs(JobRegistry * pJobRegistry);

    /// @brief  Conditionally dequeue a runtime job, based on the overall state of jobs
    JobStatus CheckAndDequeue(RuntimeJob * *ppJob, JobRegistry * pJobRegistry);

protected:
    // Disable copy constructor and assignment operator
    JobQueue(const JobQueue&) = delete;
    JobQueue(JobQueue&&) = delete;
    JobQueue& operator = (const JobQueue&) = delete;
    JobQueue& operator = (JobQueue&&) = delete;

private:
    /// @brief  Get the first eligible job of the family which can be moved to Ready state
    RuntimeJob* GetFirstEligibleJob(JobRegistry * pJobRegistry, u_int64_t hJob);

    u_int32_t m_head; ///< Queue head
    u_int32_t m_tail; ///< Queue tail
    RuntimeJob* m_pJobs[MaxRuntimeJobs]; ///< Pointer to the runtime jobs

    Mutex* m_pQueueLock; ///< Queue lock
};