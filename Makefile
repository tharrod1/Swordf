all:
	g++ main.cc -lGL -lGLU -lglut -lglfw -lsfml-audio -lpthread -O3 -Wno-write-strings
	rm *~
