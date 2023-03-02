poke327: poke327.o mapGeneration.o map.o priorityQueue.o NPCMovement.o biome.o Characters/gameCharacter.h
	gcc poke327.o NPCMovement.o mapGeneration.o map.o biome.o priorityQueue.o -o poke327

worldGen: mapGeneration.o biome.o map.o worldGeneration.o priorityQueue.o
	gcc worldGeneration.o mapGeneration.o biome.o map.o priorityQueue.o -o worldGen

poke327.o: poke327.c
	gcc -Wall -Werror -ggdb  poke327.c -c

NPCMovement.o: Characters/NPCMovement.c
	gcc -Wall -Werror -ggdb  Characters/NPCMovement.c -c

worldGeneration.o:  Map/worldGeneration.c Map/worldGeneration.h
	gcc -Wall -Werror -ggdb  Map/worldGeneration.c -c

biome.o: Map/biome.c Map/biome.h
	gcc -Wall -Werror -ggdb Map/biome.c -c

mapGeneration.o:  Map/mapGeneration.c  Map/mapGeneration.h
	gcc -Wall -Werror -ggdb  Map/mapGeneration.c -c

priorityQueue.o:  Data-Structures/priorityQueue.c  Data-Structures/priorityQueue.h
	gcc -Wall -Werror -ggdb  Data-Structures/priorityQueue.c -c

map.o:  Map/map.c  Map/map.h
	gcc -Wall -Werror -ggdb  Map/map.c -c

clean:
	rm poke327 worldGen mapGeneration.o biome.o map.o worldGeneration.o priorityQueue.o NPCMovement.o poke327.o