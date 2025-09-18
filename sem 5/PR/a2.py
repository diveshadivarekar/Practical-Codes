# cyk_parser.py
from collections import defaultdict

def cyk_parse(tokens, cnf_rules):
    """
    tokens: list of terminal tokens ['a','b',...]
    cnf_rules: list of rules like ('S', ('A', 'B')) or ('A', 'a') where rhs is tuple (nonterm,nonterm) or terminal string
    """
    n = len(tokens)
    # mapping RHS -> list of LHS nonterminals for quick lookup
    rhs_to_lhs = defaultdict(list)
    for lhs, rhs in cnf_rules:
        rhs_to_lhs[rhs].append(lhs)

    # table[i][j] = set of non-terminals that produce tokens[i:i+j] (length j)
    table = [[set() for _ in range(n+1)] for _ in range(n)]
    # length 1 (terminals)
    for i, tok in enumerate(tokens):
        for lhs in rhs_to_lhs.get(tok, []):
            table[i][1].add(lhs)

    # lengths 2..n
    for l in range(2, n+1):  # substring length
        for i in range(0, n-l+1):  # start
            for split in range(1, l):
                left = table[i][split]
                right = table[i+split][l-split]
                for A in left:
                    for B in right:
                        for lhs in rhs_to_lhs.get((A, B), []):
                            table[i][l].add(lhs)

    # debug: print table
    print("CYK table (start index row, length col):")
    for i in range(n):
        row = []
        for l in range(1, n+1):
            row.append("{" + ",".join(sorted(table[i][l])) + "}")
        print(f"{i}: {row}")
    # check if start symbol S in table[0][n]
    return 'S' in table[0][n]

# Example usage
if __name__ == "__main__":
    # Grammar in CNF:
    # S -> A B
    # S -> B C
    # A -> B A
    # A -> 'a'
    # B -> C C
    # B -> 'b'
    # C -> 'A B'
    # C -> 'a'
    rules = [
        ('S', ('A', 'B')),
        ('S', ('B', 'C')),
        ('A', ('B', 'A')),
        ('A', 'a'),
        ('B', ('C', 'C')),
        ('B', 'b'),
        ('C', ('A', 'B')),
        ('C', 'a'),
    ]
    # token string
    tokens = list("baaba")  # example
    accepted = cyk_parse(tokens, rules)
    print("Accepted?" , accepted)
