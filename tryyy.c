#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define OUTPUT_LTH 13
#define OUTPUT_CHAR "cdddddcdddddcsbbbbbsbbbbbssbcbbbcbbbcbssbbbbbsbbbbbssbbbcdcdcbbbssbbbsbbbsbbbscdcdcbbbcdcdcsbbbsbbbsbbbssbbbcdcdcbbbssbbbbbsbbbbbssbcbbbcbbbcbssbbbbbsbbbbbscdddddcdddddc"

void output_chart(char *strin);
int main()
{
	//printf(OUTPUT_CHAR);
	output_chart(OUTPUT_CHAR);
	return 0;
}
void output_chart(char *strin){
	char *str=malloc((int)pow(OUTPUT_LTH,2));
	strcpy(str,strin);
	int i;
	for (i = 0; i < OUTPUT_LTH ; i++){
	for(int k=0;k<OUTPUT_LTH;k++){	
		switch((int)str[i*OUTPUT_LTH+k]){
			case (int)'c':
printf("c");
				break;
		case (int)'b':
printf(" ");
				break;
		case (int)'d':
printf("-");
				break;
		case (int)'s':
printf("|");
				break;
		}
		
	}printf("\n");}
}
