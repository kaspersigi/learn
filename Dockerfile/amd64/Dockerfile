FROM amd64/ubuntu:latest
# FROM arm64v8/ubuntu:latest
LABEL org.opencontainers.image.authors="kaspersigi@outlook.com"
WORKDIR /root
EXPOSE 22
USER root
RUN mkdir -p /var/run/sshd \
    # perl -e 'print crypt($ARGV[0], "password")' $(passwd)
    && useradd -m -p paKe96Li2oGUE miku \
    && usermod -s /bin/bash miku \
    && apt update \
    && apt upgrade -y \
    && apt autoremove -y
RUN mkdir /home/miku/.ssh
# COPY id_ed25519 /home/miku/.ssh
# RUN chown miku:miku -R /home/miku/.ssh \
#     && chmod 600 /home/miku/.ssh/id_ed25519
RUN apt install clang-19 clangd-19 clang-format-19 lldb-19 libllvmlibc-19-dev libc++-19-dev lld-19 binutils-i686-linux-gnu binutils-riscv64-linux-gnu gcc-i686-linux-gnu bsdmainutils make gdb cgdb valgrind qemu-system-arm qemu-system-misc qemu-system-x86 openssh-server -y \
    && apt install libncurses-dev flex bison bc dwarves libssl-dev libelf-dev python-is-python3 bzip2 unzip xz-utils lz4 cpio -y
RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-19 100 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-19 100 \
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
    && git clone https://github.com/kaspersigi/learn.git \
    && echo 'code-server &> /dev/null &' > $HOME/miku.sh \
    && chmod 110 $HOME/miku.sh
USER root
WORKDIR /root
ENTRYPOINT /root/run.sh && su miku && /home/miku/miku.sh
# CMD /usr/sbin/sshd -D &
# sudo apt install apparmor-utils
# docker build -t kaspersigizz/clang:amd64 .
# docker buildx build --platform=linux/amd64 -t kaspersigizz/clang:amd64 .
# docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /Users/miku/share:/home/miku/share --name=amd64 --hostname AMD64-Miku kaspersigizz/clang:amd64
# docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /d/share:/home/miku/share --name=amd64 --hostname AMD64-Miku kaspersigizz/clang:amd64
# docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /root/share:/home/miku/share --name=amd64 --hostname AMD64-Miku kaspersigizz/clang:amd64