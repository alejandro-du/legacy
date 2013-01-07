/////////////////////////////////////////////////////////////////////////////////////////////
// BD1.java
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
//
// Autor: J. Alejandro Duarte Avendaño.
//        jaal@yahoo.com
//
// Junio 2003.
//
/////////////////////////////////////////////////////////////////////////////////////////////



import java.io.*;



/////////////////////////////////////////////////////////////////////////////////////////////
//
// EL FORMATO BD1. (Formato propio de la aplicación).
//
// Características:
// Es un formato sencillo para bases de datos basadas en tabla.
// La manipulación de los registros es fácil.
// No es muy rápida pero no consume mucha memoria RAM.
// Puede administrar un número de registros muy grande limitado sólo por el espacio en disco.
// Realiza la eliminación de registros con copias de seguridad: cuando se elimina un registro
// no se hace fisicamente sino hasta que se llama al método Inicializar siempre y cuando se
// encuentren más de 100 registros para eliminar.
// Antes de eliminar registros fisicamente se hace una copia de seguridad en un archivo con
// extensión "BAK".
//
// Su estructura es la siguiente:
//
//     - Cabecera:
//
//         3 bytes        : Cadena "BD1" para identificar el tipo de archivo.
//         4 bytes (int)  : Valor entero con el número de registros del archivo.
//         4 bytes        : # de registros eliminados.
//         2 bytes (short): Número de campos por registro.
//         x bytes        : Descripción de campos (vea a continuación).
//         x bytes        : Registros.
//
//     - Descripción de campos:
//
//         1 byte: tipo de dato: "I" entero, "S" cadena, "D" fecha.
//                 Describe la estructura de cada campo de los registros.
//
//     - Registros:
//
//         Si es "I": 4 bytes son un entero con el dato.
//         Si es "S": 2 bytes indican la longitud de la cadena y los
//         siguientes bytes son la cadena caracter a caracter.
//         Si es "D": 3 bytes indican la fecha en formato Día Mes Año, año
//         desde 2000 (fallará en el año 2256).
//         Al final del registro un byte indica si se ha eliminado el registro: si el valor
//         es 1, se debe eliminar.
//
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
//
// BD1
//
// Define la clase para el manejo de archivos BD1.
//
/////////////////////////////////////////////////////////////////////////////////////////////
public class BD1
{
	String strArchivo; // nombre del archivo
	String strExtArchivo; // extención del archivo

	protected RandomAccessFile file; // manejador del archivo
	
	protected int nRegistros;              // # de registros hábiles del archivo
	protected int nCamposPorRegistro;      // # de campos que contiene cada registro
	protected int nSiguienteCampo = 0;     // # del campo dentro del registro a escribir
	protected byte descripcionCampo[];     // tipos de datos para los campos
	protected int nRegistrosEliminados;    // # de registros eliminados
	private String strCampoTemp;
	
