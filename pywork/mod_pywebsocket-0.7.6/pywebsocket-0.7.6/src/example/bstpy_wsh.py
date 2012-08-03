"""A simple load tester for WebSocket clients.

A client program sends a message formatted as "<time> <count> <message>" to
this handler. This handler starts sending total <count> WebSocket messages
containing <message> every <time> seconds. <time> can be a floating point
value. <count> must be an integer value.
"""

from mod_pywebsocket import msgutil
import time
import boostpytest

_GOODBYE_MESSAGE = 'Goodbye'


def web_socket_do_extra_handshake(request):
	pass  # Always accept.


def web_socket_transfer_data(request):
	while True:
		s = msgutil.receive_message(request)
		print "No.1"	# test
		print request	# test
		print s			# test
		i = 0
		
		call = boostpytest.DlgCaller()
		print "No.2" # test
		print dir(call) # test
		str = u"start"
		#msgutil.send_message(request, dir(call))
		msgutil.send_message(request, "Start.")
		while str != "stop":
			time.sleep(3)
			i += 1
			#msgutil.send_message(request, str(i).decode('utf-8'))
			str = call.getCalcStatus()
			print str
			msgutil.send_message(request, str)
		else:
			msgutil.send_message(request, "stopped!")
