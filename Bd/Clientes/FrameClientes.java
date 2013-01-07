/////////////////////////////////////////////////////////////////////////////////////////////
// FrameClientes.java
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
// FrameClientes
//
// Define la clase para el manejo de la ventana de clientes.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class FrameClientes extends Frame implements ActionListener
{
	Button BotonListado;
	Button BotonBuscarCliente;
	Button BotonAgregarCliente;
	Button BotonEliminarCliente;
	Button BotonEditarCliente;
	Button BotonMenuPrincipal;
	
	MenuDeOpciones menu = new MenuDeOpciones(this, 6);
	
	Frame FramePadre;


	FrameClientes(Frame Padre) {
		
		FramePadre = Padre;

		setTitle(FramePrincipal.TITULO_APLICACION + " - Clientes");  // establecer el título
		
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				FramePadre.setVisible(true); // visualizar el anterior
				we.getWindow().setVisible(false); // ocultar este menú
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 2)); // gestor de organización
		
		BotonListado = menu.agregarOpcion("LISTADO");
		BotonBuscarCliente = menu.agregarOpcion("BUSCAR CLIENTE");
		BotonAgregarCliente = menu.agregarOpcion("AGREGAR CLIENTE");
		BotonEliminarCliente = menu.agregarOpcion("ELIMINAR CLIENTE");
		BotonEditarCliente = menu.agregarOpcion("EDITAR CLIENTE");
		BotonMenuPrincipal = menu.agregarOpcion("MENÚ PRINCIPAL");
		
		BotonListado.addActionListener(this);
		BotonBuscarCliente.addActionListener(this);
		BotonAgregarCliente.addActionListener(this);
		BotonEliminarCliente.addActionListener(this);
		BotonEditarCliente.addActionListener(this);
		BotonMenuPrincipal.addActionListener(this);
	}
	
	
	// auditor de los botones
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		
		if(str.equals("LISTADO")) {
			new DialogListadoClientes(new Frame()).show();
		}
		else if(str.equals("BUSCAR CLIENTE")) {
			new DialogBuscarCliente(this).setVisible(true);
		}
		
		else if(str.equals("AGREGAR CLIENTE")) {
			new DialogAgregarClientes(this).setVisible(true);
		}
		
		else if(str.equals("ELIMINAR CLIENTE")) {
			new DialogEliminarCliente(this).setVisible(true);
		}

		else if(str.equals("EDITAR CLIENTE")) {
			new DialogEditarCliente(this).setVisible(true);
		}

		else if(str.equals("MENÚ PRINCIPAL")) {
			FramePadre.setVisible(true); // visualizar el anterior
			setVisible(false); // ocultar este menú
			dispose();
		}
	}
}