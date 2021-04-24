#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "time.h"

int main()
{

    time_t currtime;
    srand((unsigned)time(&currtime));

    FILE *dst;

    char *name = (char *)malloc(sizeof("teste_case_.txt") + sizeof(int));
    for (int i = 0;; i++)
    {
        sprintf(name, "teste_case_%d.txt", i);
        if (access(name, F_OK) == 0)
        {
            continue;
        }
        else
        {
            dst = fopen(name, "w");
            break;
        }
    }

    int t = rand() % 20;
    int n, h, H;

    fprintf(dst, "%d\n", t);
    for (int i = 0; i < t; i++)
    {
        n = rand() % 500;
        h = rand() % 500;
        H = rand() % 60000;

        fprintf(dst, "%d %d %d\n", n, h, H);
    }

    fclose(dst);
    free(name);
    return 0;
}