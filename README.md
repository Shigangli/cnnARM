#cnnARMv7
This is an optimized shared convolution kernel for ARM v7. Users can set the arguments from command line, including width, height, channels, padding, stride, filterSizeX, filterSizeY and numfilter.
Other functions for CNN will be added.

#Performance
Single-precision test on Cortex-A15, single core.

| width | height | channels | padding | stride | filterSizeX | filterSizeY | numfilter | GFLOPS |
|:-----:|:------:|:--------:|:-------:|:------:|:-----------:|:-----------:|:---------:|:------:|
|  32  |  32  |  16  |  0  |  1  |  11  |  11  |  128  | 9.809 |
|  32  |  32  |  16  |  0  |  1  |  7  |  7  |  128  | 9.599 |
|  32  |  32  |  16  |  0  |  1  |  5  |  5  |  128  | 9.289 |
|  32  |  32  |  16  |  0  |  1  |  3  |  3  |  128  | 8.868 |


#Contributors
Shigang Li, Chunyang Xiang, Qian Wang
Send emails to shigangli.cs@gmail.com for any questions. 
