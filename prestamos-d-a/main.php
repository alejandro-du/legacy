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
			echo "<h2>Menú principal</h2>";
			echo "<a href='lend.php'>Registrar préstamo </a><br><br>";
			echo "<a href='return.php'>Registrar devolución</a><br><br>";
			echo "<a href='view.php'>Ver registro de préstamos</a><br><br>";
			echo "<a href='config.php'>Configurar cuenta</a><br><br>";
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
