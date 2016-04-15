#include <stdio.h>

int main(int argc, char *argv[])
{
	int areas[] = {10, 12, 13, 14, 20};
	areas[0] = 47;	
	
	char name[] = "Zed";
	
	name[0]=4;
	char full_name[] = { 'Z', 'e', 'd', ' ', 'A', '.'};

	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of an areas (int[]): %ld\n", sizeof(areas));
	
	printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
	
	printf("The first areas is %d, the 2nd %d.\n", areas[19], areas[1]);
	
	printf("The size of a char: %ld\n", sizeof(char));
	
	printf("The size of name (char[]): %ld\n", sizeof(name));
	
	printf("The number of chars: %ld\n", sizeof(name)/ sizeof(char));
	
	printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
	
	printf("The numbe of chars: %ld\n", sizeof(full_name) / sizeof(char));
	
	printf("name=\"%s\" and full_name=\"%s\"\n",name, full_name);
	
	return 0;
}
