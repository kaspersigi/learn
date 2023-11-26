#!/usr/bin/bash
# ubuntu 22.04
# 因为ubuntu 20.04 qemu为4.2.1 落后
# ubuntu 22.04.2 qemu为6.2.0

# sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
# sed -i 's/security.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list

apt update
apt upgrade -y

apt install clang-15 -y
apt install clang-format-15 -y
apt install lldb-15 -y
apt install libc++-15-dev -y
apt install libc++abi-15-dev -y
apt install clangd-15 -y
apt install lld-15 -y
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

# apt install clang-15 clang-format-15 lldb-15 libc++-15-dev libc++abi-15-dev make bsdmainutils qemu-system gdb cgdb valgrind libltdl7 libsdl2-2.0-0 libgtk2.0-0 binutils-i686-linux-gnu gcc-i686-linux-gnu fonts-firacode -y
apt install gcc make bzip2 libssl-dev libncurses-dev libelf-dev flex bison bc dwarves -y

update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 100
update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 100
update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-15 100
update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-15 100
update-alternatives --install /usr/bin/lld lld /usr/bin/lld-15 100

update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 100
update-alternatives --install /usr/bin/ld.lld ld.lld /usr/bin/ld.lld-15 100
update-alternatives --install /usr/bin/llvm-ar llvm-ar /usr/bin/llvm-ar-15 100
update-alternatives --install /usr/bin/llvm-nm llvm-nm /usr/bin/llvm-nm-15 100
update-alternatives --install /usr/bin/llvm-objcopy llvm-objcopy /usr/bin/llvm-objcopy-15 100
update-alternatives --install /usr/bin/llvm-objdump llvm-objdump /usr/bin/llvm-objdump-15 100
update-alternatives --install /usr/bin/llvm-readelf llvm-readelf /usr/bin/llvm-readelf-15 100
update-alternatives --install /usr/bin/llvm-strip llvm-strip /usr/bin/llvm-strip-15 100

update-alternatives --install /usr/bin/cc cc /usr/bin/clang-15 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-15 100

su miku