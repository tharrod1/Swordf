all:
	g++ main.cc -lGL -lGLU -lglut -lsfml-audio -lpthread -O3 
	rm *~
