mapGen: mapGeneration.o biome.o map.o
	gcc mapGeneration.o biome.o map.o -o mapGen

mapGeneration.o: mapGeneration.c biome.h
	gcc -Wall -Werror -ggdb mapGeneration.c -c

biome.o: biome.c biome.h
	gcc -Wall -Werror -ggdb biome.c -c

map.o: map.c map.h
	gcc -Wall -Werror -ggdb map.c -c

clean:
	rm mapGen mapGeneration.o biome.o map.o