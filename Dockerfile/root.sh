#!/usr/bin/bash
# ubuntu 24.04.1

TEMP_PATH=/mnt/c/Users/Public/Downloads

# sed -i 's@//.*archive.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources
# sed -i 's@//.*security.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources
# sed -i 's@//.*ports.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources

sudo -s <<EOF

apt update
apt upgrade -y
apt autoremove -y

apt install clang-18 clangd-18 clang-format-18 clang-tidy-18 lldb-18 libc++-18-dev libc++abi-18-dev lld-18 make bsdmainutils qemu-system-arm qemu-system-misc qemu-system-x86 gdb cgdb binutils-i686-linux-gnu gcc-i686-linux-gnu fonts-firacode pigz binutils-riscv64-linux-gnu -y
apt install bzip2 libssl-dev libncurses-dev libelf-dev flex bison bc dwarves lz4 cpio unzip xz-utils -y

echo 'LANG="zh_CN.UTF-8"' > /etc/default/locale
source /etc/default/locale

update-alternatives --install /usr/bin/python python /usr/bin/python3 100
update-alternatives --install /usr/bin/cc cc /usr/bin/clang-18 100
update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-18 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-18 100
update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-18 100

wget -P $TEMP_PATH https://dl.google.com/android/repository/android-ndk-r27c-linux.zip
wget -P $TEMP_PATH https://dl.google.com/android/repository/platform-tools-latest-windows.zip

BOCHS_VERSION=2.8
BOCHS_PATH=/mnt/d/Learning_Kernel/bochs-$BOCHS_VERSION
if [ -e "$BOCHS_PATH" ]; then
    apt install libltdl7 libsdl2-2.0-0 libgtk2.0-0t64 -y
    cp $BOCHS_PATH/bochs-$BOCHS_VERSION-bin.tar.gz ~
    cd ~
    tar zxvf bochs-$BOCHS_VERSION-bin.tar.gz
    cd bochs-$BOCHS_VERSION-bin
    make install
    cd ..
    rm -rf bochs-$BOCHS_VERSION-bin
fi

su miku