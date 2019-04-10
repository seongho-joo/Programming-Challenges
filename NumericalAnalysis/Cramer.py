import numpy

N = 4
file = '/Users/seongho/Lacture/수치해석/input/input.txt'

with open(file) as f:
    lines = f.readlines()

with open(file) as f:
    arr = [[int(i) for i in line.split()] for line in f.readlines()]

det = (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0])
det1 = (arr[2][0] * arr[1][1]) - (arr[0][1] * arr[3][0])
det2 = (arr[0][0] * arr[3][0]) - (arr[2][0] * arr[1][0]) 

x1 = det1 / det
x2 = det2 / det
print("x1 = %.1f\nx2 = %.1f" % (x1, x2))