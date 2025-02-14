ARCHIVE := testbench_rxa.a

CUSTOM_CFLAGS += -I$(CURDIR)/randomx/include -I$(CURDIR)/randomx/lib/ -I$(SRCTREE)/include 
CUSTOM_AFLAGS += -I$(CURDIR)/randomx/include -I$(CURDIR)/randomx/lib/ -I$(SRCTREE)/include 

srcs-y += \
	rxa-main.c \
	isa-test.c \
	spi-drv.c \
	spi-test.c \

srcs-$(CONFIG_RANDOMX_MINING) += \
  randomx/lib/blake2/blake2b.c \
  randomx/lib/argon2/argon2_ref.c \
  randomx/lib/argon2/argon2_ssse3.c \
  randomx/lib/argon2/argon2_avx2.c \
  randomx/lib/argon2/argon2_core.c \
  randomx/lib/utils/uint256.c \
  randomx/lib/utils/stats-utils.c \
  randomx/lib/utils/cvector.c \
  randomx/src/cpu.c \
  randomx/src/randomx.c \
  randomx/src/blake2_generator.c \
  randomx/src/instruction.c \
  randomx/src/reciprocal.c \
  randomx/src/instructions_portable.c \
  randomx/src/soft_aes.c \
  randomx/src/aes_hash.c \
  randomx/src/allocator.c \
	randomx/src/program.c  \
  randomx/src/virtual_memory.c \
  randomx/src/bytecode_machine.c \
  randomx/src/virtual_machine.c \
  randomx/src/vm_interpreted.c \
  randomx/src/vm_interpreted_light.c \
  randomx/src/superscalar.c \
  randomx/src/vm_compiled.c \
  randomx/src/vm_compiled_light.c \
  randomx/src/dataset.c \
	randomx/src/intrin_portable.c \
  randomx/src/jrx/jrx_core.c \
  randomx/src/jrx/jrx_none.c \
  randomx/src/jrx/jrx_dev.c \
  randomx/src/jrx/jrx_base.c \
  randomx/src/jrx/jrx_rxa.c \
  randomx/src/jrx/isa_a64.c \
  randomx/src/jrx/isa_rv64g.c \
  randomx/src/jrx/isa_rxa.c \
	randomx/testbench/rxbench.c \
	randomx/randomx-api.c


