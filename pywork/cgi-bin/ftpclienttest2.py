import glob
import string
import os
from ftplib import FTP
from urllib import urlopen

path=os.getcwd()
txtdir=os.path.join(path,'txt')

filelist=glob.glob(txtdir+'/*.txt')
#print filelist

ftp=FTP('172.0.0.1')
ftp.login('gunya', 'password_de_gozaimasu')
#ftp.cwd('C:/work2/ftp/')
dstlist= ftp.nlst()
for file in  dstlist:
    ftp.delete(file)
    print file + ' is deleted'
for file in filelist:
    f=open(file,'r')
    filename=os.path.basename(file)
    cmd='STOR '+filename
    print cmd
    ftp.storbinary(cmd,f)
    f.close()
ftp.quit()
