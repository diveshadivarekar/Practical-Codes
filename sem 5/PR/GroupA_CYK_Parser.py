def cyk_algorithm(w, grammar):
    n = len(w)
    table = [[set() for _ in range(n)] for _ in range(n)]

    for i, char in enumerate(w):
        for lhs, rhs_list in grammar.items():
            for rhs in rhs_list:
                if len(rhs) == 1 and rhs[0] == char:
                    table[i][i].add(lhs)

    for l in range(2, n+1):
        for i in range(n - l + 1):
            j = i + l - 1
            for k in range(i, j):
                for lhs, rhs_list in grammar.items():
                    for rhs in rhs_list:
                        if len(rhs) == 2:
                            B, C = rhs
                            if B in table[i][k] and C in table[k+1][j]:
                                table[i][j].add(lhs)

    return 'S' in table[0][n-1]

grammar = {
    'S': [('A', 'B'), ('B', 'C')],
    'A': [('B', 'A'), ('a',)],
    'B': [('C', 'C'), ('b',)],
    'C': [('A', 'B'), ('a',)]
}

w = "baaba"
result = cyk_algorithm(w, grammar)
print("String accepted by grammar?" , result)