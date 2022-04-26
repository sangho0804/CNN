#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "timer.h"
#include "utils.h"

#include <string.h>

#define WID 256
#define HEI 256
#define I_C 3
#define O_C 16
#define KER 3
#define PAD 1

//for use Cuda 
extern void gemmCuda(int transA, int transB, 
          int M, int N, int K, 
          float ALPHA, 
          float* A, int lda, 
          float* B, int ldb, 
          float BETA,  
          float* C, int ldc);

//not use GEMM with Cuda
void gemm(int transA, int transB, 
          int M, int N, int K, 
          float ALPHA, 
          float* A, int lda, 
          float* B, int ldb, 
          float BETA,  
          float* C, int ldc){

    // M   N   K
    // h*w o*c c*k*k
	int hw, oc , ckk;

	for (hw = 0; hw < M; hw++) {
		
		for (oc = 0; oc < N; oc++) {
			
			for (ckk = 0; ckk < K; ckk++) {
				
				int out_index = oc + hw * ldc;
				int input_index = ckk + hw * lda;
				int weight_index = ckk + oc * K;

				C[out_index] += A[input_index] * B[weight_index];
			}
		}
	}


}
void im2col(float *in, float *out, int H, int W, int C, int ker){

    //im2col(input,im2col_in,256,256,3,3);
	//pad contain input image

	float* pad_contain = 
		(float*)calloc((WID + (2 * PAD)) * (HEI + (2 * PAD)) * I_C,
				sizeof(float));	


	// memory value copy
	for(int insert_index = 0; insert_index < HEI; insert_index++)
	{
		memcpy(&pad_contain[(insert_index + PAD)*(WID + (2 * PAD)) * I_C
				+ I_C] , &in[(insert_index) * WID * I_C], sizeof(float) *
				(WID * I_C));
	}
	//end of copy	


	//im2col h, w, c
	int col_h = (W + 2 * PAD - ker) / 1 + 1;
	int col_w = (H + 2 * PAD - ker) / 1 + 1;
	int col_c = C * ker * ker ;
	
	//if move height 

	for(int height = 0; height < col_h; height++){
		
		int out_h = height * col_w * col_c;
        
		for(int weight = 0; weight < col_w ; weight++){
			
			int out_w = weight * col_c;

            for(int ch = 0; ch < col_c ; ch++){
				
				//out index
				int out_ch = ch ;
				int out_index = out_h + out_w + out_ch;


				//end of out index

				//in index
				//exception
				int check_in_h = ch / ker;

				if (check_in_h > 2 && check_in_h < 6 ) {
					check_in_h -= 3;
				}
				if (check_in_h > 5 && check_in_h < 9 ) {
					check_in_h -= 6;
				}

				//end of exception
				
				int move_in_ch = ch / (ker * ker);
				int move_in_w = ch % ker * C ;
				int move_in_h = check_in_h  * (col_w+PAD*2) * C;

				int in_w = weight * C ; 
				int in_h = height * (W + PAD * 2) * C ;
				
				int in_index = move_in_ch + move_in_w + move_in_h +in_w
					+ in_h;

				
				//end of in index

				out[out_index] = pad_contain[in_index];
	
			}
        }
    }

}

int main(int argc, char **argv) {

		                          // Height * Width *Channel
    float* input  = (float*)malloc(       HEI * WID * I_C * sizeof(float));
                                  // o_ch * in_ch * kernel y * x
    float* weight = (float*)malloc( O_C * I_C * KER * KER * sizeof(float));
                                  // Height * Width *Channel
    float* output = (float*)malloc(       HEI * WID * O_C * sizeof(float));


    //input initialization
    for(int h = 0; h < HEI; h++){
        for(int w = 0; w < WID; w++){
            for(int c = 0; c < I_C; c++){
                input[ (h * WID * I_C) + (w * I_C) + c] = (rand()%10000)/10000.f;
            }
        }
    }
    //weight initialization
    for(int oc = 0; oc < O_C; oc++){
        for(int ic = 0; ic < I_C; ic++){
            for(int r = 0; r < KER; r++){
                for(int s = 0; s < KER; s++){
                    weight[ (oc*I_C*KER*KER) + (ic*KER*KER) + (r*KER) + s] = (rand()%10000)/10000.f;
                }
            }
        }
    }

                                  // Height * Width *Channel
    float* input_i2c  = (float*)calloc( HEI * WID * I_C * KER * KER, sizeof(float));

    im2col(input, input_i2c,HEI,WID,I_C,KER);
	
   
	int LDA = I_C*KER*KER;
    int LDB = O_C;
    int LDC = O_C;

    gemmCuda(0,1,   //B matrix = weight matrix transpose
        HEI*WID, O_C, I_C*KER*KER,
        1.0f, 
        input_i2c,LDA, 
        weight, LDB,
        0.0f,
        output,LDC);
    
    return 0;
}
