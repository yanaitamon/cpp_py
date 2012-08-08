"""A simple load tester for WebSocket clients.

A client program sends a message formatted as "<time> <count> <message>" to
this handler. This handler starts sending total <count> WebSocket messages
containing <message> every <time> seconds. <time> can be a floating point
value. <count> must be an integer value.
"""

import Calculator
from xml.etree.ElementTree import *
from mod_pywebsocket import msgutil
import logging
import time
import boostpytest

_GOODBYE_MESSAGE = 'Goodbye'

def web_socket_do_extra_handshake(request):
	pass  # Always accept.

def web_socket_transfer_data(request):
	str_finish = "has not finished."
	while str_finish != "Finished":
		s = msgutil.receive_message(request)
		print s
		tree = parse(s)
		clac = Calculator.Calculator()
		clac.strGmdfile = tree.findtext("GmdFilePath")
		# logging.debug( 'GmdFilePath : %s' % clac.strGmdfile )
		print 'GmdFilePath : %s' % clac.strGmdfile
		clac.strProcName = tree.findtext("ProcName")
		print 'ProcName : %s' % clac.strProcName
		clac.strOrigin = tree.findtext("Origin")
		# logging.debug( 'Origin : %s' % clac.strOrigin )
		print 'Origin : %s' % clac.strOrigin
		clac.strCalcSheetPath = tree.findtext("CalcSheetPath")
		# logging.debug( 'CalcSheetPath : %s' % clac.strCalcSheetPath )
		print 'CalcSheetPath : %s' % clac.strCalcSheetPath
		clac.strTemplatePath = tree.findtext("TemplatePath")
		# logging.debug( 'TemplatePath : %s' % clac.strTemplatePath )
		print 'TemplatePath : %s' % clac.strTemplatePath
		clac.start()
		
		# s = msgutil.receive_message(request)
		print "No.1"	# test
		print request	# test
		i = 0
		
		mem = boostpytest.MemoryMapper()
		print "No.2" # test
		print dir(mem) # test
		str = u"start"
		# msgutil.send_message(request, dir(mem))
		msgutil.send_message(request, "Start.")
		while str != "Finished":
			time.sleep(3)
			i += 1
			# msgutil.send_message(request, str(i).decode('utf-8'))
			str = mem.getCalcStatus()
			print str
			# logging.debug( '%s' % str )
			msgutil.send_message(request, str)
		else:
			time.sleep(3)
			msgutil.send_message(request, "A calculation has finished!")
			str_finish = str
