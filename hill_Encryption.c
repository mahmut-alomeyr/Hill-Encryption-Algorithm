#include <stdio.h>
#include <string.h>

int main()
{
    int i, j, k;
    char word[100];
    int length = 0, new_length;
    int n, remainder, y;
    int key[100][100];
    char word_matrix[100][100];
    int total = 0;
    int total2;
    char encrypted_word[100];

    printf("Enter the word to encrypt: "); //read the word
    gets(word);

    while (word[length] != '\0') //find the length of the word
    {
        length++;
    }

    printf("\n Enter the key matrix size (rows and columns): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++) //read the key matrix
        {
            printf("%d-%d = ", i + 1, j + 1);
            scanf("%d", &key[i][j]);
        }
    }
    
    remainder = length % n;
    new_length = length + remainder; //new length
    y = new_length / n;
    
    if(word[0]>64 && word[0]<91)//for uppercase letters
    {    
        
        
        for (i = 0; i < remainder; i++) //pad the word with 'A' if needed
        {
            word[length + i] = 'A';
        }
        

        for (i = 0; i < y; i++) //store the word in a 2D matrix
        {
            for (j = 0; j < n; j++)
            {
                word_matrix[i][j] = word[total + j] - 65; // map A=0, B=1, C=2, ...
            }
            total += j;

            printf("\n");
        }
        total = 0;
        for (i = 0; i < y; i++)
        {
            for (j = 0; j < n; j++)
            {
                total2 = 0;
                for (k = 0; k < n; k++)
                {
                    total2 += word_matrix[i][k] * key[k][j]; //multiply word matrix by key matrix
                }
                total2 = total2 % 26;                       //take mod
                encrypted_word[j + total] = total2 + 65; //map back to ASCII character
            }
            total += j;
        }
                        
    }else//for lowercase letters
    {
        for (i = 0; i < remainder; i++) //pad the word with 'a' if needed
        {
            word[length + i] = 'a';
        }

          for (i = 0; i < y; i++) //store the word in a 2D matrix
        {
            for (j = 0; j < n; j++)
            {
                word_matrix[i][j] = word[total + j] - 97; // map a=0, b=1, c=2, ...
            }
            total += j;

            printf("\n");
        }
        total = 0;
        for (i = 0; i < y; i++)
        {
            for (j = 0; j < n; j++)
            {
                total2 = 0;
                for (k = 0; k < n; k++)
                {
                    total2 += word_matrix[i][k] * key[k][j]; //multiply word matrix by key matrix
                }
                total2 = total2 % 26;                       //take mod
                encrypted_word[j + total] = total2 + 97; //map back to ASCII character
            }
            total += j;
        } 
    }
        
    printf("Encrypted word: ");
    for (i = 0; i < length ; i++)
    {
        printf("%c",encrypted_word[i]);
    }
    
}
