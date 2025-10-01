import random

def generate_pattern(grammar, symbol):
    if symbol not in grammar:
        return symbol
    production = random.choice(grammar[symbol])
    return ''.join([generate_pattern(grammar, sym) for sym in production])

grammar = {
    'S': [['A', 'B']],
    'A': [['loop']],
    'B': [['loop']]
}

pattern = generate_pattern(grammar, 'S')
print("Generated Pattern:", pattern)