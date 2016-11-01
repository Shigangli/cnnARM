#include "common.h"
/*****************************
 * Shigang Li, ICT,CAS
 * 22/06/2016
 * shigangli.cs@gmail.com
 *****************************/

void gemm_n_12_alpha_copy(long block_m, long block_k, FLOAT* src, long row_index, long col_index, long ldm, FLOAT *dst, long imageWidth, long imageHeight,long channels, long padding, long stride, long filterSizeX, long filterSizeY) 
{
    long filterPixels = filterSizeX * filterSizeY;
    long channelID = col_index / filterPixels;//start from 0
    long filterX = (col_index % filterPixels) % filterSizeX;//local column index
    long filterY = (col_index % filterPixels) / filterSizeY;//local row index
    long filtertmpX;
    long filtertmpY;
    long channeltmpID;

    long numperrow = (imageWidth - 2*padding - filterSizeX + 1)%stride == 0 ? (imageWidth - 2*padding - filterSizeX + 1)/stride : (imageWidth - 2*padding - filterSizeX + 1)/stride + 1;
    long moduleY = row_index / numperrow; 
    long moduleX = row_index % numperrow;
    long posX = moduleX * stride;
    long posY = moduleY * stride;
    long postmpX=posX;
    long postmpY=posY;
    
    long _l2;

    long _l1;
    long _l0;
    long ii;

    //FLOAT* _src0, *_src1;
    FLOAT* _dst0 = dst;
    _l2 = block_m - block_m/12*12;
    for (_l1=0; _l1<block_m-11; _l1+=12) 
    {
        //reset position in filter
        filtertmpX = filterX;
        filtertmpY = filterY;
        channeltmpID = channelID;
        postmpX = posX;
        postmpY = posY;
        for (_l0=0; _l0<block_k; _l0+=1) 
        {
	   for(ii=0; ii<12; ii++)
           {   
	       long pixelposX = postmpX + padding + filtertmpX;
	       long pixelposY = postmpY + padding + filtertmpY;
               if(pixelposX>=0 && pixelposX<imageWidth && pixelposY>=0 && pixelposY<imageHeight)
	          _dst0[ii] =  src[channeltmpID*imageWidth*imageHeight + pixelposY*imageWidth + pixelposX];
               else
		  _dst0[ii] = 0;

	       //go to next image position
	       postmpX += stride;
               if(postmpX > (numperrow-1)*stride)
	       {   
		   postmpX =  0; 
		   postmpY += stride;
	       }
	   }
           _dst0  += 12;
           
           if(_l0 != block_k-1)//reset postion in image
           {
	        postmpX = posX;
                postmpY = posY;
	   }
           else//update postion in image before go to next block
           {
		posX = postmpX;
           	posY = postmpY;
	   }
	   
	   //go to next filter position
	   filtertmpX++;
           if(filtertmpX == filterSizeX)
           {
		filtertmpX = 0;
		filtertmpY++;
                if(filtertmpY == filterSizeY)
                {
		   filtertmpY=0;
		   channeltmpID++; 
		}
	   } 
        }
    }
    
    if (_l2 > 7) 
    {   
        filtertmpX = filterX;
        filtertmpY = filterY;
        channeltmpID = channelID;
        for (_l0=0; _l0<block_k; _l0+=1) 
        {
	       for(ii=0; ii<8; ii++)
               {
	           long pixelposX = postmpX + padding + filtertmpX;
	           long pixelposY = postmpY + padding + filtertmpY;
                   if(pixelposX>=0 && pixelposX<imageWidth && pixelposY>=0 && pixelposY<imageHeight)
	              _dst0[ii] =  src[channeltmpID*imageWidth*imageHeight + pixelposY*imageWidth + pixelposX];
                   else
	    	      _dst0[ii] = 0;

	           //go to next image position
	           postmpX += stride;
                   if(postmpX > (numperrow-1)*stride)
	           {   
	               postmpX =  0; 
	               postmpY += stride;
	           }
	       }
               _dst0  += 8;
               
               if(_l0 != block_k-1)//reset postion in image
               {
	    	  postmpX = posX;
                  postmpY = posY;
	       }
               else//update postion in image before go to next block
               {
	    	  posX = postmpX;
               	  posY = postmpY;
	       }
	       
	       //go to next filter position
	      filtertmpX++;
              if(filtertmpX == filterSizeX)
              {
	           filtertmpX = 0;
	           filtertmpY++;
                   if(filtertmpY == filterSizeY)
                   {
	              filtertmpY=0;
	              channeltmpID++; 
	           }
	      } 
        }
        _l2 -= 8;
    }

    if (_l2 > 3)
    {
        filtertmpX = filterX;
        filtertmpY = filterY;
        channeltmpID = channelID;
        for (_l0=0; _l0<block_k; _l0+=1) 
        {
	       for(ii=0; ii<4; ii++)
               {
	           long pixelposX = postmpX + padding + filtertmpX;
	           long pixelposY = postmpY + padding + filtertmpY;
                   if(pixelposX>=0 && pixelposX<imageWidth && pixelposY>=0 && pixelposY<imageHeight)
	              _dst0[ii] =  src[channeltmpID*imageWidth*imageHeight + pixelposY*imageWidth + pixelposX];
                   else
	    	      _dst0[ii] = 0;

	           //go to next image position
	           postmpX += stride;
                   if(postmpX > (numperrow-1)*stride)
	           {   
	               postmpX =  0; 
	               postmpY += stride;
	           }
	       }
               _dst0  += 4;
               
               if(_l0 != block_k-1)//reset postion in image
               {
	    	  postmpX = posX;
                  postmpY = posY;
	       }
               else//update postion in image before go to next block
               {
	    	  posX = postmpX;
               	  posY = postmpY;
	       }
	       
	       //go to next filter position
	      filtertmpX++;
              if(filtertmpX == filterSizeX)
              {
	           filtertmpX = 0;
	           filtertmpY++;
                   if(filtertmpY == filterSizeY)
                   {
	              filtertmpY=0;
	              channeltmpID++; 
	           }
	      } 
        }
        _l2 -= 4;
    }

    if (_l2 > 1) 
    {
        filtertmpX = filterX;
        filtertmpY = filterY;
        channeltmpID = channelID;
        for (_l0=0; _l0<block_k; _l0+=1) 
        {
	       for(ii=0; ii<2; ii++)
               {
	           long pixelposX = postmpX + padding + filtertmpX;
	           long pixelposY = postmpY + padding + filtertmpY;
                   if(pixelposX>=0 && pixelposX<imageWidth && pixelposY>=0 && pixelposY<imageHeight)
	              _dst0[ii] =  src[channeltmpID*imageWidth*imageHeight + pixelposY*imageWidth + pixelposX];
                   else
	    	      _dst0[ii] = 0;

	           //go to next image position
	           postmpX += stride;
                   if(postmpX > (numperrow-1)*stride)
	           {   
	               postmpX =  0; 
	               postmpY += stride;
	           }
	       }
               _dst0  += 2;
               
               if(_l0 != block_k-1)//reset postion in image
               {
	    	  postmpX = posX;
                  postmpY = posY;
	       }
               else//update postion in image before go to next block
               {
	    	  posX = postmpX;
               	  posY = postmpY;
	       }
	       
	       //go to next filter position
	      filtertmpX++;
              if(filtertmpX == filterSizeX)
              {
	           filtertmpX = 0;
	           filtertmpY++;
                   if(filtertmpY == filterSizeY)
                   {
	              filtertmpY=0;
	              channeltmpID++; 
	           }
	      } 
        }
        _l2 -= 2;
    }

    if (_l2 > 0)
    {
        filtertmpX = filterX;
        filtertmpY = filterY;
        channeltmpID = channelID;
        for (_l0=0; _l0<block_k; _l0+=1) 
        {
	       for(ii=0; ii<1; ii++)
               {
	           long pixelposX = postmpX + padding + filtertmpX;
	           long pixelposY = postmpY + padding + filtertmpY;
                   if(pixelposX>=0 && pixelposX<imageWidth && pixelposY>=0 && pixelposY<imageHeight)
	              _dst0[ii] =  src[channeltmpID*imageWidth*imageHeight + pixelposY*imageWidth + pixelposX];
                   else
	    	      _dst0[ii] = 0;

	           //go to next image position
	           postmpX += stride;
                   if(postmpX > (numperrow-1)*stride)
	           {   
	               postmpX =  0; 
	               postmpY += stride;
	           }
	       }
               _dst0  += 1;
               
               if(_l0 != block_k-1)//reset postion in image
               {
	    	  postmpX = posX;
                  postmpY = posY;
	       }
               else//update postion in image before go to next block
               {
	    	  posX = postmpX;
               	  posY = postmpY;
	       }
	       
	       //go to next filter position
	      filtertmpX++;
              if(filtertmpX == filterSizeX)
              {
	           filtertmpX = 0;
	           filtertmpY++;
                   if(filtertmpY == filterSizeY)
                   {
	              filtertmpY=0;
	              channeltmpID++; 
	           }
	      } 
        }
        _l2 -= 1;
    }
}
