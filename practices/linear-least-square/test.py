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

X = [[1, x] for x in data["x"]]
X_t = transpose(X)
y = data["y"]

with open('output.json', 'w') as output_file:
	sm = matrixMultiplication(X_t, X)
	output = {
		'sm': sm,
	}
	json.dump(output, output_file, sort_keys = True, ensure_ascii = False)