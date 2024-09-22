gcc -c -o XWindow.o -I /usr/include XWindow.c

gcc -o XWindow -L /usr/lib/x86_64-linux-gnu XWindow.o -l X11

