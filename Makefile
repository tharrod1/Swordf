all:
	g++ main.cc -lGL -lGLU -lglut -lsfml-audio -lpthread -O3 -Wno-write-strings -Wno-format
	rm *~
