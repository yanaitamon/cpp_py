#!/usr/bin/env python
# coding: utf-8

import threading
import time
import boostpytest

class test(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
		self.setDaemon(True)
		self.i = 0

	def run(self):
		print "Start."
		while True:
			time.sleep(10)
			self.i += 1
			print self.i * 10

# if __name__ == "__main__":
# 	t = test()
# 	t.start()
# 	time.sleep(30)
