/// @file imonitorclient.h
#pragma once

#include "types.h"
#include <vector>

/// @brief This interface can be implemented by different classes to opt for  health monitoring Service and act like a client
class IMonitorClient
{
public:
    /// @brief Method to call by HMS to scan client jobs
    virtual Result OnScanAllJobs(std::vector<HMSJobFailedStatus> & rJobStatus) = 0;
    /// @brief Method to call by HMS to pause the monitoring of a job
    virtual void OnPauseMonitoringJob(void* pJob, uint64_t pauseTime) = 0;
    /// @brief Method to call by HMS to resume the monitoring of a job if paused
    virtual void OnResumeMonitoringJob(void* pJob) = 0;

protected:
    IMonitorClient() = default;
    virtual ~IMonitorClient() = default;
    // Disable copy constructor and assignment operator
    IMonitorClient(const IMonitorClient&) = delete;
    IMonitorClient(IMonitorClient&&) = delete;
    IMonitorClient& operator = (const IMonitorClient&) = delete;
    IMonitorClient& operator = (IMonitorClient&&) = delete;
};