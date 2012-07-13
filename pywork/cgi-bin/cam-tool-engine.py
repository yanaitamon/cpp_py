#!/usr/bin/env python
# coding: utf-8

from xml.etree.ElementTree import *
import cgi
import boostpytest
import timer

html_body = u"""
<html><head>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
</head>
<body>
%s
</body>
</html>"""

content=''

form=cgi.FieldStorage()
xml_str=form.getvalue('xml_text', '')

tree = parse(xml_str)
gmdfile_utf8 = tree.findtext("GmdFilePath")
#gmdfile = unicode(gmdfile_utf8,'utf-8')

ProcName_utf8 = tree.findtext("ProcName")
#ProcName = unicode(ProcName_utf8,'utf-8')

Origin_utf8 = tree.findtext("Origin")
#Origin = unicode(Origin_utf8,'utf-8')

CalcSheetPath_utf8 = tree.findtext("CalcSheetPath")
#CalcSheetPath = unicode(CalcSheetPath_utf8,'utf-8')

TemplatePath_utf8 = tree.findtext("TemplatePath")
#TemplatePath = unicode(TemplatePath_utf8,'utf-8')

call = boostpytest.DlgCaller()
#ref = call.DoCalculation(gmdfile, ProcName, Origin, CalcSheetPath, TemplatePath)
ref = call.DoCalculation(gmdfile_utf8, ProcName_utf8, Origin_utf8, CalcSheetPath_utf8, TemplatePath_utf8)

content+=u"終了状態：%d" % (ref)
content+=u"<br />"

print "Content-type: text/html;charset=utf-8\n"
print (html_body % content).encode('utf-8')
