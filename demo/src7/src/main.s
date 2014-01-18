	.cpu arm7tdmi

	.section .init
	.global _start
	.align 2
	.arm

_start:
#define SAFE 1
#if SAFE
	@; Switch to system mode
	mov	r0, #0x1F
	msr	cpsr, r0
#endif

	@; Switch to thumb
	ldr	r3, =player
	bx	r3

	.align
	.pool

	.align 2
	.thumb
	.thumb_func
player:
@; ============================ init system =============================
	@; power sound on
	mov	r1, #1
	ldr	r0, reg_powercnt
	strh	r1, [r0]

	@; init sound, full volume
	ldr	r1, soundsetup
	ldr	r0, reg_soundcnt
	strh	r1, [r0]

	@; set irq handler
	ldr	r0, reg_irqhandler
	ldr	r2, irq_handler
	str	r2, [r0]

	@; set IE = VBLANK
@;	ldr	r0, reg_interrupts
@;	str	r1, [r0, #8]
	ldr r0, reg_ie
	str r1, [r0]

	@; set DISPSTAT = VBLANK IRQ
	ldr	r3, reg_dispstat
	mov	r2, #8
	strh	r2, [r3]

	@; set IF = ALL
@;	mov	r3, #1
@;	neg	r3, r3
@;	str	r3, [r0, #12]

	@; set IME = ON
@;	ldr	r3, reg_interrupts
@;	strh	r3, [r3]

@; ================================ play ================================
	ldr	r7, tune

player_loop:
	@; wait for vblank
	swi	0x05

	@;ldr	r5, tune
	mov	r5, r7
	mov	r6, #8

sch_loop:
	@; compute note address (r0)
	ldr	r3, [r5, #16]
	lsl	r3, #2
	add	r0, r7, r3

	@; check end of channel
@;	ldrh	r3, [r0, #2]
@;	mov	r2, #3
@;	bic	r3, r2
@;	beq	pass_note_update

	@; check if it's time to play this note
	ldr	r3, [r0]
	ldr	r2, [r5]
	lsl	r3, #19
	lsr	r3, #19
	cmp	r3, r2
	bne	pass_note_update

	@; reset timer
	mov	r3, #0
	str	r3, [r5]

	@; increment note offset
	ldr	r3, [r5, #16]
	add	r3, #1
	str	r3, [r5, #16]

	@; update volume
	ldr	r3, [r0]
	lsl	r3, #14
	lsr	r3, #27
	lsl	r3, #4
	str	r3, [r5, #4]

	@; compute sound frequency register for current channel
	ldr	r2, reg_sch0cnt
	lsl	r4, r6, #4
	add	r4, r2

	@; read frequency
	ldr	r3, [r0]
	lsr	r1, r3, #18

	@; freq*8 if wave duty channel
	cmp	r6, #13
	bgt	noise
	lsl	r1, r1, #3
noise:

	@; convert frequency to timer value (-0x1000000/freq)
	ldr	r0, timer_ref
	swi 0x09 @; swi divide !

	@; write frequency
	strh	r0, [r4, #8]

pass_note_update:
	
	@; compute volume's linear envelope
	ldr	r2, [r5, #4] 	@; read volume
	ldr	r3, [r5, #12] 	@; read decay
	sub	r2, r3 		@; compute envelope
	bgt	noclamp		@; clamp
	mov	r2, #0
noclamp:
	str	r2, [r5, #4]

	@; compute sound control register for current channel
	ldr	r2, reg_sch0cnt
	lsl	r0, r6, #4
	add	r0, r2

	@; write sound register
	ldr	r3, [r5, #4] 	@; read volume
	asr	r3, #2
	ldr	r2, [r5, #8]	@; read duty
	orr	r3, r2
	ldr	r2, sregdef	@; read default params (pan=64, psg, enable)
	orr	r3, r2
	str	r3, [r0]

	@; increment timer
	ldr	r3, [r5]
	add	r3, #1
	str	r3, [r5]

	@; increment channel counter
	add	r6, r6, #1

	cmp	r6, #16
	beq	player_loop

	add	r5, r5, #20
	b	sch_loop

	.align	2
reg_dispstat: 	.word 0x4000004
@;reg_interrupts:	.word 0x4000208
reg_ie:			.word 0x4000210
reg_powercnt: 	.word 0x4000304
reg_sch0cnt: 	.word 0x4000400
reg_soundcnt: 	.word 0x4000500
reg_irqhandler:	.word __irq_vector
irq_handler: 	.word on_irq
tune: 		.word tune_data
sregdef:	.word 0xE0400000
timer_ref:	.word -0x1000000
soundsetup:	.word (1<<15)|127

@; ========================= interrupt handler =========================
	.arm
	.align 2
	.text
on_irq:
	@ VBLANK_INTR_WAIT_FLAGS |= IRQ_VBLANK
	ldr 	r11, irqflags
	ldr 	r12, [r11]
	orr 	r12, r12, #1 @vbl
	str 	r12, [r11]
	@ REG_IF = REG_IF
	mov 	r11, #0x4000000
	ldr 	r12, [r11, #0x214]
	str 	r12, [r11, #0x214]
	@ Return
	bx 	lr

	.align 2
irqflags:
	.word __irq_flags

	.align 2
tune_data:
	.incbin "tune"
