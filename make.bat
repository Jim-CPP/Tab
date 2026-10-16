cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra Tab.cpp ControlWindow.cpp TabControlWindow.cpp StatusBarWindow.cpp -o Tab.exe
