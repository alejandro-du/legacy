<?php
	session_start();
?>

<html>

<head>
	<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
	<title> Pr�stamos Duarte Avenda�o</title>
</head>

<body>
<font face="arial">

<h1>Pr�stamos Duarte Avenda�o</h1>
	<hr>
	<br>

	<?php
	
		if(session_id() == $_SESSION['session_id'])
		{
			require("config/db_config.php");
	
			$db_connection = mysql_connect($db_host, $db_user, $db_password);
			
			if(!$db_connection)
				die("Error de conexi�n con la base de datos.");
			
			if(!@mysql_select_db($db_name, $db_connection))
				die("Error al seleccionar la base de datos.");
				
			$query = "SELECT * FROM Loans WHERE return_date IS NULL ORDER BY loan_date";
			$result = mysql_query($query, $db_connection);
			
			if(!$result)
				die("Error en la consulta a la base de datos.");
			
			echo "<h2>Pr�stamos pendientes</h2>";
			
			echo "<table  border='1'>";

			echo "	<tr>";
			echo "		<th align=left>Art�culo</th>";
			echo "		<th align=left>Prestado a</th>";
			echo "		<th align=left>Fecha pr�stamo</th>";
			echo "		<th align=left>Prestado por</th>";
			echo "		<th align=left>Tipo</th>";
			echo "	</tr>";

			for($i = 0; $i < mysql_num_rows($result); $i++)
			{
				$item_id = mysql_result($result, $i, "auto_id");
				$item = mysql_result($result, $i, "item");
				$client = mysql_result($result, $i, "client");
				$loan_date = mysql_result($result, $i, "loan_date");
				if($loan_date == 0)
					$loan_date = '------';
				else
					$loan_date = date('d-m-Y', $loan_date);
				$lender = mysql_result($result, $i, "lender");
				$type = mysql_result($result, $i, "type");

				echo "	<tr>";
				echo "		<td><a href='confirmr.php?item_id=" . $item_id . "'>-> $item</a></td>";
				echo "		<td>$client</td>";
				echo "		<td>$loan_date</td>";
				echo "		<td>$lender</td>";
				echo "		<td>$type</td>";
				echo "	</tr>";
			}

			echo "</table><br>";
			echo "<a href='main.php'>Volver al men� principal</a><br><br>";
			echo "<a href='logout.php'>Cerrar sesi�n</a>";
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
