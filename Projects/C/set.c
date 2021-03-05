#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/**
* Stala LENST okresla dlugosc setu
*/

const int LENSET = 12;

/**
* Funkcja swap jako argumnety przujmuje dwie wartosci i
* zamienia je miejscami w tablicy
*/

void swap(int* a, int* b)
{
    int swapTemp;
    swapTemp = *a;
    *a = *b;
    *b = swapTemp;
}

/**
* Funkcja pivotSet z elementow  o indekasach a, b, c w tablicy
* wybiera wartosc srodkowa. Standardowo patrzymy na warotsci
* indeks zerowy, srodkowy i ostatni. Jest to nasz pivot.
*/

int pivotSet(int a, int b, int c)
{
    if (a <= b)
    {
        if(b <= c)
        {
            return b;
        }
        else if(a <= c)
        {
            return c;
        }
        else
        {
            return a;
        }
    }
    else
    {
        if(a <= c)
        {
            return a;
        }
        else if (b <= c)
        {
            return c;
        }
        else
        {
            return b;
        }
    }
}

/**
* Funkcja partition przyjmuje jako argumenty dwie listy i dwa indeksy.
* W wyniku jej dzialania w tablicy elemnty mniejsze od pivota sa na
* lewo od niego, a wieksze na prawo. Ponadto pivot jest na swoim miejscu
* w tablicy.
*/

int partition(int a[], int idx[],  int low, int high)
{
    int midIdx = (low + high)/2;
    int piv = pivotSet(a[low], a[midIdx], a[high]);
    int pivIdx = 0;
    // ustawianie odpowdniego elementu jako pivot
    if(piv == a[low])
    {
        pivIdx = low;
    }
    else if(piv == a[midIdx])
    {
        pivIdx = midIdx;
    }
    else
    {
        pivIdx = high;
    }
    // pivot idzie na koniec tablicy
    swap(&a[pivIdx], &a[high]);
    swap(&idx[pivIdx], &idx[high]);
    int i = low;
    int j = high - 1;
    // ustawinie elementow mniejszych od pivota na lewo, a wiekszych na prawo
    while(i <= j)
    {
        if(a[i] >= piv)
        {
            if(a[j] <= piv)
            {
                swap(&a[i], &a[j]);
                swap(&idx[i], &idx[j]);
                i++;
            }
            j--;
        }
        else // a[i] < piv
        {
            i++;
        }
    }
    // wstawenie pivota na odpowendnie miejsce
    swap(&a[i], &a[high]);
    swap(&idx[i], &idx[high]);
    return i;
}

/** Funkcja quickSortSet przujmuje takie same argumenty jak funkcja
* partition i wywoluje ja rekurencyjnie na coraz mniejszych fragmentach
* tablicy. W wyniku jej dzialania otrzymujemy posotowana tablice a oraz
* indeksy sortujace a zapisane w tablicy idx.
*/

void quickSortSet(int a[], int idx[], int low, int high)
{
    if( low < high)
    {
        // rekurencyjnie sortuje tablice 
        int pInGoodPlace = partition(a,idx, low, high);
        quickSortSet(a,idx, low, pInGoodPlace - 1);
        quickSortSet(a,idx, pInGoodPlace + 1, high);
    }
}

/**
* Struktura, ktora tworzy obiekt Card majacy 4 pola a, b, c, d.
*/

typedef struct
{
    int a; // numer of shapes
    int b; // color
    int c; // fill
    int d; // shape
} Card;

/**
* Funkcja valueOfCard przujmuje jako argumnet obiekt Card i liczbe naturlana 4 cyfrowa.
* W wyniku jej dzialania przypisujemy wartosci polom w Card.
*/

void valueOfCard(Card* card, int n)
{
    card->a = n/1000;
    card->b = (n % 1000)/ 100;
    card->c = (n % 100)/ 10;
    card->d = n % 10;
}

/**
* Funkcja thirdCardToMakeSet przyjmuje jako argumenty dwa obiekty Card. Zwraca liczbe
* 4 cyfrowa, ktorej wartosc razem z pozostalymi dwoma tworzy set.
*/

