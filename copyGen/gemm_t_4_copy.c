#include "common.h"

void gemm_t_4_copy(long block_k,long block_n,FLOAT* src,long ldm,FLOAT* dst) 
{
   long _l1;
   long _l0;
   FLOAT* _src3;
   FLOAT* _src2;
   FLOAT* _src1;
   FLOAT* _src0;
   for (_l1=0; _l1<-3+block_n; _l1+=4) 
     {
        _src0 = src;
        _src1 = _src0+ldm;
        _src2 = _src1+ldm;
        _src3 = _src2+ldm;
        for (_l0=0; _l0<-3+block_k; _l0+=4) 
          {
             dst[0] = _src0[0];
             dst[4] = _src0[1];
             dst[8] = _src0[2];
             dst[12] = _src0[3];
             dst[1] = _src1[0];
             dst[5] = _src1[1];
             dst[9] = _src1[2];
             dst[13] = _src1[3];
             dst[2] = _src2[0];
             dst[6] = _src2[1];
             dst[10] = _src2[2];
             dst[14] = _src2[3];
             dst[3] = _src3[0];
             dst[7] = _src3[1];
             dst[11] = _src3[2];
             dst[15] = _src3[3];
             _src0 = _src0+4;
             _src1 = _src1+4;
             _src2 = _src2+4;
             _src3 = _src3+4;
             dst = 16+dst;
          }
        for (_l0=(block_k&3); _l0>0; _l0-=1) 
          {
             dst[0] = _src0[0];
             dst[1] = _src1[0];
             dst[2] = _src2[0];
             dst[3] = _src3[0];
             _src0 = _src0+1;
             _src1 = _src1+1;
             _src2 = _src2+1;
             _src3 = _src3+1;
             dst = 4+dst;
          }
        src = src+(4*ldm);
     }
   for (_l1=(block_n&3); _l1>0; _l1-=1) 
     {
        _src0 = src;
        for (_l0=0; _l0<-3+block_k; _l0+=4) 
          {
             dst[0] = _src0[0];
             dst[1] = _src0[1];
             dst[2] = _src0[2];
             dst[3] = _src0[3];
             _src0 = _src0+4;
             dst = 4+dst;
          }
        for (_l0=(block_k&3); _l0>0; _l0-=1) 
          {
             dst[0] = _src0[0];
             _src0 = _src0+1;
             dst = 1+dst;
          }
        src = src+ldm;
     }
}
