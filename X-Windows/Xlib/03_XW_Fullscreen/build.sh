gcc -c -o XWindow_3.o -I /usr/include XWindow_3.c

gcc -o XWindow_3 -L /usr/lib/x86_64-linux-gnu XWindow_3.o -l X11

