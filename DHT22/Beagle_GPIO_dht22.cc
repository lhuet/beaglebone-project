
#include "Beagle_GPIO.hh"
#include <time.h>
#include <iostream>

#define MAXTIMINGS 100

Beagle_GPIO	gpio;

int main()
{
	std::cout << "==========================";
	std::cout << "BeagleBone GPIO DHT22 Test";
	std::cout << "==========================" ;

	int counter = 0;
	int laststate = 1;
	int j = 0;
	unsigned short pin = Beagle_GPIO::P8_3;
	int bits[250], state[250], data[100];
	struct timespec timestamp[250];
	int bitidx = 0;
	struct timespec start;
	//clockid_t clk_id = CLOCK_PROCESS_CPUTIME_ID;
	clockid_t clk_id = CLOCK_REALTIME ;
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	std::cout << "Configuring Pin P8_3 as Output";
	gpio.configurePin( pin, Beagle_GPIO::kOUTPUT );
	gpio.enablePinInterrupts( pin, false );

	// Initialize DHT22 sensor
	gpio.writePin( pin, 1 );
	usleep(500000);  // 500 ms
	gpio.writePin( pin, 0 );
	usleep(20000);
	clock_gettime(clk_id, &start);

	gpio.configurePin( pin, Beagle_GPIO::kINPUT );
	gpio.enablePinInterrupts( pin, false );

	// wait for pin to drop?
	while (gpio.readPin(pin) == 1) {
		usleep(1);
	}
	//clock_gettime(clk_id, &start);

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

		if ((i>3) && (i%2 == 0)) {
			// shove each bit into the storage bytes
			// TODO : Use timestamp info instead of counter
			data[j/8] <<= 1;
			if (counter > 200)
				data[j/8] |= 1;
			j++;
		}
	}

	// std::cout << "Timestamp début : " << start.tv_nsec;
	std::cout << "bit -3 : " << state[0] << " - " << bits[0] << " - " << (timestamp[0].tv_nsec - start.tv_nsec) << "\n";
	std::cout << "bit -2 : " << state[1] << " - " << bits[1] << " - " << (timestamp[1].tv_nsec - timestamp[0].tv_nsec) << "\n";
	std::cout << "bit -1 : " << state[2] << " - " << bits[2] << " - " << (timestamp[2].tv_nsec - timestamp[1].tv_nsec) << "\n";

	// Debug infos
	for (int i=3; i<bitidx; i+=2) {
		std::cout << "bit" << i-3 << ": " << state[i] << " - " << bits[i] << " - " << (timestamp[i].tv_nsec - timestamp[i-1].tv_nsec) << "\n";
		std::cout << "bit" << i-2 << ": " << state[i+1] << " - " << bits[i+1] << " - " << (timestamp[i+1].tv_nsec - timestamp[i].tv_nsec) << "(" << (bits[i+1] > 200) << ")\n";
	}

	//printf("Data (%d): 0x%x 0x%x 0x%x 0x%x 0x%x\n", j, data[0], data[1], data[2], data[3], data[4]);
	//std::cout << "Data (" << data[0] << "): 0x" << data[1] << " 0x" << data[2] << " 0x" << data[3] << " 0x" << data[4] << "n";

	float f, h;
	h = data[0] * 256 + data[1];
	h /= 10;

	f = (data[2] & 0x7F)* 256 + data[3];
	f /= 10.0;
	if (data[2] & 0x80)  f *= -1;

	std::cout << "Temp = " << f << "°C, Hum = " << h << "%\n";

}
