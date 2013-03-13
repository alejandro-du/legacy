package directorio

class Ciudad {
	
	String nombre

    static constraints = {
		nombre(blank: false, unique: true)
    }
	
	String toString() {
		nombre
	}
}
