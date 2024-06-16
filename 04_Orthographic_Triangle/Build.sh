mkdir -p Window.app/Contents/MacOS
clang++ -Wno-deprecated-declarations -o Window.app/Contents/MacOS/Window Window.mm -framework Cocoa -framework QuartzCore -framework OpenGL
