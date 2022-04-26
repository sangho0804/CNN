### CNN
for deep learning study. <br>
CNU eslab in intern.

### This repo
this repo made for study deep learning and handle cnn.

### language
I used to <strong>C</strong> language.

### List
- Convolutional Layer
- Convolution Lowering
- GEMM
- GEMM with cuda
  - CUDA acceleration with GPU NVIDIA GTX 1080 <br>
  use cpu : 0.104083 sec - Time measured only for gemm function -<br> 
  use cuda : 0.888224 millisec ( 0.000888224 sec) -Time measured for using cuda -<br>
  Confirm that cuda is about <strong>117 times</strong> faster than cpu <br>
  <transmission time> <br>
  host to device : 0.000823168 sec<br> 
  device to host : 0.000583392 sec <br>
  computation + Data Transfer Overhead : 0.002294784 sec - about 45 times faster than cpu

### Blog
#### The implementation process was written through a my blog.
- https://strangecat.tistory.com/50 - Convolutional Layer(1)
- https://strangecat.tistory.com/51 - Convolutional Layer(2)
