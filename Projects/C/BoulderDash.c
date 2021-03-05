#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROCKFORD 64 //'@'
#define EMPTY  32 //' '
#define GROUND 43 //'+'
#define ROCK 35 //'#'
#define STONE 79 //'O'
#define DIAMOND 36 //'$'
#define EXIT 88 //'X'
#define UP 119 //'w'
#define DOWN 115 //'s'
#define LEFT 97 //'a'
#define RIGHT 100 //'d'
#define NEWLINE 10 //'\n'

/**
* Funkcja moveUp przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie oraz szerokosc tablicy n. W wyniku jej
* działania nastepuje przesuniecie o jeden w "gore".
*/

int moveUp(int posOfRockford, int n)
{
    return posOfRockford - n;
}

/**
* Funkcja moveDown przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie oraz szerokosc tablicy n. W wyniku jej
* działania nastepuje przesuniecie o jeden w "dol".
*/

int moveDown(int posOfRockford, int n)
{
    return posOfRockford + n;
}

/**
* Funkcja moveLeft przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie. W wyniku jej
* działania nastepuje przesuniecie o jeden w lewo.
*/

int moveLeft(int posOfRockford)
{
    return posOfRockford - 1;
}

/**
* Funkcja moveRight przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie. W wyniku jej
* działania nastepuje przesuniecie o jeden w prawo.
*/

int moveRight(int posOfRockford)
{
    return posOfRockford + 1;
}

/**
* Funkcja leftEmpty przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie oraz tablice charow a, ktora reprentuje
* kolenje zanaki wystepujace w grze na planszy. W wyniku jej
* działania pole staje sie puste.
*/

void leftEmpty(int posOfRockford, char a[])
{
    a[posOfRockford] = EMPTY;
}

/**
* Funkcja moveRockford przyjuje tablice charow a, ktora reprentuje
* kolenje zanaki wystepujace w grze na planszy oraz liczbe calkowita
* posOfRockfordAfterMove, ktora okresla poloznie po ruchu. W wyniku jej
* dzialania w tablicy na miejscu posOfRockfordAfterMove znajude sie
* Rockford.
*/

void moveRockford(char a[], int posOfRockfordAfterMove)
{
    a[posOfRockfordAfterMove] = ROCKFORD;
}

/**
* Funkcja replaceStoneOrDiamond przyjmuje tablice charow a, ktora reprentuje
* kolenje zanaki wystepujace w grze na planszy oraz dwa indeksy i, j. W wyniku jej
* działania przdmioty na mijscach i oraz j zmieniaja swoje polozenie.
*/

