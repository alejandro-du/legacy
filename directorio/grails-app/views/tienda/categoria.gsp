<html>
    <head>
        <title>${message(code: 'app.titulo')} - ${categoria.nombre}</title>
        <meta name="layout" content="public" />
	</head>
	<body>
		<h1>${categoria.nombre}</h1>
		<p>
			${categoria.html}
		</p>
		<div id="tiendas">
			<g:each var="tienda" in="${tiendas}">
				<g:render template="tienda" model="[tienda: tienda]" />
			</g:each>
		</div>
	</body>
</html>