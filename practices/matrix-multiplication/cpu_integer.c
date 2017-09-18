/**
 * CPU와 GPU 환경에서 N by N 행렬곱 연산을 했을 때, N이 최대 크기가 되도록 하는 것이 테스트의 목적이다.
 * 프로그램 수행 시 인자로 N에 해당하는 값을 받으며
 * 프로그램은 순서대로 전처리, 연산을 수행한다.
 * 충분히 커진 N에 대해서 메모리 or 연산 속도가 어떻게 변화하는지 관찰한다.
 */

#include <stdio.h>
#include <stdlib.h>

int **A, **B;

void preprocess(int** A, int** B, int N);
void matrixMultiplication(int** A, int** B, int N);

int main(int argc, char* argv[]) {
    preprocess(A, B, atoi(argv[1]));
    matrixMultiplication(A, B, atoi(argv[1]));
    return 0;
}

/**
 * 행렬 초기화 함수.
 * N x N 행렬의 각 인덱스에 자신의 인덱스값이 들어간다.
 * Time complexity ~ O(n^2)
 *
 * @param   A    N x N matrix
 * @param   B    N x N matrix
 * @param   N    a length of matrix's each row/column
 */
void preprocess(int** A, int** B, int N) {
    if((A = (int **)malloc(N * sizeof(int *))) == NULL) exit(1);
    for(int i = 0; i < N; i++) {
        if((A[i] = (int *)malloc(N * sizeof(int))) == NULL) exit(1);
    }

    if((B = (int **)malloc(N * sizeof(int *))) == NULL) exit(1);
    for(int i = 0; i < N; i++) {
        if((B[i] = (int *)malloc(N * sizeof(int))) == NULL) exit(1);
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = B[i][j] = i * N + j;
        }
    }
}

/**
 * 행렬곱 함수.
 * 두 개의 N x N 행렬에 대해서 순서대로 행렬곱 연산을 한다.
 * Time complexity ~ O(n^3)
 *
 * @param   A    N x N matrix
 * @param   B    N x N matrix
 * @param   N    a length of matrix's each row/column
 */
void matrixMultiplication(int** A, int** B, int N) {
    int accumulator;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            accumulator = 0;
            for(int k = 0; k < N; k++) {
                accumulator += A[i][k] * B[k][j];
            }
        }
    }
}