import directorio.Categoria;
import directorio.CentroComercial;
import directorio.Ciudad;


class AppFilters {
	
	def filters = {
		cargarMenu(controller: '*', action: '*') {
			before = {
				if(!session["centrosComerciales"]) {
					session["centrosComerciales"] = CentroComercial.findAllByCiudad(Ciudad.findById(1));
				}
				if(!session["categorias"]) {
					session["categorias"] = Categoria.list();
				}
			}
		}
	}

}
