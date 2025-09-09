/// @file main.cc
#include "ftrace.h"
#include "spdlog/spdlog.h"
#include "threadmanager.h"

auto main(int argc, char* argv[]) -> int
{
    Ftrace::ftrace_duration_begin("MainThread");

    ThreadManager* pPerfThreadPool = nullptr;
    Result result = ThreadManager::Create(&pPerfThreadPool, "PerfThreadManager", 4);

    spdlog::info("Hello World!");

    pPerfThreadPool->Destroy();
    pPerfThreadPool = nullptr;

    Ftrace::ftrace_duration_end();

    return 0;
}