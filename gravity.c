#include <stdio.h>
#include <stdlib.h>
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

int MaxInMas(int *mas,int size)
{
    int max = 0;
    for (int i = 0; i < size; i++) //определение максимального числа
        if (mas[i] > max)
            max = mas[i];
    return max;
}

int MinInMas(int *mas, int size)
{
    int min = 214748364;
    for (int i = 0; i < size; i++) //определение минимального числа
        if (mas[i] < min)
            min = mas[i];
    return min;
}

int main()
{

    int size = Filelen();
    struct timeval start, end;
    int *mas = malloc(sizeof(int) *size);
    FILE *f = fopen("data.txt", "r");
    
    int value;
    int countOfPositive = 0;
    int countOfNegative = 0;

    for (int i = 0; (fscanf(f, "%d", &value) != EOF); i++) //заполнение массива входных данных
    {
        mas[i] = value;
        if(value >= 0)countOfPositive++;
        else countOfNegative++;
    }

    int max = MaxInMas(mas,size);
    int min = MinInMas(mas,size);
    
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

    int heightCounter;
    gettimeofday(&start, NULL);

    //PrintAbacus(abacusPositive,max,countOfPositive);
    //PrintAbacus(abacusNegative,abs(min),countOfNegative);
    
    for(int j =0;j<max;j++)
    {
        heightCounter = 0;
        for(int i =0;i<countOfPositive;i++) //считаем кол-во бусинок в столбце
        {
            if(abacusPositive[i][j] == 1)
            {
                heightCounter++;
                abacusPositive[i][j] = 0;
            }
        }
        for(int i =countOfPositive-1;i>=0;i--) //сортируем гравитацией
        {
            if(heightCounter>0)
            {
                abacusPositive[i][j]=1;
                heightCounter--;
            }
            else break;
        }
    }
    
    for(int j =0;j<abs(min);j++)
    {
        heightCounter = 0;
         
        for(int i =0;i<countOfNegative;i++) //считаем кол-во бусинок в столбце
        {
            if(abacusNegative[i][j] == 1)
            {
                heightCounter++;
                abacusNegative[i][j] = 0;
            }
        }
        for(int i =countOfNegative-1;i>=0;i--) //сортируем гравитацией
        {
            if(heightCounter>0)
            {
                abacusNegative[i][j]=1;
                heightCounter--;
            }
            else break;
        }
       
    }
    //PrintAbacus(abacusPositive,max,countOfPositive);
    //PrintAbacus(abacusNegative,abs(min),countOfNegative);
    
    gettimeofday(&end, NULL);

    heightCounter = 0;
    int counter;

    for(int i = countOfNegative - 1;i>=0;i--)
    {
        counter = 0;
        for(int j =0;j<abs(min);j++)
        {
            if(abacusNegative[i][j] == 1)counter++;
            else break;
        }
        mas[heightCounter++] = counter * (-1);
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
        mas[heightCounter++] = counter;
    }

    // for(int i =0;i<size;i++)
    //     printf("%d: %d\n",i+1,mas[i]);

    long micros = (((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Gravity: The elapsed time is %d micros", micros);
    putchar('\n');

    return 0;
}