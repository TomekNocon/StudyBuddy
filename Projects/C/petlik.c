#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEFTPARA 40
#define RIGHTPARA 41
#define EQUAL 61
#define NEWLINE 10
#define DEFAULTLEN 1000
#define LENARRAY 26


/**
* Tworze struktore stosu i nadaje jej nazwe Stack oraz pola top,
* capacity oraz wskaznik array , ktróy będzie wskazywał na pewną tablice
*/
typedef struct
{
    int top;
    int capacity;
    int * array;
} Stack;

/**
* Funckja createStack przyjmuje wartosc nieujemna capacity. W wyniku jej dziłania
* zwracany jest wskaznik na stos. Ustwaina jest "gleboksc" stosu, wartosc top na -1,
* co oznacza ze jest on pusty oraz jest allokowana pamiec dla tablicy array
*/

Stack* createStack(int capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc((size_t)stack->capacity * sizeof(int));
    return stack;
}

/**
* Fukcja isFull przyjmuje jako argument wskaznik na stos *stack. Po jej wywołaniu
* otrzymujemy informacje czy stos jest zapelninoy
*/

int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

/**
* Fukcja isEmpty przyjmuje jako argument wskaznik na stos *stack. Po jej wywołaniu
* otrzymujemy informacje czy stos jest pusty
*/

int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

/**
* Fukcja push przyjmuje jako argument wskaznik na stos *stack oraz indeks nawiasu lub wartosc kolejenego
* wystapienia lewego nawiasu, który będzie przekazywany podczas wczytywania wejscia. W wyniku jej dzialania
* element jest wkladany na stos
*/

void push(Stack* stack, int idxParan)
{
    if (isFull(stack))
    {
        return;
    }
    stack->array[++stack->top] = idxParan;
}

/**
* Fukcja pop przyjmuje wskaznik na stos *stack. W wyniku jej dzialania jest usuwany i zwracany element ze stosu,
* ktory znajduje sie na szczycie stosu.
*/

int pop(Stack* stack)
{
    if (isEmpty(stack))
    {
        return -1;
    }
    return stack->array[stack->top--];
}

/**
* Funckja peek przyjmuje wskaznik na stos *stack. W wyniku jej dzilania mozemy sie dowiedziec jaki element znajduje sie na
* wierzchu stosu.
*/

int peek(Stack* stack)
{
    return stack->array[stack->top];
}

/**
* Funckja extend przyjmuje wartosc calkowita n. W wyniku jej dzialania
* zwracana jest wrtosc 2*n + 1
*/

int extend(int n)
{
    return 2*n + 1;
}

/**
* Funckja extend przyjmuje wartosc calkowita n (z zalozenia jest ona nieparzysta). W wyniku jej dzialania
* zwracana jest wrtosc calkowita n-1/2
*/

int shorten(int n)
{
     return (int) ((n-1)/2);
}

/**
* Funkcja fillWithZeros przyjmuje wskaznik na tablice *p, liczbe do tej pory wpisanych liczb lenNum, nie liczac elementu na pozycji p[0]
* oraz dlugosc tej tablicy len, ktory znajduje sie w elemencie p[0]. W wyniku jej dzilania elementy na miejscach od lenNum sa zerami.
*/
void fillWithZeros(int *p, int lenNum, int len)
{
    for(int i = lenNum + 1; i < len; i++)
    {
        p[i] = 0;
    }
}

/**
* Funkcja checkLenArr przujmuje wskaznik *arr. W wyniku jej dzialania jesli wskanizk ma wartosc NULL jest tworzona tablica o domyslnej dlugosci
* DEFAULTLEN. Ponaddto jest ustawiana dlugosc tej tablicy w arr[0]. W przeciwnym wypadku zwracana jest tablica arr.
*/

int* checkLenArr(int* arr)
{
    if(arr == NULL)
    {
        arr =(int*)calloc(DEFAULTLEN, sizeof(int));
        arr[0] = DEFAULTLEN;
    }
    return arr;
}

/**
* Funkcja lenOfNUmber przyjmuje wskaznik na tabice *a. W wyniku jej dzialania poznajemy jaka jest dlugosc
* trzymanej liczby w tej tablicy
*/

int lenOfNumber(int *a)
{
    int k = a[0] - 1;
    int counter = 1;
    while(k > 0 && a[k] == 0)
    {
        k--;
        counter++;
    }
    return a[0] - counter;
}

/**
* Funkcja addOne przyjmuje jako argymnety wskaznik na tabice *a oraz dlugosc przetrzymywanej tablicy n.
* W wyniku jej dzialania do przechowywanej liczby w tablicy dodawane jest jeden.
*/

