
######################################
######################################

CXX=g++

CFLAGS=-Wall -c -O3

LDFLAGS=-Wall -O3

TARGETS = Beagle_GPIO.o	\
	  Beagle_GPIO_dht22

all: $(TARGETS)

Beagle_GPIO.o: Beagle_GPIO.cc Beagle_GPIO.hh
	@echo Compiling $< to $@
	@$(CXX) $(CFLAGS) Beagle_GPIO.cc

Beagle_GPIO_dht22: Beagle_GPIO_dht22.cc Beagle_GPIO.o
	@echo Compiling $< to $@
	@$(CXX) $(LDLAGS) Beagle_GPIO_dht22.cc Beagle_GPIO.o -lrt -o Beagle_GPIO_dht22

clean:
	@rm -rf *~ *.o $(TARGETS) 


######################################
######################################

