/// @file types.h
#pragma once

#include <cstdint>

enum class Result {
    ResultSuccess = 0, ///< Operation was successful
    ResultEFailed = 1, ///< Operation encountered unspecified error
    ResultEUnsupported = 2, ///< Operation is not supported
    ResultEInvalidState = 3, ///< Invalid state
    ResultEInvalidArg = 4, ///< Invalid argument
    ResultEInvalidPointer = 5, ///< Invalid memory pointer
    ResultENoSuch = 6, ///< No such item exists or is valid
    ResultEOutOfBounds = 7, ///< Out of bounds
    ResultENoMemory = 8, ///< Out of memory
    ResultETimeout = 9, ///< Operation timed out
    ResultENoMore = 10, ///< No more items available
    ResultENeedMore = 11, ///< Operation requires more
    ResultEExists = 12, ///< Item exists
    ResultEPrivLevel = 13, ///< Privileges are insufficient for requested operation
    ResultEResource = 14, ///< Resources are insufficient for requested operation
    ResultEUnableToLoad = 15, ///< Unable to load library/object
    ResultEInProgress = 16, ///< Operation is already in progress
    ResultETryAgain = 17, ///< Could not complete request, try again
    ResultEBusy = 18, ///< Device or resource busy
    ResultEReentered = 19, ///< Non re-entrant API re-entered
    ResultEReadOnly = 20, ///< Cannot change read-only object or parameter
    ResultEOverflow = 21, ///< Value too large for defined data type
    ResultEOutOfDomain = 22, ///< Math argument or result out of domain
    ResultEInterrupted = 23, ///< Waitable call is interrupted
    ResultEWouldBlock = 24, ///< Operation would block
    ResultETooManyUsers = 25, ///< Too many users
    ResultENotImplemented = 26, ///< Function or method is not implemented
    ResultEDisabled = 27, ///< Feature disabled (by an override for example)
    ResultECancelledRequest = 28, ///< Flush in progress or bind import failure
    ResultECoreNullMetadata = 29, ///< Metadata is null
    ResultEInducedError = 30, ///< Induced error using error inducement framework
    ResultEFenceGroupError = 31, ///< Composite fence group configure incorrect
    ResultECSLStreamOn = 32, ///< Error Streaming CSL On
    ResultEAlreadyCompleted = 33, ///< Error indicating the request is already completed
    ResultEOEMStatus1 = 34, ///< Error used by OEMs for customizations
    ResultEOEMStatus2 = 35, ///< Error used by OEMs for customizations
    ResultEOEMStatus3 = 36, ///< Error used by OEMs for customizations
    ResultEProviderNotExist = 37, ///< No such provider exists
    // Increment the count below if adding additional result codes.
    ResultCount = 38, ///< The number of result codes. Not to be used.
};

/// @brief 256 character string length
static const uint32_t MaxHMSFailedJobNameLength = 256;

/// @brief Describes the failure reported by HMS.
struct HMSJobFailedStatus {
    uint32_t cameraId; ///< Logical cameraId on which failure is detected
    uint32_t errorCode; ///< Error code for a failure
    uint32_t tid; ///< Thread Id for the failed job
    uint32_t pid; ///< Process Id for the failed job
    uint64_t maxExecTime; ///< Max execution time alloted for a job
    uint64_t execTime; ///< Total execution time  for a job
    char jobName[MaxHMSFailedJobNameLength]; ///< Failed job family/node name
    void* pClient; ///< HMS Client handle
    void* pRuntimeJob; ///< Failed Job pointer
    bool paused; ///< Flag to indicate if job is paused
};

/// @brief Invalid camera id;
static const uint32_t InvalidCameraId = 0xFFFFFFFF;