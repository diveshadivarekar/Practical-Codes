# Assignment 2: Generate ANDNOT function using McCulloch-Pitts neural net

**Objective:** Implement the **ANDNOT** (A AND NOT B) logical function using a McCulloch-Pitts (MP) neuron — the simplest model of a biological neuron.

## Requirements

Generate ANDNOT function using McCulloch-Pitts neural net by a Python program.

---
def mcp_andnot(a, b):
    # weights
    w1 = 1      # for A
    w2 = -1     # for B (inhibitory input)
    threshold = 1

    # weighted sum
    net = (w1 * a) + (w2 * b)

    # activation (step function)
    if net >= threshold:
        return 1
    else:
        return 0

# Test all inputs
inputs = [(0,0), (0,1), (1,0), (1,1)]

print("A B | Output")
for a, b in inputs:
    print(a, b, "|", mcp_andnot(a, b))