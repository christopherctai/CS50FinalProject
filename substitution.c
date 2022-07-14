#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{

    // Check if the user is inputting exactly 2 command line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key is equal to exactly 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Define the second command line argument as a string secretcode
    string secretcode = argv[1];

    // Change the key to all lowercase letters and check to make sure that the key is only alphabetical
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
    }

    // Check to make sure there are no repeated characters
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

    // Ask user for the plain text of what is going to be ciphered
    string nocipher = get_string("plaintext: ");

    // Cipher the code
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

    // Print the cipher
    printf("ciphertext: %s\n", nocipher);

}