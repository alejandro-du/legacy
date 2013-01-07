/////////////////////////////////////////////////////////////////////////////////////////////
// DialogEditarVideo.java
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
// DialogEditarVideo
//
// Define la clase para el manejo de las ventanas editar Video.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogEditarVideo extends Dialog implements ActionListener
{
	public TextField tfCodigo           = new TextField();
	public TextField tfTitulo           = new TextField();
	public TextField tfCantidad         = new TextField();
	public TextField tfGenero           = new TextField();
	public TextField tfClasificacion    = new TextField();
	public TextField tfIdioma           = new TextField();
	public TextField tfTextoDescriptivo = new TextField();
	public TextField tfOtrosDatos       = new TextField();
	
	Button BotonCerrar              = new Button("Cerrar");
	Button BotonSiguiente           = new Button(">>");
	Button BotonBuscarPorCodigo     = new Button("Buscar por código");
	Button BotonGuardarModificacion = new Button("Guardar modificación");

	String[] strCampos = new String[8];
	
	boolean bRegEncontrado = false;


	DialogEditarVideo(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Editar Video", true);

		// añadir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 2, 0, 10));
		setSize(400, 320);
		
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
			dispose();
		}
		
		else if(str.equals(">>")) { // ir al siguiente registro
			if(bRegEncontrado) {
				
				byte eliminado;

				do {
				
					String strCod;
					strCod = FramePrincipal.BDVideos.leerCampo((byte)'S');
					if(strCod == null) {
						new MsgBox("No se encontraron más registros.", new Frame());
						return;
					}
				
					strCampos[0] = new String(strCod);
					strCampos[1] = new String(FramePrincipal.BDVideos.leerCampo((byte)'S'));
					strCampos[2] = new String(FramePrincipal.BDVideos.leerCampo((byte)'I'));
					strCampos[3] = new String(FramePrincipal.BDVideos.leerCampo((byte)'S'));
					strCampos[4] = new String(FramePrincipal.BDVideos.leerCampo((byte)'S'));
					strCampos[5] = new String(FramePrincipal.BDVideos.leerCampo((byte)'S'));
					strCampos[6] = new String(FramePrincipal.BDVideos.leerCampo((byte)'S'));
					strCampos[7] = new String(FramePrincipal.BDVideos.leerCampo((byte)'S'));
					
					eliminado = FramePrincipal.BDVideos.leerByteEliminacion();
				
					if(eliminado != 1) {
						tfCodigo.setText(strCampos[0]);
						tfTitulo.setText(strCampos[1]);
						tfCantidad.setText(strCampos[2]);
						tfGenero.setText(strCampos[3]);
						tfClasificacion.setText(strCampos[4]);
						tfIdioma.setText(strCampos[5]);
						tfTextoDescriptivo.setText(strCampos[6]);
						tfOtrosDatos.setText(strCampos[7]);
					}
					
				} while (eliminado == 1);

			}
			else
				new MsgBox("Primero debe buscar un registro válido.", new Frame());
		}
		
		else if(str.equals("Buscar por código")) {
			boolean b[] = new boolean[8];
			
			strCampos[0] = new String(tfCodigo.getText());
			strCampos[1] = new String();
			strCampos[2] = new String(); // cantidad
			strCampos[3] = new String();
			strCampos[4] = new String();
			strCampos[5] = new String();
			strCampos[6] = new String(); // texto descriptivo
			strCampos[7] = new String();
			
			b[0] = true;
			b[1] = false;
			b[2] = false;
			b[3] = false;
			b[4] = false;
			b[5] = false;
			b[6] = false;
			b[7] = false;
			
			if(!FramePrincipal.BDVideos.buscarRegistro(b, strCampos)) {
				new MsgBox("No se encontró el registro con el código solicitado.", new Frame());
				bRegEncontrado = false;
			}
			else {
				tfCodigo.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				tfTitulo.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				tfCantidad.setText(FramePrincipal.BDVideos.leerCampo((byte)'I'));
				tfGenero.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				tfClasificacion.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				tfIdioma.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				tfTextoDescriptivo.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				tfOtrosDatos.setText(FramePrincipal.BDVideos.leerCampo((byte)'S'));
				
				FramePrincipal.BDVideos.leerByteEliminacion();
				
				// actualizar los valores del reg a editar
				strCampos[0] = new String(tfCodigo.getText());
				strCampos[1] = new String(tfTitulo.getText());
				strCampos[2] = new String(tfCantidad.getText());
				strCampos[3] = new String(tfGenero.getText());
				strCampos[4] = new String(tfClasificacion.getText());
				strCampos[5] = new String(tfIdioma.getText());
				strCampos[6] = new String(tfTextoDescriptivo.getText());
				strCampos[7] = new String(tfOtrosDatos.getText());
				
				bRegEncontrado = true;
			}
			
			repaint();
		}
		
		else if(str.equals("Guardar modificación")) {
			if(bRegEncontrado) {
				
				boolean b[] = new boolean[8];
			
				// realizar todas las comparaciones
				for(int i = 0; i < 8; i++)
					b[i] = true;
				
				if(!FramePrincipal.BDVideos.buscarRegistro(b, strCampos)) {
					new MsgBox("Error al intentar buscar el registro a editar.", new Frame());
				}
				else { // se pudo encontrar el registro
					if(
					   new MsgBox("¿Desea guardar la modificación hecha a este registro?",
								  FramePrincipal.TITULO_APLICACION,
								  new Frame(), true).bResultado
					  )
					{
						// eliminar el actual
						FramePrincipal.BDVideos.eliminarRegistro();
						
						//escribir el nuevo:
						FramePrincipal.BDVideos.escribirCampo(tfCodigo.getText());
						FramePrincipal.BDVideos.escribirCampo(tfTitulo.getText());
						FramePrincipal.BDVideos.escribirCampo(Integer.parseInt(tfCantidad.getText()));
						FramePrincipal.BDVideos.escribirCampo(tfGenero.getText());
						FramePrincipal.BDVideos.escribirCampo(tfClasificacion.getText());
						FramePrincipal.BDVideos.escribirCampo(tfIdioma.getText());
						FramePrincipal.BDVideos.escribirCampo(tfTextoDescriptivo.getText());
						FramePrincipal.BDVideos.escribirCampo(tfOtrosDatos.getText());
						
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