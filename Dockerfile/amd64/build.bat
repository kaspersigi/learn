docker build -t kaspersigi/clang:amd64 .
docker run -it --privileged -p 2222:22 -p 8888:8888 -v /d/share:/home/miku/share --name=amd64 --hostname AMD64-Miku kaspersigi/clang:amd64
pause