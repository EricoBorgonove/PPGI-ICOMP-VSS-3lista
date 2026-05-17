from z3 import *

# Criando variáveis bit-vector de 1 bit
a = BitVec("a", 1)
b = BitVec("b", 1)
c = BitVec("c", 1)

# Valor verdadeiro em bit-vector de 1 bit
TRUE = BitVecVal(1, 1)

# Fórmula:
# (¬a ∨ ¬b) ∧ (¬b ∨ c) ∧ b
formula = ((~a | ~b) & (~b | c) & b)

# Criando o solver
s = Solver()

# Queremos saber se a fórmula pode ser verdadeira
s.add(formula == TRUE)

# Verificando satisfatibilidade
resultado = s.check()

print("Resultado:", resultado)

# Se for satisfatível, imprime o modelo
if resultado == sat:
    print("Modelo encontrado:")
    print(s.model())