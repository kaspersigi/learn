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
# apt install gcc-i686-linux-gnu -y
apt install fonts-firacode -y
apt install pigz -y

# apt install clang-17 clangd-17 clang-format-17 clang-tidy-17 lldb-17 libc++-17-dev libc++abi-17-dev lld-17 make bsdmainutils qemu-system gdb cgdb valgrind libltdl7 libsdl2-2.0-0 libgtk2.0-0 binutils-i686-linux-gnu fonts-firacode pigz -y
apt install bzip2 libssl-dev libncurses-dev libelf-dev flex bison bc dwarves lz4 -y

update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-17 100
update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 100
update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-17 100
update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-17 100
update-alternatives --install /usr/bin/lld lld /usr/bin/lld-17 100

update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 100
update-alternatives --install /usr/bin/ld.lld ld.lld /usr/bin/ld.lld-17 100
update-alternatives --install /usr/bin/llvm-ar llvm-ar /usr/bin/llvm-ar-17 100
update-alternatives --install /usr/bin/llvm-nm llvm-nm /usr/bin/llvm-nm-17 100
update-alternatives --install /usr/bin/llvm-objcopy llvm-objcopy /usr/bin/llvm-objcopy-17 100
update-alternatives --install /usr/bin/llvm-objdump llvm-objdump /usr/bin/llvm-objdump-17 100
update-alternatives --install /usr/bin/llvm-readelf llvm-readelf /usr/bin/llvm-readelf-17 100
update-alternatives --install /usr/bin/llvm-strip llvm-strip /usr/bin/llvm-strip-17 100

update-alternatives --install /usr/bin/cc cc /usr/bin/clang-17 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-17 100
update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-17 100

su miku