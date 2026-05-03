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