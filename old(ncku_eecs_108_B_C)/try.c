#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUTPUT_LTH 13
#define OUTPUT_CHAR "cdddddcdddddcsbbbbbsbbbbbssbcbbbcbbbcbssbbbbbsbbbbbssbbbcdcdcbbbssbbbsbbbsbbbscdcdcbbbcdcdcsbbbsbbbsbbbssbbbcdcdcbbbssbbbbbsbbbbbssbcbbbcbbbcbssbbbbbsbbbbbscdddddcdddddc"

void output_chart(char *strin);
int main()
{
	    printf(OUTPUT_CHAR);
	        output_chart(OUTPUT_CHAR);
		    return 0;
}
void output_chart(char *strin){
	    char *str=malloc(OUTPUT_LTH^2);
	        strcpy(str,strin);
		    int i;
		        for (i = 0; i < (OUTPUT_LTH^2) ; i++){
				        printf("%c",str[i]);
					    }
}
