docker build -t kaspersigizz/clang:arm64v8 .
docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /Users/miku/share:/home/miku/share --name=arm64 --hostname Arm64-Miku kaspersigizz/clang:arm64v8
# docker run -it --restart always --privileged -p 2222:22 -p 8888:8888 -v /root/share:/home/miku/share --name=arm64 --hostname Arm64-Miku kaspersigizz/clang:arm64v8