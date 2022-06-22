void global_avgpool(float* in, float* out, int C, int H, int W)
{
	int ch, he, we;

	for (ch = 0; ch < C; ch++) {
		float gloAvgPool = 0;

		for (he = 0; he < H; he++) {

			for (we = 0; we < W; we++) {

				gloAvgPool += in[(ch * W * H) + (he * W) + we];

			}
		}

		out[ch] = gloAvgPool / (H * W);

	}

}