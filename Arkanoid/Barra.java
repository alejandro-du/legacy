// Barra.java



import java.applet.*;
import java.awt.*;



public class Barra
{
	private int x, y, // posici�n actual
		        xt; // posicion anterior
	private int velocidad;
	private int ancho, alto; // tama�o
	private Image img; // imagen con el dibujo de la barra
	private Applet padre; // applet en el que se debe dibujar
	
	
	Barra(String str, Applet a) {
		
		padre = a;
		img = padre.getImage(padre.getDocumentBase(), str); // cargar la imagen
		ancho = img.getWidth(padre); // DEBUG
		alto = img.getHeight(padre);
		ancho = 75;
		alto = 15;
		x = (596 / 2) - (ancho / 2); // ponerla en la mitad
		y = 327 - alto - 5;
		xt = x;
		velocidad = 8;
	}
	
	
	public void moverIzquierda() {
		
		xt = x; // guardar la posici�n anterior
		x -= velocidad; // calcular la nueva posici�n
		
		if(x < 1) // verificar l�mite
			x = 1;
	}
	
	
	public void moverDerecha() {
	
		xt = x; // guardar la posici�n anterior
		x += velocidad; // calcular la nueva posici�n
		
		if(x > 595 - ancho) // verificar l�mite
			x = 595 - ancho;
	}
	
	
	public void dibujar(Graphics g) {
		
		g.setColor(Color.black);
		g.fillRect(xt, y, ancho, alto); // borrar la anterior
		g.drawImage(img, x, y, padre); // dibujar en la nueva posici�n
	}
	
	
	public int obtX() {
		return x;
	}
	
	
	public int obtY() {
		return y;
	}

	
	public int obtVelocidad() {
		return velocidad;
	}

	
	public int obtAncho() {
		return ancho;
	}
}
