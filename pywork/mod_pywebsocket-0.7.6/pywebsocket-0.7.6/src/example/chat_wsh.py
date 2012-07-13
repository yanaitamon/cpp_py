from mod_pywebsocket import msgutil
 
arr = []
 
def web_socket_do_extra_handshake(request):
	arr.append(request)
	pass

def web_socket_transfer_data(request):
	while True:
		s = msgutil.receive_message(request)
		for connect in arr:
			try:
				msgutil.send_message(connect, s)
			except:
				arr.remove(connect)
