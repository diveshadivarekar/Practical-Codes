from qiskit import QuantumCircuit, transpile
from qiskit.circuit.library import QFT
from qiskit_aer import AerSimulator

qc = QuantumCircuit(5, 5)

qc.h(0)
qc.x(1)

qc.compose(QFT(5), inplace=True)
qc.measure(range(5), range(5))

sim = AerSimulator()
result = sim.run(transpile(qc, sim), shots=1024).result()

print("QFT results:", result.get_counts())