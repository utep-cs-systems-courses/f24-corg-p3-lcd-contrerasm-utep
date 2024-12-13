/*	.arch msp430g2553
	.p2align 1,0
	.text

	.global led_init
	.extern P1DIR
	.extern P1OUT

led_init:
		mov.w #64,R14	;BIT6
		bis.w r14,&P1DIR 	;p1.6 as output
		cmp #0,R15	;
		jeq led_off	;if 0 jump to led_off
	
led_on:		bis.w r14,&P1OUT	;led on
		ret.w		;return
	
led_off:	bis.w r14, &P1OUT	;led off
		ret		;return
*/
