#!/usr/bin/bash
# ubuntu 22.04.5

LLVM_VERSION="21"
LLVM="-$LLVM_VERSION"
USER=$(cmd.exe /c echo %USERNAME% | tr -d '\r')
TOP_PATH="/mnt/d/Learning_Camera/learn"
USER_PATH="/mnt/c/Users/$USER"
TEMP_PATH="/mnt/c/Users/Public/Downloads"
ADB_PATH="$USER_PATH/Downloads/platform-tools"
KEY_PATH="$TOP_PATH/key"
PLATFORM="darwin"
ARCH=$(uname -m)
if [ "$ARCH" = "x86_64" ]; then
    PLATFORM="linux"
elif [ "$ARCH" = "aarch64" ]; then
    PLATFORM="windows"
fi

if [ -e "$KEY_PATH" ]; then
    echo "key found"
    mkdir ~/.ssh
    cp $KEY_PATH/id_ed25519 ~/.ssh
    chmod 600 ~/.ssh/id_ed25519
else
    echo "key not found"
fi

git config --global pull.rebase false
git config --global user.name kaspersigi
git config --global user.email kaspersigi@outlook.com

# ssh
ssh-keyscan github.com > ~/.ssh/known_hosts

# https
cp config ~/.ssh
chmod 644 ~/.ssh/config
ssh-keyscan -p 443 ssh.github.com >> ~/.ssh/known_hosts
ssh -T -p 443 git@github.com

cp .wslconfig $USER_PATH
cp .vimrc ~
mkdir -p ~/linux/virt
unzip $TEMP_PATH/android-ndk-r27d-$PLATFORM.zip -d ~/linux
chmod -R a+x ~/linux/android-ndk-r27d
rm -rf $TEMP_PATH/android-ndk-r27d-$PLATFORM.zip

echo "# Android Debug Bridge" >> ~/.bashrc
echo "export PATH=$PATH:$ADB_PATH" >> ~/.bashrc
# echo "export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:$ADB_PATH" >> ~/.bashrc
echo "alias adb='adb.exe'" >> ~/.bashrc
source ~/.bashrc
$ADB_PATH/adb.exe kill-server
rm -rf $ADB_PATH
unzip $TEMP_PATH/platform-tools-latest-windows.zip -d $USER_PATH/Downloads
rm -rf $TEMP_PATH/platform-tools-latest-windows.zip

cd ~/linux
git clone git@github.com:kaspersigi/learn.git
# git clone https://github.com/kaspersigi/learn.git
git clone git@github.com:kaspersigi/perf_tools.git
# git clone https://github.com/kaspersigi/perf_tools.git
git clone git@github.com:kaspersigi/CAMERA.LA.5.0.r1-07900-pakala.0-1.git
# git clone https://github.com/kaspersigi/CAMERA.LA.5.0.r1-07900-pakala.0-1.git
git clone git@github.com:kaspersigi/Camera.git
# git clone https://github.com/kaspersigi/Camera.git
git clone git@github.com:kaspersigi/Camera2.git
# git clone https://github.com/kaspersigi/Camera2.git
git clone git@github.com:kaspersigi/OnlySnapshot.git
# git clone https://github.com/kaspersigi/OnlySnapshot.git
git clone git@github.com:kaspersigi/MyCamera.git
# git clone https://github.com/kaspersigi/MyCamera.git
git clone git@github.com:kaspersigi/NoUI.git
# git clone https://github.com/kaspersigi/NoUI.git
git clone git@github.com:kaspersigi/libcamera.git
# git clone https://github.com/kaspersigi/libcamera.git
# git clone --single-branch -b oppo/sm8750_v_15.0.1_find_x8_ultra --depth 1 git@github.com:oppo-source/android_kernel_oppo_sm8750.git
# git clone --single-branch -b oppo/sm8750_v_15.0.1_find_x8_ultra --depth 1 https://github.com/oppo-source/android_kernel_oppo_sm8750.git
# git clone --single-branch -b nanopi6-v6.1.y --depth 1 git@github.com:friendlyarm/kernel-rockchip.git
# git clone --single-branch -b nanopi6-v6.1.y --depth 1 https://github.com/friendlyarm/kernel-rockchip.git
# git clone --single-branch -b linux-rolling-stable --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
git clone --single-branch -b linux-rolling-stable --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
# git clone --single-branch -b v1.7.0 --depth 1 git@github.com:raspberrypi/rpicam-apps.git
# git clone --single-branch -b v1.7.0 --depth 1 https://github.com/raspberrypi/rpicam-apps.git
# git clone --single-branch -b v0.5.0+rpt20250429 --depth 1 git@github.com:raspberrypi/libcamera.git
# git clone --single-branch -b v0.5.0+rpt20250429 --depth 1 https://github.com/raspberrypi/libcamera.git
# git clone --single-branch -b v0.5.1 --depth 1 https://git.libcamera.org/libcamera/libcamera.git

cd ~/linux/linux
time make distclean ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
wget https://gitlab.com/buildroot.org/buildroot/-/raw/master/board/qemu/aarch64-virt/linux.config
mv linux.config .config
time make olddefconfig ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
time make -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
time make modules -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=$LLVM
./scripts/clang-tools/gen_compile_commands.py