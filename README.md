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

Para editar, executar e compilar os programas deste repositório, instale:

1. VS Code
2. Git
3. Python 3
4. Z3 Solver
5. MSYS2, no Windows
6. CMake
7. Extensões do VS Code

Os scripts Python usam o pacote `z3-solver`. Os programas C++ usam um compilador C++, como `g++`, e a biblioteca Z3 instalada com os headers de C++. O CMake é recomendado para integração com o VS Code, mesmo que os comandos de compilação abaixo usem `g++` diretamente.

### Extensões do VS Code

Instale estas extensões no VS Code:

- C/C++ (`ms-vscode.cpptools`)
- Python (`ms-python.python`)
- CMake Tools (`ms-vscode.cmake-tools`)

### Windows

No Windows, use o MSYS2 com o ambiente UCRT64 para instalar `g++`, Z3, Python e CMake.

1. Instale o VS Code: <https://code.visualstudio.com/>
2. Instale o Git: <https://git-scm.com/download/win>
3. Instale o MSYS2: <https://www.msys2.org/>
4. Abra o terminal **MSYS2 UCRT64**.
5. Atualize os pacotes e instale as dependências:

```bash
pacman -Syu
pacman -S --needed git mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-z3 mingw-w64-ucrt-x86_64-python mingw-w64-ucrt-x86_64-python-pip mingw-w64-ucrt-x86_64-cmake
python -m pip install z3-solver
```

Depois disso, os comandos com `python` e `g++ ... -lz3` devem funcionar no terminal UCRT64.

### macOS

Com o Homebrew instalado:

```bash
brew install git python z3 cmake
python3 -m pip install z3-solver
```

Instale também o VS Code: <https://code.visualstudio.com/>

### Ubuntu

```bash
sudo apt update
sudo apt install -y git python3 python3-pip g++ z3 libz3-dev cmake
python3 -m pip install --user z3-solver
```

Instale também o VS Code: <https://code.visualstudio.com/>

Se o `pip` do sistema bloquear instalações globais, crie um ambiente virtual:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install z3-solver
```

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
