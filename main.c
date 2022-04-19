#include <stdio.h>
#include <stdlib.h>

FILE* openfile(const char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Foner read error!\n");
        exit(1);
    }
    return file;
}


void scan(char * commands, int size) {
    int i = 0;
    int brc = 0;
    char arr[30000];
    for(int index = 0; index < size; index++) {
        switch (commands[index]) {
         case ' ':
            break;

         case '\t':
            break;

         case '\n':
            break;
         case '>':
            i++;
            break;
        
         case '<':
            i--;
            break;
        
         case '-':
            arr[i]--;
            break;

         case '+':
            arr[i]++;
            break;
        
         case '.':
            putchar(arr[i]);
            break;
        
         case ',':
            arr[i] = getchar();
            break;

        case '[':
            if (!arr[i]) {
                ++brc;
                while (brc) {
                    ++index;
                    if (commands[index] == '[')
                        ++brc;
                    if (commands[index] == ']')
                        --brc;
                }
            }
            break;
        case ']':
            if (arr[i]) {
                if (commands[index] == ']')
                    brc++;
                while (brc) {
                    --index;
                    if (commands[index] == '[')
                        brc--;
                    if (commands[index] == ']')
                        brc++;
                }
            }
            break;
        default:
            printf("something goes wrong\n");
            break;
        }
    }
}

int main(int argc, char **argv) {
    FILE* fcommand = openfile(argv[1]);
    char * commands = (char *) calloc(30000, sizeof(char));
    int i = 0;
    for (; (commands[i] = fgetc(fcommand)) != EOF; i++);
    scan(commands, --i);
    return 0;
}