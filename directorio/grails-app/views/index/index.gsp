<html>
    <head>
        <title><g:message code="app.index.titulo" /></title>
        <meta name="layout" content="public" />
    </head>
    <body>
    	<g:each var="art" in="${articulos}">
    		<div id="articulo">
		        <h1>${art.titulo}</h1>
				<div id="html-articulo">
					${art.html}
				</div>
    		</div>
    	</g:each>
    </body>
</html>
