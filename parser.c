#include "parser.h"
#include <stdio.h>

STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t crt_char)
{
    static uint8_t state = 0;
    static uint8_t col_index = 0;
    


    switch(state)
    {
        case 0:
        {
            if(crt_char == '\r')
            {
                state = 1;
                my_data.line_count = 0;
                my_data.write = 0;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 1:
        {
            if(crt_char == '\n')
            {
                state = 2;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 2:
        {
            if(crt_char == 'O')
            {
                state = 3;
                return STATE_MACHINE_NOT_READY;
            }
            else if(crt_char == 'E')
            {
                state = 7;
                return STATE_MACHINE_NOT_READY;
            }
            else if(crt_char == '+')
            {
                state = 14;
                return STATE_MACHINE_NOT_READY;
            }
        }

        case 3:
        {
            if(crt_char == 'K')
            {
                state = 4;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 4:
        {
            if(crt_char == '\r')
            {
                state = 5;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 5:
        {
            if(crt_char == '\n')
            {
                state = 6;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 6:
        {
            return STATE_MACHINE_READY_OK;
        }
        
        case 7:
        {
            if(crt_char == 'R')
            {
                state = 8;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 8:
        {
            if(crt_char == 'R')
            {
                state = 9;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 9:
        {
            if(crt_char == 'O')
            {
                state = 10;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 10:
        {
            if(crt_char == 'R')
            {
                state = 11;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 11:
        {
            if(crt_char == '\r')
            {
                state = 12;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 12:
        {
            if(crt_char == '\n')
            {
                state = 13;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 13:
        {
            return STATE_MACHINE_READY_OK;
        }

        case 14:
        {
            if((32 <= crt_char) && (crt_char <= 126))
            {
                if(col_index < AT_COMMAND_MAX_LINE_SIZE)
                {
                    if(my_data.write == 0)
                        my_data.data[my_data.line_count][col_index] = crt_char;
                    col_index++;
                }
                return STATE_MACHINE_NOT_READY;
            }
            else if(crt_char == '\r')
            {
                state = 15;
                if(col_index <= AT_COMMAND_MAX_LINE_SIZE)
                {
                    if(my_data.write == 0)
                        my_data.data[my_data.line_count][col_index] = '\0';
                    col_index = 0;
                }
                return STATE_MACHINE_NOT_READY;
            }
        }

        case 15:
        {
            if(crt_char == '\n')
            {
                state = 16;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 16:
        {
            if(crt_char == '+')
            {
                state = 14;
                
                if(my_data.line_count >= AT_COMMAND_MAX_LINES - 1)
                    my_data.write = 1;
                my_data.line_count++;
                return STATE_MACHINE_NOT_READY;
            }
            else if(crt_char == '\r')
            {
                state = 17;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        case 17:
        {
            if(crt_char == '\n')
            {
                state = 18;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }

        }

        case 18:
        {
            if(crt_char == 'O')
            {
                state = 3;
                return STATE_MACHINE_NOT_READY; 
            }
            else if(crt_char == 'E')
            {
                state = 7;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }

        default:
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
}