from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

qc = QuantumCircuit(16, 16)

qc.h(range(16))
qc.measure(range(16), range(16))

sim = AerSimulator()
result = sim.run(transpile(qc, sim), shots=1).result()

print("Random 16-bit number:", list(result.get_counts())[0])