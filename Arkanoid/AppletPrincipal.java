// AppletPrincipal.java



import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.util.Random;



/*
<applet code = "AppletPrincipal" width = 596, height = 327>
</applet>
*/



public class AppletPrincipal extends Applet implements Runnable, KeyListener
{
	
	boolean terminar; // flag para finalizar el bucle de animación
	boolean teclado[] = new boolean[2]; // array con el estado de las teclas
	int ancho, alto; // tamaño del applet
	int puntos;
	int bolas;
	Thread hilo = null; // hilo para el bucle principal del juego
	Image frontBuffer = null; // buffer que dibujará paint
	Image backBuffer = null; // buffer en el que se realizará el dibujado
	Graphics backBufferGr = null; // contextos gráficos para acceder a los buffers
	Graphics frontBufferGr = null;
	Barra barra = null;
	Bola bola = null;
	Bloque bloques[][];
	
	
	protected void generarBloques() {
		// crear los bloques
		
		Random r = new Random();
					  
		for(int x = 0; x < 18; x++) { // cada columna
			for(int y = 0; y < 7; y++) { // cada fila
				
				int n;
				
				n = (int)(Math.random() * 100);
				
				if(n >= 0 && n <= 50)
					bloques[x][y] = new Bloque1("Bloque1.jpg", this);
				
				else if(n >= 51 && n <= 85)
					bloques[x][y] = new Bloque2("Bloque2.jpg", this);
				
				else if(n >= 86 && n <= 96)
					bloques[x][y] = new Bloque3("Bloque3.jpg", this);

				else if(n >= 97 && n <= 100)
					bloques[x][y] = new BloqueFijo("BloqueF.jpg", this);
			}
		}
	}

	
	public void init() {
		
		setBackground(Color.black); // establecer color del fondo
		ancho = 596; // inicializar valores del tamaño del applet
		alto = 327;
		
		addKeyListener(this); // auditor del teclado
	}
	
	
	public void start() {
		
		hilo = new Thread(this); // crear un nuevo hilo de ejecución
		
		// crear los buffers de animación (doble buffer)
		frontBuffer = createImage(ancho, alto);
		backBuffer = createImage(ancho, alto);

		// crear los objetos del juego
		//barra = new Barra("barra.jpg", this);
		bloques = new Bloque[18][7];
		//bola = new Bola("bola.jpg", this);
		
		generarBloques();
		
		puntos = 0;
		bolas = 3;
		
		terminar = false; // permitir que se ejecute el bucle
		teclado[0] = teclado[1] = false; // inicializar el estado de las teclas
		
		setSize(ancho, alto); // establecer el tamaño del applet
		
		requestFocus(); // solicitar el foco de entrada
		hilo.start(); // comenzar la ejecución del hilo
	}
	
	
	public void run() {
		
		// obtener un contexto gráfico para cada buffer
		backBufferGr = backBuffer.getGraphics();
		frontBufferGr = frontBuffer.getGraphics();
		
		frontBufferGr.drawImage(backBuffer, 0, 0, this);
		
		for(; !terminar; ) { // bucle principal
			
			// rellenar de negro el buffer posterior
			backBufferGr.setColor(Color.black);
			backBufferGr.fillRect(0, 0, ancho, alto);
		
			// dibujar el marco
			backBufferGr.setColor(Color.gray);
			backBufferGr.drawRect(0, 28, ancho - 1, alto - 29);
		
			// dibujar el número de bolas restantes
			backBufferGr.setColor(Color.white);
			backBufferGr.drawString("Bolas:" + (bolas - 1), 540, 20);
		
			bola = new Bola("bola.jpg", this);
			barra = new Barra("barra.jpg", this);
				
			// dibujar los bloques a destruir
			for(int x = 0; x < 18; x++) { // cada columna
				for(int y = 0; y < 7; y++) { // cada fila
					// dibujar en la posición correspondiente
					if(bloques[x][y].activo())
						bloques[x][y].dibujar(backBufferGr, (x * 33) + 1, (y * 19) + 30);
				}
			}
			
			for(; !terminar; ) { // cada bola
			
				if(teclado[0]) { // flecha izq?
					barra.moverIzquierda();
				}
				
				if(teclado[1]) { // flecha der?
					barra.moverDerecha();
				}
				
				// borrar los puntos
				backBufferGr.setColor(Color.black);
				backBufferGr.drawString("Puntos:" + puntos, 10, 20);
				
				barra.dibujar(backBufferGr);
				int p = bola.dibujar(backBufferGr, barra, teclado[0], teclado[1], bloques);
				
				if(p == -1) {
					
					bolas--;
					break;
				}
				
				else
					puntos += p;
				
				backBufferGr.setColor(Color.white);
				backBufferGr.drawString("Puntos:" + puntos, 10, 20);
				
				// "flip": dibujar lo del buffer posterior al frontal
				frontBufferGr.drawImage(backBuffer, 0, 0, this);
				
				repaint();
				
				try {
					Thread.sleep(10);
				}
				
				catch(InterruptedException e) {}
			}
			
			if(bolas <= 0) { // game over
				
				generarBloques();
				bolas = 3;
			}
		}
	}
	
	
	public void stop() {
		terminar = true; // parar el bucle principal
		hilo = null;
	}
	
	
	public void update(Graphics g) {
		paint(g);
	}
	
	
	public void paint(Graphics g) {
		g.drawImage(frontBuffer, 0, 0, this); // dibujar el buffer en la pantalla
	}
	
	
	public void keyPressed(KeyEvent k) {
		
		int tecla = k.getKeyCode(); // obtener el código de la tecla presionada
		
		if(tecla == KeyEvent.VK_LEFT) {
			teclado[0] = true;
		}
		
		if(tecla == KeyEvent.VK_RIGHT) {
			teclado[1] = true;
		}
	}
	
	
	public void keyReleased(KeyEvent k) {
		
		int tecla = k.getKeyCode(); // obtener el código de la tecla liberada
		
		if(tecla == KeyEvent.VK_LEFT) {
			teclado[0] = false;
		}
		
		if(tecla == KeyEvent.VK_RIGHT) {
			teclado[1] = false;
		}
	}
	
	
	public void keyTyped(KeyEvent k) {
	}	
	
}