#!/usr/local/bin/python
# coding: utf-8

html_body = u"""
<html>
<head>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
</head>
<body>
	<form action="/cgi-bin/cam-tool-engine.py" method="POST">
		XMLで指定されたgmdファイルを演算します。<br />
		XMLファイルを入力してください:
		<input type="text" name="xml_text" />
		<input type="submit" name="submit" />
	</form>
</body>
</html>"""

print "Content-type: text/html;charset=utf-8\n"
print (html_body).encode('utf-8')
