#!/usr/bin/python
import ftpserver

#FTP_ROOT = "/home/SOGO/ftp/"
FTP_ROOT = "c:/work2/ftp/"
ADDRESS = ("127.0.0.1", 21)

authorizer = ftpserver.DummyAuthorizer()
#authorizer.add_anonymous(FTP_ROOT)
authorizer.add_user("gunya", "password_de_gozaimasu", FTP_ROOT,perm="elradfmw")

ftp_handler = ftpserver.FTPHandler
ftp_handler.authorizer = authorizer
#ftp_handler.ftp_CWD(ftp_handler, FTP_ROOT)

ftpd = ftpserver.FTPServer(ADDRESS, ftp_handler)
ftpd.serve_forever()
