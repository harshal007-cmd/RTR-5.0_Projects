gcc -c -o XWindow_2.o -I /usr/include XWindow_2.c

gcc -o XWindow_2 -L /usr/lib/x86_64-linux-gnu XWindow_2.o -lX11

