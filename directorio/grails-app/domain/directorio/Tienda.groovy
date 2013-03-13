package directorio

class Tienda {
	
	String nombre
	String ubicacion
	byte[] imagen
	String html
	CentroComercial centroComercial
	Categoria categoria
	Usuario usuario

    static constraints = {
		nombre(blank: false)
		imagen(nullable: true)
		html(maxLength: 5000)
    }
	
	String toString() {
		nombre
	}

	def cuentaAnuncios = {
		Anuncio.countByTienda(this)
	}
}
