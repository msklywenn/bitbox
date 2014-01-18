	.arch armv5te
	.align 2
	.text
	.thumb
	.global seeya
	.thumb_func
	.type seeya, %function
seeya:
	@; dispcnt = mode 0, bg0 active
	ldr r0, =0x04000000
	ldr r1, =0x10000 | (1<<8)
	str r1, [r0]

	@; bg0cnt = tilebase=1, mapbase=0
	ldr r1, =(1<<2)
	str r1, [r0, #8]

	@; scroll text horizontally
	ldr r1, =256-108
	strh r1, [r0, #0x10]

	@; scroll text vertically
	ldr r1, =256-92
	strh r1, [r0, #0x12]

	@; enable vram A in bg mode @0x06000000
	ldr r0, =0x04000240
	ldr r1, =(1<<7)|1
	str r1, [r0]

	@; bg palette color 1 = white
	ldr r0, =0x05000002
	ldr r1, =(1<<15)-1
	strh r1, [r0]

	@; fill map
	ldr r0, =0x06000000
	mov r1, #0
textloop:
	strh r1, [r0]
	add r0, #2
	add r1, #1
	cmp r1, #(msgend-msg)/8
	bne textloop

	@; unpack tiles directly to vram
	ldr r0, =msg
	ldr r1, =0x06004000
	ldr r2, =unpackinfo
	swi 0x10

	@; infinite wait (interrupts aren't enabled ;)
	swi 0x05

	.align 2
	.pool

	.align 2
msg:
	.incbin "msg"
msgend:

	.align 2
unpackinfo:
	.hword msgend-msg
	.byte 1
	.byte 4
	.word 0
