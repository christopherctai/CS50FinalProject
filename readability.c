#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float averagewordlength(string L);
float averagesentencenumber(string S);

int main(void)
{
    // Get text and use functions to calculate the Coleman-Liau index of text
    string text = get_string("Text: ");
    float index = 0.0588 * averagewordlength(text) - 0.296 * averagesentencenumber(text) - 15.8;
    int x = round(index);

    // Print the corresponding Grade number
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

// Define function that calculates the average letters per 100 words
float averagewordlength(string L)
{
    float numberofwords = 1;
    float numberofletters = 0;

    // Run loop to count number of words
    for (int i = 0, n = strlen(L); i < n; i++)
    {
        if (L[i] == ' ')
        {
            numberofwords++;
        }
    }

    // Run loop to count number of letters
    for (int j = 0, n = strlen(L); j < n; j++)
    {
        if (isupper(L[j]) || islower(L[j]))
        {
            numberofletters++;
        }
    }

    // Calculate average number of letters per 100 words
    float averageletters = (numberofletters / numberofwords) * 100.0;

    return averageletters;
}

// Define function that calculates the average sentences per 100 words
float averagesentencenumber(string S)
{
    float numberofwords = 1;
    float numberofsentences = 0;

    // Run loop to count the number of words
    for (int i = 0, n = strlen(S); i < n; i++)
    {
        if (S[i] == ' ')
        {
            numberofwords++;
        }
    }

    // Run loop to count the number of sentences
    for (int j = 0, n = strlen(S); j < n; j++)
    {
        if (S[j] == '.' || S[j] == '!' || S[j] == '?')
        {
            numberofsentences++;
        }
    }

    // Calculate the average sentences per 100 words
    float averagesentences = (numberofsentences / numberofwords) * 100;

    return averagesentences;
}
