#!/bin/bash

batch_size=1000
total_records=100000

for ((i = $batch_size; i <= $total_records; i += $batch_size)); do
  go run SelectionSort.go $i

  # Verificar o código de retorno do programa Go
  if [ $? -ne 0 ]; then
    echo "Ocorreu um erro para o tamanho de registros: $i"
  fi
done

# Aguardar entrada do usuário para evitar o fechamento do terminal
read -p "Pressione Enter para sair..."