cls

del *.obj


cl.exe /c /EHsc  /I C:\freeglut\include *.cpp

link.exe *.obj  /LIBPATH:C:\freeglut\lib\x64 /SUBSYSTEM:CONSOLE






