#include <stdio.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <time.h>
#include "math.h"

__global__ void matMul(int transA, int transB,
		int M, int N, int K, 
		float ALPHA, float *A, int lda, 
		float *B, int ldb, float BETA, 
		float *C, int ldc)
{
    int n =  blockIdx.y * blockDim.y + threadIdx.y;
    int m =  blockIdx.x * blockDim.x + threadIdx.x;
 
    if( n < N && m < M);
    {
        float sum = 0;
        for (int k = 0; k < K; k++)
        {
            sum += B[n * K + k] * A[m * K + k];
        }
        C[n * M + m] = ALPHA * sum;
        
    }
}

extern "C" void gemmCuda(int transA, int transB, 
		int M, int N, int K, 
		float ALPHA, float *A, int lda, 
		float *B, int ldb, float BETA, 
		float *C, int ldc)
{


    float *temp_A, *temp_B, *temp_C;

    cudaMalloc((void **)&temp_A, M * K * sizeof(float));
    cudaMalloc((void **)&temp_B, N * K * sizeof(float));
    cudaMalloc((void **)&temp_C, M * N * sizeof(float));



	//send input data from host to device
    cudaMemcpy(temp_A, A, M * K * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(temp_B, B, N * K * sizeof(float), cudaMemcpyHostToDevice);


	dim3 blocksPerGrid(M/N,N/N);
    dim3 threadsPerBlock(N,N);
	

	matMul<<<blocksPerGrid, threadsPerBlock>>>(0, 1, M, N, K, 1.0f, temp_A, K, temp_B, N, 0, temp_C, N);
	cudaDeviceSynchronize();
	
	
 
	cudaMemcpy(C, temp_C, M * N * sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(temp_A);
    cudaFree(temp_B);
    cudaFree(temp_C);

}



