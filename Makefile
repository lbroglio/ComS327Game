npcDist: mapGeneration.o map.o priorityQueue.o NPCMovement.o biome.o
	gcc NPCMovement.o mapGeneration.o map.o biome.o priorityQueue.o -o npcDist

worldGen: mapGeneration.o biome.o map.o worldGeneration.o priorityQueue.o
	gcc worldGeneration.o mapGeneration.o biome.o map.o priorityQueue.o -o worldGen

NPCMovement.o: NPC/NPCMovement.c
	gcc -Wall -Werror -ggdb  NPC/NPCMovement.c -c

worldGeneration.o:  Map/worldGeneration.c Map/worldGeneration.h
	gcc -Wall -Werror -ggdb  Map/worldGeneration.c -c

mapGeneration.o: Map/mapGeneration.c 
	gcc -Wall -Werror -ggdb Map/mapGeneration.c -c

biome.o: Map/biome.c Map/biome.h
	gcc -Wall -Werror -ggdb Map/biome.c -c

mapGeneration.o:  Map/mapGeneration.c  Map/mapGeneration.h
	gcc -Wall -Werror -ggdb  Map/mapGeneration.c -c

priorityQueue.o:  Data-Structures/priorityQueue.c  Data-Structures/priorityQueue.h
	gcc -Wall -Werror -ggdb  Data-Structures/priorityQueue.c -c

map.o:  Map/map.c  Map/map.h
	gcc -Wall -Werror -ggdb  Map/map.c -c

clean:
	rm worldGen npcDist mapGeneration.o biome.o map.o worldGeneration.o priorityQueue.o NPCMovement.o