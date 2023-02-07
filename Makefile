worldGen: mapGeneration.o biome.o map.o worldGeneration.o
	gcc worldGeneration.o mapGeneration.o biome.o map.o -o worldGen


worldGeneration.o: worldGeneration.c 
	gcc -Wall -Werror -ggdb worldGeneration.c -c


mapGeneration.o: mapGeneration.c mapGeneration.h
	gcc -Wall -Werror -ggdb mapGeneration.c -c

biome.o: biome.c biome.h
	gcc -Wall -Werror -ggdb biome.c -c

map.o: map.c map.h
	gcc -Wall -Werror -ggdb map.c -c

clean:
	rm worldGen mapGeneration.o biome.o map.o worldGeneration.o