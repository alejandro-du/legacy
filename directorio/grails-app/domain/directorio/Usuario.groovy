package directorio

class Usuario {
	
	String login
	String password
	String email
	String rol

    static constraints = {
		login(blank: false, unique: true)
		password(blank: false)
		email(blank: false)
		rol(blank: false)
    }
	
	String toString() {
		login
	}
}
