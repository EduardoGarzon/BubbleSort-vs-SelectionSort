#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

long long countCompare = 0;
long long countChanges = 0;

void bubbleSort(vector<string> &arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < (n - i - 1); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                countChanges++;
            }
            countCompare++;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Nenhum argumento fornecido." << endl;
        return 0;
    }

    int tamanho = atoi(argv[1]);
    if (tamanho <= 0)
    {
        cout << "Tamanho inválido." << endl;
        return 1;
    }

    ifstream inputFile("nomes.txt");
    if (!inputFile)
    {
        cout << "Erro ao abrir o arquivo nomes.txt" << endl;
        return 1;
    }

    ofstream outputFile("nomesOrdenados.txt");
    if (!outputFile)
    {
        cout << "Erro ao abrir o arquivo nomesOrdenados.txt" << endl;
        return 1;
    }

    vector<string> dados;
    std::string linha;
    int i = 0;

    while (i < tamanho && std::getline(inputFile, linha))
    {
        dados.push_back(linha);
        i++;
    }
    inputFile.close();

    clock_t start = clock();
    bubbleSort(dados, tamanho);
    clock_t end = clock();
    double duracao = double(end - start) / CLOCKS_PER_SEC;

    for (const string &dado : dados)
    {
        outputFile << dado << endl;
    }
    outputFile.close();

    // Escrita dos dados em arquivo
    ofstream data("dadosNomes.txt", ios::app);
    data << duracao << "     " << countCompare << "     " << countChanges << endl;
    data.close();

    return 0;
}
