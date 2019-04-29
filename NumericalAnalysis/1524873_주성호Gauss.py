from numpy import array
from numpy.linalg import det
import copy

file = '/Users/seongho/Lecture/NumericalMethod/input/input.txt'

with open(file) as f:
    arr = [[int(i) for i in line.split()] for line in f.readlines()]

n = len(arr) / 2.0
n = int(n)
matA = [[0]*(n + 1) for i in range(n)]
for i in range(n):
    for j in range(n):
        matA[i][j] = arr[i][j]

for i in range(n):
    matA[i][n] = arr[i + n][0]


def pivoting(A, n):
    for i in range(0, n - 1):
        for j in range(0, n - 1):
            if(A[j][0] < A[j + 1][0]):
                temp = A[j]
                A[j] = A[j + 1]
                A[j + 1] = temp


def gauss(n):
    for j in range(n):
        if matA[j][j] == 0:
            for i in range(j + 1, n):
                if matA[i][j] != 0:
                    for k in range(j, n + 1):
                        m = matA[j][k]
                        matA[j][k] = matA[i][k]
                        matA[i][k] = m
                    break
        if matA[j][j] == 0:
            print("정칙행렬이 아님")
            return
        for i in range(j+1, n):
            matA[i][j] = -(matA[i][j] / matA[j][j])
            for k in range(j+1, n+1):
                matA[i][k] = matA[i][k] + matA[i][j]*matA[j][k]
    for i in range(n - 1, -1, -1):
        for k in range(i + 1, n):
            matA[i][n] = matA[i][n] - matA[i][k]*matA[k][n]
        matA[i][n] = matA[i][n] / matA[i][i]
    for i in range(0, n):
        print("x%d = %.1f" % (i + 1, matA[i][n]))


pivoting(matA, n)
gauss(n)
