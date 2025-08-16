# FROM amd64/ubuntu:22.04
FROM arm64v8/ubuntu:22.04
LABEL org.opencontainers.image.authors="kaspersigi@outlook.com"
WORKDIR /root
EXPOSE 22
USER root

# 创建 miku 用户，更新系统，并安装必需软件包
RUN mkdir -p /var/run/sshd \
    && useradd -m -p paKe96Li2oGUE miku \
    && usermod -s /bin/bash miku \
    && apt update \
    && apt upgrade -y \
    && apt autoremove -y \
    && apt install wget gnupg sudo curl git vim openssh-server -y

# 创建 SSH 配置文件
RUN mkdir /home/miku/.ssh
COPY id_ed25519 /home/miku/.ssh
RUN chown miku:miku -R /home/miku/.ssh \
    && chmod 600 /home/miku/.ssh/id_ed25519

# 安装 LLVM 工具链
RUN wget https://apt.llvm.org/llvm-snapshot.gpg.key -O /tmp/key \
    && gpg --dearmor -o /usr/share/keyrings/llvm-archive-keyring.gpg /tmp/key \
    && echo "deb [signed-by=/usr/share/keyrings/llvm-archive-keyring.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy-20 main" | tee /etc/apt/sources.list.d/llvm.list
RUN apt update \
    && apt upgrade -y \
    && apt autoremove -y

# 安装其他工具
RUN apt install clang-20 clangd-20 clang-format-20 lldb-20 libllvmlibc-20-dev libc++-20-dev lld-20 binutils-i686-linux-gnu binutils-riscv64-linux-gnu gcc-i686-linux-gnu binutils-x86-64-linux-gnu bsdmainutils make gdb cgdb valgrind qemu-system-arm qemu-system-misc qemu-system-x86 -y

RUN apt install libncurses-dev flex bison bc dwarves libssl-dev libelf-dev python-is-python3 python3-pip python3-virtualenv pbzip2 bzip2 zip unzip xz-utils lz4 cpio -y

# 更新 alternatives 和配置 sudo 权限
RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-20 100 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-20 100 \
    && echo 'miku    ALL=(ALL:ALL) ALL' >> /etc/sudoers

# 创建并设置 run.sh 脚本，启动 SSH 和 miku 用户的 miku.sh
RUN echo '/usr/sbin/sshd -D &' > /root/run.sh \
    && echo 'su miku -c "/home/miku/miku.sh"' >> /root/run.sh \
    && chmod +x /root/run.sh

# 设置 miku 用户
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
    && git clone git@github.com:kaspersigi/perf_tools.git \
    && git clone --single-branch -b linux-rolling-stable --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git \
    && wget https://dl.google.com/android/repository/android-ndk-r27c-linux.zip \
    && unzip android-ndk-r27c-linux.zip \
    && rm -v android-ndk-r27c-linux.zip \
    && echo 'code-server &> /dev/null &' > $HOME/miku.sh \
    && chmod +x $HOME/miku.sh

# 设置入口点，启动 run.sh 脚本
USER root
WORKDIR /root
ENTRYPOINT ["/root/run.sh"]