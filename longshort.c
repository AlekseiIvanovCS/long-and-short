#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Convert a string to uppercase
void upperCase(char *str) {
    for(int i = 0; str[i]; i++) 
    {
        do
        {
            str[i] = str[i] - ('a' - 'A');
        }
        while(str[i] >= 'a' && str[i] <= 'z');
    }
}

// Convert a string to lowercase
void lowerCase(char *str) 
{
    for(int i = 0; str[i]; i++) 
    {
        do
        {
            str[i] = str[i] + ('a' - 'A');
        }
        while(str[i] >= 'A' && str[i] <= 'Z');
    }
}

int main(int argc, char *argv[]) 
{
    int shortL = 0, longL = 0;
    char line[256];
    
    if(argc != 4)
    {
        printf("Missing reading or writing file\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        exit(1);
    }

    FILE *shortFile = fopen(argv[2], "w");
    if(!shortFile)
    {
        printf("Error: Could not open file %s\n", argv[2]);
        fclose(file);
        exit(1);
    }

    FILE *longFile = fopen(argv[3], "w");
    if(!longFile)
    {
        printf("Error: Could not open file %s\n", argv[3]);
        fclose(file);
        fclose(shortFile);
        exit(1);
    }


    while(fgets(line, sizeof(line), file)) 
    {
        line[strcspn(line, "\n")] = '\0';

        if(strlen(line) < 20)
        {
            upperCase(line);
            fprintf(shortFile, "%s\n", line);
            shortL++;
        }

        else
        {
            lowerCase(line);
            fprintf(longFile, "%s\n", line);
            longL++;
        }
    }

    fclose(file);
    fclose(shortFile);
    fclose(longFile);

    printf("%d lines written to %s\n", shortL, argv[2]);
    printf("%d lines written to %s\n", longL, argv[3]);
}