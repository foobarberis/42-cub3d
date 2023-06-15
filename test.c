#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILL 'X'
#define LINES 14



int main(void)
{
	char **map = malloc(15 * sizeof(char *));
	map[0] =	strdup("        1111111111111111111111111");
	map[1] =	strdup("        1000000000110000000000001");
	map[2] =	strdup("        1011000001110000000000001");
	map[3] =	strdup("        1001000000000000000000001");
	map[4] =	strdup("111111111011000001110000000000001");
	map[5] =	strdup("100000000011000001110111111111111");
	map[6] =	strdup("11110111111111011100000010001");
	map[7] =	strdup("11110111111111011101010010001");
	map[8] =	strdup("11000000110101011100000010001");
	map[9] =	strdup("10000000000000001100000010001");
	map[10] =	strdup("10000000000000001101010010001");
	map[11] =	strdup("1100000111010101111101111000111");
	map[12] =	strdup("11110111 1110101 101111010001");
	map[13] =	strdup("11111111 1111111 111111111111");
	map[14] = NULL;

	int x;
	int y;
	int error;

	x = 0;
	y = 0;
	error = 0;
	/* */
	get_player_pos(map, &x, &y);
	if (x < 0)
		return (printf("Player not found.\n"));
	printf("PLAYER : x = %d, y = %d\n", x, y);
	dfs(map, x, y, &error);
	if (error)
        printf("The map is open.\n");
	 else
        printf("The map is closed.\n");

	 for (int i = 0; map[i]; i++)
	 	printf("%s\n", map[i]);
	return 0;
}
