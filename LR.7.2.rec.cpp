// LR.7.2.rec.cpp
// Татарський Василь Петрович
// Лабораторна робота №7.2.rec
// Опрацювання багатовимірних масивів рекурсивним способом
// Варіант 26

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo);
void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo);
void PrintRow(int** a, const int rowNo, const int n, int colNo);
void PrintRows(int** a, const int n, int rowNo);
int SumSecondaryDiagonal(int** a, const int n, int i);

int main()
{
    srand((unsigned)time(NULL));

    int n;
    cout << "n = "; cin >> n;
    cout << endl;

    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];

    int Low = -9, High = 9;
    CreateRows(a, n, Low, High, 0);

    PrintRows(a, n, 0);

    int sum = SumSecondaryDiagonal(a, n, 0);
    cout << "Suma elementiv pobichnoi diagonali = " << sum << endl;

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < n - 1)
        CreateRow(a, rowNo, n, Low, High, colNo + 1);
}

void CreateRows(int** a, const int n, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, n, Low, High, 0);
    if (rowNo < n - 1)
        CreateRows(a, n, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int n, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < n - 1)
        PrintRow(a, rowNo, n, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int n, int rowNo)
{
    PrintRow(a, rowNo, n, 0);
    if (rowNo < n - 1)
        PrintRows(a, n, rowNo + 1);
    else
        cout << endl;
}

int SumSecondaryDiagonal(int** a, const int n, int i)
{
    if (i == n - 1)
        return a[i][n - 1 - i];
    else
        return a[i][n - 1 - i] + SumSecondaryDiagonal(a, n, i + 1);
}