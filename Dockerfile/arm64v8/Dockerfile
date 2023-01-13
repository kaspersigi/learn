# FROM i386/debian:latest
# FROM amd64/debian:latest
# FROM arm32v7/debian:latest
FROM arm64v8/debian:latest
LABEL org.opencontainers.image.authors="kaspersigi"
MAINTAINER kaspersigi "kaspersigi@gmail.com"
WORKDIR /root
EXPOSE 22
USER root
RUN mkdir -p /var/run/sshd \
    # perl -e 'print crypt($ARGV[0], "password")' $(passwd)
    && useradd -m -p paKe96Li2oGUE miku \
    && usermod -s /bin/bash miku \
    && sed -i 's/deb.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
    && sed -i 's/security.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
    && apt update \
    && apt upgrade -y
RUN rm -rf /etc/localtime && cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && echo 'Asia/Shanghai' > /etc/timezone \
    && mkdir /home/miku/.ssh
COPY id_rsa /home/miku/.ssh
COPY id_rsa.pub /home/miku/.ssh
RUN chown miku:miku -R /home/miku/.ssh \
    && chmod 600 /home/miku/.ssh/id_rsa \
    && chmod 644 /home/miku/.ssh/id_rsa.pub
RUN apt install sudo -y \
    && apt install clang-11 -y \
    && apt install clang-format-11 -y \
    && apt install lldb-11 -y \
    && apt install libc++-11-dev -y \
    && apt install libc++abi-11-dev -y \
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
    && apt install binutils-x86_64-linux-gnu -y
RUN ln -s /usr/bin/clang-11 /usr/bin/clang \
    && ln -s /usr/bin/clang-11 /usr/bin/cc \
    && ln -s /usr/bin/clang++-11 /usr/bin/clang++ \
    && ln -s /usr/bin/clang-format-11 /usr/bin/clang-format \
    && ln -s /usr/bin/lldb-11 /usr/bin/lldb \
    && ln -s /usr/bin/llvm-config-11 /usr/bin/llvm-config \
    && ln -s /usr/bin/llvm-ar-11 /usr/bin/llvm-ar \
    && echo 'miku    ALL=(ALL:ALL) ALL' >> /etc/sudoers \
    && echo '/usr/sbin/sshd -D &' > /root/run.sh \
    && chmod 110 /root/run.sh
USER miku
RUN git config --global pull.rebase false \
    && git config --global user.name kaspersigi \
    && git config --global user.email kaspersigi@gmail.com \
    # && ssh-keyscan 106.52.13.193 > $HOME/.ssh/known_hosts \
    # && ssh -T git@github.com
    && ssh-keyscan github.com > $HOME/.ssh/known_hosts \
    && echo '' > $HOME/.ssh/authorized_keys \
    # && ssh-keygen -f $HOME/.ssh/id_rsa -t rsa -N '' \
    && mkdir $HOME/linux \
    && cd $HOME \
    # && git clone git@106.52.13.193:/home/git/learn.git
    && git clone git@github.com:kaspersigi/learn.git
USER root
WORKDIR /root
ENTRYPOINT /root/run.sh && su miku
# CMD /usr/sbin/sshd -D &
# sudo apt install apparmor-utils
# docker build -t kaspersigi/debian .
# docker buildx build --platform=linux/i386 -t kaspersigi/clang:arm64v8 .
# docker run -it --privileged -p 2222:22 -v /Users/miku/Downloads/arm64:/home/miku/linux --name=arm64 --hostname Arm64-Miku kaspersigi/clang:arm64v8
# docker run -it --privileged -p 2222:22 -v /d/arm64:/home/miku/linux --name=arm64 --hostname Arm64-Miku kaspersigi/clang:arm64v8