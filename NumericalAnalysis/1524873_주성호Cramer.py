import numpy
import copy
# 소스파일이 있는 폴더에 input파일이 있는데 인식을 못해서 전체 경로로 지정했습니다.
file = '/Users/seongho/Lacture/NumericalMethod/input/input.txt'

# with open(file) as f:
#     lines = f.readlines()

with open(file) as f:
    arr = [[int(i) for i in line.split()] for line in f.readlines()]

matA = [[0]*2 for i in range(2)]
for i in range(2):
    for j in range(2):
        matA[i][j] = arr[i][j]

det = numpy.linalg.det(matA)

matA1 = copy.deepcopy(matA)
matA2 = copy.deepcopy(matA)

for i in range(2):
    matA1[i][0] = arr[i + 2][0]
for i in range(2):
    matA2[i][1] = arr[i + 2][0]

det1 = numpy.linalg.det(matA1)
det2 = numpy.linalg.det(matA2)

x1 = det1 / det
x2 = det2 / det
print("x1 = %.0f\nx2 = %.0f" % (x1, x2))
