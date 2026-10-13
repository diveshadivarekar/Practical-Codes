from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

qc = QuantumCircuit(5, 3)

# Encode a quantum state using 3 qubits
qc.ry(1.0, 0)
qc.cx(0, 1)
qc.cx(0, 2)

# Introduce a bit-flip error on qubit 1
qc.x(1)

# Detect the error using two ancilla qubits
qc.cx(0, 3)
qc.cx(1, 3)
qc.cx(0, 4)
qc.cx(2, 4)

qc.measure(3, 0)
qc.measure(4, 1)

# Correct the error based on syndrome
with qc.if_test((qc.clbits[0], 1)):
    with qc.if_test((qc.clbits[1], 0)):
        qc.x(1)

with qc.if_test((qc.clbits[0], 0)):
    with qc.if_test((qc.clbits[1], 1)):
        qc.x(2)

with qc.if_test((qc.clbits[0], 1)):
    with qc.if_test((qc.clbits[1], 1)):
        qc.x(0)

qc.measure(0, 2)

sim = AerSimulator()
result = sim.run(transpile(qc, sim), shots=1024).result()

print("Error correction results:", result.get_counts())