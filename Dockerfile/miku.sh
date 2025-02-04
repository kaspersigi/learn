#!/usr/bin/bash

USRER_PATH="/mnt/c/Users/kaspe"
TEMP_PATH="/mnt/c/Users/Public/Downloads"
ADB_PATH="$USRER_PATH/Downloads/platform-tools"
KEY_PATH="/mnt/d/key"

if [ -e "$KEY_PATH" ]; then
    echo "key found"
    mkdir ~/.ssh
    cp $KEY_PATH/id_rsa ~/.ssh
    cp $KEY_PATH/id_rsa.pub ~/.ssh
    chmod 600 ~/.ssh/id_rsa
    chmod 644 ~/.ssh/id_rsa.pub
else
    echo "key not found"
fi

git config --global pull.rebase false
git config --global user.name kaspersigi
git config --global user.email kaspersigi@outlook.com

cp config ~/.ssh
chmod 644 ~/.ssh/config
ssh-keyscan -p 443 ssh.github.com >> ~/.ssh/known_hosts
ssh -T -p 443 git@github.com

cp .wslconfig $USRER_PATH
cp .vimrc ~
mkdir -p ~/linux/virt
unzip $TEMP_PATH/android-ndk-r27c-linux.zip -d ~/linux
rm -rf $TEMP_PATH/android-ndk-r27c-linux.zip

echo "# Android Debug Bridge" >> ~/.bashrc
echo "export PATH=$PATH:$ADB_PATH" >> ~/.bashrc
# echo "export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:$ADB_PATH" >> ~/.bashrc
echo "alias adb='adb.exe'" >> ~/.bashrc
source ~/.bashrc
$ADB_PATH/adb.exe kill-server
rm -rf $ADB_PATH
unzip $TEMP_PATH/platform-tools-latest-windows.zip -d $USRER_PATH/Downloads
rm -rf $TEMP_PATH/platform-tools-latest-windows.zip

cd ~/linux
# git clone git@github.com:kaspersigi/learn.git
git clone https://github.com/kaspersigi/learn.git
git clone --single-branch -b linux-rolling-stable --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git

cd ~/linux/linux
time make distclean ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
cp $TOOL_PATH/linux.config .config
wget https://gitlab.com/buildroot.org/buildroot/-/raw/master/board/qemu/aarch64-virt/linux.config
mv linux.config .config
time make olddefconfig ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
time make -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
time make modules -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
./scripts/clang-tools/gen_compile_commands.py