# INF610 - Trabalho Prático 4

Trabalho Prático 4 da disciplina INF610 - Estruturas de Dados e Algoritmos

## Compilação

Tendo o `make` e o `g++` instalado, basta executar o comando `make`.

## Uso

```bash
$ ./bin/inf610-tp4 <entrada>
```

A entrada deve ser um arquivo contendo, na primeira linha, o tamanho $n$ do problema.
Depois, deve haver $n$ linhas contendo $n$ valores inteiros em cada, no intervalo $[-1,n)$.
Um valor $-1$ indica que o espaço está em branco.


Por exemplo, o problema:

| | | |
|:-|:-|:-|
|0| | |
| |1| |
| | |2|


É representado em arquivo como:
 
```
3
 0 -1 -1
-1  1 -1
-1 -1  2
```