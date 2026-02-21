// LR.7.3.rec.cpp
// Татарський Василь Петрович
// Лабораторна робота №7.3.rec
// Опрацювання динамічних масивів рекурсивним способом
// Варіант 26

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

// --- Вивід / введення / генерація ---
void PrintRow(int** a, const int rowNo, const int colCount, int colNo);
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo);
void InputRow(int** a, const int rowNo, const int colCount, int colNo);
void InputRows(int** a, const int rowCount, const int colCount, int rowNo);
void CreateRow(int** a, const int rowNo, const int colCount,
    const int Low, const int High, int colNo);
void CreateRows(int** a, const int rowCount, const int colCount,
    const int Low, const int High, int rowNo);

// --- Part 1 ---
// Перевіряє, чи рядок rowNo містить від'ємний елемент (починаючи з colNo)
void Part1_NegInRow(int** a, const int colCount, bool& hasNeg,
    int rowNo, int colNo);
// Підраховує суму рядка rowNo (починаючи з colNo)
int  Part1_SumRow(int** a, const int colCount, int rowNo, int colNo);
// Обходить усі рядки; накопичує суму
int  Part1_SumRows(int** a, const int rowCount, const int colCount,
    bool& anyNeg, int rowNo);

// --- Part 2 ---
bool IsMinInRowN(int** a, const int rowNo, const int val,
    const int colCount, int colNo);
bool IsMaxInColK(int** a, const int colNo, const int val,
    const int rowCount, int rowNo);
void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount,
    int& No, const int rowNo, int colNo);
void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount,
    int& No, int rowNo);

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

    CreateRows(a, rowCount, colCount, Low, High, 0);
    // InputRows(a, rowCount, colCount, 0);  // розкоментувати для ручного вводу

    PrintRows(a, rowCount, colCount, 0);

    // --- Завдання 1 ---
    bool anyNeg = false;
    int  sum = Part1_SumRows(a, rowCount, colCount, anyNeg, 0);
    if (anyNeg)
        cout << "\nSum of elements in rows with at least one negative = "
        << sum << endl;
    else
        cout << "\nThere are no negative elements." << endl;

    // --- Завдання 2 ---
    cout << "\nSaddle points: min in row & max in col" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
    int No = 0;
    Part2_SaddlePointRows(a, rowCount, colCount, No, 0);
    if (No == 0) cout << "  (none)" << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

// ---------------------------------------------------------------
// Вивід / введення / генерація
void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << setw(5) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    cout << endl;
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
}

void CreateRow(int** a, const int rowNo, const int colCount,
    const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount,
    const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

// ---------------------------------------------------------------
// Part 1

// Перевіряє, чи рядок rowNo містить від'ємний, починаючи з colNo
void Part1_NegInRow(int** a, const int colCount, bool& hasNeg,
    int rowNo, int colNo)
{
    if (a[rowNo][colNo] < 0)
        hasNeg = true;
    if (!hasNeg && colNo < colCount - 1)
        Part1_NegInRow(a, colCount, hasNeg, rowNo, colNo + 1);
}

// Сума елементів рядка rowNo, починаючи з colNo
int Part1_SumRow(int** a, const int colCount, int rowNo, int colNo)
{
    if (colNo < colCount - 1)
        return a[rowNo][colNo] + Part1_SumRow(a, colCount, rowNo, colNo + 1);
    else
        return a[rowNo][colNo];
}

// Обходить рядки і накопичує суму тих, що мають від'ємний
int Part1_SumRows(int** a, const int rowCount, const int colCount,
    bool& anyNeg, int rowNo)
{
    bool rowHasNeg = false;
    Part1_NegInRow(a, colCount, rowHasNeg, rowNo, 0);

    int rowSum = 0;
    if (rowHasNeg)
    {
        anyNeg = true;
        rowSum = Part1_SumRow(a, colCount, rowNo, 0);
    }

    if (rowNo < rowCount - 1)
        rowSum += Part1_SumRows(a, rowCount, colCount, anyNeg, rowNo + 1);

    return rowSum;
}

// ---------------------------------------------------------------
// Part 2

// Чи є val мінімальним у рядку rowNo, починаючи з colNo?
bool IsMinInRowN(int** a, const int rowNo, const int val,
    const int colCount, int colNo)
{
    if (a[rowNo][colNo] < val)
        return false;
    if (colNo < colCount - 1)
        return IsMinInRowN(a, rowNo, val, colCount, colNo + 1);
    return true;
}

// Чи є val максимальним у стовпці colNo, починаючи з rowNo?
bool IsMaxInColK(int** a, const int colNo, const int val,
    const int rowCount, int rowNo)
{
    if (a[rowNo][colNo] > val)
        return false;
    if (rowNo < rowCount - 1)
        return IsMaxInColK(a, colNo, val, rowCount, rowNo + 1);
    return true;
}

// Перевіряє елементи рядка rowNo, починаючи з colNo
void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount,
    int& No, const int rowNo, int colNo)
{
    int val = a[rowNo][colNo];
    if (IsMinInRowN(a, rowNo, val, colCount, 0) &&
        IsMaxInColK(a, colNo, val, rowCount, 0))
        cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;

    if (colNo < colCount - 1)
        Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, colNo + 1);
}

// Обходить усі рядки
void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount,
    int& No, int rowNo)
{
    Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, 0);
    if (rowNo < rowCount - 1)
        Part2_SaddlePointRows(a, rowCount, colCount, No, rowNo + 1);
}