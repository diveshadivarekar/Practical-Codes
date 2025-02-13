# Function to add two matrices
def matrix_addition(matrix1, matrix2):
    result = []
    for i in range(len(matrix1)):
        row = []
        for j in range(len(matrix1[0])):
            row.append(matrix1[i][j] + matrix2[i][j])
        result.append(row)
    return result

# Function to subtract two matrices
def matrix_subtraction(matrix1, matrix2):
    result = []
    for i in range(len(matrix1)):
        row = []
        for j in range(len(matrix1[0])):
            row.append(matrix1[i][j] - matrix2[i][j])
        result.append(row)
    return result

# Function to multiply two matrices
def matrix_multiplication(matrix1, matrix2):
    result = [[0 for _ in range(len(matrix2[0]))] for _ in range(len(matrix1))]
    for i in range(len(matrix1)):
        for j in range(len(matrix2[0])):
            for k in range(len(matrix2)):
                result[i][j] += matrix1[i][k] * matrix2[k][j]
    return result

# Function to transpose a matrix
def matrix_transpose(matrix):
    result = []
    for i in range(len(matrix[0])):
        row = []
        for j in range(len(matrix)):
            row.append(matrix[j][i])
        result.append(row)
    return result

# Input matrices
matrix1 = [[1, 2, 3],
           [4, 5, 6],
           [7, 8, 9]]

matrix2 = [[9, 8, 7],
           [6, 5, 4],
           [3, 2, 1]]

# a) Addition of two matrices
print("Addition of two matrices:")
for row in matrix_addition(matrix1, matrix2):
    print(row)

# b) Subtraction of two matrices
print("\nSubtraction of two matrices:")
for row in matrix_subtraction(matrix1, matrix2):
    print(row)

# c) Multiplication of two matrices
print("\nMultiplication of two matrices:")
for row in matrix_multiplication(matrix1, matrix2):
    print(row)

# d) Transpose of a matrix
print("\nTranspose of the first matrix:")
for row in matrix_transpose(matrix1):
    print(row)
