gcc -c -o XWindow_5.o -I /usr/include XWindow_5.c

gcc -o XWindow_5 -L /usr/lib/x86_64-linux-gnu XWindow_5.o -l X11

./XWindow_5
