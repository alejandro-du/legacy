/////////////////////////////////////////////////////////////////////////////////////////////
// FrameVideos.java
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
// FrameVideos
//
// Define la clase para el manejo de la ventana de videos.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class FrameVideos extends Frame implements ActionListener
{
	Button BotonListado;
	Button BotonBuscarVideo;
	Button BotonAgregarVideo;
	Button BotonEliminarVideo;
	Button BotonEditarVideo;
	Button BotonMenuPrincipal;
	
	MenuDeOpciones menu = new MenuDeOpciones(this, 6);
	
	Frame FramePadre;


	FrameVideos(Frame Padre) {
		
		FramePadre = Padre;
		
		setTitle(FramePrincipal.TITULO_APLICACION + " - Videos");  // establecer el título
		
		// añadir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				FramePadre.setVisible(true); // visualizar el anterior
				we.getWindow().setVisible(false);
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 2)); // gestor de organización
		
		BotonListado = menu.agregarOpcion("LISTADO");
		BotonBuscarVideo = menu.agregarOpcion("BUSCAR VIDEO");
		BotonAgregarVideo = menu.agregarOpcion("AGREGAR VIDEO");
		BotonEliminarVideo = menu.agregarOpcion("ELIMINAR VIDEO");
		BotonEditarVideo = menu.agregarOpcion("EDITAR VIDEO");
		BotonMenuPrincipal = menu.agregarOpcion("MENÚ PRINCIPAL");
		
		BotonListado.addActionListener(this);
		BotonBuscarVideo.addActionListener(this);
		BotonAgregarVideo.addActionListener(this);
		BotonEliminarVideo.addActionListener(this);
		BotonEditarVideo.addActionListener(this);
		BotonMenuPrincipal.addActionListener(this);
	}
	
	
	// auditor de los botones
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		
		if(str.equals("LISTADO")) {
			new DialogListadoVideos(new Frame()).show();
		}
		else if(str.equals("BUSCAR VIDEO")) {
			new DialogBuscarVideo(this).setVisible(true);
		}
		
		else if(str.equals("AGREGAR VIDEO")) {
			new DialogAgregarVideos(this).setVisible(true);
		}
		
		else if(str.equals("ELIMINAR VIDEO")) {
			new DialogEliminarVideo(this).setVisible(true);
		}

		else if(str.equals("EDITAR VIDEO")) {
			new DialogEditarVideo(this).setVisible(true);
		}

		else if(str.equals("MENÚ PRINCIPAL")) {
			FramePadre.setVisible(true); // visualizar el anterior
			setVisible(false); // ocultar este menú
			dispose();
		}
	}
}