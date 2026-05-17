# Lista 03 - VSS

Repositório com as soluções da Lista 03 da disciplina de Verificação, Validação e Teste de Software.

As questões usam modelagem lógica e verificação com Z3 para analisar fórmulas proposicionais, buffer overflow, vazamento de memória e acesso fora dos limites considerando alinhamento de estruturas em C.

## Estrutura

| Arquivo | Descrição |
| --- | --- |
| `questao2_a.py` | Verifica a satisfatibilidade da fórmula `(not a or not b) and (not b or c) and b` usando Z3 em Python. |
| `questao2_b.py` | Modela e verifica uma bicondicional envolvendo as variáveis `c`, `d` e `p`. |
| `questao2_c.py` | Modela e verifica a bicondicional entre `a and (b -> not a)` e `not b`. |
| `questao04_a.c` | Programa C usado como base para análise de acesso a array e possível buffer overflow. |
| `questao04_b.c` | Programa C usado como base para análise de alocação dinâmica e possível memory leak. |
| `questao05.c` | Programa C usado como base para análise de ponteiros, `struct` e acesso fora dos limites. |
| `questao4_buffer.cpp` | Modelagem em Z3/C++ da Questão 4(a), verificando `C and not(P)` para detectar buffer overflow. |
| `questao4_memory.cpp` | Modelagem em Z3/C++ da Questão 4(b), verificando `C and not(P)` para detectar memory leak. |
| `questao5.cpp` | Modelagem em Z3/C++ da Questão 5, considerando layout, alinhamento e tamanho de `struct foo`. |
| `lista03-erico-borgonove-cruz.pdf` | Documento final da lista. |
| `lista03-erico-borgonove-cruz.docx` | Versão editável do documento final da lista. |

## Dependências

Para executar os arquivos Python:

- Python 3
- Pacote `z3-solver`

Instalação:

```bash
pip install z3-solver
```

Para compilar os arquivos C++ com Z3:

- Compilador C++, como `g++`
- Biblioteca Z3 instalada com suporte a C++

## Execução

### Questão 2

```bash
python questao2_a.py
python questao2_b.py
python questao2_c.py
```

Cada script imprime o resultado da verificação (`sat`, `unsat` ou `unknown`) e, quando satisfatível, o modelo encontrado pelo solver.

### Questão 4(a) - Buffer Overflow

Compilação:

```bash
g++ questao4_buffer.cpp -o questao4_buffer -lz3
```

Execução:

```bash
./questao4_buffer
```

O programa verifica se existe uma execução em que o índice acessado fica fora dos limites do array `a[2]`.

### Questão 4(b) - Memory Leak

Compilação:

```bash
g++ questao4_memory.cpp -o questao4_memory -lz3
```

Execução:

```bash
./questao4_memory
```

O programa modela os blocos alocados por `malloc` e verifica se todo bloco alocado é liberado.

### Questão 5 - Aligned Memory Model

Compilação:

```bash
g++ questao5.cpp -o questao5 -lz3
```

Execução:

```bash
./questao5
```

O programa modela o layout da `struct foo`, incluindo offsets, tamanho dos campos e padding, para verificar se o acesso `quux->baz` ocorre dentro dos limites do objeto original.

## Observação

Os executáveis `.exe` presentes no diretório foram gerados a partir dos arquivos C++ e podem ser recriados a qualquer momento a partir dos comandos de compilação.
