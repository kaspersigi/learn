#!/usr/bin/bash

mkdir ~/.ssh
cp amd64/id_rsa ~/.ssh
cp amd64/id_rsa.pub ~/.ssh
chmod 600 ~/.ssh/id_rsa
chmod 644 ~/.ssh/id_rsa.pub

git config --global pull.rebase false
git config --global user.name kaspersigi
git config --global user.email kaspersigi@gmail.com

ssh-keyscan github.com > $HOME/.ssh/known_hosts

mkdir ~/linux
cp fs.tar.gz ~/linux
cd ~/linux
git clone git@github.com:kaspersigi/learn.git
cd learn

# ssh -T -p 443 git@github.com
# cp amd64/config ~/.ssh
# chmod 644 ~/.ssh/config