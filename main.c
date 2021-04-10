#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODVAL 1000000007

int n, h, H;

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

int arc()
{
    int sol = 0;

    for (int i = 1; i < n; i++)
    {
        if (h + i <= H && h - i >= 1)
        {
            sol++;
        }
    }

    return sol;
}

int room_arcs()
{
    int num_sols[n];
    memset(num_sols, -1, sizeof(int) * n);

    num_sols[2] = mod_abs(arc(n, h, H), MODVAL);

    for (int i = 3; i < n; i++)
    {
        num_sols[i] = mod_add(arc(i + 1, h, H), num_sols[i - 1], MODVAL);
    }

    return num_sols[n - 1];
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t > 0)
    {

        scanf("%d %d %d", &n, &h, &H);
        printf("%d\n", room_arcs(n, h, H));

        t--;
    }

    return 0;
}