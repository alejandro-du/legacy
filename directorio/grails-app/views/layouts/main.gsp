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
        <div id="pageBody">
	        <g:layoutBody />
        </div>
        <div id="footer">
        	<p>Copyright (c) 2011 Lorem ipsum dolor.</p>
        </div>
    </body>
</html>