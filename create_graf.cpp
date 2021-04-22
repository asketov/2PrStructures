#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void Centr_grafa(int** m, int n);

struct node
{
    int number_node;
    int length;
    node* next = NULL;
}**m; //список смежности


int main()
{
    setlocale(0, "Russian");
    int** k; //треугольная матрица весов
    string fil,line;
    int n,i=0,j=1;
    struct node* l, *f;
    cout << "Введите название файла:";
    cin >> fil;
    cout << "Введите количество вершин:";
    cin >> n;
    m = new struct node * [n];
    k = new int * [n];
    for (; j < n; j++)
    {
        k[j] = new int[j];
    }
    ifstream file(fil);
    if (file.is_open())
    {
        for (i = 1; i < n; i++)
        {
            getline(file, line);
            for (j = 0; j < i; j++)
            {
                file >> k[i][j];
                if (k[i][j] > 0)
                {
                    if (m[i] == NULL)
                    {
                        m[i] = new struct node;
                        m[i]->length = k[i][j];
                        m[i]->number_node = j + 1;
                    }
                    else
                    {
                        l = m[i];
                        m[i] = new struct node;
                        m[i]->length = k[i][j];
                        m[i]->number_node = j + 1;
                        m[i]->next = l;
                    }
                    if (m[j] == NULL)
                    {
                        m[j] = new struct node;
                        m[j]->length = k[i][j];
                        m[j]->number_node = i;
                    }
                    else
                    {
                        l = m[j];
                        m[j] = new struct node;
                        m[j]->length = k[i][j];
                        m[j]->number_node = i;
                        m[j]->next = l;
                    }
                }
            }
        }
    }
    file.close();
    Centr_grafa(k, n);
    for (i = 1; i < n; i++)
    {
        delete k[i];
    }
    delete k;
}


void Centr_grafa(int** m, int n)
{
    int i, j, k, min1=0, max, Imin=0;
    int** A;
    A = new int* [n]; //матрица кратчайших путей между всеми парами вершин
    for (i = 0; i < n; i++)
    {
        A[i] = new int[n];
    }
    for (i = n - 2; i >= 0; i--)
    {
        for (j = i; j >= 0; j--)
        {
            A[i + 1][j] = m[i + 1][j];
            A[j][i + 1] = m[i + 1][j];
        }
    }
    for (i = 0; i < n; i++)
        A[i][i] = 0;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (A[i][k] + A[k][j] < A[i][j]) /* если путь через k короче*/ 
                {
                    A[i][j] = A[i][k] + A[k][j]; /* запоминаем длину пути*/ 
                }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    
    for (i = 0; i < n; i++)
    {
        max = 0;
        for (j = 0; j < n; j++)
        {
            if (A[j][i] > max)
            {
                max = A[j][i];
            }
        }
        if (i == 0)
        {
            min1 = max;
            Imin = i;
        }
        else if (max < min1)
        {
            min1 = max;
            Imin=i;
        }
    }
    cout << "Центром графа является вершина под номером:" << Imin+1;
}
