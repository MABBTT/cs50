#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    int n;
    do
    {
        n = get_int("Height Positive Integer between 1 and 8: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        for (int j = (n-1); j > i; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int h = 0; h <= i; h++)
        {
            printf("#");
        }
        printf("\n");
    }
}
