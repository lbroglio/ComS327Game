mapGen: mapGeneration.o biome.o
	gcc mapGeneration.o biome.o -o mapGen

mapGeneration.o: mapGeneration.c biome.h
	gcc -Wall -Werror -ggdb mapGeneration.c -c

biome.o: biome.c biome.h
	gcc -Wall -Werror -ggdb biome.c -c




clean:
	rm mapGen mapGeneration.o biome.o