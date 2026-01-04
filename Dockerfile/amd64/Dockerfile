# 使用 Ubuntu 22.04 amd64 基础镜像
FROM amd64/ubuntu:22.04
LABEL org.opencontainers.image.authors="kaspersigi@outlook.com"

WORKDIR /root
EXPOSE 22 8888
USER root

# ========== 1. 创建用户 + SSH 目录 ==========
RUN mkdir -p /var/run/sshd \
    && useradd -m -s /bin/bash -p '*' miku \
    && mkdir -p /home/miku/.ssh \
    && chown miku:miku /home/miku/.ssh \
    && chmod 700 /home/miku/.ssh \
    && touch /home/miku/.ssh/authorized_keys \
    && chmod 600 /home/miku/.ssh/authorized_keys

# ========== 2. 安装基础工具 + 添加 LLVM 21 源 ==========
RUN apt update && apt upgrade -y && \
    apt install -y wget gnupg sudo git vim openssh-server curl ca-certificates \
    && wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | gpg --dearmor -o /usr/share/keyrings/llvm-archive-keyring.gpg \
    && echo "deb [signed-by=/usr/share/keyrings/llvm-archive-keyring.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy-21 main" > /etc/apt/sources.list.d/llvm.list

# ========== 3. 安装所有开发工具 + 清理缓存 ==========
RUN apt update && apt upgrade -y && \
    apt install -y \
        clang-21 clangd-21 clang-format-21 clang-tidy-21 lldb-21 libllvmlibc-21-dev libc++-21-dev lld-21 \
        binutils-i686-linux-gnu binutils-riscv64-linux-gnu gcc-i686-linux-gnu \
        bsdmainutils make gdb cgdb valgrind qemu-system-arm qemu-system-misc qemu-system-x86 \
        libncurses5 libncurses-dev flex bison bc dwarves libssl-dev libelf-dev \
        python-is-python3 python3-pip python3-virtualenv pbzip2 bzip2 zip unzip xz-utils lz4 cpio rsync automake autoconf libtool gawk uuid-dev libxml-simple-perl gcc-multilib \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-21 100 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-21 100 \
    && echo 'miku ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers \
    && apt autoremove -y && apt clean && rm -rf /var/lib/apt/lists/*

# ========== 4. 安装 code-server ==========
RUN mkdir -p /mnt/develop \
    && chown -R miku:miku /mnt/develop \
    && curl -fsSL https://code-server.dev/install.sh | sh

# ========== 5. 配置 miku 用户环境 ==========
USER miku
WORKDIR /home/miku

RUN git config --global pull.rebase false \
    && git config --global user.name kaspersigi \
    && git config --global user.email kaspersigi@outlook.com \
    && ssh-keyscan github.com > ~/.ssh/known_hosts \
    && echo -e "Host github.com\n    Hostname ssh.github.com\n    Port 443\n    User git" > ~/.ssh/config \
    && chmod 644 ~/.ssh/config \
    && mkdir -p share /mnt/develop/linux

# ========== 6. 创建 miku.sh ==========
RUN printf '%s\n' \
    '#!/bin/bash' \
    'echo ">>> [miku.sh] Initializing development environment..."' \
    '' \
    '# Clone repos if not exist' \
    'if [ ! -d "linux/learn" ]; then' \
    '    echo ">>> Cloning learn repo..."' \
    '    git clone https://github.com/kaspersigi/learn.git linux/learn' \
    'fi' \
    '' \
    'if [ ! -d "linux/perf_tools" ]; then' \
    '    echo ">>> Cloning perf_tools repo..."' \
    '    git clone https://github.com/kaspersigi/perf_tools.git linux/perf_tools' \
    'fi' \
    '' \
    'if [ ! -d "linux/linux" ]; then' \
    '    echo ">>> Cloning Linux kernel (stable)..."' \
    '    git clone --single-branch -b linux-rolling-stable --depth 1 https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git linux/linux' \
    'fi' \
    '' \
    '# Download and extract NDK if not exist' \
    'if [ ! -d "linux/android-ndk-r27d" ]; then' \
    '    echo ">>> Downloading Android NDK r27d..."' \
    '    cd linux && wget -q https://dl.google.com/android/repository/android-ndk-r27d-linux.zip && unzip -q android-ndk-r27d-linux.zip && rm android-ndk-r27d-linux.zip' \
    '    echo ">>> Android NDK installed."' \
    'fi' \
    '' \
    'echo ">>> Starting code-server on :8888 (password auth)..."' \
    'PASSWORD=${CODESERVER_PASSWORD:-MyCodeServer}' \
    'PASSWORD="$PASSWORD" code-server --bind-addr 0.0.0.0:8888 --auth password /home/miku &' \
    '' \
    'echo ">>> [miku.sh] Initialization complete. code-server running in background."' \
    > /mnt/develop/miku.sh \
    && chmod +x /mnt/develop/miku.sh

# ========== 7. 切回 root ==========
USER root

# ========== 8. 创建 start.sh ==========
RUN printf '%s\n' \
    '#!/bin/bash' \
    'echo ">>> [start.sh] Starting SSH daemon..."' \
    '/usr/sbin/sshd -D &' \
    '' \
    'echo ">>> [start.sh] Switching to user miku and running miku.sh..."' \
    'su - miku -c "cd /mnt/develop && ./miku.sh"' \
    '' \
    'echo ">>> [start.sh] All services started. Container running..."' \
    'wait' \
    > /root/start.sh \
    && chmod +x /root/start.sh

# ========== 9. 设置入口点 ==========
ENTRYPOINT ["/root/start.sh"]