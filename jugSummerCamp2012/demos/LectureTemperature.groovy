#!/usr/bin/env groovy

def w1SensorFile = "/sys/bus/w1/devices/28-000003c1b6e7/w1_slave"

for (int i = 0; i < 10; i++) {

	def w1Sensor = new File(w1SensorFile).readLines()[1]
				             .split("t=")[1]

	def sensorValue = (w1Sensor as int)/1000

	println("\nAu JugSummerCamp, il fait super chaud : " + sensorValue + " degC\n")
}

