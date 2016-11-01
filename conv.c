#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "common.h"
#include "interface.h"
#include <math.h>
#include "param.h"

double _DiffTime(struct timeval te, struct timeval ts)
{
	return ((double)(te.tv_sec - ts.tv_sec) + (double)(te.tv_usec - ts.tv_usec)/1000000);
}

int main(int argc, char **argv)
{
	struct timeval ts, te;
	long i, j, l;
	long km, kn, ch;

	long imageWidth; 
	long imageHeight; 
	long channels; 
	long padding; 
	long stride; 
	long filterSizeX; 
	long filterSizeY; 
	long numFilters;

        if(argc == 1)
        {
	    imageWidth = 16; 
	    imageHeight = 16; 
	    channels = 3; 
	    padding = -1; 
	    stride = 1; 
	    filterSizeX = 3; 
	    filterSizeY = 3; 
	    numFilters = 8;
	    printf("Default setting: width=%ld, height=%ld, channels=%ld, padding=%ld, stride=%ld, filterSizeX=%ld, filterSizeY=%ld, numfilter=%ld\n", imageWidth, imageHeight, channels, padding, stride, filterSizeX, filterSizeY, numFilters);
            printf("Set your own args in order line: width height channels padding stride filterSizeX filterSizeY numfilter\n");
            printf("\n");
        }
        else
        {
	    imageWidth = atoi(argv[1]); 
	    imageHeight = atoi(argv[2]); 
	    channels = atoi(argv[3]); 
	    padding = atoi(argv[4]); 
	    stride = atoi(argv[5]); 
	    filterSizeX = atoi(argv[6]); 
	    filterSizeY = atoi(argv[7]); 
	    numFilters = atoi(argv[8]);
	}

        long moduleX = (imageWidth - 2*padding - filterSizeX + 1)/stride;
        if((imageWidth - 2*padding - filterSizeX + 1) % stride != 0)
            moduleX++;

        long moduleY = (imageHeight - 2*padding - filterSizeY + 1)/stride;
        if((imageHeight - 2*padding - filterSizeY + 1) % stride != 0)
            moduleY++;

	long m = moduleX * moduleY;
	long k = filterSizeX * filterSizeY * channels;
	long n = numFilters;
        printf("moduleX=%ld, moduleY=%ld, m=%ld, k=%ld, n=%ld\n", moduleX, moduleY, m, k, n);	
	FLOAT * images = (FLOAT *)malloc(imageWidth*imageHeight*channels*sizeof(FLOAT));
	FLOAT * unfold = (FLOAT *)malloc(k*m*sizeof(FLOAT));
        

	FLOAT * filters = (FLOAT *)malloc(filterSizeX*filterSizeY*channels*numFilters*sizeof(FLOAT));
	FLOAT * output = (FLOAT *)malloc(m*n*sizeof(FLOAT));
	FLOAT * outputCheck = (FLOAT *)malloc(m*n*sizeof(FLOAT));

	for(i=0; i<imageWidth*imageHeight*channels; i++)
		images[i] = i%17;
	for(i=0; i<filterSizeX*filterSizeY*channels*numFilters; i++)
		filters[i] = i%17;
	for(i=0; i<m*n; i++)
	{	
		output[i] = 0.0;
		outputCheck[i] = 0.0;
	}
	long posX = 0;
        long posY = 0;
        for(i=0; i<moduleY; i++)
        {    
	    posX = 0;
	    for(j=0; j<moduleX; j++)
	    {
		for(ch=0; ch<channels; ch++)
                    for(km=0; km<filterSizeY; km++)
        	        for(kn=0; kn<filterSizeX; kn++)
		        {
		           long pixelposX = padding + posX + kn;
		           long pixelposY = padding + posY + km;
        	           if(pixelposX>=0 && pixelposX<imageWidth && pixelposY>=0 && pixelposY<imageHeight)
		              unfold[(ch*filterSizeX*filterSizeY+km*filterSizeX+kn)*moduleX*moduleY+i*moduleX+j] =  images[ch*imageWidth*imageHeight + pixelposY*imageWidth + pixelposX];
        	           else
		              unfold[(ch*filterSizeX*filterSizeY+km*filterSizeX+kn)*moduleX*moduleY+i*moduleX+j] =  0;
		        }
		posX += stride;
	    }
	    posY += stride;
	}


	gemm(m, n, k, images, m, filters, k, output, m, imageWidth, imageHeight, channels, padding, stride, filterSizeX, filterSizeY, numFilters);
	gettimeofday(&ts, NULL);
        for(i=0; i<16; i++)
        {
	    gemm(m, n, k, images, m, filters, k, output, m, imageWidth, imageHeight, channels, padding, stride, filterSizeX, filterSizeY, numFilters);
        }

	gettimeofday(&te, NULL);
	printf("\nComputation is over!\n");

	double Mflops = 2 * m * n / 1000000.0;
	Mflops = Mflops * k / _DiffTime(te, ts) * 16;
	printf("\nbmxbkxbn = %dx%dx%d\nPerformance of GEMM = %.3lf\n", BLOCKM, BLOCKK, BLOCKN, Mflops);

	printf("gflops is %f \n",Mflops/1000/18.564);

#if defined(DEBUG)

	//printf("\ncheckout matrices\n");
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < m; j ++)
		{
			for (l = 0; l < k; l ++)
			{
				outputCheck[i * m + j] += filters[i * k + l] * unfold[l * m + j];
			}
		}
	}

	check_result_2D(output, outputCheck, m, n);
	printf("\nCheck Over!\n");
#endif
	free(images);
	free(unfold);
	free(filters);
	free(output);
	free(outputCheck);
	return 0;
}
