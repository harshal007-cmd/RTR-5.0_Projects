gcc -c -o $1.o -I /usr/include $1 

gcc -o $1.out -L /usr/lib/x86_64-linux-gnu $1.o -lX11 -lGL -lm

cp $1.out ../bin

