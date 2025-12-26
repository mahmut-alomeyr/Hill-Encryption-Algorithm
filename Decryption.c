#include <stdio.h>
#include <string.h>

float determinant(float[][100], int);
int power(int);

int main()
{
    int i, j, uzunluk=0;
    int i2, j2, x, y;
    int i_2, j_2;
    int n, k;
    float anahtar[100][100];
    int tranzpose[100][100];
    float kofaktor[100][100];
    int r;
    int det;
    char sifrelenen[100];
    char sifrelenen_2[100][100];
    int toplam = 0, kalan, yeni_uzunluk, u, t, toplam2 = 0;
    char asil_kelime[100];

    printf("anahtarin (satir ve sutun) sayisini giriniz = ");
    scanf("%d", &n);

    do
    {
        for (i = 0; i < n; i++) //anahtar almak
        {
            for (j = 0; j < n; j++)
            {
                printf("%d_%d = ", i + 1, j + 1);
                scanf("%f", &anahtar[i][j]);
            }
        }
        k = (int)determinant(anahtar, n);
        if (k == 0)
        {
            printf("\nbu anahtar olmaz");
            printf("\nbaska bi anahtar giriniz !\n");
        }

    } while (k == 0);

    for (i = 0; i < n; i++) //anahtar matrisinin kofaktorunu bulmak
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
                        kofaktor[x][y] = anahtar[i2][j2];
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
            r = (int)power(i + j) * determinant(kofaktor, n - 1);
            if (r < 0)
            {
                r += 26;
            }
            kofaktor[i][j] = r;
        }
    }

    for (i = 0; i < n; i++) //tranzpose bulmak
    {
        for (j = 0; j < n; j++)
        {
            tranzpose[i][j] = kofaktor[j][i];
        }
    }

    i = 1;
    k = (int)determinant(anahtar, n);
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

    for (i = 0; i < n; i++) //anahtarin tersi
    {
        for (j = 0; j < n; j++)
        {
            tranzpose[i][j] = (det * tranzpose[i][j]) % 26;
        }
    }

    printf("asli istenen kelimeyi giriniz : ");
    scanf("%s", sifrelenen);

    while (sifrelenen[uzunluk] != '\0') //kelimenin uzunlugunu bulmak
    {
        uzunluk++;
    }

    kalan = uzunluk % n;
    yeni_uzunluk = uzunluk + kalan; //yeni uzunluk
    u = yeni_uzunluk / n;
   
    if (sifrelenen[0] > 64 && sifrelenen[0] < 91) //buyuk harfler için
    
    {

        for (i = 0; i < kalan; i++) //eksik girilen kelimeye 'A' eklemek
        {
            sifrelenen[uzunluk + i] = 'A';
        }

        for (i = 0; i < u; i++) //kelimeyi iki boyutlu bir matrise eklemek
        {
            for (j = 0; j < n; j++)
            {
                sifrelenen_2[i][j] = sifrelenen[toplam + j] - 65; // A=0 , B=1 , C=2 ....VS seklinde yazmak
            }
            toplam += j;

            printf("\n");
        }
        toplam = 0;
        for (i = 0; i < u; i++)
        {
            for (j = 0; j < n; j++)
            {
                toplam2 = 0;
                for (t = 0; t < n; t++)
                {
                    toplam2 += sifrelenen_2[i][t] * tranzpose[t][j]; //kelime matris ile anahtar carpimi
                }
                toplam2 = toplam2 % 26;                 //mod almak
                asil_kelime[j + toplam] = toplam2 + 65; //ascci taplosundaki degerine esitlemek
            }
            toplam += j;
        }
    }
    else //kucuk harfler icin
    {
        for (i = 0; i < kalan; i++) //eksik girilen kelimeye 'a' eklemek
        {
            sifrelenen[uzunluk + i] = 'a';
        }

        for (i = 0; i < u; i++) //kelimeyi iki boyutlu bir matrise eklemek
        {
            for (j = 0; j < n; j++)
            {
                sifrelenen_2[i][j] = sifrelenen[toplam + j] - 97; // a=0 , b=1 , c=2 ....VS seklinde yazmak
            }
            toplam += j;

            printf("\n");
        }
        toplam = 0;
        for (i = 0; i < u; i++)
        {
            for (j = 0; j < n; j++)
            {
                toplam2 = 0;
                for (t = 0; t < n; t++)
                {
                    toplam2 += sifrelenen_2[i][t] * tranzpose[t][j]; //kelime matris ile anahtar carpimi
                }
                toplam2 = toplam2 % 26;                 //mod almak
                asil_kelime[j + toplam] = toplam2 + 97; //ascci taplosundaki degerine esitlemek
            }
            toplam += j;
        }
    }

    printf("\n asil kelime: ");
    printf("%s", asil_kelime);

    
}

float determinant(float matris[][100], int n)
{
    int i, j, y;
    float toplam = 1;
    float k;
    for (i = 0; i < n; i++)
    {
        for (y = i; y < n - 1; y++)
        {
            k = matris[y + 1][i];

            for (j = 0; j < n; j++)
            {
                matris[y + 1][j] = (-1) * matris[i][j] * k / matris[i][i] + matris[y + 1][j];
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        toplam *= matris[i][i];
    }
    return toplam;
}

int power(int s)
{
    int sonuc;
    if (s % 2 == 0)
    {
        return sonuc = 1;
    }
    return sonuc = -1;
}
