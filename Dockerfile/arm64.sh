#!/bin/bash

# echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config
# echo "" >> /etc/ssh/sshd_config
# echo "miku    ALL=(ALL:ALL) ALL" >> /etc/sudoers
# echo "" >> /etc/sudoers
# useradd -m miku
# usermod -s /bin/bash miku
# passwd miku
# arp -a

sudo apt update
sudo apt upgrade -y
sudo apt install gcc gdb cgdb make clinfo valgrind clang-format-13 clangd-13 fonts-firacode -y

update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-18 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-18 100

su miku
git config --global pull.rebase false
git config --global user.name kaspersigi
git config --global user.email kaspersigi@outlook.com
ssh-keyscan github.com > $HOME/.ssh/known_hosts

echo '' > $HOME/.ssh/authorized_keys
mkdir -p $HOME/linux
cd $HOME/linux
# git clone git@github.com:kaspersigi/learn.git