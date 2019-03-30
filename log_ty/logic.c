
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10//make string



void substr(char *dest, const char* src, unsigned int start, unsigned int cnt) {
	strncpy(dest, src + start, cnt);
	dest[cnt] = 0;
}
int op(int sha,int shb,char *ship){

	char *qip=malloc(LEN+1);
	strcpy(qip,ship);
	printf("%s\n",qip);

	
}

int main()

{


return 0;

}
