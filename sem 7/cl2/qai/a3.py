# Tarrataca's Quantum Production System for the 3-puzzle (2x2 board, 0 = blank) - Qiskit version
# Register: 2 qubits per step (the production rule: 0=up 1=down 2=left 3=right) x DEPTH steps.
# Hadamards -> superposition of all rule sequences; oracle marks sequences that reach the goal; Grover diffusion.
# pip install qiskit qiskit-aer
import numpy as np
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator
from qiskit import transpile

START, GOAL, DEPTH = (3, 1, 0, 2), (1, 2, 3, 0), 3     # board cells: [0 1 / 2 3]
NAMES, SHIFT = ["up", "down", "left", "right"], [-2, 2, -1, 1]

def apply(state, rule):                                 # production rule (None = not applicable)
    b = state.index(0); n = b + SHIFT[rule]
    if not 0 <= n < 4 or (rule >= 2 and n // 2 != b // 2): return None
    s = list(state); s[b], s[n] = s[n], s[b]
    return tuple(s)

def decode(k):                                          # basis state k -> list of rules (2 bits each)
    return [(k >> (2 * i)) & 3 for i in range(DEPTH)]

def reaches_goal(k):
    s = START
    for r in decode(k):
        s = apply(s, r)
        if s is None: return False
    return s == GOAL

n = 2 * DEPTH
marked = [k for k in range(2 ** n) if reaches_goal(k)]  # classical check used to build the oracle
print("Solutions (basis states):", marked)

# Oracle: phase flip (-1) on every marked basis state, built from X + multi-controlled Z gates
oracle = QuantumCircuit(n)
for k in marked:
    zeros = [i for i in range(n) if not (k >> i) & 1]
    if zeros: oracle.x(zeros)
    oracle.h(n - 1); oracle.mcx(list(range(n - 1)), n - 1); oracle.h(n - 1)   # multi-controlled Z
    if zeros: oracle.x(zeros)

# Diffusion: H, X, multi-controlled Z, X, H  (inversion about the mean)
diffusion = QuantumCircuit(n)
diffusion.h(range(n)); diffusion.x(range(n))
diffusion.h(n - 1); diffusion.mcx(list(range(n - 1)), n - 1); diffusion.h(n - 1)
diffusion.x(range(n)); diffusion.h(range(n))

# Grover circuit
qc = QuantumCircuit(n)
qc.h(range(n))                                          # superposition of all rule sequences
iters = int(np.pi / 4 * np.sqrt(2 ** n / len(marked)))
for _ in range(iters):
    qc.compose(oracle, inplace=True)                    # 1) oracle
    qc.compose(diffusion, inplace=True)                 # 2) diffusion
qc.measure_all()

counts = AerSimulator().run(transpile(qc, AerSimulator()), shots=1024).result().get_counts()
best = max(counts, key=counts.get)
print("Grover iterations:", iters, "| top results:", dict(sorted(counts.items(), key=lambda x: -x[1])[:3]))
print("Solution moves:", [NAMES[r] for r in decode(int(best, 2))])