	BD1() {
		nRegistros = -1; // no se ha cargado ningún archivo
		nRegistrosEliminados = -1;
		nCamposPorRegistro = 0;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Crea un archivo BD1 sin registros.
	/////////////////////////////////////////////////////////////////////////////////////////
	public static boolean nuevo(String str, int nCPR, byte descCampos[]) {
		RandomAccessFile f; // manejador del archivo
		File archivo = new File(str); // archivo a crear
		
		archivo.delete(); // eliminarlo
			
		byte buffer[] = {(byte)'B', (byte)'D', (byte)'1'}; // ID del archivo

		// crear
		try {
			f = new RandomAccessFile(archivo, "rw");
		}
		catch (IOException e) {
			return false;
		}
		
		// escribir datos
		try {
			
			f.write(buffer); // "BD1"
			f.writeInt(0);   // número de registros
			f.writeInt(0);   // número de registros eliminados
			f.writeShort(nCPR); // campos por registro
			for(int i = 0; i < nCPR; i++) { // descripcion de campos
				f.writeByte(descCampos[i]);
			}
			
			f.close(); // cerrar el archivo
		}
		catch (IOException e) {
			return false;
		}
		
		return true;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Carga el archivo especificado y prepara el objeto.
	/////////////////////////////////////////////////////////////////////////////////////////
	public boolean inicializar(String str, String strExt) {
		strArchivo = new String(str); // inicializar dato miembro
		strExtArchivo = new String(strExt); // inicializar dato miembro

		String strBD1;
		byte buffer[] = new byte[3];
		
		// abrir el archivo
		try {
			file = new RandomAccessFile(str + "." + strExt, "rw");
		}
		catch (IOException e) {
			return false;
		}
		
		// leer la cabecera
		try {
			
			file.read(buffer); // "BD1"
			
			// comprobar "BD1":
			strBD1 = new String(buffer);
			if(!strBD1.equals("BD1")) // el archivo es inválido
				return false;
			
			nRegistros = file.readInt(); // leer # de registros del archivo
			nRegistrosEliminados = file.readInt(); // leer # de registros eliminados
			nCamposPorRegistro = file.readShort(); // leer # de campos por registro
			descripcionCampo = new byte[nCamposPorRegistro]; // leer descripción de registro
			
			// obtener la descripción de campos
			for(int i = 0; i < nCamposPorRegistro; i++) { // cada campo
				descripcionCampo[i] = file.readByte(); // leer el byte descriptor
			}
			
			// verificar registros eliminados
			if(nRegistrosEliminados >= 100) {
				
				// crear el archivo temporal
				if(!nuevo(strArchivo + ".TMP", nCamposPorRegistro, descripcionCampo))
					return false;
				
				// abrirlo
				RandomAccessFile fTemp = new RandomAccessFile(strArchivo + ".TMP", "rw");
				
				fTemp.seek(fTemp.length()); // ir al final
				
				for(int i = 0; i < nRegistros; i++) { // cada registro
					
					String strBuffer = new String("");
					
					for(int nCam = 0; nCam < nCamposPorRegistro; nCam++) { // cada campo
						// leer el campo
						if((strBuffer += obtenerCampo(descripcionCampo[nCam])) == null)
							return false;
					}
					
					// si no está eliminado escribir el registro
					if(file.readByte() != 1) { // se debe copiar?
						
						fTemp.writeBytes(strBuffer);
						fTemp.writeByte(0); // escribir byte de eliminación
						
					}
				} // for(...
				
				// actualizar contadores de registros
				nRegistros -= nRegistrosEliminados;
				nRegistrosEliminados = 0;
				
				fTemp.seek(3); // ir al inicio del # de registros
				fTemp.writeInt(nRegistros);
				
				// cerrar
				fTemp.close();
				file.close();
				
				// cambiar los nombres BD1 -> BAK, TMP -> BD1
				File fTMP = new File(strArchivo + ".TMP");
				File fBD1 = new File(strArchivo + "." + strExtArchivo);
				
				fBD1.renameTo(new File(strArchivo + ".BAK"));
				fTMP.renameTo(new File(strArchivo + "." + strExtArchivo));
				
				// inicializar el nuevo
				inicializar(strArchivo, strExtArchivo);

			} // if(...
		}
		catch (IOException e) {
			return false;
		}
		
		nSiguienteCampo = 0; // comenzar en el primer campo
		
		return true;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Escribe un campo de tipo cadena al final del archivo.
	/////////////////////////////////////////////////////////////////////////////////////////
	public boolean escribirCampo(String strCadena) {
		
		short nLongitud = (short)strCadena.length();
		byte cad[] = new byte[nLongitud];
		
		if(descripcionCampo[nSiguienteCampo] != (byte)'S')
			return false; // no coincide con la descripción de campos
		
		cad = strCadena.getBytes(); // obtener el buffer a escribir
		
		try {
			file.seek(file.length()); // ir al final del archivo
			file.writeShort(nLongitud); // número de caracteres de la cadena
			if(nLongitud > 0)
				file.write(cad);            // cadena
		}
		catch (IOException e) {
			return false;
		}
		
		if(!actualizarContadores())
			return false;

		return true;
	}
	

	/////////////////////////////////////////////////////////////////////////////////////////
	// Escribe un campo de tipo entero al final del archivo.
	/////////////////////////////////////////////////////////////////////////////////////////
	public boolean escribirCampo(int nNumero) {
		
		if(descripcionCampo[nSiguienteCampo] != (byte)'I')
			return false; // no coincide con la descripción de campos
		
		try {
			file.seek(file.length()); // ir al final del archivo
			file.writeInt(nNumero); // valor: WORD
		}
		catch (IOException e) {
			return false;
		}
		
		if(!actualizarContadores())
			return false;
		
		return true;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Escribe un campo de tipo fecha al final del archivo.
	/////////////////////////////////////////////////////////////////////////////////////////
	public boolean escribirCampo(int dia, int mes, int anyo) {

		if(descripcionCampo[nSiguienteCampo] != (byte)'D')
			return false; // no coincide con la descripción de campos
		
		try {
			file.seek(file.length()); // ir al final del archivo
			// escribir cada dato de la fecha
			file.writeByte(dia);
			file.writeByte(mes);
			file.writeByte(anyo);
		}
		catch (IOException e) {
			return false;
		}
		
		if(!actualizarContadores())
			return false;
		
		return true;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Cierra el archivo.
	/////////////////////////////////////////////////////////////////////////////////////////
	public boolean cerrar() {
		try {
			file.close();
		}
		catch (IOException e) {
			return false;
		}
		
		return true;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Busca la primera correspondencia del registro especificado.
	// bCamposABuscar[] contiene los flags de los campos a buscar.
	// strCa[] contiene las cadenas a buscar.
	/////////////////////////////////////////////////////////////////////////////////////////
	boolean buscarRegistro(boolean bCamposABuscar[], String strCa[])
	{
		int nCoincidencias = 0;     // # de coincidencias que se deben encontrar
		int nCoincidenciasActuales; // # de coincidencias encontradas en cada registro
		int nCampoActual = 0;       // # campo a comparar con el del archivo
		long nTotalBytes = 0;       // # de bytes leídos
		long nBytesUltimoReg = 0;   // bytes leidos durante la última lectura al archivo
		long offset = 0;            // en bytes: inicio del registro actual
		
		try {
			// ir a la posición inicial del primer registro
			nTotalBytes = 13 + descripcionCampo.length;
			file.seek(nTotalBytes);
				
			// obtener el # de coincidencias a buscar
			for(int i = 0; i < bCamposABuscar.length; i++) {
				if(bCamposABuscar[i] == true)
					nCoincidencias++;
			}
			
			nCoincidenciasActuales = 0;
		
			byte eliminado = 1;

			// iniciar la busqueda
			for(int nReg = 0; nReg < nRegistros; nReg++) { // cada registro
				
				offset = nTotalBytes;
				nCoincidenciasActuales = 0;
				nCampoActual = 0;

				for(int nCam = 0; nCam < nCamposPorRegistro; nCam++) { // cada campo
					
					nBytesUltimoReg = leerCampo2(descripcionCampo[nCam]);
					
					if(nBytesUltimoReg == -1) { // algún problema?
						return false; // error al leer
					}

					nTotalBytes += nBytesUltimoReg; // añadir el # de bytes leídos

					if(
					   bCamposABuscar[nCampoActual] == true && // se debe comparar?
					   strCampoTemp.equals(strCa[nCampoActual]) // son iguales?
					) {
						
						nCoincidenciasActuales++; // una coincidencia más para este registro
						
					}
					
					nCampoActual++; // pasar al siguiente campo (origen)
				}

				eliminado = file.readByte(); // byte de eliminación
				nTotalBytes ++; // agregar ese byte

				if(nCoincidenciasActuales == nCoincidencias) { // registro encontrado?

					if(eliminado == 0) { // si no está eliminado
						// colocar el puntero del archivo al inicio
						// del registro encontrado y retornar
						file.seek(offset);
						return true;
					}
				}
			}
		}
		catch (IOException e) {
			return false;
		}
		
		return false;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Elimina el siguiente registro del archivo.
	// Debe llamarse después de buscarRegistro().
	/////////////////////////////////////////////////////////////////////////////////////////
	public boolean eliminarRegistro() {
		
		// leer e ignorar todos los campos del registro para llegar al byte de eliminación
		for(int nCam = 0; nCam < nCamposPorRegistro; nCam++) { // cada campo
			if(leerCampo(descripcionCampo[nCam])== null)
				return false;
		}
		
		try {
			file.writeByte(1); // escribir el byte de eliminación
			if(!actualizarContadorEliminacion())
				return false;
		}
		catch (IOException e) {
			return false;
		}
		
		return true;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Lee un byte.
	// Debe llamarse después de leer todos los campos de un registro.
	/////////////////////////////////////////////////////////////////////////////////////////
	public byte leerByteEliminacion() {
		try {
			return file.readByte();
		}
		catch (IOException e) {
			return -1;
		}
	}
	

	/////////////////////////////////////////////////////////////////////////////////////////
	// Lee el siguiente campo del archivo.
	// Debe llamarse después de buscarRegistro().
	/////////////////////////////////////////////////////////////////////////////////////////
	public String leerCampo(byte tipo) {
		
		String strCampo = new String();
		
		try {
			if(tipo == (byte)'S') { // leer una cadena
				int longitud = file.readShort(); // leer longitud de la cadena
				byte buffer[] = new byte[longitud];
				
				file.read(buffer); // leer cadena

				strCampo = new String(buffer);
			}
			
			else if(tipo == (byte) 'I') {
				strCampo = new String("" + file.readInt());
			}

			else if(tipo == (byte) 'D') {
			}
		}
		catch (IOException e) {
			return null;
		}
		
		return strCampo;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Retorna una cadena con todo el campo: id y datos.
	/////////////////////////////////////////////////////////////////////////////////////////
	protected String obtenerCampo(byte tipo) {
		
		String strCampo = new String();
		
		try {
			if(tipo == (byte)'S') { // leer una cadena
				int longitud = file.readShort(); // leer longitud de la cadena
				byte buffer[] = new byte[longitud + 2];
				
				// retroceder 2 bytes
				file.seek(file.getFilePointer() - 2);
				
				file.read(buffer); // leer cadena

				strCampo = new String(buffer);
			}
			
			else if(tipo == (byte) 'I') {
				byte buffer[] = new byte[4];
				file.read(buffer); // leer
				strCampo = new String(buffer);
			}

			else if(tipo == (byte) 'D') {
			}
		}
		catch (IOException e) {
			return null;
		}
		
		return strCampo;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Lee el un campo tipo 'I' del archivo.
	// Debe llamarse después de buscarRegistro().
	/////////////////////////////////////////////////////////////////////////////////////////
	public int leerCampoI() {
		int i;
		
		try {
			i = file.readInt();
		}
		catch (IOException e) {
			return -999999;
		}
		
		return i;
	}
	

	private long leerCampo2(byte tipo) {
		
		long totalBytes = 0;
		
		try {
			if(tipo == (byte)'S') { // leer una cadena
				int longitud = file.readShort(); // leer longitud de la cadena
				
				totalBytes = 2;
				
				if(longitud > 0) {
				
					byte buffer[] = new byte[longitud];
				
					file.read(buffer); // leer cadena
					totalBytes += longitud;
				
					strCampoTemp = new String(buffer);
				}
				else {
					strCampoTemp = new String("");
				}
			}
			
			else if(tipo == (byte) 'I') {
				strCampoTemp = new String("" + file.readInt());
				totalBytes = 4;
			}

			else if(tipo == (byte) 'D') {
				// DEBUG: leer tipo fecha
			}
		}
		catch (IOException e) {
			return -1;
		}
		
		return totalBytes;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Retorna el número de registros del archivo.
	/////////////////////////////////////////////////////////////////////////////////////////
	public int obtNumeroRegistros() {
		return nRegistros - nRegistrosEliminados;
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////
	// Retorna el número de campos que tiene cada registro del archivo.
	/////////////////////////////////////////////////////////////////////////////////////////
	public int obtCamposPorRegistro() {
		return (int)nCamposPorRegistro;
	}
	
	
	protected boolean actualizarContadorEliminacion() {
		nRegistrosEliminados++; // se ha eliminado uno más

		try {
			file.seek(7); // ir a la posición inicial correspondiente
			file.writeInt(nRegistrosEliminados); // escribir el número de registros eliminados
			file.seek(file.length()); // ir al final del archivo
		}
		catch (IOException e) {
			return false;
		}

		return true;
	}
	
	
	protected boolean actualizarContadores() {
		
		nSiguienteCampo++; // pasar al siguiente tipo de campo
		if(nSiguienteCampo >= nCamposPorRegistro) { // se terminó un registro
			
			nSiguienteCampo = 0; // volver a comenzar un registro
			nRegistros++; // se ha escrito uno más

			try {
				file.seek(3); // ir a la posición inicial correspondiente
				file.writeInt(nRegistros); // escribir el número de registros
				file.seek(file.length()); // ir al final del archivo
				file.writeByte(0); // byte de eliminación
			}
			catch (IOException e) {
				return false;
			}
		}

		return true;
	}
	
	
	public boolean irAlRegistro(int nRegDestino) {
		try {
			
			file.seek(13 + descripcionCampo.length); // ir al inicio del primer registro
			
			String str;
			
			for(int nReg = 0; nReg < nRegDestino; nReg++) { // saltar los registros
				for(int nCam = 0; nCam < nCamposPorRegistro; nCam++) { // cada campo
					str = leerCampo(descripcionCampo[nCam]);
					if(str == null)
						return false;
				}
				
				file.readByte(); // byte de eliminación
			}
			
		}
		catch (IOException e) {
			return false;
		}
		
		return true;		
	}
}