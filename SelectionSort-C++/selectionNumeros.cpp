#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

long long swaps = 0;
long long comps = 0;

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            comps++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[min_idx], arr[i]);
        swaps++;
    }
}

int main(int argc, char *argv[])
{
    int numeros[100000];
    int n = stoi(argv[1]);

    // Abertura de arquivo de entrada e preenchimento dos dados no array
    ifstream entrada("numeros.txt");
    for (int i = 0; i < n; i++)
    {
        entrada >> numeros[i];
    }
    entrada.close();

    // Ordenacao e calculo de tempo de ordenacao
    clock_t start = clock();
    selectionSort(numeros, n);
    clock_t end = clock();
    double duracao = double(end - start) / CLOCKS_PER_SEC;

    // Escrita do array ordenado em arquivo
    if (n == 100000)
    {
        ofstream saida("numerosOrdenados.txt");
        for (int i = 0; i < n; i++)
        {
            saida << numeros[i] << endl;
        }
        saida.close();
    }
    ofstream data("dadosNumeros.txt", ios::app);

    // Escrita dos dados em arquivo
    data << duracao << "     " << comps << "     " << swaps << endl;
    data.close();
    return 0;
}
