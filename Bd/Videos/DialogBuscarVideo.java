/////////////////////////////////////////////////////////////////////////////////////////////
// DialogBuscarVideo.java
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
// DialogBuscarVideo
//
// Define la clase para el manejo de la ventana buscar video.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogBuscarVideo extends Dialog implements ActionListener, ItemListener
{
	TextField tfCodigo        = new TextField();
	TextField tfTitulo        = new TextField();
	TextField tfGenero        = new TextField();
	TextField tfClasificacion = new TextField();
	TextField tfIdioma        = new TextField();
	TextField tfOtrosDatos    = new TextField();
	
	Button BotonBuscar = new Button("Buscar");
	Button BotonCerrar = new Button("Cerrar");
	
	Checkbox cbCodigo        = new Checkbox("Código", true);
	Checkbox cbTitulo        = new Checkbox("Título", false);
	Checkbox cbGenero        = new Checkbox("Género", false);
	Checkbox cbClasificacion = new Checkbox("Clasificación", false);
	Checkbox cbIdioma        = new Checkbox("Idioma", false);
	Checkbox cbOtrosDatos    = new Checkbox("Otros datos", false);
	

	DialogBuscarVideo(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Buscar Video", true);

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
		
		add(BotonBuscar);
		add(BotonCerrar);
		
		cbCodigo.addItemListener(this);
		cbTitulo.addItemListener(this);
		cbGenero.addItemListener(this);
		cbClasificacion.addItemListener(this);
		cbIdioma.addItemListener(this);
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
			
			// no comparar si no se escribió nada pero se seleccionó el "cb"
			for(int i = 0; i < 8; i++) { // cada campo
				if(strCampos[i].equals(""))
				   b[i] = false;
			}
			
			if(!FramePrincipal.BDVideos.buscarRegistro(b, strCampos)) {
				new MsgBox("No se encontró el registro solicitado.", new Frame());
			}
			else {
				DialogEditarVideo dlg = new DialogEditarVideo(new Frame());

				dlg.tfCodigo.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				dlg.tfTitulo.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				dlg.tfCantidad.setText(FramePrincipal.BDVideos.leerCampo((byte)'I'));
				dlg.tfGenero.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				dlg.tfClasificacion.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				dlg.tfIdioma.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				dlg.tfTextoDescriptivo.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				dlg.tfOtrosDatos.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				
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