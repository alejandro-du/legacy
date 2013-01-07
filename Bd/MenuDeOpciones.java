/////////////////////////////////////////////////////////////////////////////////////////////
// MenuDeOpciones.java
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
//
// Autor: J. Alejandro Duarte Avendaño.
//        jaal@yahoo.com
//
// Junio 2003.
//
/////////////////////////////////////////////////////////////////////////////////////////////



import java.awt.*;
import java.applet.*;
import java.awt.event.*;



/////////////////////////////////////////////////////////////////////////////////////////////
//
// MenuDeOpciones
//
// Define la clase para el manejo de opciones por medio de botones.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class MenuDeOpciones implements MouseListener
{
	Frame ventana; // ventana en la que se colocarán los botones
	int nOpciones; // número actual de opciones
	Button aBotones[];
	
	MenuDeOpciones(Frame frm, int numeroOpciones) {
		ventana = frm;
		nOpciones = 0; // no se han agregado opciones
		ventana.setLayout(new GridLayout(0, 1)); // gestor de organización
		aBotones = new Button[numeroOpciones];
		
		Toolkit tk = ventana.getToolkit();
		Dimension d = tk.getScreenSize(); // dimensiones de la pantalla

		ventana.setBackground(Color.gray); // establecer el color de fondo
		ventana.setSize(d.width, d.height); // fijar las dimensiones de la ventana
		
		ventana.setResizable(false);
	}
	
	
	public Button agregarOpcion(String titulo) {
		aBotones[nOpciones] = new Button(titulo); // crear el objeto
		aBotones[nOpciones].setLabel(titulo); // establecer la etiqueta
		ventana.add(aBotones[nOpciones]); // añadir el control a la ventana
		aBotones[nOpciones].addMouseListener(this); // añadir auditor
		nOpciones++;
		return aBotones[nOpciones - 1];
	}
	
	
	public void mouseEntered(MouseEvent me) {
		me.getComponent().requestFocus(); // seleccionar el botón
	}
	public void mouseExited(MouseEvent me) {
	}
	public void mousePressed(MouseEvent me) {
	}
	public void mouseReleased(MouseEvent me) {
	}
	public void mouseClicked(MouseEvent me) {
	}
}