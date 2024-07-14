# FROM amd64/ubuntu:latest
FROM arm64v8/ubuntu:latest
LABEL org.opencontainers.image.authors="kaspersigizz"
MAINTAINER kaspersigizz "kaspersigi@outlook.com"
WORKDIR /root
EXPOSE 22
USER root
RUN mkdir -p /var/run/sshd \
    # perl -e 'print crypt($ARGV[0], "password")' $(passwd)
    && useradd -m -p paKe96Li2oGUE miku \
    && usermod -s /bin/bash miku \
    && sed -i 's@//.*archive.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources \
    && sed -i 's@//.*security.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources \
    && sed -i 's@//.*ports.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources \
    && apt update \
    && apt upgrade -y
RUN mkdir /home/miku/.ssh
COPY id_rsa /home/miku/.ssh
COPY id_rsa.pub /home/miku/.ssh
RUN chown miku:miku -R /home/miku/.ssh \
    && chmod 600 /home/miku/.ssh/id_rsa \
    && chmod 644 /home/miku/.ssh/id_rsa.pub
RUN apt install sudo -y \
    && apt install clang-18 -y \
    && apt install clang-format-18 -y \
    && apt install clang-tidy-18 -y \
    && apt install lldb-18 -y \
    && apt install libc++-18-dev -y \
    && apt install libc++abi-18-dev -y \
    && apt install clangd-18 -y \
    && apt install lld-18 -y \
    && apt install gdb -y \
    && apt install cgdb -y \
    && apt install qemu-system -y \
    && apt install make -y \
    && apt install git -y \
    && apt install file -y \
    && apt install wget -y \
    && apt install curl -y \
    && apt install vim -y \
    && apt install openssh-server -y \
    && apt install bsdmainutils -y \
    && apt install valgrind -y \
    && apt install binutils-i686-linux-gnu -y \
    && apt install binutils-x86-64-linux-gnu -y \
    && apt install gcc-i686-linux-gnu -y \
    && apt install fonts-firacode -y \
    && apt install pigz -y \
    && apt install binutils-riscv64-linux-gnu -y \
    && apt install bzip2 libssl-dev libncurses-dev libelf-dev flex bison bc dwarves lz4 cpio unzip xz-utils -y
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 100 \
    && update-alternatives --install /usr/bin/cc cc /usr/bin/clang-18 100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-18 100 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-18 100 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-18 100 \
    && echo 'miku    ALL=(ALL:ALL) ALL' >> /etc/sudoers \
    && echo '/usr/sbin/sshd -D &' > /root/run.sh \
    && chmod 110 /root/run.sh
USER miku
RUN git config --global pull.rebase false \
    && git config --global user.name kaspersigi \
    && git config --global user.email kaspersigi@outlook.com \
    && ssh-keyscan github.com > $HOME/.ssh/known_hosts \
    && echo '' > $HOME/.ssh/authorized_keys \
    && mkdir $HOME/share \
    && mkdir -p $HOME/linux/virt \
    && cd $HOME/linux \
    && git clone git@github.com:kaspersigi/learn.git \
    && echo 'code-server &> /dev/null &' > $HOME/miku.sh \
    && chmod 110 $HOME/miku.sh
USER root
WORKDIR /root
ENTRYPOINT /root/run.sh && su miku && /home/miku/miku.sh
# CMD /usr/sbin/sshd -D &
# sudo apt install apparmor-utils
# docker build -t kaspersigizz/clang:arm64v8 .
# docker buildx build --platform=linux/arm64v8 -t kaspersigizz/clang:arm64v8 .
# docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /Users/miku/share:/home/miku/share --name=arm64 --hostname Arm64-Miku kaspersigizz/clang:arm64v8
# docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /d/share:/home/miku/share --name=arm64 --hostname Arm64-Miku kaspersigizz/clang:arm64v8
# docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /root/share:/home/miku/share --name=arm64 --hostname Arm64-Miku kaspersigizz/clang:arm64v8