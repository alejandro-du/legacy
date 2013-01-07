// Bloque.java



import java.awt.*;
import java.applet.*;



public abstract class Bloque
{
	protected Image img;
	protected boolean activo;
	protected Applet padre;
	
	
	Bloque() {
		activo = true;
	}
	
	public abstract void dibujar(Graphics g, int x, int y);
	
	public abstract int golpear(Graphics g, int x, int y);
	
	public boolean activo() {
		return activo;
	}
}
