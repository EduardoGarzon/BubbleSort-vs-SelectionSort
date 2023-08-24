#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>

struct Pessoa
{
    int Codigo;
    std::string Nome;
};

long long countCompare = 0;
long long countChanges = 0;

bool Less(const Pessoa &p1, const Pessoa &p2)
{
    countCompare++;
    if (p1.Codigo < p2.Codigo)
    {
        return true;
    }
    else if (p1.Codigo > p2.Codigo)
    {
        return false;
    }
    else
    {
        return p1.Nome < p2.Nome;
    }
}

void bubbleSort(std::vector<Pessoa> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (Less(arr[j + 1], arr[j]))
            {
                std::swap(arr[j], arr[j + 1]);
                countChanges++;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Nenhum argumento fornecido." << std::endl;
        return 0;
    }

    int tamanho = std::stoi(argv[1]);

    std::ifstream inputFile("pessoas.txt");
    if (!inputFile)
    {
        std::cout << "Erro ao abrir arquivo pessoas.txt" << std::endl;
        return 1;
    }

    std::ofstream outputFile("pessoasOrdenados.txt");
    if (!outputFile)
    {
        std::cout << "Erro ao abrir arquivo pessoasOrdenados.txt" << std::endl;
        return 1;
    }

    std::vector<Pessoa> dados;

    std::string line;
    for (int i = 0; i < tamanho && std::getline(inputFile, line); i++)
    {
        std::stringstream ss(line);
        std::string codStr, nome;
        std::getline(ss, codStr, '\t');
        std::getline(ss, nome, '\t');

        int cod = std::stoi(codStr);
        Pessoa person{cod, nome};

        dados.push_back(person);
    }

    std::clock_t start = std::clock();

    bubbleSort(dados);

    double elapsed = (std::clock() - start) / (double)CLOCKS_PER_SEC;

    for (const auto &pessoa : dados)
    {
        outputFile << pessoa.Codigo << "\t" << pessoa.Nome << std::endl;
    }

    // Escrita dos dados em arquivo
    std::ofstream data("dadosPessoas.txt", std::ios::app);
    data << elapsed << "     " << countCompare << "     " << countChanges << std::endl;
    data.close();

    return 0;
}
