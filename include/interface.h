#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "common.h"
//void COPY_R(long m, long n, FLOAT *src, long ldm, FLOAT *dst, FLOAT alpha);
//void gemm(long m, long n, long k, FLOAT* A, long lda, FLOAT alpha, FLOAT *B, long ldb, FLOAT beta, FLOAT *C, long ldc);
void gemm(long M, long N, long K,
        FLOAT *images, long ldA,
        FLOAT *filters, long ldB,
        FLOAT *output, long ldC, long imageWidth,
        long imageHeight, long channels, long padding,
        long stride, long filterSizeX, long filterSizeY, long numFilters);
void COPY_R(long block_m, long block_k, FLOAT* src, long row_index, long col_index, long ldm, FLOAT *dst, long imageWidth, long imageHeight,long channels, long padding, long stride, long filterSizeX, long filterSizeY);
void COPY_L(long block_k, long block_n, FLOAT *src, long ldm, FLOAT *dst);
#if !defined(XEONPHI)
void gemmkernel(long BM,long BN,long BK,FLOAT* buf_a,FLOAT* buf_b,FLOAT* C,long LDC);
#else
void gemmkernel(long BM,long BN,long BK,FLOAT* buf_a,FLOAT* buf_b,FLOAT* C,long LDC, int *offset);
#endif



#endif
