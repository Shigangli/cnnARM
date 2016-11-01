#ifndef _AUXILIARY_
#define _AUXILIARY_
#include "common.h"
#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>
#if defined(XEONPHI)
#include "immintrin.h"
#endif
#define HUGE_PAGE_SIZE (2 * 1024 * 1024)
#define ALIGN_TO_PAGE_SIZE(x)\
	(((x) + HUGE_PAGE_SIZE - 1) / HUGE_PAGE_SIZE * HUGE_PAGE_SIZE)

void print_buf(long m, long n, int rn, FLOAT *buf);
#ifdef XEOEPHI
void print_simd512_var(__m512d x);
void free_huge_pages(void *ptr);
void *malloc_huge_pages(size_t size);
#endif

#endif
