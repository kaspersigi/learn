#!/usr/bin/bash
# ubuntu 24.04

apt update
apt upgrade -y

apt install clang-17 -y
apt install clangd-17 -y
apt install clang-format-17 -y
apt install clang-tidy-17 -y
apt install lldb-17 -y
apt install libc++-17-dev -y
apt install libc++abi-17-dev -y
apt install lld-17 -y
apt install make -y
apt install bsdmainutils -y
apt install qemu-system -y
apt install gdb -y
apt install cgdb -y
apt install valgrind -y
apt install libltdl7 -y
apt install libsdl2-2.0-0 -y
apt install libgtk2.0-0 -y
apt install binutils-i686-linux-gnu -y
apt install gcc-i686-linux-gnu -y
apt install fonts-firacode -y
apt install pigz -y

# apt install clang-17 clangd-17 clang-format-17 clang-tidy-17 lldb-17 libc++-17-dev libc++abi-17-dev lld-17 make bsdmainutils qemu-system gdb cgdb valgrind libltdl7 libsdl2-2.0-0 libgtk2.0-0 binutils-i686-linux-gnu gcc-i686-linux-gnu fonts-firacode pigz -y
apt install bzip2 libssl-dev libncurses-dev libelf-dev flex bison bc dwarves lz4 -y

echo 'LANG="zh_CN.UTF-8"' > /etc/default/locale
source /etc/default/locale

update-alternatives --install /usr/bin/python python /usr/bin/python3 100
update-alternatives --install /usr/bin/cc cc /usr/bin/clang-17 100
update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-17 100
update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-17 100

su miku