"# HELL_ON" 
W ramach treningu pisania programów w C++, napisałem gierkę.
Grafikę i dźwięki wykorzystałem dostępne darmowe w Internecie.
Gierka działa w okienku 800x600, po naciśnięciu [esc] zmienia się na pełny ekran.

Instrukcja:
- Statkiem poruszamy strzałkami;
- strzał [spacja];
- zmiana na pełny ekran i z powrotem[esc];

Kompilacja pod Windowsem:

g++ -std=c++0x "-IC:\\lib\\SDL2-2.0.5\\i686-w64-mingw32\\include" -O3 -Wall -c -fmessage-length=0 -std=c++11 -o main.o "..\\main.cpp"
g++ -std=c++0x "-IC:\\lib\\SDL2-2.0.5\\i686-w64-mingw32\\include" -O3 -Wall -c -fmessage-length=0 -std=c++11 -o cEngine.o "..\\cEngine.cpp"
g++ -std=c++0x "-IC:\\lib\\SDL2-2.0.5\\i686-w64-mingw32\\include" -O3 -Wall -c -fmessage-length=0 -std=c++11 -o cGame.o "..\\cGame.cpp"
g++ "-LC:\\lib\\SDL2-2.0.5\\i686-w64-mingw32\\lib" -o Hell_ON.exe cEngine.o cGame.o main.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -mwindows

