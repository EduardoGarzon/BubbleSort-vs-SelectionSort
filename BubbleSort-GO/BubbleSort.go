package main

import (
	"bufio"
	"fmt"
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

func Less(p1, p2 Pessoa) bool {
	countCompare++
	if p1.Codigo < p2.Codigo {
		return true
	} else if p1.Codigo > p2.Codigo {
		return false
	} else {
		return p1.Nome < p2.Nome
	}
}

func Swap(atual *Pessoa, proximo *Pessoa) {
	aux := *atual
	*atual = *proximo
	*proximo = aux
}

func bubbleSort(arr []Pessoa) {
	n := len(arr)
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if Less(arr[j+1], arr[j]) {
				Swap(&arr[j], &arr[j+1])
				countChanges++
			}
		}
	}
}

func main() {
	argumento := os.Args[1] // recebe via terminal a quantidade de registros
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

	// Abre arquivo dos dados ordenados
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

	// Fecha arquivo dos dados finais
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

	bubbleSort(dados)

	// Calcular o tempo de execução
	elapsed := time.Since(start)

	// Calcular o número de comparações
	numComparacoes := ((len(dados)*2)*(len(dados)*2) - (len(dados) * 2)) / 2

	// Calcular o numero de trocas caso médio
	trocasMedio := (3*(len(dados)*2)*(len(dados)*2) - (len(dados) * 2)) / 4

	// Calcular o numero de trocas pior caso
	trocarPior := (3*(len(dados)*2)*(len(dados)*2) - (len(dados)*2)) / 2

	// escreve no arquivo de saida os valores ordenados
	for _, pessoa := range dados {
		_, err := fmt.Fprintf(file2, "%d\t%s\n", pessoa.Codigo, pessoa.Nome)
		if err != nil {
			fmt.Println("Erro ao escrever dados no arquivo pessoasOrdenados:", err)
			os.Exit(1)
		}
	}

	// Imprimir o tempo de execução, comparacoes e trocas
	fmt.Println(elapsed, numComparacoes, trocasMedio, trocarPior, countCompare, countChanges)

	/*for _, pessoa := range dados {
		fmt.Printf("Número: %d, Nome: %s\n", pessoa.Codigo, pessoa.Nome)
	}*/

}

