#!/usr/bin/bash
# ubuntu 24.04.1

TEMP_PATH="/mnt/c/Users/Public/Downloads"
BOCHS_VERSION="2.8"
BOCHS_PATH="/mnt/d/Learning_Kernel/bochs-$BOCHS_VERSION"

sudo -s <<EOF

apt update
apt upgrade -y
apt autoremove -y

apt install clang-19 clangd-19 clang-format-19 lldb-19 libllvmlibc-19-dev libc++-19-dev lld-19 binutils-i686-linux-gnu binutils-riscv64-linux-gnu gcc-i686-linux-gnu bsdmainutils make gdb cgdb valgrind qemu-system-arm qemu-system-misc qemu-system-x86 -y
apt install libncurses-dev flex bison bc dwarves libssl-dev libelf-dev python-is-python3 bzip2 unzip xz-utils lz4 cpio -y

echo 'LANG="zh_CN.UTF-8"' > /etc/default/locale
source /etc/default/locale

update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-19 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-19 100

wget -P $TEMP_PATH https://dl.google.com/android/repository/android-ndk-r27c-linux.zip
wget -P $TEMP_PATH https://dl.google.com/android/repository/platform-tools-latest-windows.zip

# echo "BOCHS_PATH=$BOCHS_PATH"
if [ -e "$BOCHS_PATH" ]; then
    echo "install bochs-$BOCHS_VERSION"
    apt install libltdl7 libsdl2-2.0-0 libgtk-3-0t64 -y
    tar zxvf $BOCHS_PATH/bochs-$BOCHS_VERSION-bin.tar.gz -C /tmp
    cd /tmp/bochs-$BOCHS_VERSION-bin
    make install
else
    echo "install bochs failed"
fi

su miku