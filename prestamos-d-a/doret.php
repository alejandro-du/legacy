<?php
	session_start();
?>

<html>

<head>
	<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
	<title>Préstamos Duarte Avenaño</title>
</head>

<body>
<font face="arial">

<h1>Préstamos Duarte Avendaño</h1>
	<hr>
	<br>
	<br>

	<?php
	
		if(session_id() == $_SESSION['session_id'])
		{
			require("config/db_config.php");
	
			$db_connection = mysql_connect($db_host, $db_user, $db_password);
			
			if(!$db_connection)
				die("Error de conexión con la base de datos");
			
			if(!@mysql_select_db($db_name, $db_connection))
				die("Error al seleccionar la base de datos.");
				
			$item_id=$_GET['item_id'];
			$return_date = strtotime($_POST["date"]);
			
			if($return_date == 0)
				$return_date = strtotime(date('d-m-Y'));
			
			$query = "UPDATE Loans SET return_date = '$return_date' WHERE auto_id = '$item_id'";
			
			$result = mysql_query($query, $db_connection);
		
			if(!$result)
				die("Error en la actualización de la base de datos.");
			
			echo "Devolución registrada.<br><br>";
			echo "<a href='main.php'>Volver al menú principal</a><br><br>";
			echo "<a href='logout.php'>Cerrar sesión</a>";
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