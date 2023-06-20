# Chu-liu-Edmonds

Algoritmo que obtém uma árvore geradora mínima de um grafo ponderado e direcionado.

## Testes

1. Compile o arquivo `main.cpp` com o comando: `g++ main.cpp` (uma única vez)
2. Execute o programa com o comando `./a.out < in` (quantas testes forem necessários)

Caso queira testar outros grafos, por favor edite o arquivo `in`, seguindo o padrão de entrada: A entrada consiste em número N de vértices, logo em seguida são lidos os N vértices. Ademais deverá ser informado M representando a quantidade de arestas, logo em seguida são lidos u, v, w (origem, destino e peso) para as M arestas. Exemplo:

```
3
1 2 3
3
1 2 1
2 3 4
3 1 5
```

O exemplo acima consiste em um grafo com 3 vértices (1,2,3), e 3 arestas: (1,2) com peso 3, (2,3) com peso 4 e (3,1) com peso 5.