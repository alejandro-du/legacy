<?php
	session_start();
	
	srand((double)microtime()*1000000);
	$randval = mt_rand();
	
	if(!IsSet($_SESSION['session_id']))
	{
		session_regenerate_id();
	}
?>

<html>

<head>
	<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
	<title>Pr�stamos Duarte Avenda�o</title>
</head>

<body>
<font face="arial">

	<h1>Pr�stamos Duarte Avenda�o</h1>
	<hr>
	<br>
	<br>
	
	<form method="POST" action="login.php">
		<table>
		<tr>
			<td>Nombre:</td>
			<td><input type="text" name="user_name"></td>
		</tr>
		<tr>
			<td>Contrase�a:</td>
			<td><input type="password" name="user_password"></td>
		</tr>
		<tr>
			<td></td>
			<td><input type="submit" value="Entrar"></td>
		</tr>
		</table>
	</form>

</font>
</body>

</html>