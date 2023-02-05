mapGen: mapGeneration.o biome.o map.o priorityQueue.o
	gcc mapGeneration.o biome.o map.o priorityQueue.o -o mapGen

mapGeneration.o: mapGeneration.c biome.h map.h priorityQueue.h
	gcc -Wall -Werror -ggdb Map/mapGeneration.c -c

biome.o: biome.c biome.h
	gcc -Wall -Werror -ggdb Map/biome.c -c

map.o: map.c map.h
	gcc -Wall -Werror -ggdb Map/map.c -c

priorityQueue.o: priorityQueue.c priorityQueue.h
	gcc -Wall -Werror -ggdb Data-Structures/priorityQueue.c -c


clean:
	rm mapGen mapGeneration.o biome.o map.o