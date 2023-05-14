#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define SIZE 1000
#define swap(a, b , type) type c = a; \
                          a = b;      \
                          b = c;
int main()
{
    struct timeval start, end;
    int mas[SIZE];
    FILE *f = fopen("data.txt", "r");
    int value;
    int i = 0;

    for (int i = 0; (fscanf(f, "%d", &value) != EOF); i++)
        mas[i] = value;

    fclose(f);

    int left = 0;
    int right = SIZE - 1;
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

    for(int i =0;i<SIZE;i++)printf("%d ",mas[i]);

    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("\nThe elapsed time is %d seconds and %d micros\n", seconds, micros);

    return 0;
}