#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

// Рекурсивне формування елементів масиву випадковими числами
void Create(int* a, const int size, const int Low, const int High, int i = 0)
{
    a[i] = Low + rand() % (High - Low + 1);
    if (i < size - 1)
        Create(a, size, Low, High, i + 1);
}

// Рекурсивне форматне виведення елементів масиву в рядок
void Print(const int* a, const int size, int i = 0)
{
    cout << setw(4) << a[i];
    if (i < size - 1)
        Print(a, size, i + 1);
    else
        cout << endl;
}

// 1.1. Рекурсивне обчислення добутку елементів масиву з парними номерами (0, 2, 4...)
int ProductEvenIndices(const int* a, const int size, int i = 0)
{
    if (i < size)
        return a[i] * ProductEvenIndices(a, size, i + 2);
    else
        return 1;
}

// Рекурсивний пошук індексу першого нульового елемента (-1, якщо 0 немає)
int FirstZero(const int* a, const int size, int i = 0)
{
    if (a[i] == 0)
        return i;
    if (i < size - 1)
        return FirstZero(a, size, i + 1);
    else
        return -1;
}

// Рекурсивний пошук індексу останнього нульового елемента (-1, якщо 0 немає)
int LastZero(const int* a, int i)
{
    if (a[i] == 0)
        return i;
    if (i > 0)
        return LastZero(a, i - 1);
    else
        return -1;
}

// Допоміжна рекурсивна функція для обчислення суми між елементами
int SumBetweenZerosHelper(const int* a, const int last, int i)
{
    if (i < last)
        return a[i] + SumBetweenZerosHelper(a, last, i + 1);
    else
        return 0;
}

// 1.2. Обчислення суми елементів між першим і останнім нулями
int SumBetweenZeros(const int* a, const int size)
{
    int first = FirstZero(a, size);
    int last = LastZero(a, size - 1);

    if (first == -1 || last == -1 || first >= last - 1)
        return 0;

    return SumBetweenZerosHelper(a, last, first + 1);
}

// Рекурсивне копіювання додатних елементів та нулів (>= 0)
void CopyNonNegative(const int* a, int* temp, const int size, int i, int& index)
{
    if (i < size)
    {
        if (a[i] >= 0)
            temp[index++] = a[i];
        CopyNonNegative(a, temp, size, i + 1, index);
    }
}

// Рекурсивне копіювання від'ємних елементів (< 0)
void CopyNegative(const int* a, int* temp, const int size, int i, int& index)
{
    if (i < size)
    {
        if (a[i] < 0)
            temp[index++] = a[i];
        CopyNegative(a, temp, size, i + 1, index);
    }
}

// Рекурсивне перенесення елементів із тимчасового масиву в початковий
void CopyArray(int* a, const int* temp, const int size, int i = 0)
{
    if (i < size)
    {
        a[i] = temp[i];
        CopyArray(a, temp, size, i + 1);
    }
}

// 2. Рекурсивне перетворення масиву: спочатку >= 0, потім < 0 зі збереженням порядку
void Rearrange(int* a, const int size)
{
    int* temp = new int[size];
    int index = 0;

    CopyNonNegative(a, temp, size, 0, index);
    CopyNegative(a, temp, size, 0, index);
    CopyArray(a, temp, size, 0);

    delete[] temp;
}

int main()
{
    // Налаштування консолі для виведення кирилиці без "кракозябр"
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand((unsigned)time(NULL));

    int n;
    cout << "n = ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Розмір масиву повинен бути більшим за 0!" << endl;
        return 1;
    }

    int* a = new int[n];

    int Low = -10;
    int High = 10;

    Create(a, n, Low, High);

    cout << "\nПочатковий масив:" << endl;
    Print(a, n);

    int product = ProductEvenIndices(a, n);
    cout << "\n1.1. Добуток елементів з парними номерами: " << product << endl;

    int sum = SumBetweenZeros(a, n);
    cout << "1.2. Сума елементів між першим і останнім 0: " << sum << endl;

    Rearrange(a, n);

    cout << "\nМодифікований масив (спочатку >= 0, потім < 0):" << endl;
    Print(a, n);

    delete[] a;

    return 0;
}