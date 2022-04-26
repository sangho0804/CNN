#include <stdio.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <time.h>


// Device run
// Matrix multiplication
// Same GEMM Configuration

__global__ void matMul(int transA, int transB,
		int M, int N, int K, 
		float ALPHA, float *A, int lda, 
		float *B, int ldb, float BETA, 
		float *C, int ldc)
{
    int n =  blockIdx.y * blockDim.y + threadIdx.y;
    int m =  blockIdx.x * blockDim.x + threadIdx.x;
 
    if( n < N && m < M );
    {
        float sum = 0;
        for (int k = 0; k < K; k++)
        {
            sum += B[n * K + k] * A[m * K + k];
        }
        C[m * N + n] = ALPHA * sum;
        
    }
}

// for use Cuda
// cuda is C++ base
// so for "C" use
// write extern "C"

extern "C" void gemmCuda(int transA, int transB, 
		int M, int N, int K, 
		float ALPHA, float *A, int lda, 
		float *B, int ldb, float BETA, 
		float *C, int ldc)
{	// for check time
	// overhead	   : move data
	//				 host to device and device to host
	// computation : metmul
	// send		 -> host to device
	// send_host -> device to host
	// kernel	 -> metmul
	cudaEvent_t  send_start, send_stop, kernel_start, kernel_stop,
	send_host_start, send_host_stop;
	float foncTime, send_time, send_host_time = 0;


    float *temp_A, *temp_B, *temp_C;

    cudaMalloc((void **)&temp_A, M * K * sizeof(float));
    cudaMalloc((void **)&temp_B, N * K * sizeof(float));
    cudaMalloc((void **)&temp_C, M * N * sizeof(float));

	// send time overhead
	cudaEventCreate(&send_start);
	cudaEventCreate(&send_stop);
	cudaEventRecord(send_start);

	//send input data from host to device
    cudaMemcpy(temp_A, A, M * K * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(temp_B, B, N * K * sizeof(float), cudaMemcpyHostToDevice);
 	
	cudaEventRecord(send_stop);
	cudaEventSynchronize(send_stop);
	
	cudaEventElapsedTime(&send_time, send_start, send_stop);
	fprintf(stderr, "sned input data from host to device  Elapsed Time = %.6f millisec\n",
			send_time);

	cudaEventDestroy(send_start);
	cudaEventDestroy(send_stop);
	//fin check send time overhead

	dim3 blocksPerGrid(M/16,N/16); // 1 , 256/16
    dim3 threadsPerBlock(16,16);   // 16, 16 

	// Why did 16
	// 16 -> output chenel


	//matmul time check
	cudaEventCreate(&kernel_start);
	cudaEventCreate(&kernel_stop);
	cudaEventRecord(kernel_start);

	matMul<<<blocksPerGrid, threadsPerBlock>>>(0, 1, M, N, K, 1.0f, temp_A, K, temp_B, N, 0, temp_C, N);
	cudaDeviceSynchronize();
	

	cudaEventRecord(kernel_stop);
	cudaEventSynchronize(kernel_stop);

	cudaEventElapsedTime(&foncTime, kernel_start, kernel_stop);
	fprintf(stderr, "MatMul Elapsed Time = %.6f millisec\n", foncTime);

	cudaEventDestroy(kernel_start);
	cudaEventDestroy(kernel_stop);
	//fin matmul time 

	//send time overhead
	//send result from device to host

	memset(C, 0, M * N * sizeof(float));

	// send time overhead
	cudaEventCreate(&send_host_start);
	cudaEventCreate(&send_host_stop);
	cudaEventRecord(send_host_start);

 
	cudaMemcpy(C, temp_C, M * N * sizeof(float), cudaMemcpyDeviceToHost);

	cudaEventRecord(send_host_stop);
	cudaEventSynchronize(send_host_stop);

	cudaEventElapsedTime(&send_host_time, send_host_start, send_host_stop);
	fprintf(stderr, "sned result from device to host Elapsed Time = %.6f millisec\n",
			send_host_time);

	cudaEventDestroy(send_host_start);
	cudaEventDestroy(send_host_stop);
	//fin check send time overhead

	cudaFree(temp_A);
    cudaFree(temp_B);
    cudaFree(temp_C);

}



