#include <stdio.h>
#include <cs50.h>

long checkthesum (long x);

int main (void)
{
    long answer;
    int checksum;

    // Prompt user for credit card number until last digit of checksum is 0
    do
    {
        answer = get_long ("Number: ");
    }
    while (answer < 0);

    long z = checkthesum(answer);

    if (z == 0)
    {
        if ((answer / 10000000000000) % 100 == 34 || (answer / 10000000000000) % 100 == 37)
        {
            printf("AMEX\n");
        }
        else if ((answer / 100000000000000) % 100 == 51 || (answer / 100000000000000) % 100 == 52 || (answer / 100000000000000) % 100 == 53 || (answer / 100000000000000) % 100 == 54 || (answer / 100000000000000) % 100 == 55)
        {
            printf("MASTERCARD\n");
        }
        else if ((answer / 1000000000000000) % 10 == 4 || (answer / 1000000000000) % 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Define function that returns the last digit of the checksum
long checkthesum (long x)
{
    int checksum;
    int n = 0;
    int m = 0;
    int o = 0;

    while (x != 0)
    {
        long lastdigit = x % 10;
        long newanswer = (x - lastdigit) / 10;
        long secondtolastdigit = newanswer % 10;
        long newnewanswer = (newanswer - secondtolastdigit) / 10;
        n = (2 * secondtolastdigit);
        o = ((n % 10) + (n - (n % 10))/10) + o;
        m = lastdigit + m;
        x = newnewanswer;
    }

    // Add numbers and find last digit
    int p = m + o;
    checksum = p % 10;
    return checksum;
}
