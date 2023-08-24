#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
#include<algorithm>
using namespace std;

long long comps = 0;
long long swaps = 0;

void bubbleSort(int dados[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
        {
            if (dados[j] < dados[j - 1])
            {
                swap(dados[j], dados[j + 1]);
                swaps++;
            }
            comps++;
        }
}

int main(int argc, char *argv[])
{
    int n = stoi(argv[1]);
    int dados[100000];

    // Abertura de arquivo de entrada e preenchimento dos dados no array
    ifstream entrada("numeros.txt");
    for (int i = 0; i < n; i++)
    {
        entrada >> dados[i];
    }
    entrada.close();

    // Ordenacao e calculo de tempo de ordenacao
    clock_t start = clock();
    bubbleSort(dados, n);
    clock_t end = clock();
    double duracao = double(end - start) / CLOCKS_PER_SEC;

    // Escrita do array ordenado em arquivo
    if (n == 100000)
    {
        ofstream saida("numerosOrdenados.txt");
        for (int i = 0; i < n; i++)
        {
            saida << dados[i] << endl;
        }
        saida.close();
    }
    ofstream data("dadosNumeros.txt", ios::app);

    // Escrita dos dados em arquivo
    data << duracao << "      " << comps << "      " << swaps << endl;
    data.close();

    return 0;
}