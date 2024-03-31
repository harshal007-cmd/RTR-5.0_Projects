cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc  /I ..\include\ *.cpp

rc.exe /I ..\include\ ..\resource\Window.rc

link.exe *.obj ..\resource\window.res user32.lib gdi32.lib ..\lib\glew32.lib ..\lib\Sphere.lib kernel32.lib /OUT:..\bin\%~1.exe

del *.obj

..\bin\%~1.exe

