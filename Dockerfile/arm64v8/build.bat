docker build -t kaspersigizz/clang:arm64v8 .

docker run -d \
  --restart always \
  --privileged \
  -p 2222:22 \
  -p 8888:8888 \
  -e CODESERVER_PASSWORD=MyCodeServer \
  -v /c/Users/kaspe/.ssh:/home/miku/.ssh:ro \
  -v /c/Users/kaspe/Downloads/share:/home/miku/share \
  --name AMD64-Miku \
  --hostname Arm64-Miku \
  kaspersigizz/clang:arm64v8

pause