clang++ -Wno-depricated-declatations -c -o Window.o window.mm
mkdir -p Window.app/Contents/MacOS
clang++ -o Window.app/Contents/MacOS/Window Window.o -framework Cocoa -framework Quadcore -framework OpenGL
