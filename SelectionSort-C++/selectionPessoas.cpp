#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

long swaps = 0;
long comps = 0;

struct Pessoa
{
    int codigo;
    string nome;
};

void selectionSort(vector<Pessoa> &arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            comps++;
            if (arr[j].codigo < arr[min_idx].codigo || (arr[j].codigo == arr[min_idx].codigo && arr[j].nome < arr[min_idx].nome))
            {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
        swaps++;
    }
}

int main(int argc, char *argv[])
{
    vector<Pessoa> pessoas;
    int n = stoi(argv[1]);

    // Abertura de arquivo de entrada e preenchimento dos dados no vetor
    ifstream entrada("pessoas.txt");
    for (int i = 0; i < n; i++)
    {
        string aux;
        getline(entrada, aux);
        size_t pos = aux.find_first_of("\t");
        int codigo = stoi(aux.substr(0, pos));
        string nome = aux.substr(pos + 1);
        pessoas.push_back({codigo, nome});
    }
    entrada.close();

    // Ordenacao e calculo de tempo de ordenacao
    clock_t start = clock();
    selectionSort(pessoas, n);
    clock_t end = clock();
    double duracao = double(end - start) / CLOCKS_PER_SEC;

    // Escrita do vetor ordenado em arquivo
    if (n == 100000)
    {
        ofstream saida("pessoasOrdenadas.txt");
        for (int i = 0; i < n; i++)
        {
            saida << setw(8) << left << pessoas[i].codigo;
            saida << " " << pessoas[i].nome << endl;
        }
        saida.close();
    }

    // Escrita dos dados em arquivo
    ofstream data("dadosPessoas.txt", ios::app);
    data << duracao << "     " << comps << "     " << swaps << endl;
    data.close();

    return 0;
}
