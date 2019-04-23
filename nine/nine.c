#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OUTPUT_LTH 13
#define OUTPUT_CHAR "cdddddcdddddcsbbbbbsbbbbbssbcbbbcbbbcbssbbbbbsbbbbbssbbbcdcdcbbbssbbbsbbbsbbbscdcdcbbbcdcdcsbbbsbbbsbbbssbbbcdcdcbbbssbbbbbsbbbbbssbcbbbcbbbcbssbbbbbsbbbbbscdddddcdddddc"
#define sizeofstring 50
#define putexample "p-0-0"
#define moveexample "m-0-0,0-0"
#define removeexample "r-0-0"

int fori;
void forireset() { fori = 0; }
void inputerror() { printf("Input Error!(do again!)"); }
int inmod(int mymod);
int power(int tar,int i){int buf=tar;int k;if(i==0){return 1;}for(k=0;k<i-1;k++){tar*=buf;}return tar;}
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
    int k;
	for (i = 0; i < OUTPUT_LTH ; i++){
	for( k =0;k<OUTPUT_LTH;k++){	
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
int inmod(int mymod)
{
    int returnint = 0;
    int countforweighting = 0;
    int errorcode = 0;
    char *str = malloc(sizeofstring);
    strcpy(str, "");
    scanf("%s", str);
    //printf("%s" ,str);
    switch (mymod)
    {
    case 1:

        for (forireset(); fori < sizeof(putexample); fori++)
        {
            errorcode = 1;
            if ((int)putexample[fori] == (int)'0')
            {
                if ((((int)str[fori]) >= ((int)'0')) && (((int)str[fori]) <= ((int)'9')))
                {
                    errorcode = 0;
                    returnint += ((((int)str[fori]) - ((int)'0')) * ((int)power(10, countforweighting)));
                    countforweighting++;
                }
                else
                {
                    inputerror();
                    return -1;
                }
            }
            else
            {
                if ((int)putexample[fori] == (int)str[fori])
                {
                    errorcode = 0;
                }
                else
                {
                    inputerror();
                    return -1;
                }
            }
        }

        break;
    case 2:
        for (forireset(); fori < sizeof(moveexample); fori++)
        {
            errorcode = 1;
            if ((int)moveexample[fori] == (int)'0')
            {
                if ((((int)str[fori]) >= ((int)'0')) && (((int)str[fori]) <= ((int)'9')))
                {
                    errorcode = 0;
                    returnint += ((((int)str[fori]) - ((int)'0')) * (power(10, countforweighting)));
                    //printf("cou%d\n",countforweighting);
                    countforweighting++;
                    //printf("returnint:%d,add:%d\n",returnint,((((int)str[fori]) - ((int)'0')) * ((int)power(10, countforweighting-1))));
                    //printf("returnint:%d,add:%d\n",returnint,(int)power(10, countforweighting-1));
                    //printf("returnint:%d,add:%d\n",returnint,((int)str[fori]) - ((int)'0'));
                }
                else
                {
                    inputerror();
                    return -1;
                }
            }
            else
            {
                if ((int)moveexample[fori] == (int)str[fori])
                {
                    errorcode = 0;
                }
                else
                {
                    inputerror();
                    return -1;
                }
            }
        }
        break;
    case 3:
        for (forireset(); fori < sizeof(removeexample); fori++)
        {
            errorcode = 1;
            if ((int)removeexample[fori] == (int)'0')
            {
                if ((((int)str[fori]) >= ((int)'0')) && (((int)str[fori]) <= ((int)'9')))
                {
                    errorcode = 0;
                    returnint += ((((int)str[fori]) - ((int)'0')) * ((int)power(10, countforweighting)));
                    countforweighting++;
                }
                else
                {
                    inputerror();
                    return -1;
                }
            }
            else
            {
                if ((int)removeexample[fori] == (int)str[fori])
                {
                    errorcode = 0;
                }
                else
                {
                    inputerror();
                    return -1;
                }
            }
        }
        break;

    default:
        printf("default");
        break;
    }

    return returnint;
}