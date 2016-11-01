#include "common.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void initialize_matrix(FLOAT *mat, LONG rownum, LONG colnum)
{
	LONG i, j;
	srand(time(NULL));
	for (j = 0; j < colnum; ++j)
	{
		for (i = 0; i < rownum; ++i)
		{
			mat[j * rownum + i] = i % 13 + 1;//rand() % 100 / 10.0;
			//mat[j * rownum + i] = rand() % 100 / 10.0;
			//mat[j * rownum + i] = rand() % 10 + 1;
		}
	}
}
void prin_matrix(FLOAT* mat, LONG rownum, LONG colnum)
{
    LONG i,j;
    for(i=0;i<rownum;++i)
    {
        for(j=0;j<colnum;++j)
        {
            printf("%4.0f  ",mat[j*rownum+i]);
        }
        printf("\n");
    }

}

void initialize_vector(FLOAT *vec, LONG size)
{
	LONG i;
	srand(time(NULL));
	for (i = 0; i < size; ++i)
		vec[i] = i % 8 + 1;//rand() %  100 / 10.0;
		//vec[i] = rand() %  100 / 10.0;
}


void check_result_2D(FLOAT *trusted, FLOAT *tested, LONG rownum, LONG colnum)
{
	LONG i, j;
  int error_num=0;
	for (j = 0; j < colnum; ++j)
	{
		for (i = 0; i < rownum; ++i)
			//if (fabs(trusted[j*rownum+i]-tested[j*rownum+i])/rownum> EPS)
			if (fabs(trusted[j*rownum+i]-tested[j*rownum+i])>EPS)
      {
          error_num ++;
				//printf("Error: (%ld, %ld) : trusted result %.2lf\ttested result %.2lf\n", i, j, trusted[j*rownum+i], tested[j*rownum+i]);
      }
	}
  printf("ERROR NUM =%d\n",error_num);
}

void check_result_1D(FLOAT *trusted, FLOAT *tested, LONG size)
{
	LONG i;
	for (i = 0; i < size; ++i)
			if (fabs(trusted[i]-tested[i])> EPS)
				printf("Error: %ld : trusted result %.2lf\ttested result %.2lf\n", i, trusted[i], tested[i]);

}

void copy_matrix(FLOAT *src, FLOAT *dst, LONG rownum, LONG colnum)
{
	int i, j;

	for (j = 0; j < colnum; ++j)
		for (i = 0; i < rownum; ++i)
		{
			dst[j * rownum + i] = src[j * rownum + i];
		}
}

void copy_vector(FLOAT *src, FLOAT *dst, LONG size)
{
	int i;
	for (i = 0; i < size; ++i)
	{
		dst[i] = src[i];
	}
}
