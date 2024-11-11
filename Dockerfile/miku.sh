#!/usr/bin/bash

mkdir ~/.ssh
cp amd64/id_rsa ~/.ssh
cp amd64/id_rsa.pub ~/.ssh
chmod 600 ~/.ssh/id_rsa
chmod 644 ~/.ssh/id_rsa.pub

git config --global pull.rebase false
git config --global user.name kaspersigi
git config --global user.email kaspersigi@outlook.com

ssh-keyscan github.com > $HOME/.ssh/known_hosts

cp .wslconfig /mnt/c/Users/kaspe/
cp .vimrc ~
unzip /mnt/d/Learning_Kernel/tspi/platform-tools-latest-windows.zip -d /mnt/c/Users/kaspe/Downloads/
echo "# Android Debug Bridge" >> ~/.bashrc
# echo "export PATH=$PATH:/mnt/c/Users/kaspe/Downloads/platform-tools" >> ~/.bashrc
echo "export PATH=/home/miku/.cargo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Users/kaspe/Downloads/platform-tools" >> ~/.bashrc
echo "alias adb='adb.exe'" >> ~/.bashrc
source ~/.bashrc

# mkdir -p $HOME/linux/virt
mkdir -p $HOME/linux
cd ~/linux
git clone git@github.com:kaspersigi/learn.git
git clone --single-branch -b linux-rolling-lts --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git

cd ~
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# ssh -T -p 443 git@github.com
# cp amd64/config ~/.ssh
# chmod 644 ~/.ssh/config