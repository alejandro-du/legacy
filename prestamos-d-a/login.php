<?php

	session_start();

	require("config/db_config.php");

	$db_connection = mysql_connect($db_host, $db_user, $db_password);
	
	if(!$db_connection)
		die("Error de conexio'n con la base de datos");
		
	if(!@mysql_select_db($db_name, $db_connection))
		die("Error al seleccionar la base de datos.");
	
	$user_name = $_POST["user_name"];
	$user_password = $_POST["user_password"];
		
	$query = "SELECT * FROM Users WHERE name = '$user_name' and password = password('$user_password')";
	
	$result = mysql_query($query, $db_connection);
	
	if(!$result)
		die("Error en la consulta a la base de datos.");
	
	if(mysql_num_rows($result) > 0) // authentic user
	{
		$_SESSION['session_id'] = session_id();
		$_SESSION['valid_user'] = $user_name;
		header('Location: main.php');
	}
	else
	{
		header('Location: wronglog.php');
	}
		
?>
