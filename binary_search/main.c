/*
    Author: Botan Celik
    Date: 21.11.2020
    Program: binary search
    Purpose: A search program to find a word in a word buffer.
    Github-Rep.: https://github.com/TheBloodyAmateur/SchoolProjects/binary_search

    Comment: The programm does not work. Every time the programm is executed the following error occurs:

    "Segmentation error (core dumped)"

    Besides that, the programm does not store the
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

char findItem(char* input)
{
    int first = 0, middle;

    int fd = open("wortbuffer",O_RDONLY);

    //Get the size of the wordbuffer file
    struct stat buffersize;
    fstat(fd, &buffersize);

    char *buffer = malloc(buffersize.st_size);

    //Store words in the buffer
    read(fd,buffer,buffersize.st_size);

    int last = buffersize.st_size - 1;


    while(first <= last)
    {
        //Define new middle point
        middle = (first+last)/2;

        if(strcmp(buffer[middle],input)==0)
        {
            return input;
        }
        else if(strcmp(buffer[middle],input) > 0)
        {
            last = middle - 1;
        }
        else
        {
            last = middle + 1;
        }
    }
}

int main()
{
    for (;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;
        if (!strlen(input)) break;

        struct timeval tv_begin, tv_end, tv_diff;

        gettimeofday(&tv_begin, NULL);
        void *res = findItem(input);// wie auch immer
        gettimeofday(&tv_end, NULL);
        timersub(&tv_end, &tv_begin, &tv_diff);

        if (res != NULL)
        {
            printf("found");
        }
        else
        {
            printf("not found");
        }

        printf(" in (%ld seconds %ld microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec);
    }
    return 0;
}
