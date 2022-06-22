void softmax(float* in, float* out, int C)
{
	float max = 0;

	int ch;

	for (ch = 0; ch < C; ch++) {
		max += exp(in[ch]);
	}

	for (ch = 0; ch < C; ch++) {
		out[ch] = exp(in[ch]) / max;
	}
}