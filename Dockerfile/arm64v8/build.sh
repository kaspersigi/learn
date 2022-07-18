docker build -t kaspersigi/clang:arm64v8 .
docker run -it --privileged -p 2222:22 -v /Users/miku/Downloads/arm64:/home/miku/linux --name=arm64 --hostname Arm64-Miku kaspersigi/clang:arm64v8