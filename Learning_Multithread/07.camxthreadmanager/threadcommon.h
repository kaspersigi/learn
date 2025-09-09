/// @file threadcommon.h
#pragma once
#include "threadmanager.h"
#include "osutils.h"
#include <pthread.h>

// Forward declaration(s)
struct RuntimeJob;

// Default max number of threads per pool
static const uint32_t MaxThreadsPerPool = 15;

// Max registered jobs in a pool
static const uint32_t MaxNameLength = 128;

// Max data partitions allowed inside a job
static const uint32_t MaxDataPartition = 3;

// Max registered jobs in a pool
static const uint32_t MaxRuntimeJobs = 4096;

// Max registered jobs in a pool (64 per camera)
static const uint32_t MaxRegisteredJobs = 512;

// One queue per priority level
static const unsigned int MaxNumQueues = static_cast<unsigned int>(JobPriority::Invalid);

/// @brief Core status type
typedef uint8_t CoreStatus;

/// @brief Core status type
typedef uint8_t FlushStatus;

// The following status codes are defined as native types since
// atomic operations are not friendly with abstract types, like enum

// Thread core status
static const CoreStatus Error = 0; ///< Error state
static const CoreStatus Initialized = 1; ///< Initialized and running state
static const CoreStatus Stopped = 2; ///< Stopped state

// Flush status
static const FlushStatus Noflush = 0; ///< Default state
static const FlushStatus FlushRequested = 1; ///< A flush is requested
static const FlushStatus SyncRequested = 2; ///< A sync is requested
static const FlushStatus Flushed = 3; ///< Flush/Sync request has been fulfilled

/// @brief Status of a runtime job in the threadpool
enum class JobStatus {
    Submitted, ///< A job is being added to one of the job Queues
    Ready, ///< A submitted job is being dispatched
    OnHold, ///< A submitted job is being put on hold since one of the previous jobs in family hasn't finished
    Stopped, ///< A flush is issued on the job family and the job is being stopped
    Invalid ///< Invalid status
};

/// @brief Structure describing the properties of a registered Job family
struct RegisteredJob {
    JobFunc funcAddr; ///< Address of job function for job family
    char name[MaxNameLength]; ///< Text name of job function for job family
    JobCb flushDoneCb; ///< Flush done callback address for job family
    JobPriority priority; ///< Priority of jobs in the job family
    bool isSerial; ///< Specifies if the jobs in the family need to be executed in a serial fashion

    uint32_t uniqueCounter; ///< Unique value for this Register
    uint32_t slot; ///< The slot in the job registry in which a job family is registered
    uint32_t jobCount; ///< Number of outstanding runtime jobs of the family
    uint32_t inflightCount; ///< Number jobs in the family that are currently executing
    uint32_t holdCount; ///< Number of jobs in the family that are currently on hold
    uint32_t submittedCount; ///< Number of jobs in the family that are currently in submitted state
    uint32_t jobFamilyRefCount; ///< Number of references to a shared job family handle
    uint64_t hRegister; ///< Opaque handle to the registered job

    FlushStatus flushStatus; ///< Current flush status of the registered job
    void* pFlushUserData; ///< Userdata, opaque to the threadpool, to be passed with flush done callback
    bool blockFlush; ///< Indicates that caller is blocked on flush
    Semaphore* pFlushSemaphore; ///< Semaphore to block caller of flush

    RuntimeJob* pFirstJob; ///< Pointer to the first runtime job, of this family, in the job list
    RuntimeJob* pLastJob; ///< Pointer to the last runtime job, of this family, in the job list
    uint32_t cameraId; ///< Logical camera Id for which this family is registered, needed for HMS
};

/// @brief Structure describing the properties of a runtime Job
struct RuntimeJob {
    uint64_t hJob; ///< Opaque handle to the registered job
    const char* pName; ///< Name of a job
    JobCb stoppedCb; ///< Stopped callback of a job, called when a flush is issued on the job family
    void* pData[MaxDataPartition]; ///< Null terminated data pointers for a job
    bool isSplitable; ///< If the job can be split into multiple jobs, and executed in parallel
    bool isBlocking; ///< If the caller is blocking on the job to complete execute

    uint32_t numPartitions; ///< Number of data partitions for the job
    JobStatus status; ///< Current status of the runtime job
    uint32_t slot; ///< Slot in the job list, where the runtime job sits
    Semaphore* pJobSemaphore; ///< Semaphore to block caller of job
    uint64_t maxExecTime; ///< Max execution time alloted for a job
    RuntimeJob* pNext; ///< Pointer to the next serial job in the job list
};

/// @brief Structure describing a Worker Thread
struct ThreadConfig {
    uint32_t threadId; ///< Logical thread number
    pthread_t hWorkThread; ///< Platform thread id
    JobFunc workThreadFunc; ///< Thread entry function
    void* pContext; ///< Opaque configuration handle
};