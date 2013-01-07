/////////////////////////////////////////////////////////////////////////////////////////////
// DialogEditarCliente.java
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
import java.awt.event.*;



/////////////////////////////////////////////////////////////////////////////////////////////
//
// DialogEditarCliente
//
// Define la clase para el manejo de la ventana editar cliente.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogEditarCliente extends Dialog implements ActionListener
{
	public TextField tfCodigo              = new TextField();
	public TextField tfNombre              = new TextField();
	public TextField tfCedula              = new TextField();
	public TextField tfTelefono            = new TextField();
	public TextField tfDireccion           = new TextField();
	public TextField tfPersonasAutorizadas = new TextField();
	public TextField tfOtrosDatos          = new TextField();
	
	Button BotonCerrar              = new Button("Cerrar");
	Button BotonSiguiente           = new Button(">>");
	Button BotonBuscarPorCodigo     = new Button("Buscar por código");
	Button BotonGuardarModificacion = new Button("Guardar modificación");

	String[] strCampos = new String[7];
	
	boolean bRegEncontrado = false;

	
	DialogEditarCliente(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Editar Cliente", true);

		// añadir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 2, 0, 10));
		setSize(400, 290);
		
		add(new Label("Código:"));
		add(tfCodigo);
		add(new Label("Nombre:"));
		add(tfNombre);
		add(new Label("Cédula:"));
		add(tfCedula);
		add(new Label("Teléfono:"));
		add(tfTelefono);
		add(new Label("Dirección:"));
		add(tfDireccion);
		add(new Label("Personas autorizadas:"));
		add(tfPersonasAutorizadas);
		add(new Label("Texto descriptivo:"));
		add(tfOtrosDatos);
		
		add(BotonBuscarPorCodigo);
		add(BotonSiguiente);
		add(BotonGuardarModificacion);
		add(BotonCerrar);
		
		BotonCerrar.addActionListener(this);
		BotonSiguiente.addActionListener(this);
		BotonBuscarPorCodigo.addActionListener(this);
		BotonGuardarModificacion.addActionListener(this);
	}
	
	
	public void paint (Graphics g) {
		tfCodigo.requestFocus();
	}
	
	
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		
		if(str.equals("Cerrar")) {
			dispose(); // cerrar el cuadro
		}
		
		else if(str.equals(">>")) { // siguiente registro
			if(bRegEncontrado) {
				
				byte eliminado;

				do {
				
					String strCod;
					strCod = FramePrincipal.BDClientes.leerCampo((byte)'S');
					if(strCod == null) {
						new MsgBox("No se encontraron más registros.", new Frame());
						return;
					}
				
					strCampos[0] = new String(strCod);
					strCampos[1] = new String(FramePrincipal.BDClientes.leerCampo((byte)'S'));
					strCampos[2] = new String(FramePrincipal.BDClientes.leerCampo((byte)'S'));
					strCampos[3] = new String(FramePrincipal.BDClientes.leerCampo((byte)'S'));
					strCampos[4] = new String(FramePrincipal.BDClientes.leerCampo((byte)'S'));
					strCampos[5] = new String(FramePrincipal.BDClientes.leerCampo((byte)'S'));
					strCampos[6] = new String(FramePrincipal.BDClientes.leerCampo((byte)'S'));
					
					eliminado = FramePrincipal.BDClientes.leerByteEliminacion();
				
					if(eliminado != 1) {
						tfCodigo.setText(strCampos[0]);
						tfNombre.setText(strCampos[1]);
						tfCedula.setText(strCampos[2]);
						tfTelefono.setText(strCampos[3]);
						tfDireccion.setText(strCampos[4]);
						tfPersonasAutorizadas.setText(strCampos[5]);
						tfOtrosDatos.setText(strCampos[6]);
					}
					
				} while (eliminado == 1);

			}
			else
				new MsgBox("Primero debe buscar un registro válido.", new Frame());
		}
		
		else if(str.equals("Buscar por código")) {
			boolean b[] = new boolean[7];
			
			strCampos[0] = new String(tfCodigo.getText());
			strCampos[1] = new String();
			strCampos[2] = new String();
			strCampos[3] = new String();
			strCampos[4] = new String();
			strCampos[5] = new String();
			strCampos[6] = new String();
			
			b[0] = true;
			b[1] = false;
			b[2] = false;
			b[3] = false;
			b[4] = false;
			b[5] = false;
			b[6] = false;
			
			if(!FramePrincipal.BDClientes.buscarRegistro(b, strCampos)) {
				new MsgBox("No se encontró el registro con el código solicitado.", new Frame());
				bRegEncontrado = false;
			}
			else {
				tfCodigo.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				tfNombre.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				tfCedula.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				tfTelefono.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				tfDireccion.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				tfPersonasAutorizadas.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				tfOtrosDatos.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				
				FramePrincipal.BDClientes.leerByteEliminacion();

				// actualizar los valores del reg a editar
				strCampos[0] = new String(tfCodigo.getText());
				strCampos[1] = new String(tfNombre.getText());
				strCampos[2] = new String(tfCedula.getText());
				strCampos[3] = new String(tfTelefono.getText());
				strCampos[4] = new String(tfDireccion.getText());
				strCampos[5] = new String(tfPersonasAutorizadas.getText());
				strCampos[6] = new String(tfOtrosDatos.getText());
				
				bRegEncontrado = true;
			}
			
			repaint();
		}
		
		else if(str.equals("Guardar modificación")) {
			if(bRegEncontrado) {
				
				boolean b[] = new boolean[7];
			
				// realizar todas las comparaciones
				for(int i = 0; i < 7; i++)
					b[i] = true;
				
				if(!FramePrincipal.BDClientes.buscarRegistro(b, strCampos)) {
					new MsgBox("Error al intentar buscar el registro a editar", new Frame());
				}
				else { // se pudo encontrar el registro
					if(
					   new MsgBox("¿Desea guardar la modificación hecha a este registro?",
								  FramePrincipal.TITULO_APLICACION,
								  new Frame(), true).bResultado
					  )
					{
						// eliminar el actual
						FramePrincipal.BDClientes.eliminarRegistro();
						
						//escribir el nuevo:
						FramePrincipal.BDClientes.escribirCampo(tfCodigo.getText());
						FramePrincipal.BDClientes.escribirCampo(tfNombre.getText());
						FramePrincipal.BDClientes.escribirCampo(tfCedula.getText());
						FramePrincipal.BDClientes.escribirCampo(tfTelefono.getText());
						FramePrincipal.BDClientes.escribirCampo(tfDireccion.getText());
						FramePrincipal.BDClientes.escribirCampo(tfPersonasAutorizadas.getText());
						FramePrincipal.BDClientes.escribirCampo(tfOtrosDatos.getText());
						
						new MsgBox("La modificación ha sido guardada en la base de datos.",
								   new Frame());
					}
				}
			}
			else {
				new MsgBox("Debe buscar un registro válido para editar.", new Frame());
			}
			
			repaint();
		}
	}
}