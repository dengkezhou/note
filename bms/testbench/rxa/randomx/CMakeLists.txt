cmake_minimum_required(VERSION 2.8.7)

project(CrandomX)

set(randomx_sources	
lib/blake2/blake2b.c
lib/argon2/argon2_ref.c
lib/argon2/argon2_ssse3.c
lib/argon2/argon2_avx2.c
lib/argon2/argon2_core.c
lib/utils/uint256.c
lib/utils/stats-utils.c
lib/utils/cvector.c
src/cpu.c
src/randomx.c
src/blake2_generator.c
src/instruction.c
src/reciprocal.c
src/instructions_portable.c
src/soft_aes.c
src/aes_hash.c
src/allocator.c
src/virtual_memory.c
src/bytecode_machine.c
src/virtual_machine.c
src/vm_interpreted.c
src/vm_interpreted_light.c
src/superscalar.c
src/vm_compiled.c
src/vm_compiled_light.c
src/dataset.c
src/jrx/jrx_core.c
src/jrx/jrx_none.c
src/jrx/jrx_dev.c
src/jrx/jrx_base.c
src/jrx/jrx_rxa.c
src/jrx/isa_a64.c
src/jrx/isa_rv64g.c
src/jrx/isa_rxa.c
)

set(use_static -static)

#set(ARCH_ID "rv64")
#set(CMAKE_C_COMPILER  riscv64-buildroot-linux-gnu-gcc)
#set(CMAKE_CXX_COMPILER  riscv64-buildroot-linux-gnu-g++)

#set(ARCH_ID "arm64")
#set(CMAKE_C_COMPILER  aarch64-none-linux-gnu-gcc)
#set(CMAKE_CXX_COMPILER  aarch64-none-linux-gnu-g++)

if(NOT ARCH_ID)
  # allow cross compiling
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "")
    set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})
  endif()
  string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH_ID)
endif()

if(NOT ARM_ID)
  set(ARM_ID "${ARCH_ID}")
endif()

if(NOT ARCH)
  set(ARCH "default")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Setting default build type: ${CMAKE_BUILD_TYPE}")
endif()

include(CheckCCompilerFlag)

function(add_flag flag)
  string(REPLACE "-" "_" supported_c ${flag}_c)
  check_c_compiler_flag(${flag} ${supported_c})
  if(${${supported_c}})
    message(STATUS "Setting C flag ${flag}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}" PARENT_SCOPE)
  endif()
endfunction()

add_flag("-g")
add_flag("-pthread")

if(ARCH_ID STREQUAL "x86_64" OR ARCH_ID STREQUAL "x86-64" OR ARCH_ID STREQUAL "amd64")
	list(APPEND randomx_sources
		src/jrx/jrx_x86.c)
	list(APPEND randomx_sources src/jrx/jrx_x86_static.S)

	set_property(SOURCE src/jrx/jrx_x86_static.S PROPERTY LANGUAGE C)
	set_property(SOURCE src/jrx/jrx_x86_static.S PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.asm)

	message(STATUS "x86_64")
	if(ARCH STREQUAL "native")
  	add_flag("-march=native")
	else()
  	# default build has hardware AES enabled (software AES can be selected at runtime)
  	add_flag("-maes")
  	check_c_compiler_flag(-mssse3 HAVE_SSSE3)
  	if(HAVE_SSSE3)
    	set_source_files_properties(src/argon2_ssse3.c COMPILE_FLAGS -mssse3)
  	endif()
  	check_c_compiler_flag(-mavx2 HAVE_AVX2)
  	if(HAVE_AVX2)
    	set_source_files_properties(src/argon2_avx2.c COMPILE_FLAGS -mavx2)
  endif()
endif()

endif()

if(ARCH_ID STREQUAL "riscv64" OR ARCH_ID STREQUAL "rv64")
	add_flag("-march=rv64imafdcv -mabi=lp64 -mcmodel=medlow")
endif()

if(ARM_ID STREQUAL "aarch64" OR ARM_ID STREQUAL "arm64" OR ARM_ID STREQUAL "armv8-a")
  # not sure if this check is needed
  include(CheckIncludeFile)
  check_include_file(asm/hwcap.h HAVE_HWCAP)
  if(HAVE_HWCAP)
    add_definitions(-DHAVE_HWCAP)
  endif()

  if(ARCH STREQUAL "native")
    add_flag("-march=native")
  else()
    # default build has hardware AES enabled (software AES can be selected at runtime)
    add_flag("-march=armv8-a+crypto")
  endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
add_library(randomx ${randomx_sources})
set_property(TARGET randomx PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET randomx PROPERTY PUBLIC_HEADER include/randomx.h)

include(GNUInstallDirs)
install(TARGETS randomx
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(rxbench
		testbench/rxbench.c)
target_link_libraries(rxbench
 PRIVATE randomx
 PRIVATE ${use_static}
 rxa-driver
 m)

set_property(TARGET rxbench PROPERTY POSITION_INDEPENDENT_CODE ON)

