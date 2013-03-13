package directorio

class TiendaController {
	
	def scaffold = true
	
	static navigation = [
		[title: 'Tiendas', order: 5]
	]
	
	def centroComercial = {
		def centroComercial = CentroComercial.findById(params.id)
		[ centroComercial: centroComercial, tiendas: Tienda.findAllByCentroComercial(centroComercial) ]
	}
	
	def categoria = {
		def categoria = Categoria.findById(params.id)
		[ categoria: categoria, tiendas: Tienda.findAllByCategoria(categoria) ]
	}
	
	def detalles = {
		def tienda = Tienda.findById(params.id)
		[tienda: tienda, anuncios: Anuncio.findAllByTienda(tienda), fotos: Foto.findAllByTienda(tienda)]
	}
}
