COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc

AS              = msp430-elf-as
all: main.elf

main.elf: ${COMMON_OBJECTS} main.o led.o switches.o stateMachines.o buzzer.o wd_interrupt_handler.o p2_interrupt_vector.o libTimer.a


	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: main.elf

	msp430loader.sh main.elf

clean:

	rm -f *.o *.elf *~
