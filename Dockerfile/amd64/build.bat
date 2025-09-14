docker build -t kaspersigizz/clang:amd64 .

docker run -it \
  --restart always \
  --privileged \
  -p 2222:22 \
  -p 8888:8888 \
  -e CODESERVER_PASSWORD=MyCodeServer                \  # 👈 设置你的密码
  -v /c/Users/kaspe/.ssh:/home/miku/.ssh:ro          \  # 👈 挂载你的 SSH 密钥（只读）
  -v /c/Users/kaspe/Downloads/share:/home/miku/share \  # 👈 挂载共享工作目录
  --name dev-container \
  --hostname AMD64-Miku \
  kaspersigizz/clang:amd64

pause