/// @file threadmanager.cc

#include "threadmanager.h"
#include "ftrace.h"
#include "spdlog/spdlog.h"
#include "threadcore.h"

Result ThreadManager::Create(
    ThreadManager** ppInstance,
    const char* pName,
    uint32_t numThreads,
    bool enableHealthMonitor,
    uint32_t maxDelayedJobCount)
{
    Result result = Result::ResultEInvalidArg;
    ThreadManager* pLocalInstance = nullptr;

    Ftrace::ftrace_duration_begin("ThreadManagerCreate");

    if ((0 < numThreads) && (nullptr != ppInstance)) {
        pLocalInstance = new ThreadManager(numThreads, enableHealthMonitor, maxDelayedJobCount);
        if (nullptr != pLocalInstance) {
            result = pLocalInstance->Initialize(pName);
            if (Result::ResultSuccess != result) {
                spdlog::error("Thread manager initialization failed");
                delete pLocalInstance;
                pLocalInstance = nullptr;
            }
        } else {
            spdlog::error("OOM in thread manager creation");
            result = Result::ResultENoMemory;
        }
    } else {
        spdlog::error("Invalid args numThreads {}, ppInstance {}K", numThreads, fmt::ptr(ppInstance));
    }

    if (nullptr != ppInstance) {
        *ppInstance = pLocalInstance;
    }

    Ftrace::ftrace_duration_end();

    return result;
}

ThreadManager::ThreadManager(
    uint32_t numThreads,
    bool enableHealthMonitor,
    uint32_t maxDelayedJobCount)
{
    if (numThreads > MaxThreadsPerPool) {
        numThreads = MaxThreadsPerPool;
    }

    m_numThreads = numThreads;
    m_enableHealthMonitor = enableHealthMonitor;
    m_maxDelayedJobCount = maxDelayedJobCount;
}

ThreadManager::~ThreadManager()
{
    if (nullptr != m_pCore) {
        delete m_pCore;
        m_pCore = nullptr;
    }
    if (nullptr != m_pJobList) {
        delete m_pJobList;
        m_pJobList = nullptr;
    }
    if (nullptr != m_pJobRegistry) {
        delete m_pJobRegistry;
        m_pJobRegistry = nullptr;
    }
}

void ThreadManager::Destroy()
{
    Ftrace::ftrace_duration_begin("ThreadManagerDestroy");

    delete this;

    Ftrace::ftrace_duration_end();
}

Result ThreadManager::Initialize(
    const char* pName)
{
    Result result = Result::ResultSuccess;

    m_pJobRegistry = new JobRegistry;
    if (nullptr != m_pJobRegistry) {
        result = m_pJobRegistry->Initialize();
    } else {
        result = Result::ResultEFailed;
    }

    if (Result::ResultSuccess == result) {
        m_pJobList = new JobList(m_pJobRegistry);
        if (nullptr != m_pJobList) {
            result = m_pJobList->Initialize();
        } else {
            result = Result::ResultEFailed;
        }
    }

    if (Result::ResultSuccess == result) {
        m_pCore = new ThreadCore(m_pJobRegistry, m_pJobList, pName, m_numThreads,
            m_enableHealthMonitor, m_maxDelayedJobCount, this);
        if (nullptr != m_pCore) {
            result = m_pCore->Initialize();
        } else {
            result = Result::ResultEFailed;
        }
    }

    return result;
}