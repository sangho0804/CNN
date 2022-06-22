void im2col(float* in, float* out, int h, int w, int c, int k, int stride, int pad) {


    int rs = 0;
    int hw = 0;
    int height, width, in_ch, r, s;

    for (height = 0; height < h; height += stride) {

        for (width = 0; width < w; width += stride) {

            for (in_ch = 0; in_ch < c; in_ch++) {

                for (r = 0; r < k; r++) {

                    for (s = 0; s < k; s++) {

                        int out_index = hw * c * k * k + in_ch * k * k + rs;
                        int in_index = in_ch * h * w + (height + (r - pad)) * w + (width + (s - pad));


                        if (height + (r - pad) < 0 || width + (s - pad) < 0 || height + (r - pad) >= h || width + (s - pad) >= w) {

                            out[out_index] = 0;
                            rs += 1;
                            continue;
                        }
                        out[out_index] = in[in_index];
                        rs += 1;
                    }
                }
                rs = 0;
            }
            hw++;
        }
    }
}
