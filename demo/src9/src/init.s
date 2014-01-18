	.arch armv5te
	.thumb

	.global Init
	.text
	.thumb_func
	.type Init, %function
Init:
	@; POWERCNT = POWER_ALL
	ldr r0, =0x04000304
	ldr r1, =0x20F
	strh r1, [r0]

	@; GFX_CLEAR_COLOR = black, opaque, id=63
	ldr r0, =0x04000350
	ldr r1, =0x3F1F0000
	str r1, [r0]

	@; GFX_CLEAR_DEPTH = 0x7FFF
	ldr r1, =0x7FFF
	strh r1, [r0, #4]

	@; DISPCNT = MODE 0, BG0, 3D
	ldr r0, =0x04000000
	ldr r1, =0x10000|(1<<8)|(1<<3)
	str r1, [r0]

	@; GFX_CONTROL = ANTIALIAS, BLEND
	ldr r0, =0x04000060
	ldr r1, =(1<<3)|(1<<4)
	strh r1, [r0]

	@; DISPCNT_SUB = MODE 5, BG3, SPR, SPR_2D_BMP_256
	ldr r0, =0x04001000
	ldr r1, =0x10005|(1<<11)|(1<<12)|(2<<4)
	str r1, [r0]

	@; BG3CNT_SUB = BMP16 256x256
	ldr r1, =0x4084
	strh r1, [r0, #0x0E]

	@; BG3PA_SUB = 256
	ldr r1, =256
	strh r1, [r0, #0x30]

	@; BG3PD_SUB = 256
	strh r1, [r0, #0x36]

	bx lr

	.align 2
	.pool
