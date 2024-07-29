# run all 3 programs simultaneously
all: prog1 prog2 prog3 run clean

# compile program 1
prog1: pi_serial.c
	gcc -std=c99 -g -Wall -o pi_serial pi_serial.c -lm -lpthread

# compile program 2
prog2: pi_mutex.c
	gcc -std=c99 -g -Wall -o pi_mutex pi_mutex.c -lm -lpthread

# compile program 3
prog3: pi_semaphore.c
	gcc -std=c99 -g -Wall -o pi_semaphore pi_semaphore.c -lm -lpthread

# alert user that all 3 programs are running
run:
	@echo "**1.** RUNNING pi_serial..."
	@./pi_serial 9
	@echo "**2.** RUNNING pi_mutex..."
	@./pi_mutex 16
	@echo "**3.** RUNNNING pi_semaphore..."
	@./pi_semaphore 16

# remove makefiles
clean:
	rm -f pi_serial pi_mutex pi_semaphore
