#include <stdio.h>
#include <stdlib.h>

#define MODVAL 1000000007

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

int build_arc(int n, int h, int H)
{
    
    return 0;
}

int main()
{
    int t;
    scanf("%d", &t);

    int n, h, H;
    for (int i = 0; i < t; i++)
    {
        scanf("%d %d %d", &n, &h, &H);
    }

    return 0;
}