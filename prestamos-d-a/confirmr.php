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
				
			$item_id = $_GET["item_id"];
			
			$query = "SELECT * FROM Loans WHERE auto_id = '$item_id'";
			
			$result = mysql_query($query, $db_connection);
		
			if(!$result)
				die("Error en la consulta a la base de datos.");
				
			$item = mysql_result($result, $i, "item");
			$client = mysql_result($result, $i, "client");
			$date = mysql_result($result, $i, "loan_date");
			$loan_date = date('d-m-Y', $date);
			$lender = mysql_result($result, $i, "lender");
			$type = mysql_result($result, $i, "type");
			
			echo "<h2>Detalles:</h2>";
			
			echo "<form method='POST' action='doret.php?item_id=" . $item_id . "'>";
			echo "	<table>";
			echo "		<tr>";
			echo "			<td>Fecha devolución:</td>";
			echo "			<td><input type='text' name='date' value=" . date("d-m-Y") . "></td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td width='110'>Artículo:</td>";
			echo "			<td width='80%'>$item</td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Tipo:</td>";
			echo "			<td>$type</td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Prestado a:</td>";
			echo "			<td>$client</td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Prestado por:</td>";
			echo "			<td>$lender</td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Fecha préstamo: </td>";
			echo "			<td>". date('d-m-Y', $date) . "</td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td></td>";
			echo "			<td><input type='submit' value='Registrar devolución'></td>";
			echo "		</tr>";
			echo "	</table>";
			echo "	</form>";
			echo "<a href='return.php'>Cancelar y seleccionar otro préstamo</a><br><br>";
			echo "<a href='main.php'>Cancelar y volver al menú principal</a><br><br>";
			echo "<a href='logout.php'>Cerrar sesión</a>";
		}
		else
		{
			session_unset();
			session_destroy();
			echo "<br>Debe ingresar al sistema.<br><br>";
			echo "<a href='index.php'>Inicio</a>";
			exit;
		}
				
	?>

</font>
</body>

</html>
