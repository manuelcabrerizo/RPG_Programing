build:
	gcc -Wfatal-errors \
	./src/*.cpp \
	-I"C:\libsdl\include" \
	-L"C:\libsdl\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lm \
	-o RPG.exe
run:
	RPG.exe
