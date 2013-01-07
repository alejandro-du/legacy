/////////////////////////////////////////////////////////////////////////////////////////////
// DialogAgregarClientes.java
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
import java.awt.event.*;



/////////////////////////////////////////////////////////////////////////////////////////////
//
// DialogAgregarClientes
//
// Define la clase para el manejo de las ventanas agregar clientes.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogAgregarClientes extends Dialog implements ActionListener
{
	TextField tfCodigo              = new TextField();
	TextField tfNombre              = new TextField();
	TextField tfCedula              = new TextField();
	TextField tfTelefono            = new TextField();
	TextField tfDireccion           = new TextField();
	TextField tfPersonasAutorizadas = new TextField();
	TextField tfOtrosDatos          = new TextField();
	//DEBUG: Se deber�a incluir la fecha de inscripci�n a la base de datos.
	
	Button BotonAgregar = new Button("Agregar");
	Button BotonCerrar  = new Button("Cerrar");
	

	DialogAgregarClientes(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Agregar Cliente", true);

		// a�adir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 2, 0, 10)); // cuadr�cula
		setSize(400, 260); // cuadrar el tama�o
		
		// agregar los controles:
		add(new Label("C�digo:"));
		add(tfCodigo);
		add(new Label("Nombre:"));
		add(tfNombre);
		add(new Label("C�dula:"));
		add(tfCedula);
		add(new Label("Tel�fono:"));
		add(tfTelefono);
		add(new Label("Direcci�n:"));
		add(tfDireccion);
		add(new Label("Personas autorizadas:"));
		add(tfPersonasAutorizadas);
		add(new Label("Otros datos:"));
		add(tfOtrosDatos);
		
		add(BotonAgregar);
		add(BotonCerrar);
		
		// agregar auditores:
		BotonAgregar.addActionListener(this);
		BotonCerrar.addActionListener(this);
	}
	
	
	public void paint (Graphics g) {
		tfCodigo.requestFocus(); // poner el cursor en el "tf" del c�digo
	}
	
	
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		if(str.equals("Cerrar")) {
			dispose(); // cerrar el cuadro
		}
		
		else if(str.equals("Agregar")) {
			
			if(tfCodigo.getText().length() <= 0) {
				new MsgBox("Debe introducir el c�digo.", new Frame());
				return;
			}
			
			// verificar que el c�digo no halla sido usado
			boolean b[] = new boolean[7];
			String[] strCampos = new String[7];
			
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
			
			if(FramePrincipal.BDClientes.buscarRegistro(b, strCampos)) {
				new MsgBox("El cliente c�digo <" + strCampos[0] + "> ya existe en la base de datos.", new Frame());
				tfCodigo.setText("");
				repaint();
				return;
			}
			
			// escribir los datos en el archivo:
			FramePrincipal.BDClientes.escribirCampo(tfCodigo.getText());
			FramePrincipal.BDClientes.escribirCampo(tfNombre.getText());
			FramePrincipal.BDClientes.escribirCampo(tfCedula.getText());
			FramePrincipal.BDClientes.escribirCampo(tfTelefono.getText());
			FramePrincipal.BDClientes.escribirCampo(tfDireccion.getText());
			FramePrincipal.BDClientes.escribirCampo(tfPersonasAutorizadas.getText());
			FramePrincipal.BDClientes.escribirCampo(tfOtrosDatos.getText());
			
			new MsgBox("El cliente ha sido a�adido a la base de datos.", new Frame());
			
			// borrar los tfs del cuadro:
			tfCodigo.setText("");
			tfNombre.setText("");
			tfCedula.setText("");
			tfTelefono.setText("");
			tfDireccion.setText("");
			tfPersonasAutorizadas.setText("");
			tfOtrosDatos.setText("");
			
			repaint();
		}
	}
}