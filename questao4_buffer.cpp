#include <z3++.h>
#include <iostream>

using namespace z3;
using namespace std;

int main() {
    context c;
    solver s(c);

    // Variáveis simbólicas do programa C
    expr x = c.int_const("x");
    expr i = c.int_const("i");

    // Tamanho do array a[2]
    expr tamanho = c.int_val(2);

    // Caminho 1:
    // if (x == 0) a[i] = 0;
    expr caminho_if = (x == 0);

    // Caminho 2:
    // else a[i + 1] = 1;
    expr caminho_else = (x != 0);

    // Propriedade de segurança do caminho IF:
    // O índice i deve estar entre 0 e 1
    expr indice_if_valido = (i >= 0) && (i < tamanho);

    // Propriedade de segurança do caminho ELSE:
    // O índice i + 1 deve estar entre 0 e 1
    expr indice_else_valido = ((i + 1) >= 0) && ((i + 1) < tamanho);

    // Propriedade geral P:
    // Se x == 0, então i deve ser válido.
    // Se x != 0, então i + 1 deve ser válido.
    expr P =
        implies(caminho_if, indice_if_valido) &&
        implies(caminho_else, indice_else_valido);

    // C representa as restrições do programa.
    // Neste exemplo, x e i são variáveis não inicializadas,
    // portanto podem assumir qualquer valor inteiro.
    expr C = c.bool_val(true);

    // Verificamos C ∧ ¬P
    // Se for SAT, existe buffer overflow.
    s.add(C && !P);

    cout << "Questao 4(a) - Buffer Overflow" << endl;
    cout << "Verificando C AND not(P)..." << endl;

    check_result resultado = s.check();

    cout << "Resultado: " << resultado << endl;

    if (resultado == sat) {
        cout << "Contraexemplo encontrado:" << endl;
        cout << s.get_model() << endl;
        cout << "Conclusao: existe uma execucao que viola os limites do array." << endl;
    } else {
        cout << "Conclusao: nao foi encontrada violacao dos limites do array." << endl;
    }

    return 0;
}