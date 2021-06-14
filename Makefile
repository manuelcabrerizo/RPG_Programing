build:
	g++ -Wfatal-errors \
	./src/*.cpp \
	-I"C:\libsdl\mingw64\include" \
	-L"C:\libsdl\mingw64\lib" \
	-I"./lua" \
	-L"./lua" \
	-lmingw32 \
	-llua53 \
	-lSDL2main \
	-lSDL2 \
	-o RPG.exe
run:
	RPG.exe

