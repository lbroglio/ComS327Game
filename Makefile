poke327: poke327.o mapGeneration.o map.o priorityQueue.o NPCMovement.o biome.o Characters/gameCharacter.h screen.o playerMovement.o battles.o
	gcc ./bin/poke327.o ./bin/NPCMovement.o ./bin/mapGeneration.o ./bin/map.o ./bin/biome.o ./bin/priorityQueue.o ./bin/screen.o ./bin/playerMovement.o ./bin/battles.o -lcurses -o poke327

worldGen: mapGeneration.o biome.o map.o worldGeneration.o priorityQueue.o
	gcc worldGeneration.o mapGeneration.o biome.o map.o priorityQueue.o -o worldGen

battles.o: Battles/battles.c Battles/battles.h
	gcc -Wall -Werror -ggdb  Battles/battles.c -c -o ./bin/battles.o

playerMovement.o: Characters/playerMovement.c Characters/playerMovement.h
	gcc -Wall -Werror -ggdb  Characters/playerMovement.c -c -o ./bin/playerMovement.o

screen.o: Screen/screen.c Screen/screen.h
	gcc -Wall -Werror -ggdb  Screen/screen.c -c -o ./bin/screen.o

poke327.o: poke327.c
	gcc -Wall -Werror -ggdb  poke327.c -c -o ./bin/poke327.o

NPCMovement.o: Characters/NPCMovement.c
	gcc -Wall -Werror -ggdb  Characters/NPCMovement.c -c -o ./bin/NPCMovement.o

worldGeneration.o:  Map/worldGeneration.c Map/worldGeneration.h
	gcc -Wall -Werror -ggdb  Map/worldGeneration.c -c -o ./bin/worldGeneration.o

biome.o: Map/biome.c Map/biome.h
	gcc -Wall -Werror -ggdb Map/biome.c -c -o ./bin/biome.o

mapGeneration.o:  Map/mapGeneration.c  Map/mapGeneration.h
	gcc -Wall -Werror -ggdb  Map/mapGeneration.c -c -o ./bin/mapGeneration.o

priorityQueue.o:  Data-Structures/priorityQueue.c  Data-Structures/priorityQueue.h
	gcc -Wall -Werror -ggdb  Data-Structures/priorityQueue.c -c -o ./bin/priorityQueue.o

map.o:  Map/map.c  Map/map.h
	gcc -Wall -Werror -ggdb  Map/map.c -c -o ./bin/map.o

clean:
	rm -r poke327 bin/*