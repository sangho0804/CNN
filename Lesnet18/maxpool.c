void maxpool(float* in, float* out, int C, int H, int W, int KER, int stride, int PAD)
{
	int ch, h, w, r, s;


	int o_h = (H - KER + 2 * PAD) / stride + 1;
	int o_w = (W - KER + 2 * PAD) / stride + 1;

	float exception_val;
	for (ch = 0; ch < C; ch++) {

		for (h = 0; h < H; h += stride) {

			for (w = 0; w < W; w += stride) {
				float maxp = -FLT_MAX;

				if (w == 0 || w == stride) {
					exception_val = in[(ch * H * W) + (h * W) + w / stride];

				}

				for (r = 0; r < KER; r++) {

					for (s = 0; s < KER; s++) {

						if (h + r > H || w + s > W) {
							continue;
						}

						int in_index = (ch * H * W) + ((h + r) * W) + (w + s);


						if (maxp < in[in_index]) {
							maxp = in[in_index];
						}
					}
				}

				out[(ch * o_h * o_w) + (h / stride * o_w) + w / stride] =
					(w == 0 || w == stride) ? exception_val : maxp;



			}
		}
	}

}