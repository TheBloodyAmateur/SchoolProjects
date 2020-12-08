/*
    Author: Botan Celik
    Date: 21.11.2020
    Program: binary_search
    Purpose: A search program to find a word in a word buffer.
    Github-Rep.: https://github.com/TheBloodyAmateur/SchoolProjects/binary_search

    Comment: The programm does not work. Every time the programm is executed the following error occurs:

    "Segmentation error (core dumped)"

    The problem is, that the buffer points on single characters, for the comparison with the user input a pointer is needed
    which points on single words. But it wasn't clear on how to do it.

    Shoutout to Lukas K. for showing me how to store the words in the pointer/buffer.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

//Global variable
char* buffer;
int last, first = 0, middle;

char binary_search(char* input)
{
    while(first <= last)
    {
        //Define new middle point
        middle = (first+last)/2;

        //If the word in the middle of the range the word was found and the input string is send back
        //printf("%d\n",last);
        if(strcmp(buffer[middle],input)==0)
        {
            return middle;
        }
        //If it's not the same the range is reduced
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
    int fd = open("wortbuffer",O_RDONLY);

    //Get the size of the wordbuffer file
    struct stat buffersize;
    fstat(fd, &buffersize);

    char *buffer = malloc(buffersize.st_size);

    //Store words in the buffer
    read(fd,buffer,buffersize.st_size);

    //Get the position of the last element
    last = buffersize.st_size - 1;

    for (;;)
    {
        char input[100];

        printf("Word:");
        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;
        if (!strlen(input)) break;

        struct timeval tv_begin, tv_end, tv_diff;

        gettimeofday(&tv_begin, NULL);
        void *res = binary_search(input);// wie auch immer
        gettimeofday(&tv_end, NULL);
        timersub(&tv_end, &tv_begin, &tv_diff);

        printf("3\n");

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
