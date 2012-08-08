#!/usr/bin/env python
# coding: utf-8

import threading
import time
import boostpytest

class Calculator(threading.Thread):
	strGmdfile = "GmdFilePath"
	strProcName = "ProcName"
	strOrigin = "Origin"
	strCalcSheetPath = "CalcSheetPat"
	strTemplatePath = "TemplatePath"
	
	def __init__(self):
		threading.Thread.__init__(self)
		self.setDaemon(True)
		self.i = 0

	def run(self):
		print "  === start sub thread ==="
		call = boostpytest.DlgCaller()
		str = u"start"
		print dir(call)
		print "Start."
		ref = call.DoCalculation( self.strGmdfile, self.strProcName, self.strOrigin, self.strCalcSheetPath, self.strTemplatePath )
		print "A calculation has finished! status code: %d" % ref
		time.sleep(1)
		print "  === end sub thread ==="

# if __name__ == "__main__":
# 	t = Calculator()
# 	t.start()
# 	time.sleep(30)
