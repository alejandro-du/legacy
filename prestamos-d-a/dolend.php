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
			require("config/db_config.php");
	
			$db_connection = mysql_connect($db_host, $db_user, $db_password);
			
			if(!$db_connection)
				die("Error de conexion con la base de datos");
			
			if(!@mysql_select_db($db_name, $db_connection))
				die("Error al seleccionar la base de datos.");
				
			$loan_date = strtotime($_POST["date"]);
			
			if($loan_date == 0)
				$loan_date = strtotime(date('d-m-Y'));
				
			$client = $_POST["client"];
			$lender = $_POST["lender"];
			$item = $_POST["item"];
			$type = $_POST["type"];
			
			$query = "INSERT INTO Loans VALUES(NULL, '$loan_date', NULL, '$client', '$lender', '$item', '$type')";
			
			$result = mysql_query($query, $db_connection);
		
			if(!$result)
				die("Error en la insersi[on del registro en la base de datos.");
				
			echo "Pr�stamo registrado.<br>";
			echo "<h2>Detalles:</h2>";

			echo "<table>";
			echo "	<tr>";
			echo "		<td>Art�culo:</td>";
			echo "		<td>$item</td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "		<td>Tipo:</td>";
			echo "		<td>$type</td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "	<td>Prestado a:</td>";
			echo "	<td>$client</td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "		<td>Prestado por:</td>";
			echo "		<td>$lender</td>";
			echo "	</tr>";
			echo "	<tr>";
			echo "		<td>Fecha: </td>";
			echo "		<td>" . date('d-m-Y', $loan_date) . "</td>";
			echo "	</tr>";
			echo "</table><br>";
			
			echo "<a href='lend.php'>Registrar otro pr�stamo</a><br><br>";
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
