#!/usr/bin/bash

apt update
apt upgrade -y

apt install clang-16 -y
apt install clangd-16 -y
apt install clang-format-16 -y
apt install lldb-16 -y
apt install libc++-16-dev -y
apt install libc++abi-16-dev -y
apt install clangd-16 -y
apt install lld-16 -y
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

# apt install clang-16 clangd-16 clang-format-16 lldb-16 libc++-16-dev libc++abi-16-dev make bsdmainutils qemu-system gdb cgdb valgrind libltdl7 libsdl2-2.0-0 libgtk2.0-0 binutils-i686-linux-gnu gcc-i686-linux-gnu fonts-firacode -y
apt install gcc make bzip2 libssl-dev libncurses-dev libelf-dev flex bison bc dwarves -y

update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-16 100
update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-16 100
update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-16 100
update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-16 100
update-alternatives --install /usr/bin/lld lld /usr/bin/lld-16 100

update-alternatives --install /usr/bin/clang clang /usr/bin/clang-16 100
update-alternatives --install /usr/bin/ld.lld ld.lld /usr/bin/ld.lld-16 100
update-alternatives --install /usr/bin/llvm-ar llvm-ar /usr/bin/llvm-ar-16 100
update-alternatives --install /usr/bin/llvm-nm llvm-nm /usr/bin/llvm-nm-16 100
update-alternatives --install /usr/bin/llvm-objcopy llvm-objcopy /usr/bin/llvm-objcopy-16 100
update-alternatives --install /usr/bin/llvm-objdump llvm-objdump /usr/bin/llvm-objdump-16 100
update-alternatives --install /usr/bin/llvm-readelf llvm-readelf /usr/bin/llvm-readelf-16 100
update-alternatives --install /usr/bin/llvm-strip llvm-strip /usr/bin/llvm-strip-16 100

update-alternatives --install /usr/bin/cc cc /usr/bin/clang-16 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-16 100

su miku