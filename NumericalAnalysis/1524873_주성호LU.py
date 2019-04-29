from numpy import array, zeros

# a11 a12
# a21 a22
# b1
# b2
# b3
# 이런식으로 입력을 받았습니다.
file = '/Users/seongho/Lecture/NumericalMethod/input/input.txt'

with open(file) as f:
    arr = [[int(i) for i in line.split()] for line in f.readlines()]

n = len(arr) / 2.0
n = int(n)
A = [[0]*(n+1) for i in range(n)]
B = [[0] * 1 for i in range(n)]
L = [[0.0] * n for i in range(n)]
U = [[0.0] * n for i in range(n)]
Y = zeros(n)
X = zeros(n)
for i in range(n):
    for j in range(n):
        A[i][j] = arr[i][j]

for i in range(n):
    B[i][0] = arr[i+n][0]
# LU decomposition
for j in range(n):
    for i in range(n):
        if i <= j:
            U[i][j] = A[i][j]
            for k in range(i):
                U[i][j] = U[i][j] - L[i][k] * U[k][j]
            if i == j:
                L[i][j] = 1
            else:
                L[i][j] = 0
        else:
            L[i][j] = A[i][j]
            for k in range(j):
                L[i][j] = L[i][j] - L[i][k] * U[k][j]
            L[i][j] /= U[j][j]
            U[i][j] = 0
# Ly = B
for i in range(n):
    Y[i] = B[i][0]
    for j in range(i):
        Y[i] -= L[i][j] * Y[j]
# Ux = y
for i in range(n - 1, -1, -1):
    X[i] = Y[i]
    for j in range(i + 1, n):
        X[i] -= U[i][j] * X[j]
    X[i] /= U[i][i]
print("L : ")
print(*L, sep='\n')
print("U : ")
print(*U, sep='\n')
for i in range(n):
    print("x%d = %.1f" % (i+1, X[i]))
