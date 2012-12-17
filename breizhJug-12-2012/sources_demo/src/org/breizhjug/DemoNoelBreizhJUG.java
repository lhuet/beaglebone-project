package org.breizhjug;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.util.Collection;

import javazoom.jl.player.AudioDevice;
import javazoom.jl.player.FactoryRegistry;
import javazoom.jl.player.advanced.AdvancedPlayer;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPin;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;
import com.pi4j.io.gpio.event.GpioPinDigitalStateChangeEvent;
import com.pi4j.io.gpio.event.GpioPinListenerDigital;

public class DemoNoelBreizhJUG {

	public static Thread tplayer;
	
	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws InterruptedException {

		initPlayer();
		
		// gpio controller
		GpioController gpio = GpioFactory.getInstance();

		// provision gpio pin #02 as an input pin with its internal pull down resistor enabled
		GpioPinDigitalInput myButton = gpio.provisionDigitalInputPin(RaspiPin.GPIO_02, "interrupteur", PinPullResistance.PULL_DOWN);
		GpioPinDigitalOutput pin = gpio.provisionDigitalOutputPin(RaspiPin.GPIO_01, "lumiere", PinState.LOW);

		// create and register gpio pin listener
		myButton.addListener(new GpioLightListener());
		myButton.addListener(new GpioPlayerListener());

		// keep program running until user aborts (CTRL-C)
		for (;;) {
			Thread.sleep(500);
		}
	}
	
	private static void initPlayer() {
		tplayer = new Thread(){
			public void run() {
				try {
				AudioDevice audio = FactoryRegistry.systemRegistry().createAudioDevice();
				AdvancedPlayer player = new AdvancedPlayer(new BufferedInputStream(new FileInputStream(new File("rossi_tino_petit_papa_noel.mp3")), 12000), audio);
				//player = new AdvancedPlayer(new FileInputStream(new File("rossi_tino_petit_papa_noel.mp3")), audio);
				player.play();
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			};
		};
	}
}


class GpioLightListener implements GpioPinListenerDigital {
	@Override
	public void handleGpioPinDigitalStateChangeEvent(GpioPinDigitalStateChangeEvent event) {
		// display pin state on console
		System.out.println(" --> GPIO PIN STATE CHANGE: " + event.getPin() + " = " + event.getState());

		GpioController gpio = GpioFactory.getInstance();
		Collection<GpioPin> pins = gpio.getProvisionedPins();
		GpioPinDigitalOutput lumiere = null;
		for (GpioPin gpioPin : pins) {
			//System.out.println(gpioPin.getName());
			if (gpioPin.getName().equals("lumiere")) {
				lumiere = (GpioPinDigitalOutput)gpioPin;
			}
		}
				
		if (event.getState().isHigh()) {
			// On allume la lumière
			System.out.println("lumière on");
			lumiere.high();

		}
		
		if (event.getState().isLow()) {
			// On éteind la lumière
			System.out.println("lumière off");
			lumiere.low();
		}

	}
}


class GpioPlayerListener implements GpioPinListenerDigital {
	@Override
	public void handleGpioPinDigitalStateChangeEvent(
			GpioPinDigitalStateChangeEvent event) {
		// display pin state on console
		System.out.println(" --> GPIO PIN STATE CHANGE: " + event.getPin() + " = " + event.getState());
		
		if (event.getState().isHigh()) {
			if (!DemoNoelBreizhJUG.tplayer.isAlive()) {
				System.out.println("Lancement du player");
				// Lancement du thread s'il ne tourne pas
				DemoNoelBreizhJUG.tplayer.start();
			}
			else {
				// Relance du thread s'il tourne
				DemoNoelBreizhJUG.tplayer.resume();
				System.out.println("Player relancé");
			}
		}
		
		if (event.getState().isLow()) {
			// Pause du player
			DemoNoelBreizhJUG.tplayer.suspend();
			System.out.println("Player en pause ...");
		}

	}
}
