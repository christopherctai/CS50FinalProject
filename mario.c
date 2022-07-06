#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //define n as an integer
    int n;
    //checks so n is between 1 and 8
    do
    {
        n = get_int("Height? ");
    }
    while (n < 1 || n > 8);

    //print the rows for pyramids one row at a time
    for (int i = 0; i < n; i++)
    {
        //prints the spaces before the first triangle
        for (int j = n - i; j > 1; j--)
        {
            printf(" ");
        }
        //prints the first triangle.
        for (int k = n; k >= n - i; k--)
        {
            printf("#");
        }
        //prints the spaces between the triangles
        printf("  ");
        //prints the second triangle
        for (int l = n; l >= n - i; l--)
        {
            printf("#");
        }
        //prints space for next row
        printf("\n");
    }
}