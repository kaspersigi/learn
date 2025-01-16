#!/usr/bin/bash

# git clone --single-branch -b linux-2.6.32.y --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
git clone --single-branch -b linux-2.6.32.y --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
# git clone --single-branch -b linux-rolling-lts --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
git clone --single-branch -b linux-rolling-lts --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
# git clone --single-branch -b linux-rolling-stable --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
git clone --single-branch -b linux-rolling-stable --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
# git clone --single-branch -b 1_37_stable --depth 1 git://git.busybox.net/busybox
git clone --single-branch -b 1_37_stable --depth 1 https://git.busybox.net/busybox
# git clone --single-branch -b 2024.08.x --depth 1 git@gitlab.com:buildroot.org/buildroot.git
git clone --single-branch -b 2024.08.x --depth 1 https://gitlab.com/buildroot.org/buildroot.git

# buildroot qemu_aarch64_virt_defconfig
sudo apt install gcc g++ cpio unzip -y
make qemu_aarch64_virt_defconfig
make menuconfig
make -j$(nproc)

# git clone --single-branch -b linux-rolling-stable --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
git clone --single-branch -b linux-rolling-stable --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
cd linux
cp /mnt/d/Learning_Kernel/virt/linux.config .config
make menuconfig ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
make -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
make modules -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
./scripts/clang-tools/gen_compile_commands.py
cp arch/arm64/boot/Image ../virt/
make modules_install INSTALL_MOD_PATH=../virt/_fs -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18

sudo apt install git make openjdk-8-jdk git-core gnupg flex bison gperf build-essential zip curl zlib1g-dev libgl1-mesa-dev gcc-multilib g++-multilib libc6-dev-i386 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z1-dev libxml2-utils xsltproc unzip bc imagemagick ccache schedtool libssl-dev libncursesw5-dev libncurses5 libncursesw5 libncurses5-dev libncurses-dev libncurses-gst libncurses5-dev device-tree-compiler lz4 python3 python-is-python3 -y

# vim ./kernel/arch/arm64/configs/tspi_defconfig
# vim ./kernel/configs/rockchip/rk356x_evb.config
# vim ./kernel/configs/rockchip/android-11.config

# cd kernel
# echo '' >> ./arch/arm64/configs/tspi_defconfig
# echo CONFIG_DYNAMIC_FTRACE=y >> ./arch/arm64/configs/tspi_defconfig
# echo CONFIG_FUNCTION_TRACER=y >> ./arch/arm64/configs/tspi_defconfig
# echo CONFIG_IRQSOFF_TRACER=y >> ./arch/arm64/configs/tspi_defconfig
# echo CONFIG_FUNCTION_PROFILER=y >> ./arch/arm64/configs/tspi_defconfig
# echo CONFIG_PREEMPT_TRACER=y >> ./arch/arm64/configs/tspi_defconfig

cd u-boot && ./make.sh rk3566 && cd ../kernel && make clean && make distclean && make ARCH=arm64 tspi_defconfig rk356x_evb.config android-11.config && make ARCH=arm64 tspi-rk3566-user-v10.img -j$(nproc) && cd .. && source build/envsetup.sh && lunch rk3566_tspi-userdebug && make installclean -j$(nproc) && make -j$(nproc) && ./mkimage.sh

sudo apt install git ssh make gcc libssl-dev liblz4-tool expect g++ patchelf chrpath gawk texinfo chrpath diffstat binfmt-support qemu-user-static live-build bison flex fakeroot cmake gcc-multilib g++-multilib unzip device-tree-compiler ncurses-dev fdisk -y