void addOne(int *a, int n)
{
    int i = 2;
    int d = a[1] + 1; // dodaje jeden
    a[1] = d%10;
    int r = d/10;
    while(i < n)
    {
        d = a[i] + r;
        a[i] = d%10;
        r = d/10;
        if(r == 0) // jesli nie ma nic do przeniesienia
        {
            i = n;
        }
        i++;
    }
}

/**
* Funkcja subOne przyjmuje jako argymnety wskaznik na tabice *a.
* W wyniku jej dzialania do przechowywanej liczby w tablicy odjemowane jest jeden.
*/

void subOne(int* a)
{
    int i = 1;
    if(a[i] - 1 < 0) // jesli jes ujemne to moze miec wpywa na dalsze wartosc cyfr liczby
    {
        while(a[i] == 0) // dopoki jest zero jest szansa odjecie 1 ma wplyw na reszte cyfr
        {
            a[i] = 9;
            i++;
        }
    }
    a[i]--;
}

/**
* Funkcja setLen przyjmuje dwa wskazniki na listy *a i *b. W wyniku jej dzialania zwracaja jest
* dlugosc dluzszej listy
*/

int setLen(int *a, int* b)
{
    int len;
    if(a[0] < b[0])
    {
        len = b[0];
    }
    else
    {
        len = a[0];
    }
    return len;
}

/**
* Funkcja extendIfNeededOne przyjmuje jako argument wskaznik *a. W wyniku jej dzilania jesli sa spelnione odpowiednie
* warunki tablica jest rozszerzana o nowa dlugosc i jest ona nastepnie zwracana. Warunkiem tym jest ze dlugosc liczby
* jest rowna dlugosci tablicy - 1, co oznacza ze jest ona w pelni zapelniona. W pozniejszym procesie gwarantuje to, ze
* dodanie jednyki nie spowoduje, ze stracimy infoamcje o wartosci liczby.
*/

int* extendIfNeededOne(int *a)
{
    a = checkLenArr(a);
    int lenNum = lenOfNumber(a);
    if(a[0] - 1 == lenNum)
    {
        int len = extend(a[0]); // 2*a[0] + 1
        a = (int*)realloc(a, (size_t) len* sizeof(int));
        a[0] = len;
        fillWithZeros(a, lenNum, len);
    }
    return a;
}

/**
* Funkcja extendIfNeeded przyjmuje jako argumenty wskazniki *a i *b. W wyniku jej dzialania tablica trzymana w *a jest rozszerzana
* jesli dlugosc liczby w niej trzymana jest krotsza od tej w *b lub gdy cala tablicy w *a jest zapelniona. Nastepnie jest zwracana tablica a.
*/

int* extendIfNeeded(int *a, int* b)
{
    a = checkLenArr(a);
    int lenNumA = lenOfNumber(a);
    int lenNumB = lenOfNumber(b);
    int lenAOrB = setLen(a, b);
    if(lenNumA < lenNumB || a[0] - 1 == lenNumA)
    {
        a = (int*)realloc(a, (size_t) lenAOrB* sizeof(int));
        a[0] = lenAOrB;
        fillWithZeros(a, lenNumA, lenAOrB);
    }
    return a;
}

/**
* Funkcja shortenIfNeeded przyjmuje wskazniek *a. W wyniku jej dzialania skracany jest rozmiar tablicy a. Warunkami to
* a nie mmoze byc krotsze niz DEFAULTLEN co jest rowniwazne z tym ze jest rozne oraz dlugosc liczby musi byc co najmniej 4
* razy mniejsza niz dlugosc tablicy. Zwracany jest wskaznik na tablice.
*/

int* shortenIfNeeded(int *a)
{
    int lenNum = lenOfNumber(a);
    int* p;
    if(a[0] != DEFAULTLEN && 4*lenNum <= a[0])
    {
        int len = shorten(a[0]);
        p = (int*)realloc(a, (size_t) len* sizeof(int));
        p[0] = len;
        fillWithZeros(p, lenNum, len);
        return p;
    }
    return a;
}

/**
* Funkcja addTwoNumbers przyjmuje dwa wskazniki *a i *b na tablice oraz ich dlugosci n oraz m. Z zalozenia n >= m.
* w wyniku jej dzilania dodwane sa do siebie dwie tablice a wynik tego dzialania jest przechowywany w *a.
*/

void addTwoNumbers(int* a, int n, int* b, int m)
{
    int i = 1;
    int r = 0;
    int d;
    while(i < m)
    {
        d = a[i] + b[i] + r;
        a[i] = d%10;
        r = d/10;
        i++;
    }
    while(i < n)
    {
        d = a[i] + r;
        a[i] = d%10;
        r = d/10;
        i++;
    }
}

