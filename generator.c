#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int CountOfNumbers;
    if(argv[1] != NULL)
        CountOfNumbers = atoi(argv[1]);
    else
        scanf("%d",&CountOfNumbers);
    
    FILE *f = fopen("data.txt", "w+");

    if (f == NULL)
    {
        puts("Cannot create/open file");
        return 0;
    }
    int MinusRandom;
    int ZeroCounter = 0;
    for (int i = 0; i < CountOfNumbers; i++)
    {
        MinusRandom = 0;
        while(MinusRandom == 0)
            MinusRandom = -1 + rand()%(1-(-1)+1);
        fprintf(f, "%d ", (0 + rand()%(10000 - 0 + 1)) * MinusRandom); //[1;10000]
    }
        
    fclose(f);
    return 0;
}