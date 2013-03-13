package directorio

class Anuncio {
	
	String titulo
	Date fecha
	String texto
	Tienda tienda
	byte[] imagen

    static constraints = {
		titulo(blank: false)
		texto(blank: false)
    }
	
	String toString() {
		titulo
	}
}
