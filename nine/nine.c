#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#define OUTPUT_LTH 13
#define OUTPUT_CHAR "cdddddcdddddcsbbbbbsbbbbbssbcdddcdddcbssbsbbbsbbbsbssbsbcdcdcbsbssbsbsbbbsbsbscdcdcbbbcdcdcsbsbsbbbsbsbssbsbcdcdcbsbssbsbbbsbbbsbssbcdddcdddcbssbbbbbsbbbbbscdddddcdddddc"
#define sizeofstring 50
#define putexample "p-0-0"
#define moveexample "m-0-0,0-0"
#define removeexample "r-0-0"
#define mapping "111213212223313233182838342414373635272625171615"
#define lengthofmapping 48
#define inputlocateerror "The Location Does Not Exit"
#define greating "\n===Nine chess===\n"
#define pleaseputyourchest "Enter where to put your chest:\n"
#define player1 "player1"
#define player2 "player2"
#define thisisyourturn "This is your turn:"

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

int fori;
int blankloop;
void forireset() { fori = 0; }
void inputerror() { printf("Input Error!(do again!)"); }
int inmod(int mymod);
int put(int locate); /*translate locate=(x,y) -> need input to (y,x)*/
int currentplayer = 1;
void output_chart(char *strin);
void whoisplayer();
int data[lengthofmapping / 2] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int dataisfull();
int returnlocate(int yx);
int thisisforprintindex = 0;
int givethecofprint();
void viewrawdata();
int power(int tar, int i);
void nextplayer();

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

int main()
{
    printf("%s", greating);
    while (dataisfull() != 1)
    {
        whoisplayer();
        printf("%s", pleaseputyourchest);
        blankloop = 0;
        while (put(inmod(1)) == -1)
        {
            if (blankloop == 0)
            {
                blankloop++;
                blankloop--;
            }
            printf("%s", inputlocateerror);
            blankloop++;
        }
        output_chart(OUTPUT_CHAR);
        nextplayer();
    }

    return 0;
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

int put(int locate)
{
    //printf("locate:%d\n",locate);
    int place = returnlocate(locate);
    //printf("place:%d\n",place);
    if (place == -1)
    {
        return -1;
    }
    data[place] = currentplayer;
    return 0;
}

void output_chart(char *strin)
{
    char *str = malloc((int)pow(OUTPUT_LTH, 2));
    strcpy(str, strin);
    int i;
    int k;
    for (i = 0; i < OUTPUT_LTH; i++)
    {
        for (k = 0; k < OUTPUT_LTH; k++)
        {
            switch ((int)str[i * OUTPUT_LTH + k])
            {
            case (int)'c':
                printf("%d", givethecofprint());
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
        }
        printf("\n");
    }
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
int returnlocate(int yx)
{
    int y = yx / 10;
    int x = yx % 10;
    int a = 0;
    int b = 0;
    int locateat;
    int i;

    for (i = 0; i < lengthofmapping; i = i + 2)
    {
        a = ((int)mapping[i]) - ((int)'0');
        b = ((int)mapping[i + 1]) - ((int)'0');
        locateat = i / 2;
        if ((a == x) && (b == y))
        {
            return locateat;
        }
    }
    return -1;
}
int givethecofprint()
{
    if (thisisforprintindex == (lengthofmapping / 2) - 1)
    {
        thisisforprintindex = 0;
    }
    thisisforprintindex++;
    return data[thisisforprintindex - 1];
}
int dataisfull()
{
    int i;
    int all = 1;
    for (i = 0; i < lengthofmapping / 2; i++)
    {
        if (data[i] == 0)
        {
            all *= 0;
        }
        else
        {
            all *= 1;
        }
    }
    return all;
}
void whoisplayer()
{
    int nousefordefault = 0;
    printf("%s", thisisyourturn);
    switch (currentplayer)
    {
    case 1:
        printf("%s", player1);
        break;
    case 2:
        printf("%s", player2);
        break;

    default:
        nousefordefault++;
        nousefordefault--;
        break;
    }
    printf("\n");
}
int power(int tar, int i)
{
    int buf = tar;
    int k;
    if (i == 0)
    {
        return 1;
    }
    for (k = 0; k < i - 1; k++)
    {
        tar *= buf;
    }
    return tar;
}

void viewrawdata()
{
    printf("\n");
    int i;
    for (i = 0; i < lengthofmapping / 2; i++)
    {
        printf("%d", data[i]);
        if ((((i + 1) % 3) != 0) && ((i + 1) != 12))
        {
            printf("\n");
        }
    }
}

void nextplayer()
{
    if (currentplayer == 1)
    {
        currentplayer++;
    }
    else
    {
        currentplayer--;
    }
}