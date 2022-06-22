void conv(float* in, float* we, float* out, int image_x, int image_y, int in_ch, int out_ch, int kernel_size, int stride, int pad)
{



	int output_x = (image_x + 2 * pad - kernel_size) / stride + 1;
	int output_y = (image_y + 2 * pad - kernel_size) / stride + 1;

	for (int oc = 0; oc < out_ch; oc++) {
		for (int h_out = 0; h_out < image_y; h_out += stride) {
			for (int w_out = 0; w_out < image_x; w_out += stride) {
				//output conv result
				float out_result = 0;
				for (int ic = 0; ic < in_ch; ic++) {
					for (int r = 0; r < kernel_size; r++) {
						for (int s = 0; s < kernel_size; s++) {



							// exception : pad area is no carculating
							if (
								h_out + (r - pad) >= image_y ||
								w_out + (s - pad) >= image_x ||
								h_out + (r - pad) < 0 ||
								w_out + (s - pad) < 0)

							{
								continue;
							}

							int in_index = (ic * image_x * image_y) +
								((h_out + (r - pad)) * image_x) +
								(w_out + (s - pad));

							int weight_index = (oc * in_ch * kernel_size * kernel_size) +
								(ic * kernel_size * kernel_size) +
								(r * kernel_size) + s;

							out_result += in[in_index] * we[weight_index];

						}

					}

				}


				int out_index = oc * output_x * output_y + h_out / stride *
					output_x + w_out / stride;


				out[out_index] = out_result;


			}
		}
	}


}