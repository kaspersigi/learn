#!/usr/bin/bash
# ubuntu 22.04.5

LLVM_VERSION="21"
LLVM="-$LLVM_VERSION"
TOP_PATH="/mnt/d/Learning_Camera/learn"
DEVELOP_PATH="/mnt/develop"

if [ -e "$TOP_PATH" ]; then
    echo "$TOP_PATH exists"
    rm -rf $DEVELOP_PATH/linux/virt
    cp -R $TOP_PATH/virt $DEVELOP_PATH/linux/
else
    echo "$TOP_PATH not found"
fi

cd $DEVELOP_PATH/linux/linux
time make distclean ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
git pull
wget https://gitlab.com/buildroot.org/buildroot/-/raw/master/board/qemu/aarch64-virt/linux.config
mv linux.config .config
time make olddefconfig ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
time make -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
time make modules -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
./scripts/clang-tools/gen_compile_commands.py
cp arch/arm64/boot/Image ../virt/

cd $DEVELOP_PATH/linux/virt
sudo mount -o loop rootfs.ext4 ./_fs
sudo rm -rf _fs/lib/modules
cd ../linux
sudo make modules_install INSTALL_MOD_PATH=../virt/_fs -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
cd ../virt
sudo umount ./_fs
cd ..

if [ -e "$TOP_PATH" ]; then
    echo "$TOP_PATH exists"
    rm -rf $TOP_PATH/virt
    cp -R virt $TOP_PATH/
else
    echo "$TOP_PATH not found"
fi