/**
* Funkcja checkIfDiff przyjmuje wskaznik *all, wartosci calkowite leftIdx i rightIdx. W wyniku jej dzialania dowiadujemy sie
* czy pierwsza litera po wystepujaca na idneksie leftIdx + 1 jest rozna od pozostalych
*/

int checkIfDiff(int* all, int leftIdx, int rightIdx)
{
    int check = 0;
    for(int k = leftIdx+1; k < rightIdx - 1; k++)
    {
        if(all[leftIdx+1] == all[k+1])
        {
            check = 1;
        }
    }
    return check;
}

/**
* Funkcja isZero przyjmuje wszkanik *a jako argument. W wyniku jej dzialania zwracana jest informacja czy
* przechowywana liczba jest zerem "1" lub nie "0".
*/

int isZero(int *a)
{
    int zero = 0;
    if(lenOfNumber(a) == 0)
    {
        zero = 1;
    }
    return zero;
}

/**
* Funkcja clearVar przyjmuje jako argument wskaznik *a. W wyniku jej dzialania tablica a jest wyzerowywana i
* skracana oraz nastepnie zwracana.
*/

int* clearVar(int* a)
{
    fillWithZeros(a, 0, a[0]);
    int* arr = shortenIfNeeded(a);
    return arr;
}

/**
* Funkcja printResult przyjmuje jako argument wskaznik *a. W wyniku jej dzialania wypisywana jest wartosc liczby
* przechowyanej w tablicy lub jest wypisywane zero jesli a == NULL
*/

void printResult(int* a)
{
    if(a == NULL)
    {
        printf("0");
    }
    else
    {
        int len = lenOfNumber(a);
        if(len == 0)
        {
            printf("0");
        }
        else
        {
            while(len > 0)
            {
                printf("%d", a[len]);
                len--;
            }
        }
    }
    printf("\n");
}

/**
* Funkcja optimization przyjmuje tablice wskaznikow var[], wskaznik na tablice all oraz dwie wartosci calkowie
* leftIdx oraz rightIdx. W wyniku jej dzialania dokownywana jest optymalizacja petli.
*/

void optimization(int* var[], int *all, int leftIdx, int rightIdx)
{
    int* arr2 = var[all[leftIdx+1]-97];
    for(int k = leftIdx + 2; k < rightIdx; k++)
    {
        int* arr1 = var[all[k]-97];
        int* arr3 = extendIfNeeded(arr1, arr2);
        addTwoNumbers(arr3, arr3[0], arr2, arr2[0]);
        var[all[k]-97] = arr3;
    }
    var[all[leftIdx+1]-97] = clearVar(arr2);
}

/**
* Funkcja leftParan przyjmuje jako argumnety wskaznik do stosu *stack, tablice wskaznikow var[], wskaznik na tablice all,
* wartosc calkowita leftIdx i 3 wskanizki counter, next i isPeekZero. W wyniku jej dzialania na stos jest wrzucany numer indeksu
* lewego nawiasu oraz wartosci numeru wystapienia kolejego z nawiaskow. Jesli wartosc liczby za lewym nawiasem jest rowny co do wartosci zero
* argument isPeekZero jest ustawiany na jeden. Wpp jest ustawiany na zero.
*/

void leftParan(Stack* stack, int *var[], int* all, int leftIdx, int* counter, int* next, int* isPeekZero)
{
    if(isZero(var[all[leftIdx + 1]-97]) == 1)
    {
        *isPeekZero = 1;
    }
    else
    {
        push(stack, leftIdx);
        push(stack, *counter);
        *isPeekZero = 0;
    }
    *next = 1;
    (*counter)++;
}

/**
* Funkcja rightParan przyjmuje jako argumnety wskaznik do stosu *stack, tablice wskaznikow var[], wskaznik na tablice all,
* wartosc calkowita leftIdx, wskaznik *rightIdx oraz liczbe calkowita counter. W wyniku jej dzialania jesli sa spelnione warunki dokonywana jest
* optymlizacja. Jesli nie lewy indeks jest usatwainy za sparowny z nim lewym nawiasem.
*/

int rightParan(Stack* stack, int *var[], int* all, int leftIdx, int* rightIdx, int counter)
{
    *rightIdx = leftIdx;
    int l;
    int nestOrNot = pop(stack);
    if(nestOrNot + 1 == counter) // lewy i prawy nawias sa sparowne i nie wystepuje midzy nimmi zaden inny
    {
        l = pop(stack);
        int check = checkIfDiff(all, l, *rightIdx);
        if(check != 1) // pierwsza litera za zawiasem jest rozna od pozostalych
        {
            optimization(var, all, l, *rightIdx);
        }
        l = *rightIdx;
    }
    else // miedzy nawiasami sa inne nawaisy
    {
        if(nestOrNot >= 0)
        {
            l = pop(stack) - 1;
        }
        else
        {
            l = leftIdx;
            *rightIdx = leftIdx;
        }
    }
    return l;
}

