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

	<?php
	
		if(session_id() == $_SESSION['session_id'])
		{
			echo "<h2>Registrar Pr�stamo</h2>";
			echo "<form method='POST' action='dolend.php'>";
			echo "	<table>";
			echo "		<tr>";
			echo "			<td>Art�culo:</td>";
			echo "			<td><input type='text' name='item' size='60'></td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Tipo:</td>";
			echo "			<td><input type='text' name='type' value='Libro' size='60'></td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Prestado a:</td>";
			echo "			<td><input type='text' name='client' size='60'></td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Prestado por:</td>";
			echo "			<td><input type='text' name='lender' value=" . ucfirst($_SESSION['valid_user']) . " size='60'></td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td>Fecha: </td>";
			echo "			<td><input type='text' name='date' value=" . date("d-m-Y") . " size='60'></td>";
			echo "		</tr>";
			echo "		<tr>";
			echo "			<td></td>";
			echo "			<td><input type='submit' value='Registrar pr�stamo'></td>";
			echo "		</tr>";
			echo "	</table>";
			echo "</form>";
			echo "<a href='main.php'>Cancelar y volver al men� principal</a><br><br>";
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
