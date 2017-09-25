/**
 * CPU와 GPU 환경에서 N by N 행렬곱 연산을 했을 때, N이 최대 크기가 되도록 하는 것이 테스트의 목적이다.
 * 프로그램 수행 시 인자로 N에 해당하는 값을 받으며
 * 프로그램은 순서대로 전처리, 연산을 수행한다.
 * 충분히 커진 N에 대해서 메모리 or 연산 속도가 어떻게 변화하는지 관찰한다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"

#define DEFAULT_SIZE 1024

void preprocess(float** A, float** B, float** C, int N);
void matrixMultiplication(float** A, float** B, float** C, int N);

int main(int argc, char* argv[])
{
    int size = argc < 2 ? DEFAULT_SIZE : atoi(argv[1]);
    float *A;
    float *B;
    float *C;

    init_timer();

    preprocess(&A, &B, &C, size);
    print_time("Initializing matrix finished");
    matrixMultiplication(&A, &B, &C, size);
    print_time("Execution time");
    return 0;
}

/**
 * 행렬 초기화 함수.
 * N x N 행렬의 각 인덱스에 임의값이 들어간다.
 * Time complexity ~ O(n^2)
 *
 * @param   A    N x N matrix
 * @param   B    N x N matrix
 * @param   N    a length of matrix's each row/column
 */
void preprocess(float** A, float** B, float** C, int N) {
    if((*A = (float*) malloc(sizeof(float) * N * N)) == NULL) exit(1);
    if((*B = (float*) malloc(sizeof(float) * N * N)) == NULL) exit(1);
    if((*C = (float*) malloc(sizeof(float) * N * N)) == NULL) exit(1);

    srand(time(NULL));

    for(int i = 0; i < N * N; i++) {
        (*A)[i] = rand() / (float) RAND_MAX;
        (*B)[i] = rand() / (float) RAND_MAX;
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
void matrixMultiplication(float** A, float** B, float** C, int N) {
    float accumulator;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            accumulator = 0.0f;
            for(int k = 0; k < N; k++) {
                accumulator += (*A)[i * N + k] * (*B)[k * N + j];
            }
            (*C)[i * N + j] = accumulator;
        }
    }
}
