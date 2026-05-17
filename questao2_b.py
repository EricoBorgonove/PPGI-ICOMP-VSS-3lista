from z3 import *

# Criando variáveis bit-vector de 1 bit
c = BitVec("c", 1)
d = BitVec("d", 1)
p = BitVec("p", 1)

# Valor verdadeiro em bit-vector de 1 bit
TRUE = BitVecVal(1, 1)

# Lado esquerdo da bicondicional:
# ((d ∧ c) ∨ (p ∧ ¬((c ∧ ¬d))))
left = (d & c) | (p & ~(c & ~d))

# Lado direito da bicondicional:
# ((c ∧ d) ∨ (p ∧ c) ∨ (p ∧ ¬d))
right = (c & d) | (p & c) | (p & ~d)

# Bicondicional:
# left ↔ right
# Em Z3, podemos representar como igualdade:
formula = (left == right)

# Criando o solver
s = Solver()

# Adicionando a fórmula ao solver
s.add(formula)

# Verificando satisfatibilidade
resultado = s.check()

print("Resultado:", resultado)

# Se for satisfatível, imprime o modelo
if resultado == sat:
    print("Modelo encontrado:")
    print(s.model())