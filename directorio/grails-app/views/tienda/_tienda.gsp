<div id="tienda${tienda.id}" class="tienda">
	<div id="resumen-tienda">
		<g:if test="${tienda.imagen}">
			<div id="imagen-tienda">
				<img width="64px" height="64px" alt="Imagen" src="${createLink(controller: 'index', action: 'imagenTienda', params: [id: tienda.id])}">
			</div>
		</g:if>
		<span id="nombre-tienda">
			${tienda.nombre}
		</span>
		 <span id="categoria-tienda">
		 	${tienda.categoria.nombre}
		</span>
		<span id="ubicacion-tienda">
		 	(${tienda.centroComercial.nombre} - Local ${tienda.ubicacion})
		</span>
		<span id="cuentaAnuncios-tienda">
			<g:set var="cuentaAnuncios" value="${tienda.cuentaAnuncios()}" />
			<g:if test="${cuentaAnuncios > 0}">
				<g:link controller="tienda" action="detalles" id="${tienda.id}">${cuentaAnuncios} <g:message code="app.texto.anuncios" /></g:link>
			</g:if>
			<g:else>
				&nbsp;
			</g:else>
		</span>
	</div>

	<div id="link-tienda${tienda.id}" class="link-tienda" style="display: none;">
		<g:link controller="tienda" action="detalles" id="${tienda.id}">Ver detalles</g:link>
		<iframe src="http://www.facebook.com/plugins/like.php?href&amp;send=false&amp;layout=button_count&amp;width=450&amp;show_faces=false&amp;action=like&amp;colorscheme=light&amp;font&amp;height=35" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:100px; height:35px;" allowTransparency="true"></iframe>
	</div>
	<script type="text/javascript">
		jQuery('#tienda${tienda.id}').hover(
			function() {
				jQuery('#link-tienda${tienda.id}').show();
			}, function() {
				jQuery('#link-tienda${tienda.id}').hide();
			}
		);
	</script>
</div>	