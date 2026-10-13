# Quantum Computing Mini Projects (Qiskit)
### Documentation is AI generated

This project contains **five beginner-friendly quantum computing
programs** written in Python using Qiskit.

1.  **16-Qubit Random Number Generator**
2.  **Quantum Teleportation**
3.  **5-Qubit Quantum Fourier Transform (QFT)**
4.  **Three-Qubit Bit-Flip Error Correction**
5.  **Simplified Randomized Benchmarking**

All programs run on a local quantum simulator; no quantum computer is
required.

## 1. Requirements

-   Python 3.10 or 3.11 recommended
-   Internet connection for installing packages
-   Terminal / Command Prompt

Check Python:

``` bash
python --version
```

On Windows, if `python` is not recognized, try:

``` bat
py --version
```

## 2. Create a project folder

``` bash
mkdir quantum-projects
cd quantum-projects
```

Create and activate a virtual environment.

**Windows (Command Prompt):**

``` bat
py -m venv .venv
.venv\Scripts\activate
```

**Windows (PowerShell):**

``` powershell
py -m venv .venv
.venv\Scripts\Activate.ps1
```

**macOS / Linux:**

``` bash
python3 -m venv .venv
source .venv/bin/activate
```

## 3. Install dependencies

With the virtual environment activated:

``` bash
python -m pip install --upgrade pip
python -m pip install qiskit qiskit-aer
```

## 4. Create and run the programs

Save each code block in a separate `.py` file inside the project folder.

### Program 1: 16-Qubit Random Number Generator

Create `random_number.py`:

``` python
from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

qc = QuantumCircuit(16, 16)
qc.h(range(16))
qc.measure(range(16), range(16))

sim = AerSimulator()
result = sim.run(transpile(qc, sim), shots=1).result()
print("Random 16-bit number:", list(result.get_counts())[0])
```

Run:

``` bash
python random_number.py
```

Example output (your result will differ):

``` text
Random 16-bit number: 1011010010110101
```

### Program 2: Quantum Teleportation

Create `teleportation.py`:

``` python
from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

qc = QuantumCircuit(3, 3)
qc.ry(1.0, 0)             # State to teleport
qc.h(1)
qc.cx(1, 2)                # Entangle qubits 1 and 2
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
print("Measurement results:", result.get_counts())
```

Run:

``` bash
python teleportation.py
```

The output shows measurement bit strings and counts. This circuit
demonstrates teleportation with classical feed-forward corrections.

### Program 3: Five-Qubit Quantum Fourier Transform (QFT)

Create `qft_5qubit.py`:

``` python
from qiskit import QuantumCircuit, transpile
from qiskit.circuit.library import QFT
from qiskit_aer import AerSimulator

qc = QuantumCircuit(5, 5)
qc.h(0)
qc.x(1)                    # Example input preparation
qc.compose(QFT(5), inplace=True)
qc.measure(range(5), range(5))

sim = AerSimulator()
result = sim.run(transpile(qc, sim), shots=1024).result()
print("QFT measurement results:", result.get_counts())
```

Run:

``` bash
python qft_5qubit.py
```

### Program 4: Three-Qubit Bit-Flip Error Correction

This demonstrates the three-qubit repetition code. A bit-flip error is
deliberately introduced on one qubit, then syndrome measurements
identify and correct it.

Create `error_correction.py`:

``` python
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister, transpile
from qiskit_aer import AerSimulator

data = QuantumRegister(3, "data")
anc = QuantumRegister(2, "anc")
syn = ClassicalRegister(2, "syn")
out = ClassicalRegister(1, "out")
qc = QuantumCircuit(data, anc, syn, out)

qc.ry(1.0, data[0])        # Prepare a state
qc.cx(data[0], data[1])    # Encode across 3 qubits
qc.cx(data[0], data[2])

qc.x(data[1])              # Simulate a bit-flip error

# Measure parity checks into two ancillas
qc.cx(data[0], anc[0])
qc.cx(data[1], anc[0])
qc.cx(data[0], anc[1])
qc.cx(data[2], anc[1])
qc.measure(anc[0], syn[0])
qc.measure(anc[1], syn[1])

# Correct the qubit indicated by the syndrome
with qc.if_test((syn, 1)):
    qc.x(data[1])
with qc.if_test((syn, 2)):
    qc.x(data[2])
with qc.if_test((syn, 3)):
    qc.x(data[0])

qc.measure(data[0], out[0])

sim = AerSimulator()
result = sim.run(transpile(qc, sim), shots=1024).result()
print("Results (syndrome and output):", result.get_counts())
```

Run:

``` bash
python error_correction.py
```

The forced error is on `data[1]`, so the syndrome should identify that
qubit and the correction should restore the encoded state. The displayed
counts include the syndrome and final output.

### Program 5: Simplified Randomized Benchmarking

This small demonstration builds random sequences from single-qubit
Clifford gates (`H` and `S`), appends the inverse sequence, and measures
how often the qubit returns to `0`. A depolarizing noise model makes the
survival probability decrease as sequences get longer.

Create `randomized_benchmarking.py`:

``` python
import random
from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator
from qiskit_aer.noise import NoiseModel, depolarizing_error

noise = NoiseModel()
error = depolarizing_error(0.02, 1)
noise.add_all_qubit_quantum_error(error, ["h", "s", "sdg"])
sim = AerSimulator(noise_model=noise)

for length in [1, 2, 4, 8, 16]:
    successes = 0
    shots = 200

    for _ in range(shots):
        gates = [random.choice(["h", "s"]) for _ in range(length)]
        qc = QuantumCircuit(1, 1)

        for gate in gates:
            getattr(qc, gate)(0)

        for gate in reversed(gates):
            getattr(qc, {"h": "h", "s": "sdg"}[gate])(0)

        qc.measure(0, 0)
        result = sim.run(transpile(qc, sim, optimization_level=0),
                         shots=1).result()
        if "0" in result.get_counts():
            successes += 1

    print(f"Length {length}: survival = {successes / shots:.2f}")
```

Run:

``` bash
python randomized_benchmarking.py
```

The survival probability is the fraction of runs that measure `0`.
Results vary because of randomness and simulated noise. This is a
**simplified educational demonstration**, not a full standard
randomized-benchmarking experiment.

## 5. Project structure

``` text
quantum-projects/
├── .venv/
├── random_number.py
├── teleportation.py
├── qft_5qubit.py
├── error_correction.py
├── randomized_benchmarking.py
└── README.md
```

## 6. Troubleshooting

### `ModuleNotFoundError`

Make sure the virtual environment is activated, then run:

``` bash
python -m pip install qiskit qiskit-aer
```

### `python` is not recognized on Windows

Try `py` instead of `python`, or reinstall Python and enable **Add
Python to PATH**.

### Virtual environment activation fails

Use the activation command for your operating system in Section 2. If
PowerShell blocks scripts, use Command Prompt or follow your
organization's approved execution-policy guidance.

### QFT deprecation warning

Some Qiskit versions may warn that `QFT` is deprecated. A warning alone
does not mean the program failed. If it raises an error, check the
installed Qiskit version and its circuit-library documentation.

## 7. Notes

-   Run commands from the project folder with the virtual environment
    activated.
-   The random-number generator produces one 16-bit sample per run.
-   Teleportation uses entanglement and classical information; it does
    not copy an unknown quantum state.
-   Error correction demonstrates correction of a deliberately
    introduced bit flip.
-   The randomized benchmarking example is intentionally simplified for
    learning.
-   All five programs use a simulator, not physical quantum hardware.
