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
			echo "<form method='POST' action='doconfig.php'>";
			echo "	<table>";
			echo "	<tr>";
			echo "		<td>Nuevo nombre de usuario:</td>";
			echo "		<td><input type='text' name='new_user' value='" . $_SESSION['valid_user'] . "'></td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "		<td>Contrase�a actual:</td>";
			echo "		<td><input type='password' name='old_password'></td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "		<td>Contrase�a nueva:</td>";
			echo "		<td><input type='password' name='new_password1'></td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "		<td>Contrase�a nueva:</td>";
			echo "		<td><input type='password' name='new_password2'></td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "		<td></td>";
			echo "		<td><input type='submit' value='Realizar cambios'></td>";
			echo "	</tr>";
			echo "	</table>";
			echo "</form>";
			echo "<a href='main.php'>Cancelar y volver al men� principal</a><br><br>";
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