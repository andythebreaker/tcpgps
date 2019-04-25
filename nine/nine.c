/*
 * =====NOTAM=====
 * for string => size of
 * need -1 (will auto +1 by system)
 * ===============
*/

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
#define inputlocateerror "Input Location Is Not Available\n"
#define greating "\n===Nine chess===\n"
#define pleaseputyourchest "Enter where to put your chest:\n"
#define player1 "player1"
#define player2 "player2"
#define thisisyourturn "This is your turn:"
#define finishinputallplace "\n[Finished all input.]\n"
#define linemapping ",7|12,12|16,4|11,11|19,1|10,10|22,9|13,13|18,2|5,5|8,17|20,20|23,3|15,15|24,6|14,14|21,1-2,2-3,4-5,5-6,7-8,8-9,10-11,11-12,13-14,14-15,16-17,17-18,19-20,20-21,22-23,23-24,"

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
int numbersofmappliglineNEEDtime2();
int asciitoint(int i);
int if3dot(int changedpoint);
int return4bit(int smallerthen99a, int smallerthen99b);
int givealine(int index);

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

int main()
{
    /*try*/

    /*try*/
    printf("%s", greating);
    while (dataisfull() != 1)
    {
        whoisplayer();
        printf("%s", pleaseputyourchest);
        blankloop = 0;
        int putedplace = inmod(1);
        int putinmod1 = put(putedplace);

        while (putinmod1 == -1)
        {
            printf("%s", inputlocateerror);
            printf("%s", pleaseputyourchest);
            putedplace = inmod(1);
            putinmod1 = put(putedplace);
            if (blankloop == 0)
            {
                blankloop++;
                blankloop--;
            }

            blankloop++;
        }
        output_chart(OUTPUT_CHAR);
        printf("If 3 dot happends :%d \n", if3dot(returnlocate(putedplace) + 1));
        nextplayer();
    }
    printf("%s", finishinputallplace);

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
    if (place == -1)
    {
        return -1;
    }
    if (data[place] == 0)
    {
        data[place] = currentplayer;
    }
    else
    {
        return -1;
    }

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
    if (thisisforprintindex == (lengthofmapping / 2))
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

int numbersofmappliglineNEEDtime2()
{
    int numofa = 0;
    int i;
    for (i = 0; i < ((int)sizeof(linemapping) - 1); i++)
    {
        numofa = (((int)linemapping[i] == (int)'|') || ((int)linemapping[i] == (int)'-')) ? numofa + 1 : numofa;
    }
    return numofa;
}

int asciitoint(int i)
{
    return (i - ((int)'0'));
}

int if3dot(int changedpoint)
{
    int gotcha = 0;
    int i;
    for (i = 0; i < ((int)sizeof(linemapping) - 1); i++)
    {
        //printf("cp1!!!");
        int whatiwant = (((int)linemapping[i] == (int)'|') || ((int)linemapping[i] == (int)'-')) ? 1 : 0;
        if (whatiwant)
        {
            //printf("cp2!!!");
            //printf("changepoints=:%d,###%d",changedpoint,i);

            int givealine4bit = givealine(i);
            //printf("\n<intgivealine4bitgivealine(i)>;%d\n",givealine4bit);

            int parenum1 = givealine4bit / 100;
            int parenum2 = givealine4bit % 100;
            //printf("4bits:%d,%d<linemapping[i]:%c>",parenum1,parenum2,linemapping[i]);

            if ((parenum1 == changedpoint) || (parenum2 == changedpoint))
            {
                //printf("cp3!!!");
                int stat = (int)linemapping[i];
                int k;
                for (k = 0; k < ((int)sizeof(linemapping) - 1); k++)
                {
                    //printf("cp4!!!");
                    int fit = ((int)linemapping[k] == stat) ? 1 : 0;
                    if (fit)
                    {
                        //printf("cp5!!!");
                        //printf("\npm:%d;%d\n;",parenum1,parenum2);
                        int temp = givealine(k);
                        int fit1 = temp / 100;
                        int fit2 = temp % 100;
                        //printf("givelinetraceback::input<%d>;;output_a=##%d__b=##%d\n",k,fit1,fit2);
                        if (((fit1 == parenum1) || (fit2 == parenum1) || (fit1 == parenum2) || (fit2 == parenum2)) && (k != i))
                        {
                            //printf("cp6!!!");
                            int nest4[4] = {0, 0, 0, 0};
                            int nest3[3] = {0, 0, 0};
                            nest4[0] = fit1;
                            nest4[1] = fit2;
                            nest4[2] = parenum1;
                            nest4[3] = parenum2;
                            //printf("nst4<%d;%d;%d;%d;>\n", fit1, fit2, parenum1, parenum2);
                            int f;
                            for (f = 0; f < 4; f++)
                            {
                                int comp = nest4[f];
                                int ff = 0;
                                int dontdo = 1;
                                int have0 = 0;
                                while (ff < 3)
                                {
                                    if (nest3[ff] == comp)
                                    {
                                        dontdo = 0;
                                    }

                                    ff++;
                                }
                                ff = 0;
                                while (ff < 3)
                                {
                                    if (nest3[ff] == 0)
                                    {
                                        have0 = 1;
                                        break;
                                    }

                                    ff++;
                                }
                                nest3[ff] = (have0 && dontdo) ? comp : nest3[ff];
                            }
                            /*heart~for 4 word have one same pick it out and put in to 3[] fuck  me up shit*/
                            /*int forloop;
                            for (forloop = 0; forloop < 4; forloop++)
                            {
                                int forloop1;
                                int tar = nest4[forloop];
                                for (forloop1 = 0; forloop1 < 4; forloop1++)
                                {
                                    nest4[forloop] = ((tar == nest4[forloop1])&&(tar!=forloop1)) ? -1 : tar;
                                    //printf("nestU=<%d>\n",nest4[forloop]);
                                }
                                //printf("nestD=<%d>\n",nest4[forloop]);
                            }
                            int index3 = 0;
                            for (forloop = 0; forloop < 4; forloop++)
                            {
                                if (nest4[forloop] != -1)
                                {
                                    nest3[index3] = nest4[forloop];
                                    index3++;
                                    printf("nest=<%d>",nest3[index3]);
                                }
                                //printf("nestU=<%d>\n",nest4[forloop]);
                            }*/
                            int ap;
                            for (ap = 0; ap < 3; ap++)
                            {
                                //printf("==>%d", nest3[ap]);
                            }
                            //printf("\n");
                            int forloop;
                            int seeIfAllNoEqualsToCurrentPlayers = 0;
                            for (forloop = 0; forloop < 3; forloop++)
                            {
                                //printf("data:%d;cur:%d;;num:%d\n", data[nest3[forloop] - 1], currentplayer, nest3[forloop]);
                                seeIfAllNoEqualsToCurrentPlayers = (data[nest3[forloop] - 1] != currentplayer) ? seeIfAllNoEqualsToCurrentPlayers : seeIfAllNoEqualsToCurrentPlayers + 1;
                            }
                            gotcha = (seeIfAllNoEqualsToCurrentPlayers == 3) ? gotcha + 1 : gotcha;
                            //printf("checkpoint\n");
                        }
                    }
                }
            }
        }
    }
    int ifnot0return1 = (gotcha == 0) ? 0 : 1;
    return ifnot0return1;
}

int return4bit(int smallerthen99a, int smallerthen99b)
{

    int a = smallerthen99a;
    int b = smallerthen99b;

    //printf("\na:%d,b:%d\n",a,b);
    return (a * 100 + b);
}

int givealine(int index)
{
    //printf("giveline:input@@@%d\n",index);
    int indexreminder = index;
    int indexdontmove = index;
    int buf = 0;
    int matha = 0;
    int mathb = 0;
    int counter = 0;
    index--;
    buf = (int)linemapping[index];
    while (buf != ((int)','))
    {
        // printf("buf%dbuf",asciitoint(buf));
        matha += asciitoint(buf) * power(10, counter);
        counter++;
        index--;
        buf = (int)linemapping[index];
    }
    //counter = 1;
    indexreminder++;
    buf = (int)linemapping[indexreminder];
    while (buf != ((int)','))
    {
        // printf("buf%dbuf",asciitoint( buf ));
        //mathb += asciitoint(buf) * power(10, counter);
        //counter--;
        indexreminder++;
        buf = (int)linemapping[indexreminder];
    }
    counter = 0;
    indexreminder--;
    buf = (int)linemapping[indexreminder];
    //printf("pass");
    while (buf != ((int)linemapping[indexdontmove]))
    {
        // printf("buf%dbuf",asciitoint(buf));
        mathb += asciitoint(buf) * power(10, counter);
        counter++;
        indexreminder--;
        buf = (int)linemapping[indexreminder];
    }

    //printf("giveline:a:%d,b:%d\n",matha,mathb);
    return return4bit(matha, mathb);
}