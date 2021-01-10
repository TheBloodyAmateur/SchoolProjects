/*
    Author: Botan Celik
    Date: 10.01.2021
    Project: Quicksort
    File: main.c

    This programm compares the quicksort- and the bubbelsort algorithm and shows how fast each algorithm is.
    Both algorithms need to sort a array with 10, 100, 1000, 10000, 100000 elements

*/
//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

// creates a array of size size and fills it with random ints in range 0 to max_int
int *create_array(int size, int max_int)
{
	int *b = (int*)malloc(size * sizeof(int));

	for (int i=0; i<size; i++) {
		b[i] = rand() % max_int;
	}

	return b;
}

int split(int *a, int left, int right)
{
    int i = left;
    int j = right - 1;
    int pivot = a[right];
    int temp = 0;

    while(i < j)
    {
        //Search from left to right a element, which is >= the pivot element
        while(i < right && a[i] < pivot)
        {
            i++;
        }

        //Search from right a element which is smaller than the pivot element
        while (j > left && a[j] >= pivot)
        {
            j--;
        }

        if(i < j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    //Locates the new pivot element and passes the value to the next run
    if(a[i] > pivot)
    {
        temp = a[i];
        a[i]= a[right];
        a[right] = temp;
    }

    return i;
}

void quicksort(int *a, int left, int right)
{
    if(left < right)
    {
        int splitter = split(a, left, right);
        //After the elements of each side are sorted the quicksort function is used on each side
        quicksort(a, left, splitter-1);
        quicksort(a, splitter+1, right);
    }
}

void bubblesort(int *a, int size)
{
    int temp = 0;

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j]= a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

int main()
{
    int elements[5] = {10,100,1000,10000,100000};

    printf("==============================");
    printf("\nQuicksort:\n");

    for(int i = 0; i < 5; i++)
    {
        // create random ints based in current time
        srand(time(NULL));
        int *arrayOne = create_array(elements[i], elements[i]);

        struct timeval tv_begin, tv_end, tv_diff;
        gettimeofday(&tv_begin, NULL);

        quicksort(arrayOne, 0, elements[i]-1);

        gettimeofday(&tv_end, NULL);
        timersub(&tv_end, &tv_begin, &tv_diff);

        printf("With %d elements: %ld us\n", elements[i], tv_diff.tv_usec);
    }

    printf("==============================");
    printf("\nBubblesort:\n");

    for(int i = 0; i < 5; i++)
    {
        // create random ints based in current time
        srand(time(NULL));
        int *arrayOne = create_array(elements[i], elements[i]);

        struct timeval tv_begin, tv_end, tv_diff;
        gettimeofday(&tv_begin, NULL);

        bubblesort(arrayOne, elements[i]);

        gettimeofday(&tv_end, NULL);
        timersub(&tv_end, &tv_begin, &tv_diff);

        printf("With %d elements: %ld us\n", elements[i], tv_diff.tv_usec);
    }

    printf("==============================");
    return 0;
}
