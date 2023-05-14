#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define swap(a, b , type) type c = a; \
                          a = b;      \
                          b = c;

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
    struct timeval start, end;
    int size = Filelen();
    int *mas = (int*)malloc(sizeof(int) * size);
    FILE *f = fopen("data.txt", "r");
    int value;
    int i = 0;

    for (int i = 0; (fscanf(f, "%d", &value) != EOF); i++)
        mas[i] = value;

    fclose(f);

    int left = 0;
    int right = size - 1;
    int buffer; //так как после первого прохода наиб элемент будет справа, а наим слева, то сужаем границы

    gettimeofday(&start, NULL);

    while(left<right)
    {
        for(int i =left;i<right;i++)
        {
            if(mas[i] > mas[i+1])
            {
                swap(mas[i],mas[i+1],int);
                buffer = i;
            }
        }
        right = buffer;
        for(int i = right;i>left;i--)
        {
            if(mas[i] < mas[i-1])
            {
                swap(mas[i],mas[i-1],int);
                buffer = i;
            }
        }
        left = buffer;
    }
    
    gettimeofday(&end, NULL);

    for(int i =0;i<size;i++)printf("%d: %d\n",i+1,mas[i]);

    long micros = (((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    
    printf("\nThe elapsed time is %d micros\n", micros);

    return 0;
}