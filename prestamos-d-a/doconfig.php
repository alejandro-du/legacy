<?php
	session_start();
?>

<html>

<head>
	<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
	<title>Pr�stamos Duarte Avena�o</title>
</head>

<body>
<font face="arial">

<h1>Pr�stamos Duarte Avenda�o</h1>
	<hr>
	<br>
	<br>

	<?php
	
		if(session_id() == $_SESSION['session_id'])
		{
			$old_user = $_SESSION['valid_user'];
			$new_user =$_POST['new_user'];
			$old_password = $_POST['old_password'];
			$new_password1 = $_POST['new_password1'];
			$new_password2 = $_POST['new_password2'];
				
			if($new_password1 != $new_password2)
			{
				echo "Las nuevas contrase�as deben ser iguales.<br><br>";
			}
			else if(strlen($new_password2) < 3)
			{
				echo "La nueva contrase�a debe tener al menos 3 caracteres.<br><br>";
			}
			
			else {
				require("config/db_config.php");
		
				$db_connection = mysql_connect($db_host, $db_user, $db_password);
				
				if(!$db_connection)
					die("Error de conexi�n con la base de datos");
				
				if(!@mysql_select_db($db_name, $db_connection))
					die("Error al seleccionar la base de datos.");
					
				$query = "SELECT * FROM Users WHERE name = '$old_user' AND password=password('$old_password')";
				
				$result = mysql_query($query, $db_connection);
			
				if(!$result)
					die("Error en la consulta a la base de datos.");
				
				if(mysql_num_rows($result) > 0) // valid user
				{
					$query = "UPDATE Users SET name = '$new_user', password = password('$new_password2') WHERE name='$old_user' AND password = password('$old_password')";
					
					$result = mysql_query($query, $db_connection);
				
					if(!$result)
						die("Error en la actualizaci�n de la base de datos.");
						
					$_SESSION['valid_user'] = $new_user;
						
					echo "Informaci�n actualizada.<br><br>";
					
				}
				else
				{
					echo "Contrase�a incorrecta.<br><br>";
				}
			}

			
			echo "<a href='main.php'>Volver al men� principal</a><br><br>";
			echo "<a href='logout.php'>Cerrar sesi�n</a>";
		}
		else
		{
			session_unset();
			session_destroy();
			echo "Debe ingresar al sistema.<br><br>";
			echo "<a href='index.php'>Inicio</a>";
			exit;
		}
		
	?>

</font>
</body>

</html>