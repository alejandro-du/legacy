/////////////////////////////////////////////////////////////////////////////////////////////
// DialogListadoClientes.java
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
// DialogListadoClientes
//
// Define la clase para el manejo de la ventana listado de clientes.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class DialogListadoClientes extends Dialog implements ActionListener
{
	Button BotonSiguiente = new Button("Siguiente");
	Button BotonAnterior  = new Button("Anterior");
	Label  lbReg[];
	
	int nRegActual;
	int nFilas;
	

	DialogListadoClientes(Frame parent) {
		super(parent, FramePrincipal.TITULO_APLICACION + " - Listado de registros de clientes", true);

		// añadir un auditor para la ventana
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		
		setLayout(new GridLayout(0, 1)); // cuadrícula
		
		Toolkit tk = parent.getToolkit();
		Dimension d = tk.getScreenSize(); // dimensiones de la pantalla
		setSize(d); // cuadrar el tamaño
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
		
		if(FramePrincipal.BDClientes.obtNumeroRegistros() == 0) {
			lbReg[0].setText("<archivo vacío>");
			
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
			if(nRegActual > FramePrincipal.BDClientes.obtNumeroRegistros()) {
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
		
		if(!FramePrincipal.BDClientes.irAlRegistro(nRegActual))
			return;
		
		for(int iFila = 0; iFila < nFilas; iFila++) { // cada fila
			
			String strReg = new String("");
			
			lbReg[iFila].setText("");
			
			
			for(int nCam = 0; nCam < FramePrincipal.BDClientes.obtCamposPorRegistro(); nCam++) { // cada campo
				
				String str = FramePrincipal.BDClientes.leerCampo((byte)'S');
				
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
					
				// añadir las primeras 13 letras del campo a la cadena
				for(; i < 13; i++) {
					strReg += str.charAt(i);
				}

				strReg += " ";
			}

			if(FramePrincipal.BDClientes.leerByteEliminacion() == 1)
				iFila--;
			
			else
				lbReg[iFila].setText(strReg);
		}
	}
}