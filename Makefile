WINLIBS = -lopengl32 -lgdi32 -lwinmm
LINUXLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

ifeq ($(OS), Windows_NT)
	LIBS = $(WINLIBS)
	OUT_EXT = .exe
else
	LIBS = $(LINUXLIBS)
	OUT_EXT = 
endif

./bin/app: src/*.cpp src/include/*.hpp
	mkdir -p ./bin/
	g++ src/*.cpp -o ./bin/app$(OUT_EXT) -O1 -Wall -std=c++11 -Wno-missing-braces $(LIBS)

clean:
	rm -f ./bin/app$(OUT_EXT)

run: ./bin/app
	./bin/app
