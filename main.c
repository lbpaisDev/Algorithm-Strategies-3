#include <stdio.h>
#include <stdlib.h>

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

int getsols(int sols[2])
{
    return mod_add(sols[0], sols[1], MODVAL);
}

int arcs()
{
    // ----- Base Case
    int last_n = 0;
    for (int i = 3; i <= n; i++)
    {
        if (h + i / 2 <= H) // Caso seja possível chegar a metade do valor de n subindo apenas 1 de altura de cada vez, então há pelo menos uma solução para esse n
        {
            sols[i - 1][0][1] = 1;
            sols[i - 2][1][1] = 1;
            last_n = i;
        }
        else
        {
            sols[i - 1][0][1] = 0;
            sols[i - 2][1][1] = 0;
        }
    }

    if (last_n == 0)
    {
        return 0;
    }
    // -----

    int next_end = 0; // ultimo bloco possivel na coluna seguinte da sala
    for (int i = n - 2; i > 0; i--)
    {
        int end = next_end + h - 1;
        if (end > (h - 1) * i)
        {
            end = (h - 1) * i;
        }
        if (end > H - h)
        {
            end = H - h;
        }

        if (i == 1)
        {
            int sols_end = h;
            if (sols_end > next_end)
            {
                sols_end = next_end;
            }

            for (int j = 2; j <= sols_end; j++)
            {
                sols[i][j][0] = mod_add(sols[i][j][0], getsols(sols[i + 1][j]), MODVAL);
            }
        }

        for (int j = 2; j <= end; j++)
        {
            sols[i][j][1] = sols[i][j - 1][1];
            if (j - 1 <= next_end)
            {
                sols[i][j][1] = mod_add(sols[i][j][1], sols[i + 1][j - 1][1], MODVAL);
            }
            if (j > h - 1)
            {
                sols[i][j][1] = mod_sub(sols[i][j][1], sols[i + 1][j - h][1], MODVAL);
            }

            sols[i][j][0] = 0;
            if (j < next_end && j - i >= 0)
            {
                if (sols[i][j - 1][0] > 0)
                {
                    sols[i][j][0] = mod_sub(sols[i][j - 1][0], getsols(sols[i + 1][j]), MODVAL);
                    if (j + h - 1 <= next_end)
                    {
                        sols[i][j][0] = mod_add(sols[i][j][0], getsols(sols[i + 1][j + h - 1]), MODVAL);
                    }
                }
                else
                {
                    int upperblocks_end = j + h - 1;
                    if (upperblocks_end > next_end)
                    {
                        upperblocks_end = next_end;
                    }

                    for (int k = j + 1; k <= upperblocks_end; k++)
                    {
                        sols[i][j][0] = mod_add(sols[i][j][0], getsols(sols[i + 1][k]), MODVAL);
                    }
                }
            }
        }

        next_end = end;
    }

    for (int i = 1; i <= next_end; i++) // A soma de todas as soluções vai estar no index inicial
    {
        sols[0][0][0] = mod_add(sols[0][0][0], getsols(sols[1][i]), MODVAL);
    }

    return sols[0][0][0];
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t > 0)
    {
        scanf("%d %d %d", &n, &h, &H);
        printf("%d\n", mod_abs(arcs(), MODVAL));
        t--;
    }

    return 0;
}
