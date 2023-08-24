package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
	"time"
)

var countCompare int64
var countChanges int64

type Pessoa struct {
	Codigo int
	Nome   string
}

func Swap(menor *Pessoa, atual *Pessoa) {
	countChanges++
	aux := *atual
	*atual = *menor
	*menor = aux
}

func selectionSort(arr *[]Pessoa, n int) {
	for i := 0; i < n-1; i++ {
		menor := i
		for j := i + 1; j < n; j++ {
			if (*arr)[j].Codigo < (*arr)[menor].Codigo {
				menor = j
			} else if (*arr)[j].Codigo == (*arr)[menor].Codigo {
				if strings.Compare((*arr)[j].Nome, (*arr)[menor].Nome) < 0 {
					menor = j
				}
			}
			countCompare++
		}
		Swap(&(*arr)[menor], &(*arr)[i])
	}
}

func main() {
	argumento := os.Args[1] // recebe via terminal a quantidade de registro
	// verifica se foi passado algum argumento
	if len(argumento) == 0 {
		fmt.Println("Nenhum argumento fornecido.")
		os.Exit(0)
	}

	// converte argumento para um numero inteiro
	tamanho, err := strconv.Atoi(argumento)
	// verifica erro na conversao
	if err != nil {
		fmt.Printf("Erro ao converter argumento para inteiro.")
		os.Exit(1)
	}

	// Abre arquivo dos dados a serem ordenados
	file, ferror := os.Open("pessoas.txt")
	if ferror != nil {
		fmt.Println("Erro ao abrir arquivo pessoas.txt")
		os.Exit(1)
	}

	// Abre arquivo para armazenar os dados ordenados
	file2, ferror := os.OpenFile("pessoasOrdenados.txt", os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0644)
	if ferror != nil {
		fmt.Println("Erro ao abrir arquivo pessoasOrdenados.txt: ", ferror)
		os.Exit(1)
	}

	// Fecha arquivo dos dados iniciais
	defer func() {
		if ferror := file.Close(); ferror != nil {
			fmt.Println("Erro ao fechar arquivo pessoas.txt")
			os.Exit(1)
		}
	}()

	// Fecha arquivo dos dados ordenados
	defer func() {
		if ferror := file2.Close(); ferror != nil {
			fmt.Println("Erro ao fechar arquivo pessoasOrdenados.txt")
			os.Exit(1)
		}
	}()

	// cria um slice de pessoas
	dados := make([]Pessoa, 0)

	// scanner para ler cada linha
	scanner := bufio.NewScanner(file)
	for i := 0; i < tamanho && scanner.Scan(); i++ {
		line := scanner.Text()                 // leitura da linha
		parts := strings.SplitN(line, "\t", 2) // divide a linha pela tabulacao (cod \t name)

		// verifica divisao da linha
		if len(parts) != 2 {
			fmt.Println("Formato inválido no arquivo pessoas.txt")
			os.Exit(1)
		}

		// converte codigo string para inteiro
		cod, err := strconv.Atoi(parts[0])
		if err != nil {
			fmt.Println("Erro ao converter código para inteiro:", err)
			os.Exit(1)
		}

		// adiciona os valores na struct pessoa
		person := Pessoa{
			Codigo: cod,
			Nome:   parts[1],
		}

		// adiciona pessoa no slice de pessoas
		dados = append(dados, person)
	}

	// Medir o tempo de execução
	start := time.Now()

	// ordena os dados
	selectionSort(&dados, tamanho)

	// Calcular o tempo de execução
	elapsed := time.Since(start)

	// escreve no arquivo de saida os valores ordenados
	for _, pessoa := range dados {
		_, err := fmt.Fprintf(file2, "%d\t%s\n", pessoa.Codigo, pessoa.Nome)
		if err != nil {
			fmt.Println("Erro ao escrever dados no arquivo pessoasOrdenados:", err)
			os.Exit(1)
		}
	}

	// Calcular o número de comparações
	numComparacoes := (len(dados)*len(dados) - len(dados)) / 2

	// Calcular o numero de trocas caso médio
	trocasMelhor := 3 * (len(dados) - 1)

	// Calcular o numero de trocas pior caso
	trocarPior := ((len(dados) * len(dados)) / 4) + (3 * (len(dados) - 1))

	// Calcular o numero de trocas no caso medio
	y := float64(len(dados)) + float64(0.57721)
	trocarMedio := len(dados) * (int(math.Log(y)))

	// Imprimir o tempo de execução, comparacoes e trocas
	fmt.Println(elapsed, numComparacoes, trocasMelhor, trocarPior, trocarMedio, countCompare, countChanges)

}
