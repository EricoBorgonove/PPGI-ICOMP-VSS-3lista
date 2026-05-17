#include <z3++.h>
#include <iostream>

using namespace z3;
using namespace std;

int main() {
    context c;
    solver s(c);

    // Cada malloc é representado como um bloco de memória.
    // Todos os blocos foram alocados.
    expr bloco1_alocado = c.bool_const("bloco1_alocado");
    expr bloco2_alocado = c.bool_const("bloco2_alocado");
    expr bloco3_alocado = c.bool_const("bloco3_alocado");

    // Cada free é representado como a liberação de um bloco.
    expr bloco1_liberado = c.bool_const("bloco1_liberado");
    expr bloco2_liberado = c.bool_const("bloco2_liberado");
    expr bloco3_liberado = c.bool_const("bloco3_liberado");

    // C representa o comportamento do programa:
    // p = malloc(5)  -> bloco1 alocado
    // q = malloc(5)  -> bloco2 alocado
    // p = q          -> perde-se a referência ao bloco1
    // free(p)        -> libera bloco2
    // p = malloc(5)  -> bloco3 alocado
    // free(p)        -> libera bloco3
    expr C =
        bloco1_alocado &&
        bloco2_alocado &&
        bloco3_alocado &&
        !bloco1_liberado &&
        bloco2_liberado &&
        bloco3_liberado;

    // Propriedade de segurança P:
    // Todo bloco alocado deve ser liberado.
    expr P =
        implies(bloco1_alocado, bloco1_liberado) &&
        implies(bloco2_alocado, bloco2_liberado) &&
        implies(bloco3_alocado, bloco3_liberado);

    // Verificamos C ∧ ¬P
    // Se for SAT, existe memory leak.
    s.add(C && !P);

    cout << "Questao 4(b) - Memory Leak" << endl;
    cout << "Verificando C AND not(P)..." << endl;

    check_result resultado = s.check();

    cout << "Resultado: " << resultado << endl;

    if (resultado == sat) {
        cout << "Contraexemplo encontrado:" << endl;
        cout << s.get_model() << endl;
        cout << "Conclusao: existe memory leak, pois ha bloco alocado nao liberado." << endl;
    } else {
        cout << "Conclusao: nao foi encontrado memory leak." << endl;
    }

    return 0;
}