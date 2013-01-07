/////////////////////////////////////////////////////////////////////////////////////////////
// FramePrincipal.java
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
//
// Autor: J. Alejandro Duarte Avendaño.
//        jaal@yahoo.com
//
// Junio 2003.
//
/////////////////////////////////////////////////////////////////////////////////////////////



//import java.io.*;
import java.awt.*;
import java.applet.*;
import java.awt.event.*;



/////////////////////////////////////////////////////////////////////////////////////////////
//
// FramePrincipal
//
// Define la clase para el manejo de la ventana principal de la aplicación.
// Define la función de entrada a la aplicación: main().
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class FramePrincipal extends Frame implements ActionListener
{
	public static final String TITULO_APLICACION = new String("BD Versión 1");
	public static BD1 BDClientes = new BD1();
	public static BD1 BDVideos = new BD1();
	
	// botones con las opciones del menú principal
	Button BotonAlquiler;
	Button BotonDevolucion;
	Button BotonBaseDeDatos;
	
	MenuDeOpciones menu = new MenuDeOpciones(this, 3);


	// constructor
	FramePrincipal() {
		
		// añadir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				//*
				new MsgBox("J. Alejandro Duarte A.",
						   "                jaal81@yahoo.com                ",
						   "Créditos", new Frame());//*/
				dispose();
				System.exit(0);
			}
		});
		
		// añadir opciones al menú
		BotonAlquiler = menu.agregarOpcion("ALQUILER");
		BotonDevolucion = menu.agregarOpcion("DEVOLUCIÓN");
		BotonBaseDeDatos = menu.agregarOpcion("BASE DE DATOS");
		
		// añadir los auditores para los botones
		BotonAlquiler.addActionListener(this);
		BotonDevolucion.addActionListener(this);
		BotonBaseDeDatos.addActionListener(this);

		// inicializar la base de datos:
		if(!BDClientes.inicializar("CLIENTES", "BD1")) {
			new MsgBox("CLIENTES.BD1: Error al inicializar el archivo.", this);
			if(new MsgBox("¿Desea crear el archivo CLIENTES.BD1?",
			    	      FramePrincipal.TITULO_APLICACION,
					      new Frame(),
					      true).bResultado == true)
			{ // crear el archivo
				byte descCamposC[] = new byte[7];
				
				descCamposC[0] = (byte)'S';
				descCamposC[1] = (byte)'S';
				descCamposC[2] = (byte)'S';
				descCamposC[3] = (byte)'S';
				descCamposC[4] = (byte)'S';
				descCamposC[5] = (byte)'S';
				descCamposC[6] = (byte)'S';
				
				if(!BD1.nuevo("CLIENTES.BD1", 7, descCamposC)) {
					new MsgBox("CLIENTES.BD1: Error al intentar crear el archivo.", this);
					dispose();
					System.exit(0);
				}
			}
			// intentar de nuevo
			if(!BDClientes.inicializar("CLIENTES", "BD1")) {
				new MsgBox("CLIENTES.BD1: No se pudo inicializar el archivo.", this);
				dispose();
				System.exit(0);
			}
		}
		
		if(!BDVideos.inicializar("VIDEOS", "BD1")) {
			new MsgBox("VIDEOS.BD1: Error al inicializar el archivo.", this);
			if(new MsgBox("¿Desea crear el archivo VIDEOS.BD1?",
			    	      FramePrincipal.TITULO_APLICACION,
					      new Frame(),
					      true).bResultado == true)
			{ // crear el archivo
				byte descCamposV[] = new byte[7];
				
				descCamposV[0] = (byte)'S';
				descCamposV[1] = (byte)'S';
				descCamposV[2] = (byte)'I';
				descCamposV[3] = (byte)'S';
				descCamposV[4] = (byte)'S';
				descCamposV[5] = (byte)'S';
				descCamposV[6] = (byte)'S';
				descCamposV[7] = (byte)'S';
				
				if(!BD1.nuevo("VIDEOS.BD1", 8, descCamposV)) {
					new MsgBox("VIDEOS.BD1: Error al intentar crear el archivo.", this);
					dispose();
					System.exit(0);
				}
			}
			// intentar de nuevo
			if(!BDVideos.inicializar("Videos", "BD1")) {
				new MsgBox("VIDEOS.BD1: No se pudo inicializar el archivo.", this);
				dispose();
				System.exit(0);
			}
		}
	}
	
	
	// auditor de los botones
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();

		if(str.equals("ALQUILER")) {
			
			new MsgBox("Esta característica no ha sido implementada todavía.", this);
		}

		else if(str.equals("DEVOLUCIÓN")) {
			
			new MsgBox("Esta característica no ha sido implementada todavía.", this);
			
		}		
		
		else if(str.equals("BASE DE DATOS")) {
			FrameBaseDeDatos frame = new FrameBaseDeDatos(this);
			frame.show();
			setVisible(false); // ocultar este menú
		}
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Punto de entrada de la aplicación.
	/////////////////////////////////////////////////////////////////////////////////////////
	public static void main(String args[]) {
		
		FramePrincipal app = new FramePrincipal(); // crear la ventana principal
		
		app.setTitle(TITULO_APLICACION + " - Menú principal"); // establecer el título
		app.setVisible(true);          // visualizar
	}
}