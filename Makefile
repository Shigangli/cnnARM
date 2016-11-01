CC=gcc
CFLAGS= 
#CFLAGS= -g 
LDFLAGS=
INCdirs=./include
COPYCODEdir=copyGen
#DRIVERdir=.
DRIVERdir=driver
KERNELCODEdir=kernelCodes

GEMM ?= 1
blockm ?= 240
blockn ?= 512
blockk ?= 512


DOUBLE ?= 0
ASM	?= 1
#SHAPE ?= "L"
#OPENMP ?= 0

ARCH=ARM
#CFLAGS += -D$(ARCH) -DDEBUG
CFLAGS += -D$(ARCH)
CFLAGS += -lm

CORE=A15


ifeq ($(ASM), 1)
SUFFIX=S
else
SUFFIX=c
endif

#ifeq ($(DEBUG), 1)
#	CFLAGS += -DDEBUG -g -O0
#else
	CFLAGS += -O3
#endif

ifneq ($(ASM), 1)
	CFLAGS += -DINTRINSIC
endif

ifeq ($(ARCH), ARM)
	CFLAGS += -marm -march=armv7-a -mfloat-abi=hard -mfpu=neon
endif

ifeq ($(CORE), A15)
ifeq ($(DOUBLE), 0)
	CFLAGS += -UDOUBLE
	RM=12
	RN=4
endif
endif

CFLAGS += -D$(CORE)
OBJS=conv.o data_initialization.o auxiliary.o 
ifeq ($(GEMM), 1)
	CFLAGS += -DGEMM
	CFLAGS += -DCOPY_R=gemm_n_$(RM)_alpha_copy -DCOPY_L=gemm_t_$(RN)_copy -DBLOCKN=$(blockn) -DBLOCKM=$(blockm) -DBLOCKK=$(blockk) #-DPRE_A_SIZE=$(preA) -DPRE_B_SIZE=$(preB)
	OBJS += $(KERNELCODEdir)/gemmkernel.o\
			gemm.o \
			gemm_n_alpha_copy.o gemm_t_copy.o 
ASMNAME=gemmkernel
endif

conv: $(OBJS)
	$(CC) $(CFLAGS) -I$(INCdirs) $^ -o $@ $(LDdirs) $(LDFLAGS)

conv.o: conv.c
	$(CC) $(CFLAGS) -I$(INCdirs) -c $^ -o $@

data_initialization.o : data_initialization.c
	$(CC) $(CFLAGS) -I$(INCdirs) -c $^ -o $@

auxiliary.o : auxiliary.c
	$(CC) $(CFLAGS) -I$(INCdirs) -c $^ -o $@


gemm.o: $(DRIVERdir)/gemm.c
	$(CC) $(CFLAGS) -I$(INCdirs) -c $^ -o $@ $(LDFLAGS)
#gemmkernel.o: $(KERNELCODEdir)/gemmkernel.$(SUFFIX)
#	$(CC) $(CFLAGS) -DASMNAME=$(ASMNAME) -I$(INCdirs) -c $^ -o $@

gemm_n_alpha_copy.o: $(COPYCODEdir)/gemm_n_$(RM)_alpha_copy.c
	$(CC) $(CFLAGS) -I$(INCdirs) -c $^ -o $@

gemm_t_copy.o: $(COPYCODEdir)/gemm_t_$(RN)_copy.c
	$(CC) $(CFLAGS) -I$(INCdirs) -c $^ -o $@

clean:
	rm  conv *.o -rf
