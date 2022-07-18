docker buildx build --platform=linux/amd64 -t kaspersigi/clang:amd64 .
docker run -it --privileged -p 3333:22 -v /d/amd64:/home/miku/linux --name=amd64 --hostname AMD64-Miku kaspersigi/clang:amd64
pause