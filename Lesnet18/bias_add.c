void bias_add(float* bias, float* out, int C, int H, int W)
{

	int c, h, w;

	for (c = 0; c < C; c++) {
		for (h = 0; h < H; h++) {
			for (w = 0; w < W; w++) {
				int index = (c * H * W) + (h * W) + w;
				out[index] += bias[c];
			}
		}
	}
}