#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void PrintMatrix(int** A, const int k, const int n, int i = 0, int j = 0) {
    if (i >= k) {
        cout << endl;
        return;
    }

    cout << setw(4) << A[i][j];

    if (j < n - 1) {
        PrintMatrix(A, k, n, i, j + 1);
    }
    else {
        cout << endl;
        PrintMatrix(A, k, n, i + 1, 0);
    }
}

void MatrixValue(int** A, const int k, const int n, const int Low, const int High, int i = 0, int j = 0) {
    if (i >= k) {
        return;
    }

    A[i][j] = Low + rand() % (High - Low + 1);

    if (j < n - 1) {
        MatrixValue(A, k, n, Low, High, i, j + 1);
    }
    else {
        MatrixValue(A, k, n, Low, High, i + 1, 0);
    }
}

void FindMinRecursive(int** A, const int k, const int n, int& min1, int& min2, int i = 0, int j = 0) {
    if (i >= k) {
        return;
    }

    if (j == 2 && A[i][j] < min1) {
        min1 = A[i][j];
    }
    if (j == 4 && A[i][j] < min2) {
        min2 = A[i][j];
    }

    if (j < n - 1) {
        FindMinRecursive(A, k, n, min1, min2, i, j + 1);
    }
    else {
        FindMinRecursive(A, k, n, min1, min2, i + 1, 0);
    }
}

int MaxAmongMinRecursive(int** A, const int k, const int n, int min1, int min2, int i = 0) {
    if (i >= k) {
        return (min1 > min2) ? min1 : min2;
    }

    FindMinRecursive(A, k, n, min1, min2, i);
    return MaxAmongMinRecursive(A, k, n, min1, min2, i + 1);
}

int main() {
    int Low = 5;
    int High = 25;

    const int k = 5;
    const int n = 5;

    int min1 = INT_MAX;
    int min2 = INT_MAX;

    int** A = new int* [k];

    for (int i = 0; i < k; i++)
        A[i] = new int[n];

    srand(static_cast<unsigned>(time(0)));

    MatrixValue(A, k, n, Low, High);

    cout << "Matrix: " << endl;
    PrintMatrix(A, k, n);

    FindMinRecursive(A, k, n, min1, min2);
    cout << "MinElement1 = " << min1 << endl;
    cout << "MinElement2 = " << min2 << endl;

    int Z = MaxAmongMinRecursive(A, k, n, min1, min2);
    cout << "Max Among Min = " << Z << endl;

    for (int i = 0; i < k; i++)
        delete[] A[i];
    delete[] A;

    return 0;
}
