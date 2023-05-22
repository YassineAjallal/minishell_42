#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int x;
	char *str;

	str = malloc(6);
	x = read(0, str, 5);
	str[5] = 0;
	printf("%s\n", str);
	return 0;
}