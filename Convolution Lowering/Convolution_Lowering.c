#include "im2col.h"
#include <stdio.h>
#include <string.h>


/// <summary>
/// im2col implement
/// </summary>
/// <returns></returns>

int main() {
    
    //set value
    int w = 256;
    int h = 256;
    int c = 3;
    int k = 3;
    int stride = 1;
    int pad = 1;
    float in =
        (float*)calloc(w * h * c, sizeof(float));

    float pad_contain_in =
        (float*)calloc((w + (2 * pad)) * (h + (2 * pad)) * c, sizeof(float));
    float out =
        (float*)calloc(w * h * k * k * c, sizeof(float));

    //Extend to include pad
    //and copy input image
    for (int insert_index = 0; insert_index < y; insert_index++)
    {
        int pad_contain_index =
            (insert_index + pad) * (w + (2 * pad)) * c + c;

        int input_image_index =
            (insert_index)* w * c;

        memcpy(&pad_contain_in[pad_contain_index]
            , &in[input_image_index]
            , sizeof(float) * (w * c));
    }


    int col_h = (w + 2 * pad - k) / 1 + 1;
    int col_w = (h + 2 * pad - k) / 1 + 1;
    int col_c = c * k * k;


    for (int height = 0; height < col_h; height++)
    {
        int out_h = height * col_w * col_c;
        
        for (int weight = 0; weight < col_w; weight++)
        {
            int out_w = weight * col_c;

            for (int ch = 0; ch < col_c; ch++)
            {
                //out index
                int out_ch = ch;
                int out_index = out_h + out_w + out_ch;
                //end of out index


                //in index
                //exception
                int check_in_h = ch / k;

                if (check_in_h > 2 && check_in_h < 6)
                {
                    check_in_h -= 3;
                }
                if (check_in_h > 5 && check_in_h < 9)
                {
                    check_in_h -= 6;
                }
                //end of exception



                int move_in_ch = ch / (k * k);
                int move_in_w = ch % k * c;
                int move_in_h = check_in_h * (col_w + PAD * 2) * c;

                int in_w = weight * c;
                int in_h = height * (col_w + PAD * 2) * c;
                int in_index = move_in_ch + move_in_w + move_in_h + in_w + in_h;
                //end of in index

                out[out_index] = pad_contain_in[in_index];
            }
        }
    }




}