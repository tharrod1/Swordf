ARGS = -O3 -Wno-write-strings -Wno-format
LNK = -lGL -lGLU -lglut -lsfml-audio -lpthread
OBJS = Swordf.o Light.o AudioPool.o Map.o CollisionGun.o error.o

all: $(OBJS) main clean

main:
	g++ -c main.cc $(ARGS)
	g++ -o Swordf $(OBJS) main.o $(ARGS) $(LNK)

Swordf.o:
	g++ -c Swordf.cc $(ARGS)

Light.o:
	g++ -c Light.cc $(ARGS)

AudioPool.o:
	g++ -c AudioPool.cc $(ARGS)

Map.o:
	g++ -c Map.cc $(ARGS)

CollisionGun.o:
	g++ -c CollisionGun.cc $(ARGS)

error.o:
	g++ -c error.c $(ARGS)
clean:
	mv Swordf ../bin
	mv *.o ../bin
	rm *~
