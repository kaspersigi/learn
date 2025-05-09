#!/usr/bin/bash
# ubuntu 22.04.5

LLVM_VERSION="20"
LLVM="-$LLVM_VERSION"
TOP_PATH="/mnt/d/Learning_Perf/learn"
TEMP_PATH="/mnt/c/Users/Public/Downloads"
BOCHS_VERSION="3.0"
BOCHS_PATH="$TOP_PATH/bochs-$BOCHS_VERSION"
PLATFORM="darwin"
ARCH=$(uname -m)
if [ "$ARCH" = "x86_64" ]; then
    PLATFORM="linux"
elif [ "$ARCH" = "aarch64" ]; then
    PLATFORM="windows"
fi

sudo -s <<EOF

wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo gpg --dearmor -o /usr/share/keyrings/llvm-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/llvm-archive-keyring.gpg] https://apt.llvm.org/jammy/ llvm-toolchain-jammy$LLVM main" | sudo tee /etc/apt/sources.list.d/llvm.list

wget -qO - https://repositories.intel.com/gpu/intel-graphics.key | sudo gpg --yes --dearmor --output /usr/share/keyrings/intel-graphics.gpg
echo "deb [arch=amd64,i386 signed-by=/usr/share/keyrings/intel-graphics.gpg] https://repositories.intel.com/gpu/ubuntu jammy unified" | sudo tee /etc/apt/sources.list.d/intel-gpu-jammy.list

apt update
apt upgrade -y
apt autoremove -y

apt install clang$LLVM clangd$LLVM clang-format$LLVM lldb$LLVM libllvmlibc$LLVM-dev libc++$LLVM-dev lld$LLVM binutils-i686-linux-gnu binutils-x86-64-linux-gnu binutils-riscv64-linux-gnu gcc-i686-linux-gnu bsdmainutils make gdb cgdb valgrind qemu-system-arm qemu-system-misc qemu-system-x86 -y
apt install libncurses-dev flex bison bc dwarves libssl-dev libelf-dev python-is-python3 bzip2 unzip xz-utils lz4 cpio -y
apt install libze-intel-gpu1 libze1 intel-opencl-icd libze-dev intel-ocloc intel-level-zero-gpu-raytracing clinfo -y

apt update
apt upgrade -y
apt autoremove -y

echo 'LANG="zh_CN.UTF-8"' > /etc/default/locale
source /etc/default/locale

update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format$LLVM 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd$LLVM 100

wget -P $TEMP_PATH https://dl.google.com/android/repository/android-ndk-r27c-$PLATFORM.zip
wget -P $TEMP_PATH https://dl.google.com/android/repository/platform-tools-latest-windows.zip
# systrace
# wget -P $TEMP_PATH https://dl.google.com/android/repository/platform-tools_r33.0.0-$PLATFORM.zip

# echo "BOCHS_PATH=$BOCHS_PATH"
if [ -e "$BOCHS_PATH" ]; then
    echo "install bochs-$BOCHS_VERSION"
    apt install libltdl7 libsdl2-2.0-0 libgtk2.0-0 -y
    tar zxvf $BOCHS_PATH/bochs-$BOCHS_VERSION-bin-$ARCH.tar.gz -C /tmp
    cd /tmp/bochs-$BOCHS_VERSION-bin
    make install
else
    echo "install bochs failed"
fi

su miku