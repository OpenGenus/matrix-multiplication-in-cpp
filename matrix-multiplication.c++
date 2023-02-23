#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>

using namespace std;

int Number_of_Threads;
int p, q, r;

vector<vector<int>> matrixA;
vector<vector<int>> matrixB;
vector<vector<int>> matrixC;

int rowOfC = 0;

void *operation(void *arg)
{
    int i = rowOfC;

    for (int j = 0; j < r; j++)
        for (int k = 0; k < q; k++)
            matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
    ++rowOfC;
    return NULL;
}

int main()
{
    cout << "                \033[33mMatrix Multiplication Using Threads\033[0m" << endl
         << "-------------------------------------------------------------------" << endl
         << "        \033[31mNote: The thread number would be given the value of p " << endl
         << "         so enter the value according to available resources.\033[0m" << endl
         << "Rows and columns of matrix A are p & q" << endl
         << "Rows and columns of matrix B are q & r" << endl
         << endl
         << "Enter number of rows (p) & number of columns (q) of matrix A: ";
    cin >> p >> q;
    cout << "Enter number of columns (r) of matrix B: ";
    cin >> r;
    Number_of_Threads = p;
    matrixA.resize(p);
    for (int i = 0; i < p; i++)
    {
        matrixA[i].resize(q);
    }
    matrixB.resize(q);
    for (int i = 0; i < q; i++)
    {
        matrixB[i].resize(r);
    }
    matrixC.resize(p);
    for (int i = 0; i < p; i++)
    {
        matrixC[i].resize(r);
    }
    char choice;
    cout << "Enter Y/y to enter values to both matrices else random values will be generated: ";
    cin >> choice;
    switch (choice)
    {
    case 'y':
    case 'Y':
        cout << "Enter the values for matrix A: ";
        for (int i = 0; i < p; i++)
        {
            for (int j = 0; j < q; j++)
            {
                cin >> matrixA[i][j];
            }
        }
        cout << "Enter the values for matrix B: ";
        for (int i = 0; i < q; i++)
        {
            for (int j = 0; j < r; j++)
            {
                cin >> matrixB[i][j];
            }
        }
        break;

    default:
        for (int i = 0; i < p; i++)
        {
            for (int j = 0; j < q; j++)
            {
                matrixA[i][j] = rand() % 10;
            }
        }
        for (int i = 0; i < q; i++)
        {
            for (int j = 0; j < r; j++)
            {
                matrixB[i][j] = rand() % 10;
            }
        }
        break;
    }

    cout << endl
         << "\033[1;34mMatrix A:" << endl;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
            cout << matrixA[i][j] << " ";
        cout << endl;
    }

    cout << endl
         << "Matrix B:" << endl;
    for (int i = 0; i < q; i++)
    {
        for (int j = 0; j < r; j++)
            cout << matrixB[i][j] << " ";
        cout << endl;
    }
    cout << "\033[0m";

    pthread_t threads[Number_of_Threads];

    for (int i = 0; i < Number_of_Threads; i++)
    {
        int *point;
        pthread_create(&threads[i], NULL, operation, (void *)(point));
    }

    for (int i = 0; i < Number_of_Threads; i++)
        pthread_join(threads[i], NULL);

    cout << endl
         << "\033[1;32mProduct matrix C is: " << endl;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
            cout << matrixC[i][j] << " ";
        cout << endl;
    }
    cout << "\033[0m";
    return 0;
}
