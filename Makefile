

poke327: poke327.o mapGeneration.o map.o priorityQueue.o worldGeneration.o NPCMovement.o biome.o Characters/gameCharacter.h Characters/NPCMapInfo.h screen.o playerMovement.o battles.o point.o fileParser.o pokeData.o
	g++ ./bin/poke327.o ./bin/NPCMovement.o ./bin/mapGeneration.o ./bin/worldGeneration.o ./bin/PokemonData.o ./bin/fileParser.o ./bin/map.o ./bin/biome.o ./bin/priorityQueue.o ./bin/screen.o ./bin/playerMovement.o ./bin/battles.o ./bin/point.o -lcurses -o poke327

fileParser.o: Parser/fileParser.h Parser/fileParser.cpp
	g++ -Wall -Werror -ggdb  Parser/fileParser.cpp -c -o ./bin/fileParser.o

pokeData.o: PokemonData/PokemonData.h PokemonData/PokemonData.cpp
	g++ -Wall -Werror -ggdb  PokemonData/PokemonData.cpp -c -o ./bin/PokemonData.o

battles.o: Battles/battles.cpp Battles/battles.h
	g++ -Wall -Werror -ggdb  Battles/battles.cpp -c -o ./bin/battles.o

playerMovement.o: Characters/playerMovement.cpp Characters/playerMovement.h
	g++ -Wall -Werror -ggdb  Characters/playerMovement.cpp -c -o ./bin/playerMovement.o

screen.o: Screen/screen.cpp Screen/screen.h
	g++ -Wall -Werror -ggdb  Screen/screen.cpp -c -o ./bin/screen.o

poke327.o: poke327.cpp
	g++ -Wall -Werror -ggdb  poke327.cpp -c -o ./bin/poke327.o

NPCMovement.o: Characters/NPCMovement.cpp
	g++ -Wall -Werror -ggdb  Characters/NPCMovement.cpp -c -o ./bin/NPCMovement.o

worldGeneration.o:  Map/worldGeneration.cpp Map/worldGeneration.h
	g++ -Wall -Werror -ggdb  Map/worldGeneration.cpp -c -o ./bin/worldGeneration.o

biome.o: Map/biome.cpp Map/biome.h
	g++ -Wall -Werror -ggdb Map/biome.cpp -c -o ./bin/biome.o

mapGeneration.o:  Map/mapGeneration.cpp  Map/mapGeneration.h
	g++ -Wall -Werror -ggdb  Map/mapGeneration.cpp -c -o ./bin/mapGeneration.o

priorityQueue.o:  Data-Structures/priorityQueue.cpp  Data-Structures/priorityQueue.h
	g++ -Wall -Werror -ggdb  Data-Structures/priorityQueue.cpp -c -o ./bin/priorityQueue.o

map.o:  Map/map.cpp  Map/map.h
	g++ -Wall -Werror -ggdb  Map/map.cpp -c -o ./bin/map.o

point.o:  Map/point.cpp  Map/point.h
	g++ -Wall -Werror -ggdb  Map/point.cpp -c -o ./bin/point.o

clean:
	rm -r poke327 bin/*