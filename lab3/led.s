	.arch msp430g2553
	.p2align 1,0
	.text

	.global led_init
	.extern P1DIR
	.extern P1OUT

led_init:
		mov #64,R12	;BIT6
		bis r12,&P1DIR 	;p1.6 as output
		cmp #0,R13	;r13=cur state
		jeq led_off	;if 0 jump to led_off
	
led_on:		bis r13,&P1OUT	;led on
		ret		;return
	
led_off:	bis r13, &P1OUT	;led off
		ret		;return
