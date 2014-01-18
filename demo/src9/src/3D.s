	.arch armv5te
	.thumb
	.text
	.align 2
	.global call_list
	.thumb_func
	.type call_list, %function
call_list:
	ldr	r3, dmasrc
	str	r0, [r3]
	ldr	r2, fifo
	str	r2, [r3, #4]
	ldr	r2, param
	orr	r1, r2
	str	r1, [r3, #8]
busy:
	ldr	r2, [r3, #8]
	cmp	r2, #0
	blt	busy
	bx lr
.L6:
	.align	2
dmasrc:	.word 0x40000B0
fifo:	.word 0x4000400
param:	.word (1<<31)|(7<<27)|(1<<22)|(1<<26) @; enable, startfifo, destfix, 32bit
