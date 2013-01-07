/////////////////////////////////////////////////////////////////////////////////////////////
// MsgBox.java
/////////////////////////////////////////////////////////////////////////////////////////////



import java.awt.*;
import java.awt.event.*;



/////////////////////////////////////////////////////////////////////////////////////////////
//
// MsgBox
//
// Define la clase para el manejo de mensajes sencillos en un cuadro de diálogo.
// Incluye varios constructores para crear diferentes tipos de cuadros de mensaje.
// Puede crear un cuadro con un solo botón o con dos botones.
// Puede crear un cuadro con un mensaje o dos.
//
/////////////////////////////////////////////////////////////////////////////////////////////
class MsgBox extends Dialog implements ActionListener
{
	public boolean bResultado = false;

	// botones del cuadro
	Button BotonAceptar = new Button("Aceptar");
	Button BotonNo = new Button("No");

	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Crea un cuadro con un titulo predeterminado.
	/////////////////////////////////////////////////////////////////////////////////////////
    MsgBox(String msg, Frame parent) {
		super(parent, msg, true);
		prepararCuadro("Atención", msg, true);
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Crea un cuadro con un titulo y mensaje dados.
	/////////////////////////////////////////////////////////////////////////////////////////
    MsgBox(String msg, String titulo, Frame parent) {
		super(parent, msg, true);
		prepararCuadro(titulo, msg, true);
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Crea un cuadro con dos estiquetas.
	/////////////////////////////////////////////////////////////////////////////////////////
    MsgBox(String msg1, String msg2,String titulo, Frame parent) {
		super(parent, msg2, true);
		
		Label lblMsg1 = new Label(msg1);
		lblMsg1.setAlignment(Label.CENTER); // el mensaje va centrado en el cuadro
		add("North", lblMsg1);
		
		prepararCuadro(titulo, msg2, false);
		
		// fijar el tamaño adecuado:
		Dimension tam = getSize();
		tam.height -= 10;
		setSize(tam);
		
		setVisible(true);
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Crea un cuadro con dos botones: Si, No.
	/////////////////////////////////////////////////////////////////////////////////////////
    MsgBox(String msg, String titulo, Frame parent, boolean bDosBotones) {
		super(parent, msg, true);
		
		prepararCuadro(titulo, msg, false);
		
		if(bDosBotones) {
			
			removeAll();
			setLayout(new GridLayout(0, 1));
			
			// fijar el tamaño adecuado:
			Dimension tam = getSize();
			tam.height -= 10;
			setSize(tam);
			
			// cambiar la etiqueta del boton Aceptar
			BotonAceptar.setLabel("Si");

			// agragar los controles
			Label lblMsg = new Label(msg);
			lblMsg.setAlignment(Label.CENTER); // el mensaje va centrado en el cuadro
			add(lblMsg);
			add(BotonAceptar);
			add(BotonNo);
			
			BotonNo.addActionListener(this);
		}
		
		setVisible(true);
	}
	
	
	public void paint (Graphics g) {
		BotonNo.requestFocus();
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Manejador de los botones.
	/////////////////////////////////////////////////////////////////////////////////////////
	public void actionPerformed(ActionEvent ae) {
		String str = ae.getActionCommand();
		if(str.equals("Aceptar")) {
			dispose(); // cerrar el cuadro
			bResultado = true;
		}

		else if(str.equals("Si")) {
			dispose(); // cerrar el cuadro
			bResultado = true;
		}

		else if(str.equals("No")) {
			dispose(); // cerrar el cuadro
			bResultado = false;
		}
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Configura el cuadro: tamaño, posición, controles.
	/////////////////////////////////////////////////////////////////////////////////////////
	void prepararCuadro(String titulo, String msg, boolean bVisible) {
		
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		
		setTitle(titulo); // establecer el título
		
		setForeground(Color.black);
		setBackground(Color.gray);
		
		setFont(new Font("Helvetica", Font.PLAIN, 12));
		FontMetrics fm = getFontMetrics(getFont());
		
		int ancho = 50 + fm.stringWidth(msg);
		
		setSize(ancho, 110); // fijar el tamaño adecuado
		setResizable(false);
		
		Toolkit tk = getToolkit();		
		Dimension d = tk.getScreenSize(); // dimensiones de la pantalla
		
		// mover al centro de la pantalla
		setLocation((d.width - this.getSize().width) / 2,
					 (d.height - this.getSize().height) / 2);
		
		// agragar los controles
		Label lblMsg = new Label(msg);
		lblMsg.setAlignment(Label.CENTER); // el mensaje va centrado en el cuadro
		add("Center", lblMsg);
		add("South", BotonAceptar);
		
		BotonAceptar.addActionListener(this);
		
		bResultado = false;

		setVisible(bVisible); // visualizar		
	}
}