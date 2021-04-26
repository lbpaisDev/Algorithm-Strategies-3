#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MODVAL 1000000007

int H;
int h;
int n;
int sols[500][60000][2];

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

void getlowerblocks(int limits[2], int y, int x)
{
    int init, end;

    if (y == 0)
    {
        init = -1;
        end = 0;
    }
    else if (y < h - 1)
    {
        init = y - 1;
        end = 1;
    }
    else
    {
        init = y - 1;
        end = y - h + 1;
    }

    if (init - (h - 1) * x > 0)
    {
        init = (h - 1) * x;
    }

    if (end - x < 0)
    {
        end = x;
    }

    limits[0] = init;
    limits[1] = end;
}

void getupperblocks(int limits[2], int y, int x)
{
    int init, end;

    if (y + h == H)
    {
        init = 0;
        end = -1;
    }
    else if (y + 2 * h - 1 > H)
    {
        init = y + 1;
        end = H - h;
    }
    else
    {
        init = y + 1;
        end = y + h - 1;
    }

    if (end - (h - 1) * x > 0)
    {
        end = (h - 1) * x;
    }

    limits[0] = init;
    limits[1] = end;
}

int getsols(int sols[2])
{
    return mod_add(sols[0], sols[1], MODVAL);
}

int arcs()
{
    // Caso seja possível chegar a metade do valor de n subindo apenas 1 de altura de cada vez, então há pelo menos uma solução para esse n
    // Caso não dê, não é possível chegar a esse n
    for (int i = 3; i <= n; i++)
    {
        if (h + i / 2 <= H)
        {
            sols[i - 1][0][1] = 1;
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
                if (j > 0)
                {
                    break;
                }
                continue;
            }

            // Ir buscar blocos possíveis anteriores a partir do atual e que estão acima deste
            getupperblocks(limits, j, i - 1);
            for (int k = limits[0]; k <= limits[1]; k++)
            {
                sols[i - 1][k][1] = mod_add(sols[i - 1][k][1], sols[i][j][1], MODVAL);
            }

            // Ir buscar blocos possíveis anteriores a partir do atual e que estão abaixo deste
            getlowerblocks(limits, j, i - 1);
            for (int k = limits[0]; k >= limits[1]; k--)
            {
                sols[i - 1][k][0] = mod_add(sols[i - 1][k][0], getsols(sols[i][j]), MODVAL);
            }
        }
    }

    for (int i = 1; i < h; i++)
    {
        sols[0][0][0] = mod_add(sols[0][0][0], getsols(sols[1][i]), MODVAL);
    }

    // A soma de todas as soluções vai estar no index inicial
    return sols[0][0][0];
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t > 0)
    {
        scanf("%d %d %d", &n, &h, &H);
        clock_t begin = clock();
        memset(sols, 0, 500 * 60000 * 2 * sizeof(int));
        printf("%d\n", mod_abs(arcs(), MODVAL));
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time Spent: %f seconds\n", time_spent);
        t--;
    }

    return 0;
}
