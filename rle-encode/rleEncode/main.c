#include <stdio.h>
#include <stdlib.h>

#define MAX_RLEN 42

//Functions
char* encode();

int main(int argc, char **argv)
{
    char str[MAX_RLEN];

    do{
        if(fgets(str, MAX_RLEN, stdin) == NULL) break;
		str[MAX_RLEN-1] = 0;    // TODO: is this really needed?
		str[strlen(str)-1] = 0; // TODO: why is this here?
        char* res = encode(str);
        printf(">%s\n", res);
        free(res);              // see: malloc

    }while (strlen(str)> 1);

    return 0;
}

char* encode(char* str)
{
    int lengthString = strlen(str), j = 0, count;
    //Storage is reserved with the size 2 * MAX_RLEN
    char* res = malloc(2 * MAX_RLEN * sizeof(char));

    for(int i = 0; i < lengthString;)
    {
        res[j] = str[i];
        count = 0;

        //count the characters
        for(count = 0; res[j] == str[i]; count++, i++){}
        res[++j] = count + '0';
        j++;
    }
    //Mark the end of the array
    res[++j] = '\0';
    return res;
}
