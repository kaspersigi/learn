#!/usr/bin/bash

TOP_PATH=/mnt/d/Learning_Kernel
TOOL_PATH=$TOP_PATH/tools

rm -rf ~/linux/virt
cp -R $TOP_PATH/virt ~/linux/

cd ~/linux/linux
time make distclean ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
git pull
cp $TOOL_PATH/linux.config .config
time make olddefconfig ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
time make -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
time make modules -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
./scripts/clang-tools/gen_compile_commands.py
cp arch/arm64/boot/Image ../virt/

cd ~/linux/virt
sudo mount -o loop rootfs.ext4 ./_fs
sudo rm -rf _fs/lib/modules
cd ../linux
sudo make modules_install INSTALL_MOD_PATH=../virt/_fs -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
cd ../virt
sudo umount ./_fs
cd ..
rm -rf $TOP_PATH/virt
cp -R virt $TOP_PATH/