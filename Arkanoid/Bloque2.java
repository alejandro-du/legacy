// Bloque2.java



import java.awt.*;
import java.applet.*;



public class Bloque2 extends Bloque
{
	
	Bloque2(String str, Applet a) {
		
		super();
		padre = a;
		img = padre.getImage(padre.getDocumentBase(), str);
	}
	
	
	public void dibujar(Graphics g, int x, int y) {
		
		g.drawImage(img, x, y, padre);
	}
	
	
	public int golpear(Graphics g, int x, int y) {
		
		g.setColor(Color.black);
		g.fillRect(x, y, 33, 19);
		
		activo = false;
		
		return 500; // 500 puntos
	}

}
