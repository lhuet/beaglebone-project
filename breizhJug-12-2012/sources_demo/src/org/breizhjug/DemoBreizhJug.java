package org.breizhjug;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;

public class DemoBreizhJug {

	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws InterruptedException {
        System.out.println("<--Pi4J--> GPIO Control Example ... started.");
        
        // gpio controller
        GpioController gpio = GpioFactory.getInstance();
        
        // Configuration du pin #01 comme sortie et initialisation à l'état "high"
        GpioPinDigitalOutput pin = gpio.provisionDigitalOutputPin(RaspiPin.GPIO_01, "lumiere", PinState.HIGH);
        System.out.println("--> La lumière doit être allumée !");
        
        Thread.sleep(5000);
        
        pin.low();
        System.out.println("--> Extinction des feux ...");

        Thread.sleep(5000);

        pin.toggle();
        System.out.println("--> La lumière doit être allumée !");

        Thread.sleep(5000);

        pin.toggle();
        System.out.println("--> Extinction des feux ...");
        
        Thread.sleep(5000);

        System.out.println("--> Clignotement de 1 seconde");
        pin.pulse(1000);
    }


}
