// Bola.java



import java.applet.*;
import java.awt.*;



public class Bola
{
	private int x, y; // posición
	private int velx, vely; // vector de movimiento
	private int ancho, alto; // tamaño
	private Image img; // imagen con el dibujo
	private Applet padre; // applet en el que se debe dibujar
	
	
	Bola(String str, Applet a) {

		padre = a;
		img = padre.getImage(padre.getDocumentBase(), str); // cargar la imagen solicitada
		
		ancho = img.getWidth(padre); // DEBUG
		alto = img.getHeight(padre);
		
		ancho = alto = 15;
		
		// calcular la posición
		x = (596 / 2) - (ancho / 2); // posicionar en la mitad
		y = 327 - 15 - 5 - alto - 1;
		
		velx = 1 + (int)(Math.random() * 2);
		vely = -(1 + (int)(Math.random() * 2));
	}
	
	
	public int dibujar(Graphics g, Barra barra, boolean iz, boolean der, Bloque bloques[][]) {
		
		int xb, yb, // posiciones de la barra o de los bloques
			anchoBar, // tamaño de la barra
			dx, dx1, dx2, dy1, dy2, dy,
			x2, y2,
			puntos;
		
		boolean rx, ry;
		
		g.setColor(Color.black);
		g.fillRect(x, y, ancho, alto);
		
		puntos = 0;
		
		if(vely > 10)
			vely = 10;
		
		else if(vely < -10)
			vely = -10;

		x += velx;
		y += vely;
		
		if(x < 1) { // chocó con la vertical izquierda?
			x = 1;
			velx = -velx; // cambiar dirección
		}
		
		else if(x > 595 - ancho) { // chocó con la vertical derecha?
			x = 595 - ancho;
			velx = -velx;
		}

		if(y < 29) { // chocó con la horizontal superior?
			y = 29;
			vely = -vely;
		}
		
		if(y > 326) {
			y = 326;
			vely = -vely;
			puntos = -1;
		}
		
		// calcular punto opuesto
		x2 = x + ancho - 1;
		y2 = y + alto - 1;
		
		rx = false;
		ry = false;
		
		if(y < 163) { // controlar choque con bloques
			
			// calcular posicion dentro del array de bloques
			xb = (x - 1) / 33;
			yb = (y - 30) / 19;
			
			if(bloques[xb][yb].activo()) { // si está en la pantalla
				
				puntos += bloques[xb][yb].golpear(g, (xb * 33) + 1, (yb * 19) + 30);
				
				// rebotar
				dx1 = x - (xb * 33) + 1;
				dx2 = (xb * 33) + 1 + 33 - x;
				
				// guardar en dx la menor distancia
				if(dx1 < dx2)
					dx = dx1;
				else
					dx = dx2;
				
				dy1 = y - (yb * 19) + 30;
				dy2 = (yb * 19) + 30 + 19 - y;
				
				// guardar en dy la menor distancia
				if(dy1 < dy2)
					dy = dy1;
				else
					dy = dy2;
				
				if(dy > dx) { // rebotar horizontamente?
					
					velx = -velx;
					
					if(velx < 0)
						velx = -velx;
					
					rx = true;
				}
				
				else {
					
					vely = -vely;
					
					if(vely < 0)
						vely = -vely;
					
					ry = true;
				}
				
			}
			
			xb = (x2 - 1) / 33;
			yb = (y - 30) / 19;
			
			if(bloques[xb][yb].activo()) { // si está en la pantalla
				
				puntos += bloques[xb][yb].golpear(g, (xb * 33) + 1, (yb * 19) + 30);
				
				// rebotar
				dx1 = x2 - (xb * 33) + 1;
				dx2 = (xb * 33) + 1 + 33 - x2;
				
				// guardar en dx la menor distancia
				if(dx1 < dx2)
					dx = dx1;
				else
					dx = dx2;
				
				dy1 = y - (yb * 19) + 30;
				dy2 = (yb * 19) + 30 + 19 - y;
				
				// guardar en dy la menor distancia
				if(dy1 < dy2)
					dy = dy1;
				else
					dy = dy2;
				
				if(dy > dx && !rx) { // rebotar horizontamente?
					
					velx = -velx;
					
					if(velx > 0)
						velx = -velx;
					
					rx = true;
				}
				
				else if(!ry) {
					
					vely = -vely;
					
					if(vely < 0)
						vely = -vely;
					
					ry = true;
				}

			}
			
			if(y < 163 - alto) { // controlar puntos de arriba?
				xb = (x2 - 1) / 33;
				yb = (y2 - 30) / 19;
			
				if(bloques[xb][yb].activo()) { // si está en la pantalla
				
					puntos += bloques[xb][yb].golpear(g, (xb * 33) + 1, (yb * 19) + 30);
				
					// rebotar
					dx1 = x2 - (xb * 33) + 1;
					dx2 = (xb * 33) + 1 + 33 - x2;
					
					// guardar en dx la menor distancia
					if(dx1 < dx2)
						dx = dx1;
					else
						dx = dx2;
					
					dy1 = y2 - (yb * 19) + 30;
					dy2 = (yb * 19) + 30 + 19 - y2;
					
					// guardar en dy la menor distancia
					if(dy1 < dy2)
						dy = dy1;
					else
						dy = dy2;
					
					if(dy > dx && !rx) { // rebotar horizontamente?
						
						velx = -velx;
						
						if(velx > 0)
							velx = -velx;
						
						rx = true;
					}
					
					else if(!ry) {
						
						vely = -vely;
						
						if(vely > 0)
							vely = -vely;
						
						ry = true;
					}
				}
			
				xb = (x - 1) / 33;
				yb = (y2 - 30) / 19;
			
				if(bloques[xb][yb].activo()) { // si está en la pantalla
				
					puntos += bloques[xb][yb].golpear(g, (xb * 33) + 1, (yb * 19) + 30);
					// rebotar
					dx1 = x - (xb * 33) + 1;
					dx2 = (xb * 33) + 1 + 33 - x;
					
					// guardar en dx la menor distancia
					if(dx1 < dx2)
						dx = dx1;
					else
						dx = dx2;
					
					dy1 = y2 - (yb * 19) + 30;
					dy2 = (yb * 19) + 30 + 19 - y2;
					
					// guardar en dy la menor distancia
					if(dy1 < dy2)
						dy = dy1;
					else
						dy = dy2;
					
					if(dy > dx && !rx) { // rebotar horizontamente?
						
						velx = -velx;

						if(velx < 0)
							velx = -velx;
						
						rx = true;
					}
					
					else if(!ry) {
						
						vely = -vely;
						
						if(vely > 0)
							vely = -vely;
						
						ry = true;
					}
				}
			}
			
			if(rx) {
				x += velx;
			}
			
			if(ry) {
				y += vely;
			}
		}
		
		else { // controlar el choque de la bola con la barra:
			
		yb = barra.obtY();
		
		if(y2 >= yb) { // llegó la bola al nivel de la barra?
			//if((x + ancho) > barra.obtX() && x < (barra.obtX() + barra.obtAncho())) {
			
			xb = barra.obtX();
			anchoBar = barra.obtAncho();
				
			// está sobre la barra?
			if((x2 > xb && x2 < (xb + anchoBar)) ||
			   (x > xb && x < (xb + anchoBar)))
			{
				// calcular distancias
				dx1 = x2 - xb;
				dx2 = xb + anchoBar - x;
				
				// guardar en dx la menor distancia
				if(dx1 < dx2)
					dx = dx1;
				else
					dx = dx2;
				
				dy = y2 - yb;
								
				if(dy > dx) { // rebota horizontalmente?
					
					if(velx < 0) {
						x = xb + anchoBar + 2;
						velx = -velx + barra.obtVelocidad(); // cambiar la dirección horizontal
					}
					
					else {
						x = xb - ancho - 1;
						velx = -velx - barra.obtVelocidad(); // cambiar la dirección horizontal
					}
					
					
				}
				
				else { // rebota verticalmente
					
					if(der) {
						velx -= 1;
						
						if(velx == 2)
							velx = 3;
						
						else if(velx == -2)
							velx = -3;
						
						if(velx < -11)
							velx = -10;
					}
						
					if(iz) {
						velx += 1;

						if(velx == 2)
							velx = 3;
						
						else if(velx == -2)
							velx = -3;
						
						if(velx > 11)
							velx = 10;
					}
					
					vely = -vely; // cambiar la dirección vertical
					y = yb - alto - 1;
				}
			}
		}
		}
		
		g.drawImage(img, x, y, padre); // dibujar
		
		return puntos;
	}
	
}
