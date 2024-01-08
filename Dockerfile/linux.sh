#!/usr/bin/bash

apt install openssh-server -y
systemctl status ssh
systemctl enable ssh
apt install qemu-system git vim net-tools fonts-firacode -y
apt install gcc make libssl-dev libncurses-dev libelf-dev flex bison bc dwarves libyaml-dev pkg-config autoconf -y

# arm
apt install gcc-arm-linux-gnueabi -y
apt install u-boot-tools -y
apt install tftp-hpa tftpd-hpa xinetd uml-utilities bridge-utils -y
apt install nfs-kernel-server -y

su miku
cd ~/linux
mkdir Learning_ARM

git clone --depth 1 git@github.com:oracle/opengrok.git

git clone --depth 1 git@github.com:universal-ctags/ctags.git
cd ctags
./autogen.sh
./configure
make -j16
sudo make install

wget https://dlcdn.apache.org/tomcat/tomcat-10/v10.1.17/bin/apache-tomcat-10.1.17.tar.gz

# git clone --single-branch -b linux-6.6.y --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
git clone --single-branch -b linux-6.6.y --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
# git clone --single-branch -b 1_36_stable --depth 1 git://git.busybox.net/busybox
git clone --single-branch -b 1_36_stable --depth 1 https://git.busybox.net/busybox
git clone --single-branch -b u-boot-2023.07.y --depth 1 git@github.com:u-boot/u-boot.git
# git clone --single-branch -b u-boot-2023.07.y --depth 1 https://source.denx.de/u-boot/u-boot.git

cd linux
make vexpress_defconfig ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make menuconfig ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
# File System —> Network File Systems —> NFS client support for NFS version 4
# open all nfs client switch
make -j16 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make modules -j16 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make dtbs -j16 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make LOADADDR=0x60003000 uImage -j16 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make modules_install INSTALL_MOD_PATH=../_fs -j16 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
cd ..

cd busybox
make menuconfig ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make -j16 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make install ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- CONFIG_PREFIX=../_fs
cp -R -d /usr/arm-linux-gnueabi/lib ../_fs
cd ..

cd u-boot
make vexpress_ca9x4_defconfig ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make menuconfig ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
# Networking Support —> set a default gateway...
# Boot options —> Enable a default value for bootcmd
make -j16 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
cd ..

# tftp 0x60003000 linux/arch/arm/boot/uImage; tftp 0x60800000 linux/arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb; setenv bootargs 'root=/dev/nfs rw nfsroot=192.168.204.133:/home/miku/linux/filesystem,proto=tcp,nfsvers=3,nolock init=/linuxrc ip=192.168.204.200 console=ttyAMA0';bootm 0x60003000 - 0x60800000;