# 2by2 matrix only
# m: 90
# n: 1
import json

with open('data.json') as data_file:
	data = json.load(data_file)

def transpose(matrix):
	return list(zip(*matrix))

def matrixMultiplication(A, B):
	ret = [[0 for j in range(len(B[0]))] for i in range(len(A))]
	for i in range(len(A)):
		for j in range(len(B[0])):
			accumulator = 0
			for k in range(len(B)):
				accumulator += A[i][k] * B[k][j]
			ret[i][j] = accumulator
	return ret

def matrixDeterminant(A):
	return A[0][0]*A[1][1] - A[0][1]*A[1][0]

def matrixInverse(A):
	determinant = matrixDeterminant(A)
	return [
		[A[1][1]/determinant, -1*A[0][1]/determinant],
		[-1*A[1][0]/determinant, A[0][0]/determinant]
	]

X = [[1, x] for x in data["x"]]
X_t = transpose(X)
y = [[x] for x in data["y"]]

with open('output.json', 'w') as output_file:
	X_transByX = matrixMultiplication(X_t, X)
	output = {
		'X_transByX': X_transByX,
	}
	json.dump(output, output_file, sort_keys = True, ensure_ascii = False)

with open('output2.json', 'w') as output_file:
	InverseX_transByX = matrixInverse(X_transByX)
	output = {
		'InverseX_transByX': InverseX_transByX,
	}
	json.dump(output, output_file, sort_keys = True, ensure_ascii = False)

with open('output3.json', 'w') as output_file:
	X_transByY = matrixMultiplication(X_t, y)
	output = {
		'X_transByY': X_transByY,
	}
	json.dump(output, output_file, sort_keys = True, ensure_ascii = False)

with open('output4.json', 'w') as output_file:
	betaHat = matrixMultiplication(InverseX_transByX, X_transByY)
	output = {
		'betaHat': betaHat,
	}
	json.dump(output, output_file, sort_keys = True, ensure_ascii = False)

with open('output5.json', 'w') as output_file:
	yHat = matrixMultiplication(X, betaHat)
	output = {
		'yHat': yHat,
	}
	json.dump(output, output_file, sort_keys = True, ensure_ascii = False)