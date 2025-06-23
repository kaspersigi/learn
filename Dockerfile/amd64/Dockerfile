FROM amd64/ubuntu:22.04
# FROM arm64v8/ubuntu:22.04
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
    && apt autoremove -y \
    && apt install wget gnupg -y
RUN mkdir /home/miku/.ssh
COPY id_ed25519 /home/miku/.ssh
RUN chown miku:miku -R /home/miku/.ssh \
    && chmod 600 /home/miku/.ssh/id_ed25519
RUN wget https://apt.llvm.org/llvm-snapshot.gpg.key -O /tmp/key \
    && gpg --dearmor -o /usr/share/keyrings/llvm-archive-keyring.gpg /tmp/key \
    && echo "deb [signed-by=/usr/share/keyrings/llvm-archive-keyring.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy-20 main" | tee /etc/apt/sources.list.d/llvm.list
RUN apt update \
    && apt upgrade -y \
    && apt autoremove -y
RUN apt install sudo wget git vim openssh-server -y
RUN apt install clang-20 clangd-20 clang-format-20 lldb-20 libllvmlibc-20-dev libc++-20-dev lld-20 binutils-i686-linux-gnu binutils-riscv64-linux-gnu gcc-i686-linux-gnu bsdmainutils make gdb cgdb valgrind qemu-system-arm qemu-system-misc qemu-system-x86 -y
RUN apt install libncurses-dev flex bison bc dwarves libssl-dev libelf-dev python-is-python3 pbzip2 bzip2 zip unzip xz-utils lz4 cpio -y
RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-20 100 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-20 100 \
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
    && mkdir $HOME/linux \
    && cd $HOME/linux \
    && git clone git@github.com:kaspersigi/learn.git \
    && wget https://dl.google.com/android/repository/android-ndk-r27c-linux.zip \
    && unzip android-ndk-r27c-linux.zip \
    && rm -v android-ndk-r27c-linux.zip \
    && git clone --single-branch -b oppo/sm8750_v_15.0.1_find_n5 --depth 1 git@github.com:oppo-source/android_kernel_oppo_sm8750.git \
    && git clone --single-branch -b linux-rolling-stable --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git \
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