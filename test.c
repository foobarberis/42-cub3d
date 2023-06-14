#include <stdio.h>

int main(void)
{

	char *s = "hello world!";
	char *p;
	char *arr[3];

	p = s;
	arr[0] = p++;
	arr[1] = p++;
	arr[2] = p++;

	printf("%s\n%s\n%s\n", arr[0], arr[1], arr[2]);
}
