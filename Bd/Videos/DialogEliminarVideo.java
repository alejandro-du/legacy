/////////////////////////////////////////////////////////////////////////////////////////////
// DialogEliminarVideo.java
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
// DialogEliminarVideo
//
// Define la clase para el manejo de la ventana eliminar video.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogEliminarVideo extends Dialog implements ActionListener, ItemListener
{
	TextField tfCodigo        = new TextField();
	TextField tfTitulo        = new TextField();
	TextField tfGenero        = new TextField();
	TextField tfClasificacion = new TextField();
	TextField tfIdioma        = new TextField();
	TextField tfOtrosDatos    = new TextField();
	
	Button BotonEliminar = new Button("Eliminar");
	Button BotonCerrar = new Button("Cerrar");
	
	Checkbox cbCodigo        = new Checkbox("C�digo", true);
	Checkbox cbTitulo        = new Checkbox("T�tulo", false);
	Checkbox cbGenero        = new Checkbox("G�nero", false);
	Checkbox cbClasificacion = new Checkbox("Clasificaci�n", false);
	Checkbox cbIdioma        = new Checkbox("Idioma", false);
	Checkbox cbOtrosDatos    = new Checkbox("Otros datos", false);
	

	DialogEliminarVideo(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Eliminar Video", true);

		// a�adir un auditor para la ventana
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
		add(cbTitulo);
		add(tfTitulo);
		add(cbGenero);
		add(tfGenero);
		add(cbClasificacion);
		add(tfClasificacion);
		add(cbIdioma);
		add(tfIdioma);
		add(cbOtrosDatos);
		add(tfOtrosDatos);
		
		add(BotonEliminar);
		add(BotonCerrar);
		
		cbCodigo.addItemListener(this);
		cbTitulo.addItemListener(this);
		cbGenero.addItemListener(this);
		cbClasificacion.addItemListener(this);
		cbIdioma.addItemListener(this);
		cbOtrosDatos.addItemListener(this);
		
		BotonEliminar.addActionListener(this);
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
		
		else if(str.equals("Eliminar")) {
			boolean b[] = new boolean[8];
			
			String[] strCampos = new String[8];
			
			strCampos[0] = new String(tfCodigo.getText());
			strCampos[1] = new String(tfTitulo.getText());
			strCampos[2] = new String(); // cantidad
			strCampos[3] = new String(tfGenero.getText());
			strCampos[4] = new String(tfClasificacion.getText());
			strCampos[5] = new String(tfIdioma.getText());
			strCampos[6] = new String(); // texto descriptivo
			strCampos[7] = new String(tfOtrosDatos.getText());
			
			b[0] = cbCodigo.getState();
			b[1] = cbTitulo.getState();
			b[2] = false; // cantidad
			b[3] = cbGenero.getState();
			b[4] = cbClasificacion.getState();
			b[5] = cbIdioma.getState();
			b[6] = false; // texto descriptivo
			b[7] = cbOtrosDatos.getState();
			
			// deshabilitar comparaci�n si no se escribi� nada pero se seleccion� el "cb"
			for(int i = 0; i < 8; i++) { // cada campo
				if(strCampos[i].equals(""))
				   b[i] = false;
			}

			
			if(!FramePrincipal.BDVideos.buscarRegistro(b, strCampos)) {
				new MsgBox("No se encontr� el registro solicitado.", new Frame());
			}
			else {
				if(new MsgBox("�Desea eliminar este registro de la base de datos?",
						      FramePrincipal.TITULO_APLICACION,
						      new Frame(),
						      true).bResultado == true)
				{
					// eliminar
					if(FramePrincipal.BDVideos.eliminarRegistro())
						new MsgBox("El registro ha sido eliminado.", new Frame());
					else
						new MsgBox("Error al intentar eliminar el registro.", new Frame());
				}
				else {
				}
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
		
		if(cbTitulo.getState())
			tfTitulo.setEnabled(true);
		else
			tfTitulo.setEnabled(false);
		
		if(cbGenero.getState())
			tfGenero.setEnabled(true);
		else
			tfGenero.setEnabled(false);
		
		if(cbClasificacion.getState())
			tfClasificacion.setEnabled(true);
		else
			tfClasificacion.setEnabled(false);
		
		if(cbIdioma.getState())
			tfIdioma.setEnabled(true);
		else
			tfIdioma.setEnabled(false);

		if(cbOtrosDatos.getState())
			tfOtrosDatos.setEnabled(true);
		else
			tfOtrosDatos.setEnabled(false);
	}
}