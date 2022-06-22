### CNN
for deep learning study. <br>
CNU eslab in intern.

### This repo
this repo made for study deep learning and handle cnn.

### language
I used to <strong>C</strong> language.

### List
- Convolutional Layer
- Convolution Lowering ( im2col )
- GEMM
- GEMM with cuda <br>
  <pre>
  <strong>CUDA acceleration with GPU NVIDIA GTX 1080 </strong> 
  
  Use cpu  : 0.104083 sec      / Time measured only for gemm function 
  Use cuda : 0.888224 millisec / Time measured for using cuda 
  
  About <strong>117x</strong> performance improvement using cuda
  
  <strong>send time</strong>
  
  Host to Device                       : 0.000823168 sec
  Device to Host                       : 0.000583392 sec 
  Computation + Data Transfer Overhead : 0.002294784 sec
  
  Include send time, about <strong>45x</strong> performance improvement using cuda
  </pre>
  - Lesnet18

### Blog
#### The implementation process was written through a my blog.
- Convolutional Layer
  - https://strangecat.tistory.com/50 (1)
  - https://strangecat.tistory.com/51 (2)
- Convolution Lowering ( im2col ) 
  - https://strangecat.tistory.com/53
