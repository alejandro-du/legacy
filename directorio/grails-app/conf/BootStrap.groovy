import directorio.Anuncio;
import directorio.Articulo;
import directorio.Categoria;
import directorio.CentroComercial;
import directorio.Ciudad;
import directorio.Foto;
import directorio.Tienda;
import directorio.Usuario;

class BootStrap {

    def init = { servletContext ->
		
		Random random = new Random()
		def minCategorias = 10
		def maxCategorias = 10
		def minCiudades = 1
		def maxCiudades = 1
		def minCentrosComerciales = 10
		def maxCentrosComerciales = 10
		def minTiendas = 0
		def maxTiendas = 3
		def minAnuncios = 0
		def maxAnuncios = 3
		
		def numCategorias = random.nextInt(maxCategorias - minCategorias + 1) + minCategorias
		def numCiudades = random.nextInt(maxCiudades - minCiudades + 1) + minCiudades
		
		(1..numCategorias).each { new Categoria(nombre: "Categoría ${it}", html: "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium.").save(failOnError: true) }
			
		(1..numCiudades).each {
		
			def numCentrosComerciales = random.nextInt(maxCentrosComerciales - minCentrosComerciales + 1) + minCentrosComerciales
			
			def ciudad = new Ciudad(nombre: "Ciudad ${it}");
			ciudad.save(failOnError: true)
			
			def usu = new Usuario(login: "usuario${it}", password: "usuario${it}", email: "test${it}@test.test", rol: "TIENDA")
			usu.save(failOnError: true)
			if(numCentrosComerciales > 0) {
				(1..numCentrosComerciales).each { new CentroComercial(nombre: "Centro Comercial ${it}", ciudad: ciudad, html: "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium.").save(failOnError: true) }
				
				def i = 1
				CentroComercial.list().each { cc ->
					Categoria.list().each { cat ->
						def numTiendas = random.nextInt(maxTiendas - minTiendas + 1) + minTiendas
						if(numTiendas > 0) {
							(1..numTiendas).each {
								File logoFile = new File("web-app/images/demo/logo${random.nextInt(6) + 1}.png")
								def tienda = new Tienda(nombre: "Tienda ${i++}", centroComercial:cc, categoria: cat, usuario: usu, html: "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur blandit, enim a convallis sollicitudin, lacus tellus mollis mauris, non vulputate nisi lorem sit amet nibh. Integer porta, est id rhoncus laoreet, nunc erat semper nunc, et dictum est ante eu lacus. Quisque non ligula at nisi facilisis scelerisque laoreet facilisis nisl. In auctor urna vel dolor mattis iaculis. In hac habitasse platea dictumst. Pellentesque neque magna, interdum pulvinar aliquam a, volutpat non ligula. Curabitur in purus neque. Aliquam aliquet mattis blandit. Ut aliquet vehicula eleifend. Fusce dictum dictum vehicula. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Fusce et est metus, id varius risus. Sed laoreet volutpat quam eu pellentesque. Sed id nunc sit amet ante posuere malesuada scelerisque eget mauris. Etiam ullamcorper iaculis velit et aliquet.</p><br/><p>Donec vel eros at nisl egestas congue in quis felis. Vivamus volutpat ultrices metus, vel gravida mauris scelerisque sit amet. Curabitur in dolor justo, sed faucibus mauris. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Pellentesque dolor libero, feugiat eget tempus in, ultricies a massa. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer rhoncus enim aliquet ipsum suscipit dictum placerat neque auctor. Fusce porta, ligula vitae convallis varius, metus sapien pellentesque augue, euismod tristique diam urna non quam. Praesent a lobortis nisl. Morbi euismod iaculis nulla. Cras sed leo nisl. Sed tincidunt, nunc id mollis pharetra, libero diam rutrum enim, in tempus ligula justo eget purus. Maecenas dignissim accumsan risus a auctor. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Vestibulum lorem arcu, euismod et tincidunt malesuada, malesuada at nisi. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Duis hendrerit faucibus leo, ut porttitor nunc pellentesque ac.</p><br/><p>Aenean nec lorem nec dui eleifend blandit et quis felis. In egestas rhoncus elit, et fermentum turpis mollis vel. Aenean vitae magna nulla, non aliquam nibh. Quisque euismod, eros non mollis cursus, risus massa hendrerit eros, et pulvinar leo diam rhoncus dolor. Maecenas viverra venenatis luctus. Aliquam a ligula a odio dapibus rhoncus sed ac augue. In hac habitasse platea dictumst. Duis quis nisl nec libero pretium adipiscing. Ut eu auctor enim. Sed nec tellus ac ligula porttitor tempor eu nec odio.</p><br/><p>Pellentesque metus arcu, tempor in aliquet ac, convallis sit amet libero. Aenean eu tortor libero, in pharetra neque. Donec id volutpat eros. Nam elementum, ligula eu lobortis dignissim, dui orci faucibus est, vitae gravida magna purus id nisi. Nullam enim augue, consectetur vel hendrerit ac, aliquam quis erat. Suspendisse ac magna dolor, a molestie felis. Cras dapibus magna sit amet arcu suscipit laoreet. Etiam dictum suscipit quam vel convallis. Fusce ante enim, eleifend in sagittis dapibus, fermentum eu felis. Ut orci diam, egestas at viverra at, luctus quis metus. Duis elit ante, auctor sed placerat nec, convallis ut sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer facilisis, diam a scelerisque placerat, orci sem cursus mi, ac placerat massa arcu sit amet quam. Cras gravida dolor nisl, eu luctus erat. Phasellus mollis magna ac risus ullamcorper quis gravida massa semper. Pellentesque id lectus nec sapien condimentum pellentesque. Proin nulla quam, lacinia vel tincidunt ac, imperdiet posuere felis. Duis imperdiet sem sed mi blandit eu pretium nibh sodales. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.</p>", ubicacion: "10${it}", imagen: logoFile.getBytes())
								tienda.save(failOnError: true)
								def numAnuncios = random.nextInt(maxAnuncios - minAnuncios + 1) + minAnuncios
								if(numAnuncios > 0) {
									(1..numAnuncios).each {
										File imagenFile = new File("web-app/images/demo/imagen${random.nextInt(6) + 1}.png")
										new Anuncio(titulo: "Anuncio ${it}", fecha: new Date(), texto: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam vestibulum rhoncus quam id lobortis. Quisque ac sapien fermentum augue consequat semper in vitae erat.", tienda: tienda, imagen: imagenFile.getBytes()).save(failOnError: true)
									}
								}
								def numFotos = random.nextInt(6)
								if(numFotos > 0) {
									(1..numFotos).each {
										File fotoFile = new File("web-app/images/demo/foto${it}.jpg")
										def foto = new Foto(titulo: "Foto ${it}", descripcion: "Lorem ipsum dolor sit amet.", imagen: fotoFile.getBytes(), tienda: tienda).save(failOnError: true)
									}
								}
							}
						}
					}
				}
			}
			
			new Articulo(titulo: "Lorem ipsum dolor sit amet", fecha: new Date(), html: "<p><img src='images/demo/foto4.jpg' style='float: left; margin-right: 10px;' width='128' height='100'>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur blandit, enim a convallis sollicitudin, lacus tellus mollis mauris, non vulputate nisi lorem sit amet nibh. Integer porta, est id rhoncus laoreet, nunc erat semper nunc, et dictum est ante eu lacus. Quisque non ligula at nisi facilisis scelerisque laoreet facilisis nisl. In auctor urna vel dolor mattis iaculis. In hac habitasse platea dictumst. Pellentesque neque magna, interdum pulvinar aliquam a, volutpat non ligula. Curabitur in purus neque. Aliquam aliquet mattis blandit. Ut aliquet vehicula eleifend. Fusce dictum dictum vehicula. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Fusce et est metus, id varius risus. Sed laoreet volutpat quam eu pellentesque. Sed id nunc sit amet ante posuere malesuada scelerisque eget mauris. Etiam ullamcorper iaculis velit et aliquet.</p><br/><p>Donec vel eros at nisl egestas congue in quis felis. Vivamus volutpat ultrices metus, vel gravida mauris scelerisque sit amet. Curabitur in dolor justo, sed faucibus mauris. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Pellentesque dolor libero, feugiat eget tempus in, ultricies a massa. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer rhoncus enim aliquet ipsum suscipit dictum placerat neque auctor. Fusce porta, ligula vitae convallis varius, metus sapien pellentesque augue, euismod tristique diam urna non quam. Praesent a lobortis nisl. Morbi euismod iaculis nulla. Cras sed leo nisl. Sed tincidunt, nunc id mollis pharetra, libero diam rutrum enim, in tempus ligula justo eget purus. Maecenas dignissim accumsan risus a auctor. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Vestibulum lorem arcu, euismod et tincidunt malesuada, malesuada at nisi. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Duis hendrerit faucibus leo, ut porttitor nunc pellentesque ac.</p>", mostrar: true).save(failOnError: true)
			new Articulo(titulo: "Lorem ipsum dolor sit amet", fecha: new Date(), html: "<p><img src='images/demo/foto5.jpg' style='float: left; margin-right: 10px;' width='128' height='100'>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur blandit, enim a convallis sollicitudin, lacus tellus mollis mauris, non vulputate nisi lorem sit amet nibh. Integer porta, est id rhoncus laoreet, nunc erat semper nunc, et dictum est ante eu lacus. Quisque non ligula at nisi facilisis scelerisque laoreet facilisis nisl. In auctor urna vel dolor mattis iaculis. In hac habitasse platea dictumst. Pellentesque neque magna, interdum pulvinar aliquam a, volutpat non ligula. Curabitur in purus neque. Aliquam aliquet mattis blandit. Ut aliquet vehicula eleifend. Fusce dictum dictum vehicula. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Fusce et est metus, id varius risus. Sed laoreet volutpat quam eu pellentesque. Sed id nunc sit amet ante posuere malesuada scelerisque eget mauris. Etiam ullamcorper iaculis velit et aliquet.</p><br/><p>Donec vel eros at nisl egestas congue in quis felis. Vivamus volutpat ultrices metus, vel gravida mauris scelerisque sit amet. Curabitur in dolor justo, sed faucibus mauris. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Pellentesque dolor libero, feugiat eget tempus in, ultricies a massa. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer rhoncus enim aliquet ipsum suscipit dictum placerat neque auctor. Fusce porta, ligula vitae convallis varius, metus sapien pellentesque augue, euismod tristique diam urna non quam. Praesent a lobortis nisl. Morbi euismod iaculis nulla. Cras sed leo nisl. Sed tincidunt, nunc id mollis pharetra, libero diam rutrum enim, in tempus ligula justo eget purus. Maecenas dignissim accumsan risus a auctor. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Vestibulum lorem arcu, euismod et tincidunt malesuada, malesuada at nisi. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Duis hendrerit faucibus leo, ut porttitor nunc pellentesque ac.</p>", mostrar: true).save(failOnError: true)
			new Articulo(titulo: "Lorem ipsum dolor sit amet", fecha: new Date(), html: "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur blandit, enim a convallis sollicitudin, lacus tellus mollis mauris, non vulputate nisi lorem sit amet nibh. Integer porta, est id rhoncus laoreet, nunc erat semper nunc, et dictum est ante eu lacus. Quisque non ligula at nisi facilisis scelerisque laoreet facilisis nisl. In auctor urna vel dolor mattis iaculis. In hac habitasse platea dictumst. Pellentesque neque magna, interdum pulvinar aliquam a, volutpat non ligula. Curabitur in purus neque. Aliquam aliquet mattis blandit. Ut aliquet vehicula eleifend. Fusce dictum dictum vehicula. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Fusce et est metus, id varius risus. Sed laoreet volutpat quam eu pellentesque. Sed id nunc sit amet ante posuere malesuada scelerisque eget mauris. Etiam ullamcorper iaculis velit et aliquet.</p><br/><p><img src='images/demo/foto2.jpg' style='float: right; margin-left: 10px;' width='230' height='180'>Donec vel eros at nisl egestas congue in quis felis. Vivamus volutpat ultrices metus, vel gravida mauris scelerisque sit amet. Curabitur in dolor justo, sed faucibus mauris. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Pellentesque dolor libero, feugiat eget tempus in, ultricies a massa. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer rhoncus enim aliquet ipsum suscipit dictum placerat neque auctor. Fusce porta, ligula vitae convallis varius, metus sapien pellentesque augue, euismod tristique diam urna non quam. Praesent a lobortis nisl. Morbi euismod iaculis nulla. Cras sed leo nisl. Sed tincidunt, nunc id mollis pharetra, libero diam rutrum enim, in tempus ligula justo eget purus. Maecenas dignissim accumsan risus a auctor. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Vestibulum lorem arcu, euismod et tincidunt malesuada, malesuada at nisi. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Duis hendrerit faucibus leo, ut porttitor nunc pellentesque ac.</p><br/><p>Aenean nec lorem nec dui eleifend blandit et quis felis. In egestas rhoncus elit, et fermentum turpis mollis vel. Aenean vitae magna nulla, non aliquam nibh. Quisque euismod, eros non mollis cursus, risus massa hendrerit eros, et pulvinar leo diam rhoncus dolor. Maecenas viverra venenatis luctus. Aliquam a ligula a odio dapibus rhoncus sed ac augue. In hac habitasse platea dictumst. Duis quis nisl nec libero pretium adipiscing. Ut eu auctor enim. Sed nec tellus ac ligula porttitor tempor eu nec odio.</p>", mostrar: true).save(failOnError: true)
		}

    }
	
    def destroy = {
    }
	
}
