// LR.7.2iter.cpp
// Татарський Василь Петрович
// Лабораторна робота №7.2iter
// Опрацювання багатовимірних масивів ітераційним способом
// Варіант 26

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int n, const int Low, const int High);
void Print(int** a, const int n);
int SumSecondaryDiagonal(int** a, const int n);

int main()
{
    srand((unsigned)time(NULL));

    int Low = -9;
    int High = 9;

    int n;
    cout << "n = "; cin >> n;
    cout << endl;

    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];

    Create(a, n, Low, High);
    Print(a, n);

    int sum = SumSecondaryDiagonal(a, n);
    cout << "Suma elementiv pobichnoi diagonali = " << sum << endl;

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int n, const int Low, const int High)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** a, const int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

int SumSecondaryDiagonal(int** a, const int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        // Побічна діагональ: елемент a[i][n-1-i]
        sum += a[i][n - 1 - i];
    }
    return sum;
}