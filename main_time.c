#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//===Estrategias Algoritmicas 2020/2021
//==Problema 2
//=Afonso Magalhães 2016228735
//=Leandro Pais 2017251509

// MODVAL in case number of solutions gets too big and exceeds size of int
// All operations involved should use MODVAL
#define MODVAL 1000000007

int H; // Room height
int h; // Lego height
int n; // Room witdh

// Dp programing table
int dp[500][60000][2];

//=== Código fornecido pelos professores

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

//=== Fim do código fornecido pelos professores

// Get sum of solutions from a certain blocks (increasing and decreasing solutions)
int get_sols(int dp[2])
{
    return mod_add(dp[0], dp[1], MODVAL);
}

int arcs()
{
    // Base Case
    int last_n = 0;
    for (int i = 3; i <= n; i++)
    {
        
        // Visual explanation: https://gyazo.com/af10d2aea5cc55a44c3b2c45fc8b57b5
        if (h + i / 2 <= H) // If the blocks height can reach half of i, by increasing 1 from each block then there is at least one solution for i legos
        {
            dp[i - 1][0][1] = 1;
            dp[i - 2][1][1] = 1; // Blocks of height one can have a maximum of one decreasing solutions
            last_n = i;
        }
        else // If not there is no solution
        {
            dp[i - 1][0][1] = 0;
            dp[i - 2][1][1] = 0;
        }
    }

    if (last_n == 0) // If there's no solution for at least one value of n (i)
    {
        return 0; // Then there's no solution for the test case
    }

    
    int next_max_height = 0; // Maximum height of the blocks in i + 1
    
    for (int i = last_n - 2; i > 0; i--) // Start at the last lego where's at least one solution
    {
        int current_max_height = next_max_height + h - 1; // Maximum height the block is allowed to go, in the current value of i
        if (current_max_height > (h - 1) * i) // If in the calculated maximum height the block can't reach the starting block then it's to high
        {
            current_max_height = (h - 1) * i;
        }
        if (current_max_height > H - h) // If in the calculated maximum height the block is over the room's height then it's to high
        {
            current_max_height = H - h;
        }

        
        if (i == 1) // Calculate the increasing blocks solutions for the first possible block in the second column, since it's the only on that height that can have increasing solutions
        {
            int sols_end = h;
            if (sols_end > next_max_height)
            {
                sols_end = next_max_height;
            }

            dp[i][1][0] = 0; // Set current index increasing solutions to 0
            for (int j = 2; j <= sols_end; j++)
            {
                dp[i][1][0] = mod_add(dp[i][1][0], get_sols(dp[i + 1][j]), MODVAL);
            }
        }

        // Iterate through possible blocks in current column
        for (int j = 2; j <= current_max_height; j++)
        {
            dp[i][j][1] = dp[i][j - 1][1]; // Since consecutive blocks in the same column have similar solutions, add previous index solutions to the current block
            if (j - 1 <= next_max_height) // If previous index block has a block at the next column at the same height, add this block's solutions to the current one
            {
                dp[i][j][1] = mod_add(dp[i][j][1], dp[i + 1][j - 1][1], MODVAL);
            }
            if (j > h - 1) // If the current blocks height is bigger or equal to h, then the previous index has solutions from one block that don't belong to the current index
            {
                dp[i][j][1] = mod_sub(dp[i][j][1], dp[i + 1][j - h][1], MODVAL);
            }

            dp[i][j][0] = 0; // Set current index increasing solutions to 0
            if (j < next_max_height && j - i >= 0) // If the current index is lower than the next columns blocks max height and it can decrease to the first block in the room, then in can have increasing solutions
            {
                if (dp[i][j - 1][0] > 0) // If there is already a block in that column with increasing solutions
                {
                    dp[i][j][0] = mod_sub(dp[i][j - 1][0], get_sols(dp[i + 1][j]), MODVAL); // Add to current index increasing solutions previous index increasing solutions less the ones from the next column and same height as the current block
                    if (j + h - 1 <= next_max_height) // If the there a block in the next column and at the highest possible height from the current block
                    {
                        dp[i][j][0] = mod_add(dp[i][j][0], get_sols(dp[i + 1][j + h - 1]), MODVAL); // Add the highest possible height block from the current block solutions to the current index
                    }
                }
                else
                {
                    int upperblocks_end = j + h - 1; // Get highest possible block from the current block
                    if (upperblocks_end > next_max_height) // If higher than the highest block possible in the next column
                    {
                        upperblocks_end = next_max_height; // Substitute value calculated with next maximum height
                    }

                    for (int k = j + 1; k <= upperblocks_end; k++) // Add possible incresing solutions to current block
                    {
                        dp[i][j][0] = mod_add(dp[i][j][0], get_sols(dp[i + 1][k]), MODVAL);
                    }
                }
            }
        }

        // Update next_end
        next_max_height = current_max_height;
    }

    // Get and store all solutions in the first slot of dp matrix
    dp[0][0][0] = 0;
    for (int i = 1; i <= next_max_height; i++)
    {
        dp[0][0][0] = mod_add(dp[0][0][0], get_sols(dp[1][i]), MODVAL);
    }

    // Return solutions
    return dp[0][0][0];
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t > 0)
    {
        scanf("%d %d %d", &n, &h, &H);
        clock_t begin = clock();
        printf("%d\n", mod_abs(arcs(), MODVAL));
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time Spent: %f seconds\n", time_spent);
        t--;
    }

    return 0;
}
