/**
 * CPU와 GPU 환경에서 N by N 행렬곱 연산을 했을 때, N이 최대 크기가 되도록 하는 것이 테스트의 목적이다.
 * 프로그램 수행 시 인자로 N에 해당하는 값을 받으며
 * 프로그램은 순서대로 전처리, 연산을 수행한다.
 * 충분히 커진 N에 대해서 메모리 or 연산 속도가 어떻게 변화하는지 관찰한다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef __linux__
#include <CL/opencl.h>
#elif __APPLE__
#include <OpenCL/opencl.h>
#endif
#include "timer.h"

#define DEFAULT_SIZE 8192

const char *KernelSource = "\n" \
"__kernel void matrixMultiplication(          \n" \
"   __global float* C,                        \n" \
"   __global float* A,                        \n" \
"   __global float* B,                        \n" \
"   int wA, int wB)                           \n" \
"{                                            \n" \
"   int tx = get_global_id(0);                \n" \
"   int ty = get_global_id(1);                \n" \
"   float value = 0;                          \n" \
"   for (int k = 0; k < wA; ++k)              \n" \
"   {                                         \n" \
"      float elementA = A[ty * wA + k];       \n" \
"      float elementB = B[k * wB + tx];       \n" \
"      value += elementA * elementB;          \n" \
"   }                                         \n" \
"   C[ty * wA + tx] = value;                  \n" \
"}                                            \n" \
"\n";

void initializeComputeKernel(void);
void destroyComputeKernel(void);

int main(int argc, char** argv)
{
    int err;
    int size = argc < 2 ? DEFAULT_SIZE : atoi(argv[1]);
    int mem_size = sizeof(float) * size * size;
    float *A;
    float *B;
    float *C;

    size_t localWorkSize[2];
    size_t globalWorkSize[2];

    cl_device_id device_id;
    cl_context context;
    cl_command_queue commands;
    cl_program program;
    cl_kernel kernel;

    cl_mem device_A;
    cl_mem device_B;
    cl_mem device_C;

    init_timer();

    //Allocate host memory for matrices A and B
    A = (float*) malloc(mem_size);
    B = (float*) malloc(mem_size);
    C = (float*) malloc(mem_size);

    //Initialize host memory
    srand(time(NULL));
    for(int i = 0; i < size * size; i++) {
        A[i] = rand() / (float) RAND_MAX;
        B[i] = rand() / (float) RAND_MAX;
    }

    print_time("Initializing matrix finished");

    // Connect to a compute device
    //
    int gpu = argc < 3 ? 1 : atoi(argv[2]);
    err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to create a device group!\n");
        return EXIT_FAILURE;
    }

    // Create a compute context
    //
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
    if (!context)
    {
        printf("Error: Failed to create a compute context!\n");
        return EXIT_FAILURE;
    }

    // Create a command commands
    //
    commands = clCreateCommandQueue(context, device_id, 0, &err);
    if (!commands)
    {
        printf("Error: Failed to create a command commands!\n");
        return EXIT_FAILURE;
    }

    // Create the compute program from the source buffer
    //
    program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);
    if (!program)
    {
        printf("Error: Failed to create compute program!\n");
        return EXIT_FAILURE;
    }

    // Build the program executable
    //
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];

        printf("Error: Failed to build program executable!\n");
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);
        exit(1);
    }

    // Create the compute kernel in the program we wish to run
    //
    kernel = clCreateKernel(program, "matrixMultiplication", &err);
    if (!kernel || err != CL_SUCCESS)
    {
        printf("Error: Failed to create compute kernel!\n");
        exit(1);
    }

    print_time("Create compute kernel finished");

    device_C = clCreateBuffer(context, CL_MEM_READ_WRITE, mem_size, NULL, &err);
    device_A = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, mem_size, A, &err);
    device_B = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, mem_size, B, &err);
    if (!device_A || !device_B || !device_C)
    {
        printf("Error: Failed to allocate device memory!\n");
        exit(1);
    }

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&device_C);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&device_A);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&device_B);
    err |= clSetKernelArg(kernel, 3, sizeof(int), (void *)&size);
    err |= clSetKernelArg(kernel, 4, sizeof(int), (void *)&size);

    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to set kernel arguments! %d\n", err);
        exit(1);
    }

    // CL_KERNEL_WORK_GROUP_SIZE
    // CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE
    err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof(localWorkSize[0]), &localWorkSize[0], NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to retrieve kernel work group info! %d\n", err);
        exit(1);
    }

    err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof(localWorkSize[1]), &localWorkSize[1], NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to retrieve kernel work group info! %d\n", err);
        exit(1);
    }

    localWorkSize[0] = ceil(localWorkSize[0] / 2);
    localWorkSize[1] = ceil(localWorkSize[1] / 2);

    globalWorkSize[0] = localWorkSize[0] * ceil(size/localWorkSize[0]);
    globalWorkSize[1] = localWorkSize[1] * ceil(size/localWorkSize[1]);

    printf("local: %d, %d\nglobal: %d, %d\n",
      localWorkSize[0],
      localWorkSize[1],
      globalWorkSize[1],
      globalWorkSize[1]);

    err = clEnqueueNDRangeKernel(commands, kernel, 2, NULL, globalWorkSize, NULL,
   0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to execute kernel! %d\n", err);
        exit(1);
    }

    // Wait for the command commands to get serviced before reading back results
    //
    clFinish(commands);

    print_time("Command commands finished");

    //Retrieve result from device
    err = clEnqueueReadBuffer(commands, device_C, CL_TRUE, 0, mem_size, C, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to read output array! %d\n", err);
        exit(1);
    }

    print_time("Execution time");

    // Shutdown and cleanup
    //
    clReleaseMemObject(device_A);
    clReleaseMemObject(device_B);
    clReleaseMemObject(device_C);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);
    return 0;
}
