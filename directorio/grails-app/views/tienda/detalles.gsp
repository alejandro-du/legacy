<html>
	<head>
        <title>${message(code: 'app.titulo')} - ${tienda.nombre}</title>
        <meta name="layout" content="public" />
        <link rel="stylesheet" href="${resource(dir:'js/jquery/jquery-lightbox/styles/',file:'jquery.lightbox.min.css')}" />
	</head>
	<body>
		<h1>${tienda.nombre}</h1>
		<span id="categoria-detalles-tienda">
			${tienda.categoria.nombre}
		</span>
		<span id="ubicacion-detalles-tienda">
		 	(${tienda.centroComercial.nombre} - <g:message code="app.texto.local" /> ${tienda.ubicacion})
		</span>
		<br/><br/>
		<iframe src="http://www.facebook.com/plugins/like.php?href&amp;send=false&amp;layout=standard&amp;width=450&amp;show_faces=true&amp;action=like&amp;colorscheme=light&amp;font&amp;height=80" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:450px; height:50px;" allowTransparency="true"></iframe>
		<div id="anuncios">
			<g:each var="a" in="${anuncios}">
				<div id="anuncio">
					<div id="imagen-anuncio">
						<g:set var="url" value="${createLink(controller: 'index', action: 'imagenAnuncio', params: [id: a.id])}" />
						<g:link rel="lightbox-anuncios" url="${url}" title="${a.tienda.nombre}, ${a.titulo}">
							<img width="64px" height="64px" alt="${a.titulo}" src="${url}">
						</g:link>
					</div>
					<span id="titulo-anuncio">
						${a.titulo}
					</span>
					<span id="fecha-anuncio">
						${a.fecha}
					</span>
					<span id="texto-anuncio">
						${a.texto}
					</span>
				</div>
			</g:each>
		</div>
		<div id="fotos-tienda" class="gallery">
			<ul class="images">
				<g:each var="foto" in="${fotos}">
					<li class="image">
						<g:set var="url" value="${createLink(controller: 'index', action: 'imagenFoto', params: [id: foto.id])}" />
						<g:link rel="lightbox-fotos" url="${url}" title="${foto.titulo}, ${foto.descripcion}">
							<img width="64px" height="64px" alt="${foto.titulo}" src="${url}">
						</g:link>
					</li>
				</g:each>
			</ul>
		</div>
		<jq:plugin name="lightbox" />
		<jq:jquery>
			jQuery.Lightbox.construct({
			     "show_linkback": false,
			     "text": {
                        // For translating
                        "image":        "Foto",
                        "of":           "de",
                        "close":        "Cerrar X",
                        "closeInfo":    "Tambi&eacute;n puede hacer clic fuera de la imagen para cerrar.",
                        "download":     "Descargar.",
                        "help": {
                            "close":    "Clic para cerrar",
                            "interact": "Se&ntilde;ale para interactuar"
                        },
                        "about": {
                            "text":     "jQuery Lightbox Plugin (balupton edition)",
                            "title":    "Licenced under the GNU Affero General Public License.",
                            "link":     "http://www.balupton.com/projects/jquery-lightbox"
                        }
                    }
			 });
		</jq:jquery>
		 <div id="html-tienda">
			${tienda.html}
		</div>
	</body>
</html>