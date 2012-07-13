from mod_pywebsocket import msgutil

_GOODBYE_MESSAGE = 'Goodbye'


def web_socket_do_extra_handshake(request):
	pass  # Always accept.


def web_socket_transfer_data(request):
	while True:
		s = msgutil.receive_message(request)
		n = int(s)
		total = 0
		for i in range(1,n + 1):
			total = total + i
		s2 = str(total)
		msgutil.send_message(request, s2)
