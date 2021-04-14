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

int arc(int dp[], int i)
{
    if (dp[i] != 0)
    {
        int narcs = 0;
        for (int j = 0; j < i; j++)
        {
            narcs += dp[j];
        }
        return narcs;
    }
    else
    {
    }
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t > 0)
    {
        scanf("%d %d %d", &n, &h, &H);

        int dp[n];
        memset(dp, 0, sizeof(dp));

        printf("%d\n", arc(dp));

        t--;
    }

    return 0;
}