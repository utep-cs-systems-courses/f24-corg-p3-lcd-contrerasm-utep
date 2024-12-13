# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

COMMON_OBJECTS = led.o
ASM_SOURCES = led.s

all:main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

%.o: %.s
	${AS} $< -o $@
load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