void replaceStoneOrDiamond(char a[], int i, int j)
{
    char temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

/**
* Funkcja computeIdx przyjmuje wartosc calkowita currentPos oraz howMany, ktora
* okresla ile jest pol pusty nad lub pod obecym indeksem. Liczba ta jest obliczna w innej
* fubkcji. Poandto liczba coff, kotorej wartosc to 1 lub -1 a jej wybor od tego czy obliczmy
* dla przejscia w "gore" tablicy czy w "dol". Ostatni argumet to szeroksc planszy. Zwarancany
* jest obliczony indeks.
*/

int computeIdx(int currnetPos, int howMany, int coff, int n)
{
    return currnetPos + (coff*howMany*n);
}

/** Funkcja checkIfEmptyStoneDiamond przyjmuje tablice charow a, ktora reprentuje
* kolenje zanaki wystepujace w grze na planszy oraz wartosc całkowita posOfRockford,
* ktora okresla jego polozenie. Jesli pole w wyniku ruchu jest puste, jest na nim kamien lub
* diament to zanczy, że Rockfod przesunal sie i jest zwracana wartosc 1. W przeciwnym wypadku
* zwracane jest 0.
*/

int checkIfEmptyStoneDiamond(char a[], int posOfRockford)
{
    int isEmpty = 0;
    if(a[posOfRockford] == EMPTY || a[posOfRockford] == STONE || a[posOfRockford] == DIAMOND)
    {
        isEmpty = 1;
    }
    return isEmpty;
}

/** Funkcja countDiamonds przyjmuje tablice charow a, ktora reprentuje
* kolenje zanaki wystepujace w grze na planszy oraz jej dlugosc len. W wyniku jej
* dzilania zwaranca jest liczba diamentow na planszy.
*/

int countDiamonds(char a[], int len)
{
    int howMany = 0;
    for(int k = 0; k < len; k++)
    {
        if(a[k] == DIAMOND)
        {
            howMany++;
        }
    }
    return howMany;
}

/** Funkcja findRockford przyjmuje tablice charow a, ktora reprentuje
* kolenje zanaki wystepujace w grze na planszy oraz jej dlugosc len. W wyniku
* jej dzialania zwracane jest polozenie Rockforda lub -1 gdy nie ma go na planszy.
*/

int findRockford(char a[], int len)
{
    int idx = -1;
    for(int k = 0; k < len; k++)
    {
        if(a[k] == ROCKFORD)
        {
            idx = k;
        }
    }
    return idx;
}

/** Funkcja howManyEmptyFiledsUnderRockford przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie, tablice charow a, ktora reprentuje kolenje zanaki
* wystepujace w grze na planszy oraz szeroksc planszy n. W wyniku jej dzialania zwracana jest
* liczba pustych pol nad miejscem, w ktorym znajduje sie Rockford lub inny przdmiot.
*/

int howManyEmptyFiledsUnderRockford(int posOfRockford, char a[], int n)
{
    int underIdx = posOfRockford;
    int howMany = 0;
    while(a[underIdx] == EMPTY)
    {
       howMany++;
       underIdx = underIdx + n;
    }
    return howMany;
}

/** Funkcja CanRockfordMoveStone przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie, tablice charow a, ktora reprentuje kolenje zanaki
* wystepujace w grze na planszy, zank c oraz szeroksc planszy n. W wyniku jej dzialania
* jesli kamien mozna przsunac to jest on przemiszczany w lewo lub w prawo o jedno pol.
* jesli po wykonaniu tego ruchu pod kamieniem znajduja sie puste pola, kamien spada wtedy w
* dol tak, ze po wykonaniu tego ruchu nie ma pod nim juz pustych pol. Rockford jest przemiszczany
* na pole, na ktorym pierwotnie znajdowal sie kamian. Jesli kamien nie moglbyc przesuniety nic sie
* nie dzieje.
*/

void CanRockfordMoveStone(int posOfRockford, char a[], char c, int n)
{
    int leftOrRight;
    int whereIsStone;
    if(c == LEFT)
    {
        leftOrRight = posOfRockford - 2;
        whereIsStone = posOfRockford - 1;
    }
    else // c == RIGHT
    {
        leftOrRight = posOfRockford + 2;
        whereIsStone = posOfRockford + 1;
    }
    if(a[leftOrRight] == EMPTY)
    {
        a[leftOrRight] = STONE;
        moveRockford(a, whereIsStone);
        leftEmpty(posOfRockford, a);
        int underStone = howManyEmptyFiledsUnderRockford((leftOrRight + n), a, n);
        if(underStone > 0) // kamien moze spasc w dol
        {
            int whereFalls = computeIdx(leftOrRight, underStone, 1,  n); // indeks gdzie spadnie
            replaceStoneOrDiamond(a, leftOrRight , whereFalls); // przeniesienie kamienia na odpowiedni indeks
        }
    }
}

/** Funkcja howManyStoneOrDiamndAboveRockford przyjmuje wartosc całkowita posOfRockford,
* ktora okresla jego polozenie, tablice charow a, ktora reprentuje kolenje zanaki
* wystepujace w grze na planszy oraz szeroksc planszy n. W wyniku jej dzialania zwracana jest
* liczba kamieni lub diamentow nad miejscem, w ktorym znajduje sie Rockford lub inny przdmiot.
*/

int howManyStoneOrDiamndAboveRockford(int posOfRockford, char a[], int n)
{
    int aboveIdx = posOfRockford - n;
    int howMany = 0;
    while(a[aboveIdx] == STONE || a[aboveIdx] == DIAMOND)
    {
        howMany++;
        aboveIdx = aboveIdx - n;
    }
    return howMany;
}

/** Funkcja stabilizedTheColumn przyjmuje tablice charow a, ktora reprentuje kolenje zanaki
* wystepujace w grze na planszy, indeks pola pustego idxOfEmptyFiled, oraz szerokosc planszy n.
* W wyniku jej dzialania w kolumnie w ktorej jest puste pole do liczby pol pustych pod idxOfEmptyFiled
* jest dokonywana stabilizacja planszy, czyli że pod zadnym z kamieni lub diamntow nie ma pol pustych.
*/

void stabilizedTheColumn(char a[], int idxOfEmptyFiled, int n)
{
    int aboveEmptyField = howManyStoneOrDiamndAboveRockford(idxOfEmptyFiled,  a, n);
    int underEmptyFiled = howManyEmptyFiledsUnderRockford(idxOfEmptyFiled, a, n);
    int i = underEmptyFiled;
    for(int j = 0; j < aboveEmptyField; j++)
    {
        int putThereStoneOrDiamond = computeIdx(idxOfEmptyFiled, i-1, 1, n); //  i-1, poniewaz funkja liczy liczbe pustch pol pod obecnym polem
        int whichStoneOrDiamond = computeIdx(idxOfEmptyFiled, j+1, -1, n); // j+1, poniewaz j zaczyna sie od 0
        replaceStoneOrDiamond(a, putThereStoneOrDiamond, whichStoneOrDiamond);
        i--;
    }
}

/** Funkcja stabilizedTheBoard przyjmuje tablice charow a, ktora reprentuje kolenje zanaki
* wystepujace w grze na planszy, kek dlugosc len oraz szerokosc plnaszy n. W wyniku jej dzialania
* plansza jest przksztalcona do posatci stabilnej,
*/

void stabilizedTheBoard(char a[], int len, int n)
{
    for(int i = 0; i < len; i++)
    {
        if(a[i] == EMPTY)
        {
            stabilizedTheColumn(a, i, n);
        }
    }
}

/** Funkcja upOrDown przyjmuje wartosc całkowita posOfRockford,ktora okresla jego polozenie,
* tablice charow a, ktora reprentuje kolenje zanaki wystepujace w grze na planszy, indeks po ruchu idxAfterMove,
* liczbe zebranych diamnetow collectDiamonds, liczbe wszytkich dimantow na planszy allDiamonds oraz szerokosc planszy n.
* W wyniku jej dzialania dla kazdego z przpadkow ruchu w "gore" lub "dol" jest dokonywane odpowiednie przesuniece wraz z dzialanianmi,
* ktore ono wywoluje. Funckcja zwraca liczbe diamntow po wykonaniu operacji.
*/

int upOrDown(int posOfRockford, char a[], int idxAfterMove, int collectDiamonds, int allDiamonds, int n)
{
    if(a[idxAfterMove] == DIAMOND)
    {
        collectDiamonds++;
        leftEmpty(posOfRockford, a);
        moveRockford(a, idxAfterMove);
    }
    if(a[idxAfterMove] == EXIT && collectDiamonds == allDiamonds)
    {
        collectDiamonds++; // bedzie to powodwalo, ze w warunku funkcji loadDataAndPlayGame nie beda wykonywaly sie ruch jak Rockford zniknie z planszy,
                           // zas bedzie sie tylko wypisywala plansza bez Rockforda
        leftEmpty(posOfRockford, a);
    }
    if(a[idxAfterMove] == EMPTY || a[idxAfterMove] == GROUND)
    {
        leftEmpty(posOfRockford, a);
        moveRockford(a, idxAfterMove);
    }
    if(idxAfterMove > posOfRockford)
    {
        stabilizedTheColumn(a, posOfRockford, n); // Rockford ruszyl sie w dol, zatem moga byc puste pola nad nim oraz kaminie i diamenty, dlatego trzeba
                                                  // je przesunac w dol
    }
    return collectDiamonds;
}

/** Funkcja leftOrRight przyjmuje wartosc całkowita posOfRockford,ktora okresla jego polozenie,
* tablice charow a, ktora reprentuje kolenje zanaki wystepujace w grze na planszy, zank c, indeks po ruchu idxAfterMove,
* liczbe zebranych diamnetow collectDiamonds, liczbe wszytkich dimantow na planszy allDiamonds oraz szerokosc planszy n.
* W wyniku jej dzialania dla kazdego z przpadkow ruchu w "lewo" lub "prawo" jest dokonywane odpowiednie przesuniece wraz z dzialanianmi,
* ktore ono wywoluje. Funckcja zwraca liczbe diamntow po wykonaniu operacji.
*/

int leftOrRight(int posOfRockford, char a[], char c, int idxAfterMove, int collectDiamonds, int allDiamonds, int n)
{
    if(a[idxAfterMove] == DIAMOND)
    {
        collectDiamonds++;
        leftEmpty(posOfRockford, a);
        moveRockford(a, idxAfterMove);
    }
    if(a[idxAfterMove] == EXIT && collectDiamonds == allDiamonds)
    {
        collectDiamonds++; // bedzie to powodwalo, ze w warunku funkcji loadDataAndPlayGame nie beda wykonywaly sie ruch jak Rockford zniknie z planszy,
                           // zas bedzie sie tylko wypisywala plansza bez Rockforda
        leftEmpty(posOfRockford, a);
    }
    if(a[idxAfterMove] == EMPTY || a[idxAfterMove] == GROUND)
    {
        leftEmpty(posOfRockford, a);
        moveRockford(a, idxAfterMove);
    }
    if(a[idxAfterMove] == STONE)
    {
         CanRockfordMoveStone(posOfRockford, a,  c, n);
    }
    if(a[posOfRockford] == EMPTY)
    {
        stabilizedTheColumn(a, posOfRockford, n);
    }
    return collectDiamonds;
}

/** Funkcja printBoulderDash przyjmuje tablice charow a, ktora reprentuje kolenje zanaki wystepujace w grze na planszy,
* szerokosc planszy n, oraz jej wysokosc m. W wyniku jej dzialania zostaje wypisana plansza.
*/

void printBoulderDash(char a[], int n, int m)
{
    int len = n*m;
    for(int i = 0; i < len; i++)
    {
        if(i != 0 && i%n == 0)
        {
            printf("\n");
        }
        printf("%c", a[i]);
    }
    printf("\n");
}

/**
* Funkcja printDims przyjumje szerokosc planszy n i jej wysokosc. W wyniku jej dzialania zostaja wypisane wymiary planszy.
*/

void printDims(int n, int m)
{
    printf("%d ",  m);
    printf("%d\n",  n);
}

/**
* Funkcja boulderDashMoves przyjumje zank awsd, wartosc całkowita posOfRockford,ktora okresla jego polozenie, szerokosc planszy n,
* tablice charow a, ktora reprentuje kolenje zanaki wystepujace w grze na planszy, liczbe diamentow na pierwontej planszy howManyDiamonds,
* liczbe dotad zebranych diamentow collectDiamonds oraz dwuelemtowa tablice movesAndDiamonds, ktora przechowuje polozenie po ruchu oraz liczbe
* zebranych diamentow. W wyniku jej dzialania dokonywana jest odpowiednia dla danego ruchu w gore, dol, lewo, prawo operacja.
*/

void boulderDashMoves(char awsd, int posOfRockford, int n, char a[], int howManyDiamonds, int collectDiamonds, int movesAndDiamonds[])
{
    int idxAfterMove = posOfRockford;
    if(awsd == UP)
    {
        idxAfterMove = moveUp(posOfRockford, n);
        collectDiamonds = upOrDown(posOfRockford, a, idxAfterMove, collectDiamonds, howManyDiamonds, n);
    }
    if(awsd == DOWN)
    {
        idxAfterMove = moveDown(posOfRockford, n);
        collectDiamonds = upOrDown(posOfRockford, a, idxAfterMove, collectDiamonds, howManyDiamonds, n);
    }
    if(awsd == LEFT)
    {
        idxAfterMove = moveLeft(posOfRockford);
        collectDiamonds = leftOrRight(posOfRockford, a, awsd, idxAfterMove, collectDiamonds, howManyDiamonds, n);
    }
    if(awsd == RIGHT)
    {
        idxAfterMove = moveRight(posOfRockford);
        collectDiamonds = leftOrRight(posOfRockford, a, awsd, idxAfterMove, collectDiamonds, howManyDiamonds, n);
    }
    if(checkIfEmptyStoneDiamond(a, posOfRockford) == 0) // sprawdzam czy Rockford ruszyl sie z pola, jesli nie, czyli 0, to nie zmieniam jego polozenia
    {
        idxAfterMove = posOfRockford;
    }
    movesAndDiamonds[0] = idxAfterMove; // zapisuje obecne polozenie
    movesAndDiamonds[1] = collectDiamonds; // zapisuje obenca liczbe diamnetow zebranych przez Rockforda
}

/**
* Funkcja loadDataAndPlay jest bezargumnetowa. W wyniku jej dzialania sa wczytywane rozmiary planszy, jest ona nastepnie tworzona
* i ostatecznie sa wykonywane ruchy gracza.
*/

void loadDataAndPlayGame()
{
    int counter = 0; // licznik dla wymiarow
    int howManyDiamonds;
    int posOfRockford;
    int collectDiamonds = 0;
    int movesAndDiamonds[2] = {0};
    int endOfBoard = 0; // sprawdza czy juz zostaly wczytane wszystkie pola na plansze
    int endStabilized = 0; // spawdza czy plansza jest juz ustabilizowana po jej wczytaniu
    int j = 0;
    int n = 0;
    int m = 0;
    int len;
    char *a;
    int dims;
    char boardAndMoves;
    while(counter < 2)
    {
        scanf("%d", &dims);
        if(counter == 0)
        {
            m = dims;
        }
        else
        {
            n = dims;
        }
    counter++;
    }
    len = n*m;
    a = (char*)malloc((size_t)len*sizeof(char)); // tworze tanlice o dlugosci len, bede do niej zapisywal zanki planszy
    counter = 0; // ustawiam na zero, zeby nie czytac potem pierwszej linijki wejscia
    while(scanf("%c", &boardAndMoves) != EOF)
    {
        if(counter == 0) // po to zeby piewsza linijka wejsca nie byla wczytywana do planszy
        {
            counter++;
        }
        else // counter > 0
        {
            if(counter > n*m + m) // plansza ma n*m zankow + m znakow nowej lini, po tym powinnismy zakonczyc wczytywanie planszy
            {
                endOfBoard = 1;
            }
            counter++;
        }
        if(endOfBoard == 0) // jesli zanki sa rozne od a w s d
        {
            if(boardAndMoves != NEWLINE) // omijam zank nowej lini
            {
                a[j] = boardAndMoves;
                j++;
            }
        }
        else // endOfBoard == 1
        {
            if(endStabilized == 0) // plansza zostala wczytana, ale nie odbyla sie jeszcze jej stabilizacja
            {
                 stabilizedTheBoard(a, len, n);
                 howManyDiamonds =  countDiamonds(a, len);
                 posOfRockford = findRockford(a, len); // znajduje pozycje Rocforda
                 printDims(n, m);
                 printBoulderDash(a, n, m);
                 endStabilized = 1;
            }
            if(boardAndMoves != NEWLINE)
            {
                if((collectDiamonds <=  howManyDiamonds) && posOfRockford != -1) // jesli nie wyszylismy jeszce z planszy i Rockford był na planszy
                {
                    boulderDashMoves(boardAndMoves, posOfRockford, n, a, howManyDiamonds, collectDiamonds, movesAndDiamonds); // wykonuje ruch
                    posOfRockford = movesAndDiamonds[0]; //  ustalam nowa pozycje Rocforda
                    collectDiamonds = movesAndDiamonds[1]; // ustalam ile jest zebranych diamentow
                }
            }
            else // boardAndMoves  == NEWLINE
            {
                printDims(n, m);
                printBoulderDash(a, n, m);
            }
        }
    }
    free(a); // zwalniam pamiec 
}

int main(void)
{
    loadDataAndPlayGame();
    return 0;
}