int thirdCardToMakeSet(Card* card1,Card* card2)
{
    // szukam wartosci, ktora wraz z dwiema pozostalymi tworzy set, jesli liczby na danej "wspolrzednej" sa rowne,
    // to szukana liczba ma tez taka, jeli nie obliczamy ja ze wzoru 6 - 1wsporzedna - 2wspolrzedna.
    int valueOfThirdCard = 0;
    if(card1->a == card2->a)
    {
        valueOfThirdCard = card1->a*1000;
    }
    else
    {
        valueOfThirdCard = (6 - card1->a - card2->a)*1000;
    }
    if(card1->b == card2->b)
    {
        valueOfThirdCard = valueOfThirdCard + card1->b*100;
    }
    else
    {
        valueOfThirdCard = valueOfThirdCard + (6 - card1->b - card2->b)*100;
    }
    if(card1->c == card2->c)
    {
        valueOfThirdCard = valueOfThirdCard + card1->c*10;
    }
    else
    {
        valueOfThirdCard = valueOfThirdCard + (6- card1->c - card2->c)*10;
    }
    if(card1->d == card2->d)
    {
        valueOfThirdCard = valueOfThirdCard + card1->d;
    }
    else
    {
        valueOfThirdCard = valueOfThirdCard + (6 - card1->d - card2->d);
    }
    return valueOfThirdCard;
}

/**
* Funkcja binsearchForThird przyjmuje tablice a, jej dlugosc
* oraz liczbe v, ktora szukamy w tablicy. Jesli wartosc istnieje to
* zwracamy jej indeks, jesli nie to zwracamy -1.
*/

int binsearchForThird(int a[], int n, int v)
{
    int idx = -1;
    int l = 0;
    int r = n-1;
    int s = 0;
    // szukam indesku w tablicy gdzie znajduje sie moja wartosc, jesli nie ma zwracam -1
    while(l < r)
    {
        s = (l+r)/2;
        if(a[s] > v)
        {
            r = s;
        }
        else if(a[s] < v)
        {
            l = s+1;
        }
        else // a[s] == v
        {
            idx = s;
            l = l+n;
        }
    }
    return idx;
}

/**
* Funkcja lookForSet przujmuje 3 tablice, ich dlugosci,3 indeksy pod ktorymi
* stoja elementy tworzace set, liczba calkowita ad, ktora jest ogranicznem elemtow w tablicy, ad przyjmuje
* wrtosci podzielne przez 3. W wyniku dzialania funkcji znamy, na ktorych indeksach sa wartosci tworzace set
* oraz zostaje zwrocone 1, gdy jest set, zero w przeciwnym przypadku.
*/

int lookForSet(int a[], int n, int b[], int c[], int* set1, int* set2, int* set3, int ad)
{
    int i = 0;
    int j = 1;
    int isSet = 0;
    // dwie karty
    Card card1;
    Card card2;
    // domyslnie ustawiam je na zero
    *set1 = 0;
    *set2 = 0;
    *set3 = 0;
    while(i < LENSET + ad && i < n) // jesli LENSET + ad <= n to tylko operuje na tych indeksach  
    {
        if(a[i] != 0)
        {
            valueOfCard(&card1, a[i]);
            while(j < LENSET + ad && j < n) // analogiczna sytuacja jak wyzej
            {
                if(a[j] != 0)
                {
                    valueOfCard(&card2, a[j]);
                    int v3 = thirdCardToMakeSet(&card1, &card2);
                    int idx = binsearchForThird(b, n, v3);
                    if(idx != -1 && a[c[idx]] != 0 && c[idx] < LENSET + ad) // jesli sa spelninoe warunki to znczy ze jest karta ktora razem utowrzy set
                    {
                        isSet = 1;
                        *set1 = i;
                        *set2 = j;
                        *set3 = c[idx];
                        i = i + n;
                        j = j + n;
                    }
                }
                j++;
            }
        }
        // przesuwam sie z indeksami
        i++;
        j=i;
        j++;
    }
    return isSet;
}

/**
* Funkcja deleteFromSet przyjmuje tablice a i 3 indeksy set1, set2, set3.
* Ustawia wartsci elementow na zero w indeksach set1, set2, set3.
*/

