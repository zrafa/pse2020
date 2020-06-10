#include<string.h>
char arr[500];
const char *punt = "Hello";

int main()
{
	char a[] = "Hello";
	char b[] = "World";
	char resultado [10];
	strcpy(resultado,a);
	strcat(resultado," ");
	strcat(resultado,b);
}
