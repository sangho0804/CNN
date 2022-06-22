void shortcut(float* shrt, int s_C, int s_H, int s_W, float* prev, int p_C, int p_H, int p_W, float* out)
{

	int ch, he, we;
	int o_c, o_h, o_w;
	int not_equal_step = 2;
	o_c = s_C;
	o_h = s_H;
	o_w = s_W;

	if (s_C == p_C) {

		for (ch = 0; ch < o_c; ch++) {

			for (he = 0; he < o_h; he++) {

				for (we = 0; we < o_w; we++) {

					int index = (ch * o_h * o_w) + (he * o_w) + we;

					out[index] = shrt[index] + prev[index];
				}
			}
		}

	}
	else {
		int	out_h = o_h / not_equal_step;
		int	out_w = o_w / not_equal_step;


		for (ch = 0; ch < p_C; ch++) {

			for (he = 0; he < p_H; he++) {

				for (we = 0; we < p_W; we++) {

					int index = (ch * p_H * p_W) + (he * p_W) + we;

					out[index] = prev[index];
				}
			}
		}


		for (ch = 0; ch < o_c; ch++) {

			for (he = 0; he < o_h; he += not_equal_step) {

				for (we = 0; we < o_w; we += not_equal_step) {

					if (we == 0) {
						we == 1;
					}

					int shrt_index = (ch * o_h * o_w) + (he * o_w) + we;


					int out_index = (ch * out_h * out_w) +
						((he / not_equal_step) * out_w) +
						(we / not_equal_step);

					out[out_index] = shrt[shrt_index] + prev[out_index];


				}
			}
		}

	}

}