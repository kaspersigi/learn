#!/bin/bash

# 1. 设置 NDK 路径 (请修改为你实际的路径)
export NDK_ROOT=/mnt/develop/android-ndk-r27d

# 2. 设置构建目录
BUILD_DIR=out

# 3. 创建构建目录
mkdir -p $BUILD_DIR

# 4. 运行 CMake 配置
# -DCMAKE_TOOLCHAIN_FILE: 指定 NDK 自带的 CMake 脚本，这是核心
# -DANDROID_ABI: 目标架构 (arm64-v8a, armeabi-v7a, x86_64, x86)
# -DANDROID_PLATFORM: 目标 Android API 等级 (例如 android-21 对应 Android 5.0)
cmake -H. -B$BUILD_DIR \
    -DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-35 \
    -DANDROID_STL=c++_shared \
    -DCMAKE_BUILD_TYPE=Release

# 5. 开始编译
cmake --build $BUILD_DIR