/**
* Funkcja normalLoop przyjmuje tablice wskaznikow var[], wskaznik na tablice all,
* wartosc calkowita leftIdx, wskaznik *arrTemp oraz *next. W wyniku jej dzialania do zmiennych sa dodwanw lub
* odejmowane 1.
*/


void normalLoop(int* var[], int* all, int leftIdx, int* arrTemp, int *next)
{
    arrTemp = extendIfNeededOne(var[all[leftIdx]-97]);
    if(*next == 1)
    {
        subOne(arrTemp);
        *next = 0;
    }
    else
    {
        addOne(arrTemp, arrTemp[0]);
    }
    var[all[leftIdx]-97] = arrTemp;
}

/**
* Funckja fillNull przyjmuje pusta tablice var[] i jej dlugosc. Nastepnie jest ona inicjalizowana Nullami.
*/

void fillNull(int* var[], int len)
{
    for(int i = 0; i < len; i++)
    {
        var[i] = NULL;
    }
}

/**
* Funkcja freeRest przyjmuje wskaznik do stosu *stack i do tablicy all. W wyniku jej dzialanaia uwalania jest pamiec i a jest ustawiany na NULL
*/

int* freeRest(Stack *stack, int* all)
{
    free(stack->array);
    free(stack);
    free(all);
    int *a = NULL;
    return a;
}

/**
* Funkcja freeArrays przyjmuje jako argument tablice wskaznikow var[] i jej dlugosc len. Nastepnie jest uwalniana pamiec.
*/

void freeArrays(int* var[], int len)
{
    for(int i = 0; i < len; i++)
    {
        free(var[i]);
    }
}

/**
* Funckja zeroTheVa jako argumnety przyjmuje wskanizki: counter, len, isPeekZero, rightIdx, next, lenLine i ustawia wartosci przez nie
* wskazywane na zero.
*/

void zeroTheVar(int *counter, int* len, int* isPeekZero, int* rightIdx, int* next, int* lenLine)
{
    *counter = 0;
    *len = 0;
    *isPeekZero = 0;
    *rightIdx = 0;
    *next = 0;
    *lenLine = 0;
}

/**
* Funkcja readLine nie przyjmuje zadnych argumentow. W wyniku jej dzialania wykonwyany jest program.
*/

void readLine(void)
{
    int *all = NULL;
    int lenLine = 0;
    int counter = 0;
    int len = 0;
    int letter;
    int rightIdx = 0;
    int isPeekZero = 0;
    int next = 0;
    int flag = 1;
    int lenParan;
    int *arrTemp = NULL;
    int *var[LENARRAY];
    fillNull(var, LENARRAY);
    while((letter = getchar()) != EOF)
    {
        if(letter != NEWLINE && letter != EQUAL && flag == 1)
        {
            if(counter == len || counter == 1)
            {
                len = extend(len);
                all = (int*)realloc(all, (size_t) len * sizeof(int));
            }
            all[counter] = letter;
            counter++;
        }
        if(letter == EQUAL || flag == 0)
        {
            flag = 0;
            if(letter == NEWLINE) flag = 1;
            if(letter != EQUAL && letter != NEWLINE) printResult(var[letter - 97]);
        }
        else if(letter == NEWLINE && flag == 1)
        {
            lenLine = counter;
            counter = 1;
            lenParan = (int)(lenLine/2) + 2;
            Stack *stack = createStack(lenParan);
            for(int leftIdx = 0; leftIdx < lenLine; leftIdx++)
            {
                if(all[leftIdx] == LEFTPARA)
                {
                    leftParan(stack, var, all, leftIdx, &counter, &next, &isPeekZero);
                }
                else if(all[leftIdx] == RIGHTPARA && isPeekZero == 0)
                {
                    leftIdx = rightParan(stack, var, all, leftIdx, &rightIdx, counter);
                }
                else if(isPeekZero == 0)
                {
                    normalLoop(var, all, leftIdx, arrTemp, &next);
                }
                else if(isPeekZero == 1 && all[leftIdx-1] == LEFTPARA)
                {
                    if(leftIdx < rightIdx)
                    {
                        leftIdx = rightIdx;
                    }
                }
                //printResult(var[106-97]);
                //printResult(var[107-97]);
                //printResult(var[108-97]);
            }
            all = freeRest(stack, all);
        }
        if(letter == NEWLINE)
        {
            zeroTheVar(&counter, &len, &isPeekZero, &rightIdx, &next, &lenLine);
        }
    }
    freeArrays(var, LENARRAY);
    free(all);
}

int main(void)
{
    readLine();
    return 0;
}