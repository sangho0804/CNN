#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	//set value
	int x = 256;
	int y = 256;
	int in_ch = 3;
	int out_ch = 16;
	int k_size = 3;
	int stride = 1;
	int pad = 1;

	float input_image =
		(float*)calloc(x * y * in_ch, sizeof(float));

	float output =
		(float*)calloc(x * y * out_ch, sizeof(float));

	float pad_contain_in =
		(float*)calloc((x + (2 * pad)) * (y + (2 * pad)) * in_ch, sizeof(float));

	float weight =
		(float*)calloc(out_ch * in_ch * k_size * k_size	, sizeof(float));


	//Extend to include pad
	//and copy input image
	for (int insert_index = 0; insert_index < y; insert_index++)
	{
		int pad_contain_index =
			(insert_index + pad) * (x + (2 * pad)) * in_ch + in_ch;

		int input_image_index =
			(insert_index)*x * in_ch;

		memcpy(&pad_contain_in[pad_contain_index]
			, &input_image[input_image_index]
			, sizeof(float) * (x * in_ch));
	}

	//start convolution

	for (int h_out = 0; h_out < y; h_out += stride)
	{
		for (int w_out = 0; w_out < x; w_out += stride)
		{
			for (int oc = 0; oc < out_ch; oc++)
			{
				//output conv result
				float out_result = 0;

				for (int ic = 0; ic < in_ch; ic++)
				{
					for (int r = 0; r < k_size; r++)
					{
						for (int s = 0; s < k_size; s++)
						{
							//exception : pad area is no carculating
							if (
								h_out + (r-1) >= y ||
								w_out + (s-1) >= x ||
								h_out + (r-1) < 0 ||
								w_out + (s-1) < 0)
							{
								continue;
							}

							int pad_contain_index =
								((h_out + r) * (x + (pad * 2)) * in_ch) +
								((w_out + s) * in_ch) + ic;
							int weight_index =
								(oc * in_ch * k_size * k_size) +
								(ic * k_size * k_size) +
								(r * k_size) + s;


							out_result +=
								pad_contain_in[pad_contain_index] * weight[weight_index];

						}


					}

				}

				//insert output map
				int out_index = (h_out * x * out_ch) + (w_out * out_ch) + oc;
				output[out_index] += out_result;
			}
		}

	}

}