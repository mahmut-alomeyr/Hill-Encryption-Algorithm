#include <stdio.h>
#include <string.h>

float determinant(float[][100], int);
int power(int);

int main()
{
    int i, j, length=0;
    int i2, j2, x, y;
    int i_2, j_2;
    int n, k;
    float key[100][100];
    int transpose[100][100];
    float cofactor[100][100];
    int r;
    int det;
    char ciphertext[100];
    char ciphertext_matrix[100][100];
    int total = 0, remainder, new_length, u, t, total2 = 0;
    char original_word[100];

    printf("Enter the key matrix size (rows and columns): ");
    scanf("%d", &n);

    do
    {
        for (i = 0; i < n; i++) //read the key matrix
        {
            for (j = 0; j < n; j++)
            {
                printf("%d_%d = ", i + 1, j + 1);
                scanf("%f", &key[i][j]);
            }
        }
        k = (int)determinant(key, n);
        if (k == 0)
        {
            printf("\nThis key is invalid");
            printf("\nPlease enter a different key!\n");
        }

    } while (k == 0);

    for (i = 0; i < n; i++) //find the cofactor matrix of the key
    {
        for (j = 0; j < n; j++)
        {
            x = 0;
            y = 0;

            for (i2 = 0; i2 < n; i2++)
            {
                for (j2 = 0; j2 < n; j2++)
                {
                    if (i2 != i && j2 != j)
                    {
                        cofactor[x][y] = key[i2][j2];
                        if (y < (n - 2))
                        {
                            y++;
                        }
                        else
                        {
                            y = 0;
                            x++;
                        }
                    }
                }
            }
            r = (int)power(i + j) * determinant(cofactor, n - 1);
            if (r < 0)
            {
                r += 26;
            }
            cofactor[i][j] = r;
        }
    }

    for (i = 0; i < n; i++) //find the transpose
    {
        for (j = 0; j < n; j++)
        {
            transpose[i][j] = cofactor[j][i];
        }
    }

    i = 1;
    k = (int)determinant(key, n);
    k = k % 26;
    if (k < 0)
    {
        k += 26;
    }
    while ((1 + 26 * i) % k != 0 && i<97)
    {                                                           //  (1/determinant)mod26  //inverse mode
        i++;
    }

    det = 1 + 26 * i;

    for (i = 0; i < n; i++) //inverse of the key matrix
    {
        for (j = 0; j < n; j++)
        {
            transpose[i][j] = (det * transpose[i][j]) % 26;
        }
    }

    printf("Enter the ciphertext to decrypt: ");
    scanf("%s", ciphertext);

    while (ciphertext[length] != '\0') //find the length of the word
    {
        length++;
    }

    remainder = length % n;
    new_length = length + remainder; //new length
    u = new_length / n;
   
    if (ciphertext[0] > 64 && ciphertext[0] < 91) //for uppercase letters
    
    {

        for (i = 0; i < remainder; i++) //pad the word with 'A' if needed
        {
            ciphertext[length + i] = 'A';
        }

        for (i = 0; i < u; i++) //store the word in a 2D matrix
        {
            for (j = 0; j < n; j++)
            {
                ciphertext_matrix[i][j] = ciphertext[total + j] - 65; // map A=0, B=1, C=2, ...
            }
            total += j;

            printf("\n");
        }
        total = 0;
        for (i = 0; i < u; i++)
        {
            for (j = 0; j < n; j++)
            {
                total2 = 0;
                for (t = 0; t < n; t++)
                {
                    total2 += ciphertext_matrix[i][t] * transpose[t][j]; //multiply word matrix by key matrix
                }
                total2 = total2 % 26;                 //take mod
                original_word[j + total] = total2 + 65; //map back to ASCII character
            }
            total += j;
        }
    }
    else //for lowercase letters
    {
        for (i = 0; i < remainder; i++) //pad the word with 'a' if needed
        {
            ciphertext[length + i] = 'a';
        }

        for (i = 0; i < u; i++) //store the word in a 2D matrix
        {
            for (j = 0; j < n; j++)
            {
                ciphertext_matrix[i][j] = ciphertext[total + j] - 97; // map a=0, b=1, c=2, ...
            }
            total += j;

            printf("\n");
        }
        total = 0;
        for (i = 0; i < u; i++)
        {
            for (j = 0; j < n; j++)
            {
                total2 = 0;
                for (t = 0; t < n; t++)
                {
                    total2 += ciphertext_matrix[i][t] * transpose[t][j]; //multiply word matrix by key matrix
                }
                total2 = total2 % 26;                 //take mod
                original_word[j + total] = total2 + 97; //map back to ASCII character
            }
            total += j;
        }
    }

    printf("\n Decrypted word: ");
    printf("%s", original_word);

    
}

float determinant(float matrix[][100], int n)
{
    int i, j, y;
    float total = 1;
    float k;
    for (i = 0; i < n; i++)
    {
        for (y = i; y < n - 1; y++)
        {
            k = matrix[y + 1][i];

            for (j = 0; j < n; j++)
            {
                matrix[y + 1][j] = (-1) * matrix[i][j] * k / matrix[i][i] + matrix[y + 1][j];
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        total *= matrix[i][i];
    }
    return total;
}

int power(int s)
{
    int result;
    if (s % 2 == 0)
    {
        return result = 1;
    }
    return result = -1;
}
