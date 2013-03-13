package directorio

class Foto {

	String titulo
	String descripcion
	byte[] imagen
	Tienda tienda
	
    static constraints = {
		titulo(blank: false)
		descripcion(blank: false)
    }
	
	String toString() {
		titulo
	}
}
