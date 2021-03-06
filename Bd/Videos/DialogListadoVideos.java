/////////////////////////////////////////////////////////////////////////////////////////////
// DialogListadoVideos.java
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
// DialogListadoVideos
//
// Define la clase para el manejo de la ventana listado de Videos.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogListadoVideos extends Dialog implements ActionListener
{
	Button BotonSiguiente = new Button("Siguiente");
	Button BotonAnterior  = new Button("Anterior");
	Label  lbReg[];
	
	int nRegActual;
	int nFilas;
	

	DialogListadoVideos(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Listado de registros de videos", true);

		// a�adir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 1)); // cuadr�cula
		
		Toolkit tk = parent.getToolkit();
		Dimension d = tk.getScreenSize(); // dimensiones de la pantalla
		setSize(d); // cuadrar el tama�o
		setResizable(false);
		
		// agregar los controles:
		
		nFilas = d.height / 20;
		lbReg = new Label[nFilas];
		nRegActual = 0;
		
		for(int  i = 0; i < nFilas; i++) { // crear cada control
			lbReg[i] = new Label();
			lbReg[i].setFont(new Font("Courier", Font.PLAIN, 12));
			add(lbReg[i]);
		}

		add(BotonAnterior);
		add(BotonSiguiente);
		
		if(FramePrincipal.BDVideos.obtNumeroRegistros() == 0) {
			lbReg[0].setText("<archivo vac�o>");
			
			BotonSiguiente.setEnabled(false);
			BotonAnterior.setEnabled(false);
		}
		else
			actualizar();
		
		// agregar auditores:
		BotonSiguiente.addActionListener(this);
		BotonAnterior.addActionListener(this);
	}
	
	
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		if(str.equals("Siguiente")) {
			nRegActual += nFilas;
			if(nRegActual > FramePrincipal.BDVideos.obtNumeroRegistros()) {
				nRegActual -= nFilas;
			}
			else
				actualizar();
		}
		
		else if(str.equals("Anterior")) {
			nRegActual -= nFilas;
			if(nRegActual < 0) {
				nRegActual = 0;
			}
			else
				actualizar();
		}
		
	}
	
	
	private void actualizar() {
		
		if(!FramePrincipal.BDVideos.irAlRegistro(nRegActual))
			return;
		
		byte descCampo[] = { (byte)'S',
							 (byte)'S',
							 (byte)'I',
							 (byte)'S',
							 (byte)'S',
							 (byte)'S',
							 (byte)'S',
							 (byte)'S' };
		
		for(int iFila = 0; iFila < nFilas; iFila++) { // cada fila
			
			String strReg = new String("");
			
			lbReg[iFila].setText("");
			
			for(int nCam = 0; nCam < FramePrincipal.BDVideos.obtCamposPorRegistro(); nCam++) { // cada campo
				
				String str = FramePrincipal.BDVideos.leerCampo(descCampo[nCam]);
				
				if(str == null) {
					lbReg[iFila].setText("");
					continue;
				}
				
				int nLongitud = str.length();
				int i;
				// completar la cadena a 13 caracteres si es necesario
				for(i = 0; i  < (13 - nLongitud); i++) { // cada caracter a agragar
					str += ' ';
					strReg += str.charAt(i);
				}
					
				// a�adir las primeras 13 letras del campo a la cadena
				for(; i < 13; i++) {
					strReg += str.charAt(i);
				}

				strReg += " ";
			}

			if(FramePrincipal.BDVideos.leerByteEliminacion() == 1)
				iFila--;
			
			else			
				lbReg[iFila].setText(strReg);
		}
	}
}