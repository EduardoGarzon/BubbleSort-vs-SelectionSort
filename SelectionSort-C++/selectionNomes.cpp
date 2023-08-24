#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

long long countCompare = 0;
long long countChanges = 0;

void selectionSort(vector<string> &arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;
        for (int j = i + 1; j < n; j++)
        {
            countCompare++;
            if (arr[j] < arr[menor])
            {
                menor = j;
            }
        }
        swap(arr[menor], arr[i]);
        countChanges++;
    }
}

int main(int argc, char *argv[])
{
    string argumento = argv[1]; // recebe via terminal a quantidade de registros
    // verifica se foi passado algum argumento
    if (argumento.empty())
    {
        cout << "Nenhum argumento fornecido." << endl;
        return 0;
    }

    // converte argumento para um número inteiro
    int tamanho = stoi(argumento);
    // verifica erro na conversão
    if (tamanho == 0)
    {
        cout << "Erro ao converter argumento para inteiro." << endl;
        return 1;
    }

    // Abre arquivo dos dados a serem ordenados
    ifstream file("nomes.txt");
    if (!file.is_open())
    {
        cout << "Erro ao abrir arquivo nomes.txt" << endl;
        return 1;
    }

    // Abre arquivo para armazenar os dados ordenados
    ofstream file2("nomesOrdenados.txt");
    if (!file2.is_open())
    {
        cout << "Erro ao abrir arquivo nomesOrdenados.txt" << endl;
        return 1;
    }

    // Cria um vetor para armazenar os dados lidos
    vector<string> dados;

    // Lê cada linha e armazena no vetor
    string linha;
    for (int i = 0; i < tamanho && getline(file, linha); i++)
    {
        dados.push_back(linha);
    }

    file.close();

    // Medir o tempo de execução
    clock_t start = clock();

    // Ordena os dados
    selectionSort(dados, tamanho);

    // Calcular o tempo de execução
    double elapsed = (clock() - start) / (double)CLOCKS_PER_SEC;

    // Escreve os dados ordenados no arquivo
    for (int i = 0; i < tamanho; i++)
    {
        file2 << dados[i] << endl;
    }

    file2.close();

    // Escrita dos dados em arquivo
    ofstream data("dadosNomes.txt", ios::app);
    data << elapsed << "     " << countCompare << "     " << countChanges << endl;
    data.close();

    return 0;
}
