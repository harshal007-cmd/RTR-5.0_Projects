cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc /I ..\Include\ *.cpp

rc.exe /I ..\Include\ ../resource/ogl.rc 

link *.obj /LIBPATH:..\lib ../resource/ogl.res user32.lib gdi32.lib kernel32.lib /OUT:..\bin\%1.exe

del *.obj

..\bin\%1.exe
