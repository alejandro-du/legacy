/////////////////////////////////////////////////////////////////////////////////////////////
// FrameBaseDeDatos.java
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
//
// Autor: J. Alejandro Duarte Avenda�o.
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
// FrameBaseDeDatos
//
// Define la clase para el manejo de la ventana de base de datos.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class FrameBaseDeDatos extends Frame implements ActionListener
{
	Button BotonVideos;
	Button BotonClientes;
	Button BotonHistorialDeAlquiler;
	Button BotonMenuPrincipal;
	
	MenuDeOpciones menu = new MenuDeOpciones(this, 4);
	
	Frame FramePadre;


	FrameBaseDeDatos(Frame Padre) {
		
		FramePadre = Padre;
		
		// establecer el t�tulo
		setTitle(FramePrincipal.TITULO_APLICACION  + " - Base de datos");
		
		// a�adir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				FramePadre.setVisible(true); // visualizar el anterior
				we.getWindow().setVisible(false);
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 2)); // gestor de organizaci�n

		BotonVideos = menu.agregarOpcion("VIDEOS");
		BotonClientes = menu.agregarOpcion("CLIENTES");
		BotonHistorialDeAlquiler = menu.agregarOpcion("HISTORIAL DE ALQUILER");
		BotonMenuPrincipal = menu.agregarOpcion("MEN� PRINCIPAL");
		
		BotonVideos.addActionListener(this);
		BotonClientes.addActionListener(this);
		BotonHistorialDeAlquiler.addActionListener(this);
		BotonMenuPrincipal.addActionListener(this);
	}
	
	
	// auditor de los botones
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		
		if(str.equals("VIDEOS")) {
			FrameVideos frame = new FrameVideos(FramePadre);
			frame.show();
			setVisible(false); // ocultar este men�
			dispose();
		}
		
		else if(str.equals("CLIENTES")) {
			FrameClientes frame = new FrameClientes(FramePadre);
			frame.show();
			setVisible(false); // ocultar este men�
			dispose();
		}
		
		else if(str.equals("HISTORIAL DE ALQUILER")) {
			new MsgBox("Esta caracter�stica no ha sido implementada todav�a.", this);
		}

		else if(str.equals("MEN� PRINCIPAL")) {
			FramePadre.setVisible(true); // visualizar el anterior
			setVisible(false); // ocultar este men�
			dispose();
		}
	}
}