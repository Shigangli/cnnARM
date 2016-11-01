#include "common.h" 
#include "param.h"
#include "auxiliary.h"
#include <stdlib.h>
#include <stdio.h>

void COPY_R(long block_m, long block_k, FLOAT* src, long row_index, long col_index, long ldm, FLOAT *dst, long imageWidth, long imageHeight,long channels, long padding, long stride, long filterSizeX, long filterSizeY); 
void COPY_L(long block_k, long block_n, FLOAT *src, long ldm, FLOAT *dst);
void gemmkernel(long BM, long BN, long BK, FLOAT* buf_a, FLOAT* buf_b, FLOAT* C, long LDC);


void gemm(long M, long N, long K, 
        FLOAT *images, long ldA,
        FLOAT *filters, long ldB,
        FLOAT *output, long ldC, long imageWidth, 
	long imageHeight, long channels, long padding, 
	long stride, long filterSizeX, long filterSizeY, long numFilters)
{
    long i, j, l;
    long block_n, block_m, block_k;
    void *buffer = (void *) malloc ((BLOCKM * BLOCKK + BLOCKK * BLOCKN) * sizeof(FLOAT) + PAD);
    FLOAT *buf_b = (FLOAT *)(((unsigned long )buffer + PAD) & ~(PAD - 1));
    FLOAT *buf_a = buf_b + BLOCKK * BLOCKN;
    //printf("\nEnter gemm subroutine\n\tBLOCKM %d\n\tBLOCKN %d\n\tBLOCKK %d\n", BLOCKM, BLOCKN, BLOCKK);
    //printf("\tREGBLOCKM %d\n\tREGBLOCKN %d\n", REGBLOCKM, REGBLOCKN);
    //printf("\bAddresses of internal buffer: \n\tbut_A %x\n\tbuf_B %x  buf_a=%d;buf_b=%d\n", buf_a, buf_b,buf_a,buf_b);
    long m = M;
    long n = N;
    long k = K;
    long lda = ldA;
    long ldb = ldB;
    long ldc = ldC;
    //FLOAT alpha = ALPHA;
    //FLOAT beta  = BETA;

    for (j = 0; j < n; j += BLOCKN)
    {
        block_n = MIN(BLOCKN, (n - j));

        for (l = 0; l < k; l += BLOCKK)
        {
            block_k = MIN(BLOCKK, (k - l));

            COPY_L(block_k, block_n, filters + j * ldb + l, ldb, buf_b);
#ifdef DEBUG
            //printf("\nCOPY_L: \n\tblock_kxblock_n = %dx%d\n", block_k, block_n);
            //print_buf(block_k, block_n, REGBLOCKN, buf_b);
            //printf("\n");
#endif
            for (i = 0; i < m; i += BLOCKM)
            {
                block_m = MIN(BLOCKM, (m - i));
                COPY_R(block_m, block_k, images, i, l, lda, buf_a, imageWidth, imageHeight, channels, padding, stride, filterSizeX, filterSizeY);
                //printf("\n**************TEST A********\n");
                //printf(buf_a,block_m,block_k);

                
#ifdef DEBUG
               // printf("\nCOPY_R: \n\tblock_mxblock_k = %dx%d\n", block_m, block_k);
               // print_buf(block_k, block_m, REGBLOCKM, buf_a);
               // printf("\n");
#endif
                //invoking assembly function 
                gemmkernel(block_m, block_n, block_k, buf_a, buf_b, output + j * ldc + i, ldc);
            }
        }
    }

    free(buffer);
}
