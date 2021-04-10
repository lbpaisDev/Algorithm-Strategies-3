#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int arc(int n, int h, int H)
{
    int room[n];

    int sol = 0;

    for (int i = 1; h - i >= 1; i++)
    {
        if (h + i <= H)
        {
            sol++;
        }
    }

    return sol;
}

int room_arcs(int n, int h, int H, int num_sols[n])
{
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
        int n, h, H;

        scanf("%d %d %d", &n, &h, &H);
        printf("%d\n", build_arc(n, h, H));

        t--;
    }

    return 0;
}