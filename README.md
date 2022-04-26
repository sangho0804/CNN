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
  - 목표하는 성능에 도달하기 위해 선택한 가속 옵션 : GPU  NVIDIA GTX 1080를 이용한 CUDA 가속 <br> 현재 성능 : 0.104083 sec ( gemm 함수 연산 만을 측정한 시간 ) < br> 달성한 성능 : 0.888224 millisec / 0.000888224 sec ( cuda를 이용한 연산 만을 측정한 시간) - 약 117배 < br> 전송 시간 - host to device : 0.000823168 sec <br> device to host : 0.000583392 sec < br> computation + Data Transfer Overhead : 0.002294784 sec - 약 45배

### Blog
#### The implementation process was written through a my blog.
- https://strangecat.tistory.com/50 - Convolutional Layer(1)
- https://strangecat.tistory.com/51 - Convolutional Layer(2)
