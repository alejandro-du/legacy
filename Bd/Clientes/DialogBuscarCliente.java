/////////////////////////////////////////////////////////////////////////////////////////////
// DialogBuscarCliente.java
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
// DialogBuscarCliente
//
// Define la clase para el manejo de la ventana buscar cliente.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogBuscarCliente extends Dialog implements ActionListener, ItemListener
{
	TextField tfCodigo    = new TextField();
	TextField tfNombre    = new TextField();
	TextField tfCedula    = new TextField();
	TextField tfTelefono  = new TextField();
	TextField tfDireccion = new TextField();
	TextField tfOtrosDatos = new TextField();
	
	Button BotonBuscar = new Button("Buscar");
	Button BotonCerrar = new Button("Cerrar");
	
	Checkbox cbCodigo     = new Checkbox("Código", true);
	Checkbox cbNombre     = new Checkbox("Nombre", false);
	Checkbox cbCedula     = new Checkbox("Cédula", false);
	Checkbox cbTelefono   = new Checkbox("Teléfono", false);
	Checkbox cbDireccion  = new Checkbox("Dirección", false);
	Checkbox cbOtrosDatos = new Checkbox("Otros datos", false);
	

	DialogBuscarCliente(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Buscar Cliente", true);

		// añadir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 2, 0, 10));
		setSize(400, 230);
		
		// agragar controles
		add(cbCodigo);
		add(tfCodigo);
		add(cbNombre);
		add(tfNombre);
		add(cbCedula);
		add(tfCedula);
		add(cbTelefono);
		add(tfTelefono);
		add(cbDireccion);
		add(tfDireccion);
		add(cbOtrosDatos);
		add(tfOtrosDatos);
		
		add(BotonBuscar);
		add(BotonCerrar);
		
		cbCodigo.addItemListener(this);
		cbNombre.addItemListener(this);
		cbCedula.addItemListener(this);
		cbTelefono.addItemListener(this);
		cbDireccion.addItemListener(this);
		cbOtrosDatos.addItemListener(this);
		
		BotonBuscar.addActionListener(this);
		BotonCerrar.addActionListener(this);
		
		actualizar();
	}
	
	
	public void paint (Graphics g) {
		tfCodigo.requestFocus();
	}
	
	
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		if(str.equals("Cerrar")) {
			dispose(); // cerrar el cuadro
		}
		
		else if(str.equals("Buscar")) {
			boolean b[] = new boolean[7];
			
			String[] strCampos = new String[7];
			
			strCampos[0] = new String(tfCodigo.getText());
			strCampos[1] = new String(tfNombre.getText());
			strCampos[2] = new String(tfCedula.getText());
			strCampos[3] = new String(tfTelefono.getText());
			strCampos[4] = new String(tfDireccion.getText());
			strCampos[5] = new String(); // personas autorizadas
			strCampos[6] = new String(tfOtrosDatos.getText());
			
			b[0] = cbCodigo.getState();
			b[1] = cbNombre.getState();
			b[2] = cbCedula.getState();
			b[3] = cbTelefono.getState();
			b[4] = cbDireccion.getState();
			b[5] = false; // personas autorizadas
			b[6] = cbOtrosDatos.getState();
			
			// no comparar si no se escribió nada pero se seleccionó el "cb"
			for(int i = 0; i < 7; i++) { // cada campo
				if(strCampos[i].equals(""))
				   b[i] = false;
			}
			
			if(!FramePrincipal.BDClientes.buscarRegistro(b, strCampos)) {
				new MsgBox("No se encontró el registro solicitado.", new Frame());
			}
			else {
				DialogEditarCliente dlg = new DialogEditarCliente(new Frame());

				dlg.tfCodigo.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				dlg.tfNombre.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				dlg.tfCedula.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				dlg.tfTelefono.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				dlg.tfDireccion.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				dlg.tfPersonasAutorizadas.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				dlg.tfOtrosDatos.setText(FramePrincipal.BDClientes.leerCampo((byte)'S'));
				
				dlg.setVisible(true);
				
			}
			
			repaint();
		}
	}
	
	
	public void itemStateChanged(ItemEvent ie) {
		actualizar();
	}
	
	
	void actualizar() {
		if(cbCodigo.getState())
			tfCodigo.setEnabled(true);
		else
			tfCodigo.setEnabled(false);
		
		if(cbNombre.getState())
			tfNombre.setEnabled(true);
		else
			tfNombre.setEnabled(false);
		
		if(cbCedula.getState())
			tfCedula.setEnabled(true);
		else
			tfCedula.setEnabled(false);
		
		if(cbTelefono.getState())
			tfTelefono.setEnabled(true);
		else
			tfTelefono.setEnabled(false);
		
		if(cbDireccion.getState())
			tfDireccion.setEnabled(true);
		else
			tfDireccion.setEnabled(false);
		
		if(cbOtrosDatos.getState())
			tfOtrosDatos.setEnabled(true);
		else
			tfOtrosDatos.setEnabled(false);
	}
}