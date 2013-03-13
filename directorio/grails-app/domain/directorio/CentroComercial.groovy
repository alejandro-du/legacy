package directorio

class CentroComercial {
	
	String nombre
	byte[] imagen
	String html
	Ciudad ciudad

    static constraints = {
		nombre(blank: false)
		imagen(nullable: true)
		html(maxLength: 5000)
    }
	
	String toString() {
		nombre
	}
}
