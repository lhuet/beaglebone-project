/*
  DHT22 reader for Beaglebone
  
  Inspired by adafruit code : 
    https://github.com/adafruit/Adafruit-Raspberry-Pi-Python-Code/tree/master/Adafruit_DHT_Driver
  Library used for GPIO access : 
    https://github.com/majestik666/Beagle_GPIO
  
*/
#include "Beagle_GPIO.hh"
#include <time.h>
#include <stdlib.h>
#include <iostream>

#define MAXTIMINGS 100

timespec diff(timespec start, timespec end);

Beagle_GPIO	gpio;

int main()
{
	//std::cout << "==========================\n";
	//std::cout << "BeagleBone GPIO DHT22 Test\n";
	//std::cout << "==========================\n" ;

	int counter = 0;
	int laststate = 1;
	int j = 0;
	unsigned short pin = Beagle_GPIO::P8_3;
	int bits[250], state[250], data[100];
	struct timespec timestamp[250];
	int bitidx = 0;
	//clockid_t clk_id = CLOCK_PROCESS_CPUTIME_ID;
	clockid_t clk_id = CLOCK_REALTIME ;
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	//std::cout << "Configuring Pin P8_3 as Output\n";
	gpio.configurePin( pin, Beagle_GPIO::kOUTPUT );
	gpio.enablePinInterrupts( pin, false );

	// Initialize DHT22 sensor
	gpio.writePin( pin, 1 );
	usleep(500000);  // 500 ms
	gpio.writePin( pin, 0 );
	usleep(20000);

	gpio.configurePin( pin, Beagle_GPIO::kINPUT );
	gpio.enablePinInterrupts( pin, false );

	// wait for pin to drop?
	while (gpio.readPin(pin) == 1) {
		usleep(1);
	}

	// read data!
	for (int i=0; i< MAXTIMINGS; i++) {
		counter = 0;
		while ( gpio.readPin(pin) == laststate) {
			counter++;
			if (counter == 1000)
				break;
		}
		laststate = gpio.readPin(pin);
		if (counter == 1000) break;
		state[bitidx] = laststate;
		clock_gettime(clk_id, &timestamp[bitidx]);
		bits[bitidx++] = counter;
	}

	// analyse data and 
	j = 0;
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
	for (int i=0; i<bitidx; i++) {
		if ((i>3) && (i%2 == 0)) {
			// shove each bit into the storage bytes
			//std::cout << "bit " << j/8 << " - " << (diff(timestamp[i-1], timestamp[i]).tv_nsec/1000) << " \n";
			data[j/8] <<= 1;
			//if ((bits[i])>200)
			if ((diff(timestamp[i-1], timestamp[i]).tv_nsec/1000) > 40) 
				data[j/8] |= 1;
			j++;
		}
	}

	// Debug infos
//	for (int i=3; i<bitidx; i+=2) {
//		std::cout << "bit" << i-3 << ": " << state[i] << " - " << bits[i] << " - " << (diff(timestamp[i-1], timestamp[i]).tv_nsec/1000) << "\n";
//		std::cout << "bit" << i-2 << ": " << state[i+1] << " - " << bits[i+1] << " - " << (diff(timestamp[i], timestamp[i+1]).tv_nsec/1000) << "(" << (bits[i+1] > 200) << ")\n";
//	}
//	for (int i=4; i<bitidx; i+=2) {
//		std::cout << "bit" << i-4 << ": " << " - " << (diff(timestamp[i-1], timestamp[i]).tv_nsec/1000) << "\n";
//		std::cout << "bit" << i-2 << ": " << state[i+1] << " - " << bits[i+1] << " - " << (diff(timestamp[i], timestamp[i+1]).tv_nsec/1000) << "(" << (bits[i+1] > 200) << ")\n";
//	}

	// Compute the checksum
	int checksum = (data[0] + data [1] + data [2] + data [3]) & 0xFF;
	if (checksum != data[4]) {
		std::cout << "Checksum KO !\n";
		exit(1);
	}

	// Compute the Temp & Hum from data (for RHT3 / DHT22)
	float f, h;
	h = data[0] * 256 + data[1];
	h /= 10;

	f = (data[2] & 0x7F)* 256 + data[3];
	f /= 10.0;
	if (data[2] & 0x80)  f *= -1;

	// Print to console
	std::cout << "Temp = " << f << "°C, Hum = " << h << "%\n";

}


/* Compute diff for timespec (from clock_gettime)*/
timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
