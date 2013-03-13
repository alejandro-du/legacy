package directorio

class Categoria {
	
	String nombre
	byte[] imagen
	String html

    static constraints = {
		nombre(blank: false, unique: true)
		imagen(nullable: true)
		html(maxLength: 5000)
    }
	
	String toString() {
		nombre
	}
}
