#!/usr/bin/env python
# coding: utf-8

import threading
import time
import boostpytest

class timer(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
		self.setDaemon(True)
		self.i = 0

	def run(self):
		call = boostpytest.DlgCaller()
		str = u"start"
		print dir(call)
		print "Start."
		while str != "stop":
			time.sleep(3)
			self.i += 1
			print self.i * 10
			str = call.getCalcStatus()
			print str
		else:
			print "stopped!"

# if __name__ == "__main__":
# 	t = test()
# 	t.start()
# 	time.sleep(30)
