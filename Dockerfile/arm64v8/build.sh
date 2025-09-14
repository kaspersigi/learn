docker build -t kaspersigizz/clang:arm64v8 .

docker run -it \
  --restart always \
  --privileged \
  -p 2222:22 \
  -p 8888:8888 \
  -e CODESERVER_PASSWORD=MyCodeServer           \  # 👈 设置你的密码
  -v ~/.ssh:/home/miku/.ssh:ro \                   # 👈 挂载你的 SSH 密钥（只读）
  -v ~/share:/home/miku/share \                    # 👈 挂载共享工作目录
  --name dev-container \
  --hostname Arm64-Miku \
  kaspersigizz/clang:arm64v8