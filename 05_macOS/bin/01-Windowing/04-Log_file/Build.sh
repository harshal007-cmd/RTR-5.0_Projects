clang -c -o Window.o window.m
mkdir -p Window.app/Contents/MacOS
clang -o Window.app/Contents/MacOS/Window Window.o -framework Cocoa
