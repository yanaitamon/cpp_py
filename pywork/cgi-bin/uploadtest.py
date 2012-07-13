#!/usr/bin/env python
# coding: utf-8

import charcodeconv
import cgi
import cgitb; cgitb.enable()
import os, sys
try: # Windows needs stdio set for binary mode.
    import msvcrt
    msvcrt.setmode (0, os.O_BINARY) # stdin  = 0
    msvcrt.setmode (1, os.O_BINARY) # stdout = 1
except ImportError:
    pass

UPLOAD_DIR = "c:/work2/uploadzone" #最初に作っておきます
HTML_TEMPLATE = """Content-Type: text/html

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<HTML>
<HEAD>
	<META http-equiv="Content-Type" content="text/html; charset=utf-8">
	<TITLE>ファイルアップロード</TITLE>
</HEAD>
<BODY>
<P>ファイルアップロード</P>
<FORM ACTION="uploadtest.py" METHOD="POST" ENCTYPE="multipart/form-data">
	<INPUT NAME="file" TYPE="file"><br>
	<INPUT NAME="submit" TYPE="submit">
</FORM>
<P>%(RESULT)s</P>
</BODY>
</HTML>
"""

result = ''
result2 = ''
u = ''
form = cgi.FieldStorage()
if form.has_key('file'):
	item = form['file']
	if item.file:
		# result2 = item.filename.encode('utf-8')
		u = item.filename.decode('utf-8')
		fout = file(os.path.join(UPLOAD_DIR,u), 'wb')
		while 1:
			chunk = item.file.read(100000)
			if not chunk:
				break
			fout.write(chunk)
		fout.close()
		result = 'アップロードしました。'
		
	result2 = item.filename

print HTML_TEMPLATE % {'RESULT':result}
print 'filename : %s' % result2
