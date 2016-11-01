#ifndef _COMMON_H
#define _COMMON_H

#define PAD	128
//#define PAD	1024
#define EPS	1.e-7


#define MIN(a, b)	(((a) < (b)) ? (a) : (b))
#define MAX(a, b)	(((a) < (b)) ? (b) : (a))

#if defined(DOUBLE)
#define FLOAT	double
#else
#define FLOAT	float
#endif

#define LONG	long

#endif
