<html>
  <head>
	  <title>Error</title>
	  <meta name="layout" content="public" />
	  <style type="text/css">
	  		.message {
	  			border: 1px solid black;
	  			padding: 5px;
	  			background-color:#E9E9E9;
	  		}
	  		.stack {
	  			border: 1px solid black;
	  			padding: 5px;
	  			overflow:auto;
	  			height: 300px;
	  		}
	  		.snippet {
	  			padding: 5px;
	  			background-color:white;
	  			border:1px solid black;
	  			margin:3px;
	  			font-family:courier;
	  		}
	  </style>
  </head>

  <body>
    <h1>Lo sentimos</h1>
    <h2>Ha ocurrido un error</h2>

  	<div class="message">
  		Por favor informe al administrador sobre el error.
		<g:if test="${exception}">
	  		<strong>Fecha de ocurrencia: </strong> ${new Date()} <br />
		</g:if>
  	</div>
  </body>
</html>