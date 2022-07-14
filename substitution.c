#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string secretcode = argv[1];
    int norepeats = 0;

    for (int i = 0, n = strlen(secretcode); i < n; i++)
    {
        if (isupper(secretcode[i]))
        {
            secretcode[i] = tolower(secretcode[i]);
        }
        else if (isalpha(secretcode[i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        norepeats = secretcode[i] + norepeats;
    }

    for (int k = 0, n = strlen(secretcode); k < n; k++)
    {
        for (int l = 1 + k, m = strlen(secretcode); l < m; l++)
        {
            if (secretcode[l] == secretcode[k])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string nocipher = get_string("plaintext: ");

    for (int j = 0, n = strlen(nocipher); j < n; j++)
    {
        if (isupper(nocipher[j]))
        {
            int upperletterposition = nocipher[j] - 'A';
            nocipher[j] = secretcode[upperletterposition];
            nocipher[j] = nocipher[j] - 32;
        }
        else if (islower(nocipher[j]))
        {
            int lowerletterposition = nocipher[j] - 'a';
            nocipher[j] = secretcode[lowerletterposition];
        }
    }

    printf("ciphertext: %s\n", nocipher);

}