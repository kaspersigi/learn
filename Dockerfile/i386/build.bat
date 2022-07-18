docker buildx build --platform=linux/i386 -t kaspersigi/clang:i386 .
docker run -it --privileged -p 3333:22 -v /d/i386:/home/miku/linux --name=i386 --hostname I386-Miku kaspersigi/clang:i386
pause