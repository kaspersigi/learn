/// @file def.h
#pragma once
#include <cstdint>

/// @brief Define Default maximum execution time for a job
static const uint64_t MaxExecutionTimeMilliseconds = 66; ///< Maxtime of execution in 30FPS case and considering SBM delays
static const uint64_t MaxConfigureExecutionTimeMs = 300; ///< Max time of execution for feature2 or configureTIme jobs
static const uint64_t MaxExecutionTimeForCSLMs = 90; ///< Max Execution time for CSL thread
static const uint64_t MaxExecutionTimeForResultMs = 200; ///< Maximum execution time for camxsession result processing
static const uint32_t DefaultMaxDelayCount = 1; ///< Default Mas Delay count used in case it is not set explicitly