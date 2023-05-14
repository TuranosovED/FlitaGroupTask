#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int CountOfNumbers;
    int CountOfDigits;
    int countOfZero;
    puts("Enter count of numbers: ");
    scanf("%d", &CountOfNumbers);

    puts("Enter count of digits: ");
    scanf("%d", &CountOfDigits);

    puts("Enter count of Zero: ");
    scanf("%d", &countOfZero);

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
        if(ZeroCounter >= countOfZero)
        {
            while(MinusRandom == 0)
                MinusRandom = -1 + rand()%(1-(-1)+1);
        }
        else ZeroCounter++;
        fprintf(f, "%d ", (rand() % ((int)pow(10, CountOfDigits))) * MinusRandom);
    }
        
    fclose(f);
    return 0;
}