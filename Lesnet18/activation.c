void activation(float* out, int C, int H, int W)
{

	int ch, he, we;
	for (he = 0; he < H; he++) {

		for (we = 0; we < W; we++) {

			for (ch = 0; ch < C; ch++) {

				int index = (he * W * C) + (we * C) + ch;

				if (out[index] < 0) {
					out[index] *= 0.1;
				}
			}
		}
	}


}