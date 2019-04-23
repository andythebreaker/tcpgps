#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define mapping "111213212223313233182838342414373635272625171615"
#define lengthofmapping 48
int returnlocate(int yx);
int main()
{
    printf("%d", returnlocate(51));
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
        a = ((int)mapping[i])-((int)'0');
        b = ((int)mapping[i+1])-((int)'0');
        locateat = i / 2;
        if ((a == x) && (b == y))
        {
            return locateat;
        }
    }
    return -1;
}