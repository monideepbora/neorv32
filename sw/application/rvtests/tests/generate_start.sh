#!/bin/bash

# script to generate asm code dynamically for each test

INST=$1

cat > sw/application/rvtests/tests/start.S <<EOF

// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

	.section .text
	.global start

reset_vec:
	j start

; /* Main program
;  **********************************/

start:
	/* zero-initialize all registers */
	addi x1, zero, 0
	addi x2, zero, 0
	addi x3, zero, 0
	addi x4, zero, 0
	addi x5, zero, 0
	addi x6, zero, 0
	addi x7, zero, 0
	addi x8, zero, 0
	addi x9, zero, 0
	addi x10, zero, 0
	addi x11, zero, 0
	addi x12, zero, 0
	addi x13, zero, 0
	addi x14, zero, 0
	addi x15, zero, 0

#ifndef ABI_ILP32E
	addi x16, zero, 0
	addi x17, zero, 0
	addi x18, zero, 0
	addi x19, zero, 0
	addi x20, zero, 0
	addi x21, zero, 0
	addi x22, zero, 0
	addi x23, zero, 0
	addi x24, zero, 0
	addi x25, zero, 0
	addi x26, zero, 0
	addi x27, zero, 0
	addi x28, zero, 0
	addi x29, zero, 0
	addi x30, zero, 0
	addi x31, zero, 0
#endif

/* running tests from riscv-tests */

#define TEST(n) \\
	.global n; \\
	addi x1, zero, 1000; \\
	jal zero,n; \\
	.global n ## _ret; \\
	n ## _ret:

	TEST(${INST})

	/* set stack pointer 
	lui sp,(39312)>>12 */

	 /*set gp and tp 
	lui gp, %hi(0xdeadbeef)
	addi gp, gp, %lo(0xdeadbeef)
	addi tp, gp, 0 */

	call success

EOF