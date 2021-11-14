#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, char *argv[])
{
    STATE_MACHINE_RETURN_VALUE result;
    if (argc < 2)
    {
      fprintf (stderr, "incorrect usage\n");
      exit(1);
    }

    FILE *f = NULL;
    f = fopen(argv[1], "rb");
    uint8_t character;
    if (f == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    do
    {
        character = fgetc(f);
        
        result = at_command_parse(character);

        if(result == 1)
        {
            for (int i = 0; i <= my_data.line_count; i++)
            {
                for (int j = 0; j < AT_COMMAND_MAX_LINE_SIZE; j++)
                {
                    printf("%c",my_data.data[i][j]);
                }
                printf("\n");
            }
            printf("Parsing completed -> result OK");
            return 0;
        }
        else if(result == 2)
        {
            if (character == '\r')
                printf("CR");
            else if (character == '\n')
                printf("LF");
            else
                putc(character,stdout);
            printf(" - %u: Parsing stopped -> result NOK\n",result);
            return 0;
        }

    }while(character != EOF);

    if(result == 0)
    {
        printf("Parsing reached the end of file without result");
    }
    
    fclose(f);

    
    return 0;
}