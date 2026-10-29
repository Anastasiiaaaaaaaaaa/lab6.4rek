#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Рекурсивні функції для тестування
int ProductEvenIndices(const int* a, const int size, int i = 0)
{
    if (i < size)
        return a[i] * ProductEvenIndices(a, size, i + 2);
    else
        return 1;
}

int FirstZero(const int* a, const int size, int i = 0)
{
    if (a[i] == 0)
        return i;
    if (i < size - 1)
        return FirstZero(a, size, i + 1);
    else
        return -1;
}

int LastZero(const int* a, int i)
{
    if (a[i] == 0)
        return i;
    if (i > 0)
        return LastZero(a, i - 1);
    else
        return -1;
}

int SumBetweenZerosHelper(const int* a, const int last, int i)
{
    if (i < last)
        return a[i] + SumBetweenZerosHelper(a, last, i + 1);
    else
        return 0;
}

int SumBetweenZeros(const int* a, const int size)
{
    int first = FirstZero(a, size);
    int last = LastZero(a, size - 1);

    if (first == -1 || last == -1 || first >= last - 1)
        return 0;

    return SumBetweenZerosHelper(a, last, first + 1);
}

void CopyNonNegative(const int* a, int* temp, const int size, int i, int& index)
{
    if (i < size)
    {
        if (a[i] >= 0)
            temp[index++] = a[i];
        CopyNonNegative(a, temp, size, i + 1, index);
    }
}

void CopyNegative(const int* a, int* temp, const int size, int i, int& index)
{
    if (i < size)
    {
        if (a[i] < 0)
            temp[index++] = a[i];
        CopyNegative(a, temp, size, i + 1, index);
    }
}

void CopyArray(int* a, const int* temp, const int size, int i = 0)
{
    if (i < size)
    {
        a[i] = temp[i];
        CopyArray(a, temp, size, i + 1);
    }
}

void Rearrange(int* a, const int size)
{
    int* temp = new int[size];
    int index = 0;

    CopyNonNegative(a, temp, size, 0, index);
    CopyNegative(a, temp, size, 0, index);
    CopyArray(a, temp, size, 0);

    delete[] temp;
}

namespace UnitTestLab64Rec
{
    TEST_CLASS(UnitTestLab64Rec)
    {
    public:

        // Тест 1: Перевірка рекурсивного обчислення добутку елементів з парними індексами (0, 2, 4...)
        TEST_METHOD(TestProductEvenIndices)
        {
            const int size = 5;
            // Парні індекси [0, 2, 4]: елементи 2, 3, 4 => 2 * 3 * 4 = 24
            int a[size] = { 2, 5, 3, 7, 4 };
            int expected = 24;

            int actual = ProductEvenIndices(a, size);

            Assert::AreEqual(expected, actual);
        }

        // Тест 2: Перевірка рекурсивного обчислення суми елементів між першим і останнім 0
        TEST_METHOD(TestSumBetweenZeros)
        {
            const int size = 6;
            // Нулі на індексах 1 та 4. Елементи між ними: 3 + 4 = 7
            int a[size] = { 1, 0, 3, 4, 0, 5 };
            int expected = 7;

            int actual = SumBetweenZeros(a, size);

            Assert::AreEqual(expected, actual);
        }

        // Тест 3: Перевірка рекурсивного перетворення масиву (спочатку >= 0, потім < 0 зі збереженням порядку)
        TEST_METHOD(TestRearrange)
        {
            const int size = 5;
            int a[size] = { -2, 5, 0, -3, 4 };
            int expected[size] = { 5, 0, 4, -2, -3 };

            Rearrange(a, size);

            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(expected[i], a[i]);
            }
        }
    };
}