/* Karen Flores,
	Katherina Navarrete
*/

#include "font.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("el caracter es: %c\n", *argv[1]);
	unsigned char *p = &font[(*argv[1]*5)];
	printf("primer byte: %x\n", *p);
	printf("segundo byte: %x\n", *(p+1));
	printf("tercero byte: %x\n", *(p+2));
	printf("cuarto byte: %x\n", *(p+3));
	printf("quinto byte: %x\n", *(p+4));
	return 0;
}
