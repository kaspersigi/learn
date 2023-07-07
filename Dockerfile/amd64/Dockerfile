# FROM i386/debian:latest
FROM amd64/debian:latest
# FROM arm32v7/debian:latest
# FROM arm64v8/debian:latest
LABEL org.opencontainers.image.authors="kaspersigi"
MAINTAINER kaspersigi "kaspersigi@gmail.com"
WORKDIR /root
EXPOSE 22
USER root
RUN mkdir -p /var/run/sshd \
    # perl -e 'print crypt($ARGV[0], "password")' $(passwd)
    && useradd -m -p paKe96Li2oGUE miku \
    && usermod -s /bin/bash miku \
    # && sed -i 's/deb.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
    # && sed -i 's/security.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
    && sed -i 's/deb.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list.d/debian.sources \
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
    && apt install clang-15 -y \
    && apt install clang-format-15 -y \
    && apt install lldb-15 -y \
    && apt install libc++-15-dev -y \
    && apt install libc++abi-15-dev -y \
    && apt install clangd-15 -y \
    && apt install lld-15 -y \
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
    && apt install gcc-i686-linux-gnu -y \
    && apt install gcc-multilib -y \
    && apt install fonts-firacode -y
RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 100 \
    && update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-15 100 \
    && update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-15 100 \
    && update-alternatives --install /usr/bin/lld lld /usr/bin/lld-15 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 100 \
    && update-alternatives --install /usr/bin/ld.lld ld.lld /usr/bin/ld.lld-15 100 \
    && update-alternatives --install /usr/bin/llvm-ar llvm-ar /usr/bin/llvm-ar-15 100 \
    && update-alternatives --install /usr/bin/llvm-nm llvm-nm /usr/bin/llvm-nm-15 100 \
    && update-alternatives --install /usr/bin/llvm-objcopy llvm-objcopy /usr/bin/llvm-objcopy-15 100 \
    && update-alternatives --install /usr/bin/llvm-objdump llvm-objdump /usr/bin/llvm-objdump-15 100 \
    && update-alternatives --install /usr/bin/llvm-readelf llvm-readelf /usr/bin/llvm-readelf-15 100 \
    && update-alternatives --install /usr/bin/llvm-strip llvm-strip /usr/bin/llvm-strip-15 100 \
    && update-alternatives --install /usr/bin/cc cc /usr/bin/clang-15 100 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-15 100 \
    && echo 'miku    ALL=(ALL:ALL) ALL' >> /etc/sudoers \
    && echo '/usr/sbin/sshd -D &' > /root/run.sh \
    && chmod 110 /root/run.sh
USER miku
RUN git config --global pull.rebase false \
    && git config --global user.name kaspersigi \
    && git config --global user.email kaspersigi@gmail.com \
    && ssh-keyscan github.com > $HOME/.ssh/known_hosts \
    && echo '' > $HOME/.ssh/authorized_keys \
    && mkdir $HOME/linux \
    && cd $HOME \
    && git clone git@github.com:kaspersigi/learn.git
USER root
WORKDIR /root
ENTRYPOINT /root/run.sh && su miku
# CMD /usr/sbin/sshd -D &
# sudo apt install apparmor-utils
# docker build -t kaspersigi/debian .
# docker buildx build --platform=linux/amd64 -t kaspersigi/clang:amd64 .
# docker run -it --privileged -p 3333:22 -v /Users/miku/Downloads/amd64:/home/miku/linux --name=amd64 --hostname AMD64-Miku kaspersigi/clang:amd64
# docker run -it --privileged -p 3333:22 -v /d/amd64:/home/miku/linux --name=amd64 --hostname AMD64-Miku kaspersigi/clang:amd64