// BloqueFijo.java



import java.awt.*;
import java.applet.*;



public class BloqueFijo extends Bloque
{
	
	BloqueFijo(String str, Applet a) {
		
		super();
		padre = a;
		img = padre.getImage(padre.getDocumentBase(), str);
	}
	
	
	public void dibujar(Graphics g, int x, int y) {
		
		g.drawImage(img, x, y, padre);
	}
	
	
	public int golpear(Graphics g, int x, int y) {
		
		g.drawImage(img, x, y, padre);
		return 0; // cero puntos
	}

}
