#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODVAL 1000000007

int H;
int h;
int n;

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

int accept(int x,int y)
{
    if(x == 1 && y == 0) // rejection test 2: se y = 0 na segunda posição horizontal da sala então k < 3 (regra 1)
    {
        return 0;
    }

    if(x == n - 1 && y > 0) // rejection test 3: se o bloco estiver no fim da sala e a sua altura for superior a 0 (regra 2)
    {
        return 0;
    }

    int missing_space = n - 1 - x;
    if(y >= h + (missing_space - 1) * (h - 1)) // rejection test 3: se já não houver espaço suficiente para os blocos chegarem a y = 0 até ao fim da sala (regra 2)
    {
        return 0;
    }

    return 1;
}

void getlimits(int limits[2], int y, int d) {
    int init, end;

    if(y > h - 1) // se o bloco estiver numa altura superior a h - 1 
    {
        init = y - h + 1;
    }
    else
    {
        init = 0;
    }
    limits[0] = init;

    if(d == -1 || H - y == h) // se os blocos estão a descer ou chegou à máxima altura possível na sala (para a altura do bloco)
    {
        end = y - 1;
    }
    else if(H - y < 2 * h)
    {
        end = H - h;
    }
    else
    {
        end = y + h - 1;
    }

    limits[1] = end;
}

int iscached(int sols[2], int d)
{
    if(d == -1 && sols[1] != 0)
    {
        return sols[1];
    }
    
    if(d == 1 && (sols[0] != 0 || sols[1] != 0))
    {
        return sols[0] + sols[1];
    }

    return 0;
}

int arcs(int x, int y, int d, int sols[n][H][2])
{
    if(accept(x, y) == 0) // testes de rejeição
    {
        return 0;
    }

    int cached_val = iscached(sols[x][y], d);
    if(cached_val != 0) // verificar se bloco está cached
    {
        return cached_val;
    }

    if(x > 1 && y == 0) // teste de aceitação
    {
        return 1;
    }

    int limits[2];
    getlimits(limits, y, d); // calcular limites de posições do próximo bloco de modo a que os blocos atual e seguinte partilhem pelo menos 1 de altura (regra 3)

    for(int i = limits[0]; i <= limits[1]; i++)
    {
        if(i == y) // se a altura do próximo bloco for igual à do atual, rejeitar (regra 4)
        {
            continue;
        }

        if(i < y) // se a altura do próximo bloco for inferior à do atual, então chamar a função recursiva atualizando x para x + 1, y para i e direção para -1
        {
            sols[x][y][1] += arcs(x+1, i, -1, sols);
        }
        else // se a altura do próximo bloco for superior à do atual, então chamar a função recursiva atualizando x para x + 1, y para i e direção para 1
        { 
            sols[x][y][0] += arcs(x+1, i, 1, sols);
        }
    }

    return sols[x][y][0] + sols[x][y][1];
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t > 0)
    {
        scanf("%d %d %d", &n, &h, &H);
        int sols[n][H][2];
        memset(sols, 0, n * H * 2 * sizeof(int));
        printf("%d\n", mod_abs(arcs(0, 0, 1, sols), 1000000007));
        
        t--;
    }

    return 0;
}