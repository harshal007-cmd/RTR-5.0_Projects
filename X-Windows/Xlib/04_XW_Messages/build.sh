gcc -c -o XWindow_4.o -I /usr/include XWindow_4.c

gcc -o XWindow_4 -L /usr/lib/x86_64-linux-gnu XWindow_4.o -l X11

./XWindow_4
