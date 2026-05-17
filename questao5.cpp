#include <z3++.h>
#include <iostream>

using namespace z3;
using namespace std;

int main() {
    context c;
    solver s(c);

    /*
        Modelagem da struct foo:

        struct foo {
            uint16_t bar[2]; // 2 bytes cada elemento
            uint8_t baz;     // 1 byte
        };

        Layout considerando alinhamento:
        bar[0] -> offset 0, ocupa bytes 0 e 1
        bar[1] -> offset 2, ocupa bytes 2 e 3
        baz    -> offset 4, ocupa byte 4
        padding -> offset 5

        sizeof(struct foo) = 6 bytes
    */

    expr base_qux = c.int_const("base_qux");

    expr align_foo = c.int_val(2);
    expr size_uint16 = c.int_val(2);
    expr size_uint8 = c.int_val(1);

    expr offset_bar0 = c.int_val(0);
    expr offset_bar1 = c.int_val(2);
    expr offset_baz = c.int_val(4);

    expr size_foo = c.int_val(6);

    // quux inicialmente aponta para &qux
    expr quux_inicial = base_qux;

    // quux++ avança sizeof(struct foo), isto é, 6 bytes
    expr quux_apos_incremento = quux_inicial + size_foo;

    // quux->baz acessa o campo baz no offset 4 da nova posição apontada por quux
    expr endereco_acesso = quux_apos_incremento + offset_baz;

    /*
        Fórmula C:
        representa as restrições do programa e do layout de memória.
    */
    expr C =
        (base_qux >= 0) &&
        (mod(base_qux, align_foo) == 0) &&
        (offset_bar0 == 0) &&
        (offset_bar1 == 2) &&
        (offset_baz == 4) &&
        (size_foo == 6) &&
        (quux_inicial == base_qux) &&
        (quux_apos_incremento == base_qux + size_foo) &&
        (endereco_acesso == quux_apos_incremento + offset_baz);

    /*
        Propriedade P:
        o acesso quux->baz deve estar dentro dos limites do objeto qux.

        Como baz possui 1 byte, o acesso é seguro se:
        base_qux <= endereco_acesso
        e
        endereco_acesso + 1 <= base_qux + size_foo
    */
    expr P =
        (base_qux <= endereco_acesso) &&
        (endereco_acesso + size_uint8 <= base_qux + size_foo);

    /*
        Verificação:
        C AND not(P)

        Se for SAT, existe violação da propriedade de segurança.
    */
    s.add(C && !P);

    cout << "Questao 5 - Aligned Memory Model" << endl;
    cout << "Verificando C AND not(P)..." << endl;

    check_result resultado = s.check();

    cout << "Resultado: " << resultado << endl;

    if (resultado == sat) {
        cout << "Contraexemplo encontrado:" << endl;
        cout << s.get_model() << endl;

        cout << "Conclusao: existe acesso fora dos limites do objeto qux." << endl;
        cout << "O ponteiro quux foi incrementado em sizeof(struct foo), "
             << "e o acesso quux->baz ocorre fora da area de memoria de qux." << endl;
    } else {
        cout << "Conclusao: nao foi encontrada violacao de memoria." << endl;
    }

    return 0;
}