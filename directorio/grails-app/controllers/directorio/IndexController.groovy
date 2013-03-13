package directorio

class IndexController {
	
	static navigation = [
		[title: 'Inicio', order: 1]
	]

    def index = {
		[articulos: Articulo.findAllByMostrar(true)]
	}
	
	private imagen(byte[] bytes) {
		response.setHeader('Content-length', bytes.length as String)
		response.contentType = 'image'
		response.outputStream << bytes
		response.outputStream.flush()
	}
	
	def imagenTienda = {
		imagen(Tienda.findById(params.id).imagen)
	}
	
	def imagenFoto = {
		imagen(Foto.findById(params.id).imagen)
	}
	
	def imagenAnuncio = {
		imagen(Anuncio.findById(params.id).imagen)
	}
	
}
