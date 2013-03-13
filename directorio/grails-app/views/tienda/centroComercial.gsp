<html>
    <head>
        <title>${message(code: 'app.titulo')} - ${centroComercial.nombre}</title>
        <meta name="layout" content="public" />
	</head>
	<body>
		<h1>${centroComercial.nombre}</h1>
		<p>
			${centroComercial.html}
		</p>
		<div id="tiendas">
			<g:each var="tienda" in="${tiendas}">
				<g:render template="tienda" model="[tienda: tienda]" />
			</g:each>
		</div>
	</body>
</html>