#include <ctype.h>
#include <stdio.h>
#include <string.h>

char encrypt(char letter, const char *key);
char decrypt(char letter, const char *key);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isalpha((unsigned char) argv[1][i]))
        {
            printf("Key must contain 26 unique alphabetic characters.\n");
            return 1;
        }

        argv[1][i] = (char) toupper((unsigned char) argv[1][i]);

        char k = argv[1][i];

        for (int n = 0; argv[1][n] != '\0'; n++)
        {
            if (k == argv[1][n] && i != n)
            {
                printf("Key must contain 26 unique alphabetic characters.\n");
                return 1;
            }
        }
    }

    char mode;
    char mode_input[16];
    char plain[1000];
    char encrypted[1000];

    do
    {
        printf("Encrypt or Decrypt (e/d)? ");

        if (fgets(mode_input, sizeof(mode_input), stdin) == NULL)
        {
            return 1;
        }

        mode = (char) tolower((unsigned char) mode_input[0]);

        if (mode == 'e')
        {
            printf("plaintext:     ");

            if (fgets(plain, sizeof(plain), stdin) == NULL)
            {
                return 1;
            }

            plain[strcspn(plain, "\n")] = '\0';

            for (int l = 0; plain[l] != '\0'; l++)
            {
                plain[l] = encrypt(plain[l], argv[1]);
            }

            printf("encryptedtext: %s\n", plain);

            return 0;
        }
        else if (mode == 'd')
        {
            printf("encryptedtext: ");

            if (fgets(encrypted, sizeof(encrypted), stdin) == NULL)
            {
                return 1;
            }

            encrypted[strcspn(encrypted, "\n")] = '\0';

            for (int l = 0; encrypted[l] != '\0'; l++)
            {
                encrypted[l] = decrypt(encrypted[l], argv[1]);
            }

            printf("decryptedtext: %s\n", encrypted);

            return 0;
        }
    }
    while (mode != 'e' && mode != 'd');

    return 0;
}

char encrypt(char letter, const char *key)
{
    if (isupper((unsigned char) letter))
    {
        int letter_position = letter - 65;
        letter = key[letter_position];
    }
    else if (islower((unsigned char) letter))
    {
        int letter_position = letter - 97;
        letter = key[letter_position];
        letter = (char) tolower((unsigned char) letter);
    }

    return letter;
}

char decrypt(char letter, const char *key)
{
    if (isupper((unsigned char) letter))
    {
        int letter_position = 0;

        while (letter != key[letter_position])
        {
            letter_position++;
        }

        letter = (char) (letter_position + 65);
    }
    else if (islower((unsigned char) letter))
    {
        int letter_position = 0;

        letter = (char) toupper((unsigned char) letter);

        while (letter != key[letter_position])
        {
            letter_position++;
        }

        letter = (char) (letter_position + 97);
    }

    return letter;
}
