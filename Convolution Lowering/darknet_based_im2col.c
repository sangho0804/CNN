void im2col(float* in, float* out, int h, int w, int c, int k, int stride, int pad) {



	//im2col h, w, c
	int col_h = (w + 2 * pad - k) / stride + 1;
	int col_w = (h + 2 * pad - k) / stride + 1;
	int col_c = c * k * k;

	//make up
	for (int height = 0; height < col_h; height++) {

		int out_h = height * col_w * col_c;

		for (int weight = 0; weight < col_w; weight++) {

			int out_w = weight * col_c;

			for (int ch = 0; ch < col_c; ch++) {

				//out index
				int out_ch = ch;
				int out_index = out_h + out_w + out_ch;

				//in index
				int im_ch = ch / (k * k);
				int im_w = weight * stride + (ch % k);
				int im_h = height * stride + ((ch / k) % k);


				//exception
				if ((im_h - pad) < 0 || (im_w - pad) < 0 || (im_h - pad) >= h || (im_w - pad) >= w) {

					out[out_index] = 0;

					continue;
				}


				int in_index = im_ch * h * w + (im_h - pad) * w + (im_w - pad);

				//insert
				out[out_index] = in[in_index];

			}
		}
	}

}