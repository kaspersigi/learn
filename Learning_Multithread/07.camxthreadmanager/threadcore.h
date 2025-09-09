/// @file threadcore.h
#pragma once
#include "imonitorclient.h"
#include <cassert>

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

    inline uint32_t GetJobCount(JobHandle hJob) const
    {
        if (!((Initialized == GetStatus()) && m_pJobregistry && (m_pJobregistry->ValidateJob(hJob) == TRUE))) {
            spdlog::error("Cannot get job count: status={}, hasRegistry={}, handle={}",
                static_cast<int>(GetStatus()),
                m_pJobregistry != nullptr,
                hJob /* 若不是可打印类型，改用 {:p}+static_cast<const void*>(&hJob) */);
            assert(false && "Cannot get job count"); // Debug 会触发断言，Release 无操作
        }

        return m_pJobregistry->GetJobCount(hJob);
    }
};