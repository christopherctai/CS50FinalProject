#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float averagewordlength(string L);
float averagesentencenumber(string S);

int main(void)
{
    string text = get_string("Text: ");
    float index = 0.0588 * averagewordlength(text) - 0.296 * averagesentencenumber(text) - 15.8;
    int x = round(index);
    if (x > 15)
    {
        printf("Grade 16+\n");
    }
    else if (x < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", x);
    }
}

float averagewordlength(string L)
{
    float numberofwords = 1;
    float numberofletters = 0;

    for (int i = 0, n = strlen(L); i < n; i++)
    {
        if (L[i] == ' ')
        {
            numberofwords++;
        }
    }

    for (int j = 0, n = strlen(L); j < n; j++)
    {
        if (isupper(L[j]) || islower(L[j]))
        {
            numberofletters++;
        }
    }

    float averageletters = (numberofletters / numberofwords) * 100.0;

    return averageletters;
}


float averagesentencenumber(string S)
{
    float numberofwords = 1;
    float numberofsentences = 0;

    for (int i = 0, n = strlen(S); i < n; i++)
    {
        if (S[i] == ' ')
        {
            numberofwords++;
        }
    }

    for (int j = 0, n = strlen(S); j < n; j++)
    {
        if (S[j] == '.' || S[j] == '!' || S[j] == '?')
        {
            numberofsentences++;
        }
    }

    float averagesentences = (numberofsentences / numberofwords) * 100;

    return averagesentences;
}
