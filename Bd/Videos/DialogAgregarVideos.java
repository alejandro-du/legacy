/////////////////////////////////////////////////////////////////////////////////////////////
// DialogAgregarVideos.java
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
// DialogAgregarVideos
//
// Define la clase para el manejo de las ventanas agregar videos.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogAgregarVideos extends Dialog implements ActionListener
{
	TextField tfCodigo           = new TextField();
	TextField tfTitulo           = new TextField();
	TextField tfCantidad         = new TextField();
	TextField tfGenero           = new TextField();
	TextField tfClasificacion    = new TextField();
	TextField tfIdioma           = new TextField();
	TextField tfTextoDescriptivo = new TextField();
	TextField tfOtrosDatos       = new TextField();
	
	Button BotonAgregar = new Button("Agregar");
	Button BotonCerrar  = new Button("Cerrar");
	

	DialogAgregarVideos(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Agregar Video", true);

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
		add(new Label("Título:"));
		add(tfTitulo);
		add(new Label("Cantidad:"));
		add(tfCantidad);
		add(new Label("Género:"));
		add(tfGenero);
		add(new Label("Clasificación:"));
		add(tfClasificacion);
		add(new Label("Idioma:"));
		add(tfIdioma);
		add(new Label("Texto descriptivo:"));
		add(tfTextoDescriptivo);
		add(new Label("Otros datos:"));
		add(tfOtrosDatos);
		
		add(BotonAgregar);
		add(BotonCerrar);
		
		BotonAgregar.addActionListener(this);
		BotonCerrar.addActionListener(this);
	}
	
	
	public void paint (Graphics g) {
		tfCodigo.requestFocus();
	}
	
	
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		if(str.equals("Cerrar")) {
			dispose(); // cerrar el cuadro
		}
		
		else if(str.equals("Agregar")) {
			
			if(tfCodigo.getText().length() <= 0) {
				new MsgBox("Debe introducir el código.", new Frame());
				return;
			}
			
			// verificar que el código no halla sido usado
			boolean b[] = new boolean[8];
			String[] strCampos = new String[8];
			
			strCampos[0] = new String(tfCodigo.getText());
			strCampos[1] = new String();
			strCampos[2] = new String();
			strCampos[3] = new String();
			strCampos[4] = new String();
			strCampos[5] = new String();
			strCampos[6] = new String();
			strCampos[7] = new String();
			
			b[0] = true;
			b[1] = false;
			b[2] = false;
			b[3] = false;
			b[4] = false;
			b[5] = false;
			b[6] = false;
			b[7] = false;
			
			if(FramePrincipal.BDVideos.buscarRegistro(b, strCampos)) {
				new MsgBox("El video código <" + strCampos[0] + "> ya existe en la base de datos.", new Frame());
				tfCodigo.setText("");
				repaint();
				return;
			}
			
			int nCantidad;
			try {
				nCantidad = Integer.parseInt(tfCantidad.getText());
			}
			catch(NumberFormatException e) {
				new MsgBox("Debe introducir un valor entero en el campo <cantidad>.", new Frame());
				
				tfCantidad.setText("");
				tfCantidad.requestFocus();
				return;
			}

			FramePrincipal.BDVideos.escribirCampo(tfCodigo.getText());
			FramePrincipal.BDVideos.escribirCampo(tfTitulo.getText());
			FramePrincipal.BDVideos.escribirCampo(nCantidad);
			FramePrincipal.BDVideos.escribirCampo(tfGenero.getText());
			FramePrincipal.BDVideos.escribirCampo(tfClasificacion.getText());
			FramePrincipal.BDVideos.escribirCampo(tfIdioma.getText());
			FramePrincipal.BDVideos.escribirCampo(tfTextoDescriptivo.getText());
			FramePrincipal.BDVideos.escribirCampo(tfOtrosDatos.getText());
			
			new MsgBox("La información ha sido añadida a la base de datos.", new Frame());
			
			tfCodigo.setText("");
			tfTitulo.setText("");
			tfCantidad.setText("");
			tfGenero.setText("");
			tfClasificacion.setText("");
			tfIdioma.setText("");
			tfTextoDescriptivo.setText("");
			tfOtrosDatos.setText("");
			
			repaint();
		}
	}
}