./build.sh lunch
3
export RK_ROOTFS_SYSTEM=buildroot
./build.sh all
export RK_ROOTFS_SYSTEM=debian
sudo dpkg -i debian/ubuntu-build-service/packages/*
sudo apt install -f
./build.sh debian
./mkfirmware.sh

sudo apt install gcc-aarch64-linux-gnu gcc lz4 -y
sudo ln -s /usr/bin/python3 /usr/bin/python
cp /mnt/d/Learning_Kernel/tspi/kernel.tar.gz .
tar zxvf kernel.tar.gz
cd kernel
cp arch/arm64/configs/rockchip_linux_defconfig .config
make menuconfig ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
make tspi-rk3566-user-v10-linux.img -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
cp boot.img /mnt/d/Learning_Kernel/tspi/

# git clone --single-branch -b nanopi6-v6.1.y --depth 1 https://github.com:friendlyarm/kernel-rockchip.git
git clone --single-branch -b nanopi6-v6.1.y --depth 1 git@github.com:friendlyarm/kernel-rockchip.git
mv kernel-rockchip linux
cd linux
cp /mnt/d/Learning_Kernel/tspi/dts/* arch/arm64/boot/dts/rockchip/
cp arch/arm64/configs/rockchip_linux_defconfig .config
echo "CONFIG_USB_CONFIGFS_ECM=y" >> .config
echo "CONFIG_USB_CONFIGFS_ECM_SUBSET=y" >> .config
echo "CONFIG_USB_CONFIGFS_RNDIS=y" >> .config
echo "CONFIG_USB_CONFIGFS_EEM=y" >> .config
echo "CONFIG_USB_ETH=y" >> .config
make menuconfig ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
make rk3566-tspi-v10-miku.img -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- LLVM=-18
cp boot.img /mnt/d/Learning_Kernel/tspi/

# rndis
echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config
echo "" >> /etc/ssh/sshd_config
echo "miku    ALL=(ALL:ALL) ALL" >> /etc/sudoers
echo "" >> /etc/sudoers
useradd -m miku
usermod -s /bin/bash miku
passwd miku
# arp -a

ip addr
sudo dhclient usb0

# DVD
# https://cdimage.debian.org/cdimage/archive/10.13.0/arm64/iso-dvd/
adb push debian-10.13.0-arm64-DVD-1.iso userdata
adb push SHA512SUMS.sign userdata
adb shell
cd /userdata
date 122012402024.59
hwclock --systohc
gpg --verify SHA512SUMS.sign debian-10.13.0-arm64-DVD-1.iso
mkdir dvd
mount -o loop debian-10.13.0-arm64-DVD-1.iso dvd
echo "deb file:///userdata/dvd/ buster main contrib" > /etc/apt/sources.list
apt update --allow-insecure-repositories

# /etc/apt/sources.list
# deb http://mirrors.ustc.edu.cn/debian buster main contrib non-free
# deb-src http://mirrors.ustc.edu.cn/debian buster main contrib non-free
# deb http://mirrors.ustc.edu.cn/debian-security buster/updates main contrib non-free
# deb-src http://mirrors.ustc.edu.cn/debian-security buster/updates main contrib non-free
# deb http://mirrors.ustc.edu.cn/debian buster-updates main contrib non-free
# deb-src http://mirrors.ustc.edu.cn/debian buster-updates main contrib non-free

umount dvd

# code-server
code-server
vim .config/code-server/config.yaml
```
bind-addr: 0.0.0.0:8888
auth: password
password: $(password)
cert: false
```
code-server &> /dev/null &

# frp
# server
# 开放端口 2222,6000,7000,8888
./frps -c ./frps.toml &> /dev/null &
vim frps.toml
```
# frps.toml
bindPort = 7000
```

# client
./frpc -c ./frpc.toml &> /dev/null &
```
# frpc.toml
serverAddr = "106.52.13.193"
serverPort = 7000

[[proxies]]
name = "ssh"
type = "tcp"
localIP = "127.0.0.1"
localPort = 22
remotePort = 2222

[[proxies]]
name = "http"
type = "tcp"
localIP = "127.0.0.1"
localPort = 8888
remotePort = 8888
```

# arm64 kernel LTO feature
General architecture-dependent options --->
    Link Time Optimization (LTO) (Clang ThinLTO (EXPERIMENTAL)) --->
        Clang ThinLTO (EXPERIMENTAL)(X)

sudo apt install libstb-dev libsfml-dev libglew-dev libglm-dev libtclap-dev ruby doxygen -y
git clone https://github.com/KhronosGroup/OpenCL-SDK.git --recursive
cmake -D CMAKE_INSTALL_PREFIX=./OpenCL-SDK/install -B ./OpenCL-SDK/build -S ./OpenCL-SDK
cmake --build OpenCL-SDK/build --config Release --target install