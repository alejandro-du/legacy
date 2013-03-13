package directorio

class Articulo {
	
	String titulo
	String html
	boolean mostrar

    static constraints = {
		titulo(blank: false)
		html(blank: false, maxLength: 5000)
    }
}
