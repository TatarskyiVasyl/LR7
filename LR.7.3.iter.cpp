// LR.7.3.iter.cpp
// Татарський Василь Петрович
// Лабораторна робота №7.3.iter
// Опрацювання динамічних масивів ітераційнийним способом
// Варіант 26

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void   Create(int** a, const int rowCount, const int colCount,
    const int Low, const int High);
void   Input(int** a, const int rowCount, const int colCount);
void   Print(int** a, const int rowCount, const int colCount);

// Part 1
int    Part1_Sum(int** a, const int rowCount, const int colCount,
    bool& hasNeg);

// Part 2 helpers
bool   IsMinInRowN(int** a, const int rowNo, const int k,
    const int colCount);
bool   IsMaxInColK(int** a, const int colNo, const int n,
    const int rowCount);
void   Part2_SaddlePoint(int** a, const int rowCount, const int colCount);

// ---------------------------------------------------------------
int main()
{
    srand((unsigned)time(NULL));

    const int Low = -10, High = 10;
    int rowCount, colCount;

    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    // Input(a, rowCount, colCount);   // розкоментувати для ручного вводу

    Print(a, rowCount, colCount);

    // --- Завдання 1 ---
    bool hasNeg = false;
    int  sum = Part1_Sum(a, rowCount, colCount, hasNeg);
    if (hasNeg)
        cout << "\nSum of elements in rows with at least one negative = "
        << sum << endl;
    else
        cout << "\nThere are no negative elements." << endl;

    // --- Завдання 2 ---
    cout << endl;
    Part2_SaddlePoint(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

// ---------------------------------------------------------------
void Create(int** a, const int rowCount, const int colCount,
    const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Input(int** a, const int rowCount, const int colCount)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
        {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
}

void Print(int** a, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(5) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

// ---------------------------------------------------------------
// Part 1: сума елементів у рядках з хоча б одним від'ємним.
// hasNeg — чи є взагалі такі рядки.
int Part1_Sum(int** a, const int rowCount, const int colCount,
    bool& hasNeg)
{
    int sum = 0;
    hasNeg = false;

    for (int i = 0; i < rowCount; i++)
    {
        // перевіряємо, чи є від'ємний у рядку i
        bool rowHasNeg = false;
        for (int j = 0; j < colCount; j++)
            if (a[i][j] < 0) { rowHasNeg = true; break; }

        if (rowHasNeg)
        {
            hasNeg = true;
            for (int j = 0; j < colCount; j++)
                sum += a[i][j];
        }
    }
    return sum;
}

// ---------------------------------------------------------------
// Part 2 helpers

// Чи є a[rowNo][k] мінімальним у рядку rowNo?
bool IsMinInRowN(int** a, const int rowNo, const int k,
    const int colCount)
{
    for (int j = 0; j < colCount; j++)
        if (a[rowNo][j] < a[rowNo][k])
            return false;
    return true;
}

// Чи є a[n][colNo] максимальним у стовпці colNo?
bool IsMaxInColK(int** a, const int colNo, const int n,
    const int rowCount)
{
    for (int i = 0; i < rowCount; i++)
        if (a[i][colNo] > a[n][colNo])
            return false;
    return true;
}

// Виводить сідлові точки: мінімум у рядку І максимум у стовпці
void Part2_SaddlePoint(int** a, const int rowCount, const int colCount)
{
    cout << "Saddle points: min in row & max in col" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;

    int No = 0;
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (IsMinInRowN(a, i, j, colCount) &&
                IsMaxInColK(a, j, i, rowCount))
                cout << setw(4) << ++No
                << setw(6) << i
                << setw(6) << j << endl;

    if (No == 0)
        cout << "  (none)" << endl;
}