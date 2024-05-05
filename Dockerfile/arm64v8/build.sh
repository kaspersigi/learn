docker build -t kaspersigi/clang:arm64v8 .
docker run -it --privileged -p 2222:22 -p 8888:8888 -v /root/share:/home/miku/share --name=arm64 --hostname Arm64-Miku kaspersigi/clang:arm64v8