void deleteFromSet(int a[], int set1, int set2, int set3)
{
    a[set1] = 0;
    a[set2] = 0;
    a[set3] = 0;
}

/**
* Funkcja printSet przyjmuje tablice a i liczbe n, ktora jest nie wieksza od dlugosci tablicy.
* Jej zadaniem  jest wypisanie obecenego stanu kart na stole
*/

void printSet(int a[], int len, int n, int isSet)
{
    printf("=");
    for(int i = 0; i < len; i++)
    {
        if(a[i] != 0)
        {
            printf(" %d", a[i]);
        }
    }
    if(len < n || isSet == 1) // sa jeszce dodatkowe karty i istnieje set wsrod nich
    {
        printf("\n");
    }
}

/**
* Funkcja printSubOrAdd przyjmuje tablice a, liczbe len nie wikesza niz licza n, parametr isSet,
* ktorego wartosc wynosi 0 albo 1 i 3 indeksy set1, set2, set3. W wyniku jej dzialania zostaje wypisany
* znak "-" i liczby tworzace set albo znak "+" gdy w tablicy nie ma setu
*/

void printSubOrAdd(int a[], int len, int n, int isSet, int set1, int set2, int set3)
{
    if(isSet == 1)
    {
        printf("-");
        printf(" %d", a[set1]);
        printf(" %d", a[set2]);
        printf(" %d", a[set3]);
    }
    else
    {
        if(len < n)
        {
            printf("+");
        }
    }
    printf("\n");
}

/**
* zwracam mniejsza z wartosci n lub LENSET
*/

int inLenSet(int n)
{
    if( LENSET > n)
    {
        return n;
    }
    else
    {
        return LENSET;
    }
}

/**
* Funkcja set przyjmuje tablice a, jej dlugosc n, trzy indeksy set1, set2, set3,
*liczbe calkowita ad. W wyniku jej dzilania otrzymujemy  wypisanie przebiegu konca gry.
*/

void set(int a[], int n, int set1, int set2, int set3, int ad)
{
    // alokuje pamiec na tablice sortowana i indeksy sortujace tablice
    int* sortArr;
    int* sortIdx;
    int isSet = 0;
    int mn;
    sortArr = (int*)calloc((size_t)n,sizeof(int));
    sortIdx = (int*)calloc((size_t)n,sizeof(int));
    for(int k = 0; k < n; k++)
    {
       sortArr[k] = a[k];
       sortIdx[k] = k;
    }
    quickSortSet(sortArr, sortIdx, 0, n-1);
    // ustawaim liczbe elementow wpisanych w pierwszym kroku
    int len = inLenSet(n);
    while(len + ad <= n || isSet == 1) // dopoki moge jeszce brac dodatkowe karty lub jest w nich set
    {
        // ten warunek jest po to poniewaz majac uzyte juz wszytkie kartu nadal moge w nich znalezc set, a w kazdej iteracji ad rosnie,
        // czyli faktycznie moze byc len + ad > n
        if (len + ad > n)
        {
            mn = n;
        }
        else
        {
            mn = len + ad;
        }
        isSet = lookForSet(a, n, sortArr, sortIdx, &set1, &set2, &set3, ad);
        printSet(a, mn, n, isSet);
        printSubOrAdd(a, mn, n,  isSet, set1, set2, set3);
        // usuwam set ze stolu
        if(isSet == 1)
        {
           deleteFromSet(a, set1, set2, set3);
        }
        ad = ad + 3;
    }
    // zwalniam pamiec
    free(sortArr);
    free(sortIdx);
}

int main(void)
{
    //int b[12] = {1332, 1131, 3111, 3313, 2133, 2322, 3133, 1222, 3122, 1211, 3221, 2112};
    int b[81];
    //int *a;
    int i = 0;
    int x;
    while(scanf("%d", &x) != EOF)
    {
       b[i] = x;
       i++;
    }
    //a = (int*)malloc((size_t)i*sizeof(int));
    //for(int j = 0; j < i; j++)
    //{
    //    a[j] = b[j];
    //}
    int set1 = 0;
    int set2 = 0;
    int set3 = 0;
    set(b, i, set1, set2, set3, 0);
    //free(a);
    return 0;
}

