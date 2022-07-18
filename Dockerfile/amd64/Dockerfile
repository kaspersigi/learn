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
    && apt install make -y \
    && apt install nasm -y \
    && apt install git -y \
    && apt install file -y \
    && apt install wget -y \
    && apt install curl -y \
    && apt install vim -y \
    && apt install openssh-server -y
RUN ln -s /usr/bin/clang-11 /usr/bin/clang \
    && ln -s /usr/bin/clang-11 /usr/bin/cc \
    && ln -s /usr/bin/clang++-11 /usr/bin/clang++ \
    && ln -s /usr/bin/clang-format-11 /usr/bin/clang-format \
    && ln -s /usr/bin/lldb-11 /usr/bin/lldb \
    && echo 'miku    ALL=(ALL:ALL) ALL' >> /etc/sudoers \
    && touch /root/run.sh \
    && echo '/usr/sbin/sshd -D &' >> /root/run.sh \
    && chmod 110 /root/run.sh
USER miku
RUN git config --global pull.rebase false \
    && git config --global user.name kaspersigi \
    && git config --global user.email kaspersigi@gmail.com \
    && ssh-keyscan 106.52.13.193 >> $HOME/.ssh/known_hosts \
    && echo '' >> $HOME/.ssh/authorized_keys \
    # && ssh-keygen -f $HOME/.ssh/id_rsa -t rsa -N '' \
    && mkdir $HOME/linux \
    && cd $HOME \
    && git clone git@106.52.13.193:/home/git/learn.git
USER root
WORKDIR /root
ENTRYPOINT /root/run.sh && su miku
# CMD /usr/sbin/sshd -D &
# sudo apt install apparmor-utils
# docker build -t kaspersigi/debian .
# docker buildx build --platform=linux/amd64 -t kaspersigi/clang:amd64 .
# docker run -it --privileged -p 3333:22 -v /Users/miku/Downloads/amd64:/home/miku/linux --name=amd64 --hostname AMD64-Miku kaspersigi/clang:amd64
# docker run -it --privileged -p 3333:22 -v /d/amd64:/home/miku/linux --name=amd64 --hostname AMD64-Miku kaspersigi/clang:amd64