mapGeneration: mapGeneration.c biome.h
	gcc -Wall -Werror -ggdb mapGeneration.c -o mapGen

clean:
	rm mapGe