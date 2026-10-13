from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

qc = QuantumCircuit(3, 3)

qc.ry(1.0, 0)
qc.h(1)
qc.cx(1, 2)

qc.cx(0, 1)
qc.h(0)

qc.measure(0, 0)
qc.measure(1, 1)

with qc.if_test((qc.clbits[1], 1)):
    qc.x(2)

with qc.if_test((qc.clbits[0], 1)):
    qc.z(2)

qc.measure(2, 2)

sim = AerSimulator()
result = sim.run(transpile(qc, sim), shots=1024).result()

print("Teleportation results:", result.get_counts())