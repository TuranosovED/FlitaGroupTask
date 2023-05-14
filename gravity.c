#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void PrintAbacus(int **mas,int width,int height)
{
    for(int i =0;i<height;i++)
    {
        for(int j = 0;j<width;j++)
            printf("%d",mas[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

int Filelen()
{
    FILE *f = fopen("data.txt", "r");
    int len=0;
    int value;
    while(fscanf(f, "%d", &value) != EOF)
        len++;
    return len;
}

int main()
{
    int size = Filelen();
    struct timeval start, end;
    int *mas = malloc(sizeof(int) *size);
    FILE *f = fopen("data.txt", "r");
    int value;
    int i = 0;

    int countOfPositive = 0;
    int countOfNegative = 0;

    for (int i = 0; (fscanf(f, "%d", &value) != EOF); i++) //заполнение массива входных данных
    {
        mas[i] = value;
        if(value >= 0)countOfPositive++;
        else countOfNegative++;
    }

    fclose(f);
    int min = 214748364;
    int max = 0;

    for (int i = 0; i < size; i++) //определение минимального числа
        if (mas[i] < min)
            min = mas[i];

    for (int i = 0; i < size; i++) //определение максимального числа
        if (mas[i] > max)
            max = mas[i];

    int **abacusPositive = (int **)malloc(countOfPositive * sizeof(int *)); //выделение памяти под счеты
    int **abacusNegative = (int **)malloc(countOfNegative * sizeof(int *)); //выделение памяти под счеты

    for (int i = 0; i < countOfPositive; i++) //выделение памяти под счеты
        abacusPositive[i] = (int *)calloc(max, sizeof(int));

    for (int i = 0; i < countOfNegative; i++)
        abacusNegative[i] = (int *)calloc(abs(min), sizeof(int)); //выделение памяти под счеты

    int PossitiveCounter = 0; //счетчики под каждый из абаков
    int Negativecounter = 0;

    for (int i = 0; i < size; i++)     //заполнение счет
    {
        if(mas[i] >= 0)
        {
            for (int j = 0; j < mas[i]; j++)
                abacusPositive[PossitiveCounter][j] = 1;
            PossitiveCounter++;
        }
        else
        {
            for (int j = 0; j < abs(mas[i]); j++)
                abacusNegative[Negativecounter][j] = 1;
            Negativecounter++;
        }
    }   
        
    //PrintAbacus(abacusNegative,abs(min),countOfNegative);
    //PrintAbacus(abacusPositive,max,countOfPositive);

    gettimeofday(&start, NULL); //начало отсчета

    for(int count = 0;count < countOfPositive-1;count++)
    {
        for(int i =0;i<max;i++)
        {
            for(int j = countOfPositive-1;j>=0;j--)
            {
                if(abacusPositive[j][i] != 0)
                {
                    if((j+1 < countOfPositive )&& (abacusPositive[j+1][i] == 0))
                    {
                        abacusPositive[j][i] = 0;
                        abacusPositive[j+1][i] = 1;
                    }
                }
            }
        }
    }
    
    for(int count = 0;count < countOfNegative-1;count++)
    {
        for(int i =0;i<abs(min);i++)
        {
            for(int j = countOfNegative-1;j>=0;j--)
            {
                if(abacusNegative[j][i] != 0)
                {
                    if((j+1 < countOfNegative )&& (abacusNegative[j+1][i] == 0))
                    {
                        abacusNegative[j][i] = 0;
                        abacusNegative[j+1][i] = 1;
                    }
                }
            }
        }
    }

    //PrintAbacus(abacusNegative,abs(min),countOfNegative);
    //PrintAbacus(abacusPositive,max,countOfPositive);
    gettimeofday(&end, NULL);

    int counter;
    int Cyclecounter = 0;

    for(int i = countOfNegative - 1;i>=0;i--)
    {
        counter = 0;
        for(int j =0;j<abs(min);j++)
        {
            if(abacusNegative[i][j] == 1)counter++;
            else break;
        }
        mas[Cyclecounter++] = counter * (-1);
    }
    
    counter = 0;

    for(int i = 0;i < countOfPositive;i++)
    {
        counter = 0;
        for(int j =0;j<max;j++)
        {
            if(abacusPositive[i][j] == 1)counter++;
            else break;
        }
        mas[Cyclecounter++] = counter;
    }

    // for(int i =0;i<size;i++)
    //     printf("%d: %d\n",i+1,mas[i]);

    long micros = (((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Gravity: The elapsed time is %d micros", micros);
    putchar('\n');
    return 0;
}