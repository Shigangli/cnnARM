#ifdef DOUBLE
#if defined(SANDYBRIDGE)
#define BLOCKM			256
#define BLOCKN			256
#define BLOCKK			256

#define REGBLOCKM		8
#define REGBLOCKN		4

#elif defined(XEONPHI)
#define BLOCKM			30
#define BLOCKN			64
#define BLOCKK			32

#define REGBLOCKM		30
#define REGBLOCKN		8

#define THREADGROUPNUM	4
#define THREADNUMGROUP	2
#endif
#elif defined(A15)
#define REGBLOCKM		12
#define REGBLOCKN		4

//#define BLOCKM			240
//#define BLOCKK			512
//#define BLOCKN			1024
#else
#define REGBLOCKM	8
#define REGBLOCKN	4
#endif


#if	defined(X86_64)
#include "common_x86.h"
#endif

#if defined(ARM)
#include "common_arm.h"
#endif
