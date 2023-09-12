cls

del *.obj
del *.exe
del *.txt

cl.exe /c /EHsc  /I ..\Include\ *.cpp

rc.exe /I ..\Include\ Window.rc

link.exe *.obj window.res user32.lib gdi32.lib kernel32.lib /OUT:%~1.exe



