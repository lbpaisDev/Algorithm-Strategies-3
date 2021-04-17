#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODVAL 1000000007

int H;
int h;
int n;
int ***sols;

int mod_abs(int a, int mod)
{
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod)
{
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod)
{
    return mod_add(a, -b, mod);
}

void getlowerblocks(int limits[2], int x, int y)
{
    if (y == 0 || y - x < 1)
    {
        limits[0] = 0;
        limits[1] = -1;
    }
    else
    {
        if(y > h - 1)
        {
            limits[0] = y - h + 1;
        }
        else
        {
            limits[0] = 0;
        }
        
        limits[1] = y - 1;
    }
}

void getupperblocks(int limits[2], int x, int y)
{
    if (y == H - h || y - x * (h - 1) > 0)
    {
        limits[0] = 0;
        limits[1] = -1;
    }
    else
    {
        if(y <= H - 2 * h)
        {
            limits[1] = y + h - 1;
        }
        else
        {
            limits[1] = H - h;
        }
        
        limits[0] = y + 1;
    }
}

int getsols(int sols[2])
{
    return sols[0] + sols[1];
}

int arcs()
{
    // Caso seja possível chegar a metade do valor de n subindo apenas 1 de altura de cada vez, então há pelo menos uma solução para esse n
    // Caso não dê, não é possível chegar a esse n
    // -----> Tem de se fazer um caso especial para h = 2
    for (int i = 3; i <= n; i++)
    {
        //printf("Sols: %d\n", h + i / 2);
        if (h + i / 2 <= H)
        {
            sols[i-1][0][1] = 1;
        }
    }
   
    int limits[2];
    
    // Percorrer matriz do fim ao início
    for (int i = n - 1; i > 1; i--)
    {
        for (int j = 0; j < H; j++)
        {
            // Se o index não tiver nenhuma solução e for maior que 0 quer dizer que ja não há mais blocos nesse valor de i (penso eu)
            if (getsols(sols[i][j]) == 0)
            {
                if(j > 0)
                {
                    break;
                }
                continue;
            }
            
            // Ir buscar blocos possíveis anteriores a partir do atual e que estão acima deste
            getupperblocks(limits, i, j);
            //printf("I: %d\tJ: %d\tUPPER_BAIXO: %d\tUPPER_CIMA: %d\n", i, j, limits[0], limits[1]);
            for (int k = limits[0]; k <= limits[1]; k++)
            {
                sols[i - 1][k][1] += sols[i][j][1];
            }

            // Ir buscar blocos possíveis anteriores a partir do atual e que estão abaixo deste
            getlowerblocks(limits, i, j);
            //printf("I: %d\tJ: %d\tLOWER_BAIXO: %d\tLOWER_CIMA: %d\n", i, j, limits[0], limits[1]);
            for (int k = limits[0]; k <= limits[1]; k++)
            {
                sols[i - 1][k][0] += getsols(sols[i][j]);
            }
        }
    }

    for(int i = 0; i < H; i++)
    {
        sols[0][0][0] += getsols(sols[1][i]);
    }

    // A soma de todas as soluções vai estar no index inicial
    return getsols(sols[0][0]);
}

void set_sols()
{
    sols = (int ***)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        sols[i] = (int **)malloc(H * sizeof(int *));
        for (int j = 0; j < H; j++)
        {
            sols[i][j] = (int *)calloc(2, sizeof(int));
        }
    }
}

void free_sols()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < H; j++)
        {
            free(sols[i][j]);
        }
        free(sols[i]);
    }
    free(sols);
}

void print_sols()
{
    for(int j = H - 1; j >= 0; j--)
    {
        for(int i = 0; i < n; i++)
        {
            printf("[%d %d] ", sols[i][j][0], sols[i][j][1]);
        }
        printf("\n");
    }
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t > 0)
    {
        scanf("%d %d %d", &n, &h, &H);
        set_sols();
        printf("%d\n", mod_abs(arcs(), MODVAL));
        print_sols();
        free_sols();
        t--;
    }

    return 0;
}
