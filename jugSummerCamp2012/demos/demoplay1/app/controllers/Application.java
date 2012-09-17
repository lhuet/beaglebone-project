package controllers;

import play.*;
import play.mvc.*;

import java.util.*;
import java.io.*;

import models.*;

public class Application extends Controller {

	public static void index() {
		render();
	}

	public static void getTemp() {

		float temperature = 0;
		try {
			FileReader f = new FileReader("/sys/bus/w1/devices/28-000003c1b6e7/w1_slave");
			BufferedReader fichier = new BufferedReader(f);
			// Lecture de la première ligne
			String ligne = fichier.readLine();
			// Lecture de la seconde ligne
			ligne = fichier.readLine();
			// Extraction de la température
			String tempChaine = ligne.split("t=")[1];
			temperature = Float.valueOf(tempChaine).floatValue()/1000;
		} catch (Exception e) {
			e.printStackTrace();
		}
		renderJSON(temperature);
	}

}
