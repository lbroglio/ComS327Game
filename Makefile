
mapGen: mapGeneration.o biome.o map.o priorityQueue.o
	gcc mapGeneration.o biome.o map.o priorityQueue.o -o mapGen

mapGeneration.o: Map/mapGeneration.c Map/biome.h Map/map.h Data-Structures/priorityQueue.h
	gcc -Wall -Werror -ggdb Map/mapGeneration.c -c

biome.o: Map/biome.c Map/biome.h
	gcc -Wall -Werror -ggdb Map/biome.c -c

map.o: Map/map.c Map/map.h
	gcc -Wall -Werror -ggdb Map/map.c -c

priorityQueue.o: Data-Structures/priorityQueue.c Data-Structures/priorityQueue.h
	gcc -Wall -Werror -ggdb Data-Structures/priorityQueue.c -c


clean:
	rm mapGen mapGeneration.o biome.o map.o