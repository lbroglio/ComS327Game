worldGen: mapGeneration.o biome.o map.o worldGeneration.o
	gcc worldGeneration.o mapGeneration.o biome.o map.o -o worldGen


worldGeneration.o:  Map/worldGeneration.c Map/worldGeneration.h
	gcc -Wall -Werror -ggdb  Map/worldGeneration.c -c


mapGeneration.o:  Map/mapGeneration.c  Map/mapGeneration.h
	gcc -Wall -Werror -ggdb  Map/mapGeneration.c -c

biome.o:  Map/biome.c  Map/biome.h
	gcc -Wall -Werror -ggdb  Map/biome.c -c

map.o:  Map/map.c  Map/map.h
	gcc -Wall -Werror -ggdb  Map/map.c -c

clean:
	rm worldGen mapGeneration.o biome.o map.o worldGeneration.o