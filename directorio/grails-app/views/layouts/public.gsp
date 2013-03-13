<!DOCTYPE html>
<html>
    <head>
        <title><g:layoutTitle default="${message(code: 'app.titulo')}" /></title>
        <link rel="stylesheet" href="${resource(dir:'css',file:'main.css')}" />
        <link rel="shortcut icon" href="${resource(dir:'images',file:'favicon.ico')}" type="image/x-icon" />
        <nav:resources override="true"/>
        <g:layoutHead />
        <g:javascript library="jquery" />
    </head>
    <body>
        <div id="spinner" class="spinner" style="display:none;">
            <img src="${resource(dir:'images',file:'spinner.gif')}" alt="${message(code:'spinner.alt',default:'Loading...')}" />
        </div>
        <div id="header">
        	<h1>Lorem ipsum dolor sit amet</h1>
        </div>
        <div id="menu">
        	<nav:render/>
        </div>
        <div id="nav">
            <div class="homePagePanel">
                <div class="panelBody">
                    <h1><g:message code="app.texto.centrosComerciales" /></h1>
                    <ul>
                    	<g:each var="cc" in="${session['centrosComerciales']}">
                    		<li>
                    			<g:if test="${(centroComercial && centroComercial.id == cc.id) || (tienda && tienda.centroComercial.id == cc.id)}">
                    				<div id="homePanelSelected">
		                    			<g:link controller="tienda" action="centroComercial" id="${cc.id}">${cc.nombre}</g:link>
                    				</div>
                    			</g:if>
                    			<g:else>
	                    			<g:link controller="tienda" action="centroComercial" id="${cc.id}">${cc.nombre}</g:link>
                    			</g:else>
                    		</li>
                    	</g:each>
                    </ul>
                    <h1><g:message code="app.texto.categorias" /></h1>
                    <ul>
                    	<g:each var="c" in="${session['categorias']}">
                    		<li>
                    			<g:if test="${(categoria && categoria.id == c.id) || (tienda && tienda.categoria.id == c.id)}">
                    				<div id="homePanelSelected">
		                    			<g:link controller="tienda" action="categoria" id="${c.id}">${c.nombre}</g:link>
                    				</div>
                    			</g:if>
                    			<g:else>
	                    			<g:link controller="tienda" action="categoria" id="${c.id}">${c.nombre}</g:link>
                    			</g:else>
                    		</li>
                    	</g:each>
                    </ul>
                </div>
            </div>
        </div>
        <div id="pageBody">
	        <g:layoutBody />
        </div>
        <div id="footer">
        	<p><g:message code="app.texto.footer" /></p>
        </div>
    </body>
</html>