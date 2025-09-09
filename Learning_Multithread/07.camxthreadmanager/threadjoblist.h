/// @file threadjoblist.h
#pragma once
#include "threadcommon.h"

/// @brief A slot in the runtime JobList
struct JobSlot {
    uint32_t slot; ///< This slot
    uint32_t next; ///< Pointer to the next available slot
};

/// @brief JobList holds and keeps track of all submitted jobs in the thread library
class JobList
{
public:
    /// @brief Constructor for JobList object
    explicit JobList(JobRegistry * pJobRegistry);

    /// @brief Destructor for JobList object
    ~JobList();

    /// @brief Fits a runtime job into the job list
    RuntimeJob* AcquireJobEntry(JobHandle hJob);

    /// @brief  Releases a runtime job from the job list after it finished execution or was stopped
    void ReleaseJobEntry(RuntimeJob * pJob);

    /// @brief Initialize a newly created JobList object
    Result Initialize();

protected:
    // Disable copy constructor and assignment operator
    JobList(const JobList&) = delete;
    JobList(JobList&&) = delete;
    JobList& operator = (const JobList&) = delete;
    JobList& operator = (JobList&&) = delete;

private:
    JobRegistry* m_pJobRegistry; ///< Cache the job registry
    RuntimeJob m_jobList[MaxRuntimeJobs]; ///< Container of runtime jobs

    uint32_t m_freeHead; ///< Head of free slot list
    uint32_t m_freeTail; ///< Tail of free slot list
    JobSlot m_freeList[MaxRuntimeJobs]; ///< List of free slots

    uint32_t m_jobOccupancy; ///< Current job occupancy in the list
    Mutex* m_pListLock; ///< Job List lock
};