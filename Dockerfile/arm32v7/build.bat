docker buildx build --platform=linux/arm32v7 -t kaspersigi/clang:arm32v7 .
docker run -it --privileged -p 2222:22 -v /d/arm32:/home/miku/linux --name=arm32 --hostname Arm32-Miku kaspersigi/clang:arm32v7
pause