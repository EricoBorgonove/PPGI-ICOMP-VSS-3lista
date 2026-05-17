from z3 import *

# Criando variáveis bit-vector de 1 bit
a = BitVec("a", 1)
b = BitVec("b", 1)

# Implicação:
# b → ¬a
# Em lógica proposicional, isso equivale a:
# ¬b ∨ ¬a
implication = (~b | ~a)

# Lado esquerdo:
# a ∧ (b → ¬a)
left = a & implication

# Lado direito:
# ¬b
right = ~b

# Bicondicional:
# left ↔ right
# Podemos representar a bicondicional como igualdade:
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