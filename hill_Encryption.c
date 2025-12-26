#include <stdio.h>
#include <string.h>

int main()
{
    int i, j, k;
    char kelime[100];
    int uzunluk = 0, yeni_uzunluk;
    int n, kalan, y;
    int anahtar[100][100];
    char kelime_2[100][100];
    int toplam = 0;
    int toplam2;
    char sifrelenen_kelime[100];

    printf("sifrelemek isteiginiz kelimeyi giriniz  : "); //kelime almak
    gets(kelime);

    while (kelime[uzunluk] != '\0') //kelimenin uzunlugunu bulmak
    {
        uzunluk++;
    }

    printf("\n anahatarin (satir ve sutun ) sayisini giriniz = ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++) //anahtar almak
        {
            printf("%d-%d = ", i + 1, j + 1);
            scanf("%d", &anahtar[i][j]);
        }
    }
    
    kalan = uzunluk % n;
    yeni_uzunluk = uzunluk + kalan; //yeni uzunluk
    y = yeni_uzunluk / n;
    
    if(kelime[0]>64 && kelime[0]<91)//buyuk harfler için
    {    
        
        
        for (i = 0; i < kalan; i++) //eksik girilen kelimeye 'A' eklemek
        {
            kelime[uzunluk + i] = 'A';
        }
        

        for (i = 0; i < y; i++) //kelimeyi iki boyutlu bir matrise eklemek
        {
            for (j = 0; j < n; j++)
            {
                kelime_2[i][j] = kelime[toplam + j] - 65; // A=0 , B=1 , C=2 ....VS seklinde yazmak
            }
            toplam += j;

            printf("\n");
        }
        toplam = 0;
        for (i = 0; i < y; i++)
        {
            for (j = 0; j < n; j++)
            {
                toplam2 = 0;
                for (k = 0; k < n; k++)
                {
                    toplam2 += kelime_2[i][k] * anahtar[k][j]; //kelime matris ile anahtar carpimi
                }
                toplam2 = toplam2 % 26;                       //mod almak
                sifrelenen_kelime[j + toplam] = toplam2 + 65; //ascci taplosundaki degerine esitlemek
            }
            toplam += j;
        }
                        
    }else//kucuk harfler icin
    {
        for (i = 0; i < kalan; i++) //eksik girilen kelimeye 'a' eklemek
        {
            kelime[uzunluk + i] = 'a';
        }

          for (i = 0; i < y; i++) //kelimeyi iki boyutlu bir matrise eklemek
        {
            for (j = 0; j < n; j++)
            {
                kelime_2[i][j] = kelime[toplam + j] - 97; // a=0 , b=1 , c=2 ....VS seklinde yazmak
            }
            toplam += j;

            printf("\n");
        }
        toplam = 0;
        for (i = 0; i < y; i++)
        {
            for (j = 0; j < n; j++)
            {
                toplam2 = 0;
                for (k = 0; k < n; k++)
                {
                    toplam2 += kelime_2[i][k] * anahtar[k][j]; //kelime matris ile anahtar carpimi
                }
                toplam2 = toplam2 % 26;                       //mod almak
                sifrelenen_kelime[j + toplam] = toplam2 + 97; //ascci taplosundaki degerine esitlemek
            }
            toplam += j;
        } 
    }
        
    printf("sifrelenen kelime : ");
    for (i = 0; i < uzunluk ; i++)
    {
        printf("%c",sifrelenen_kelime[i]);
    }
    
}
