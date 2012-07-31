#! /usr/bin/env python
# -*- coding:utf-8 -*-
import os, os.path, sys
import ftplib
import sqlite3
from stat import *
from cStringIO import StringIO
from datetime import datetime


#監視対象のファイルを定義
FILE_LIST = [
'test1.php',
'test2.php'	#,
#'js/jsample1.js',
#'js/jsample2.js'
]


#ローカルのディレクトリ
#FROM_DIR = '/home/anyuser/develop/'
FROM_DIR = 'c:/work2/user/develop/'
#ftpサーバー上のディレクトリ
TO_DIR = '/home/SOGO/ftp/'


def upload(con, _ftp, file_path):
    
    dblasttime = None
    #ローカルファイルの更新時間を取得
    lasttime = os.stat(FROM_DIR + file_path)[ST_MTIME]
    
    #sqliteデータベースから前回アップロードした時の更新時間を取得
    c = con.cursor()
    c.execute("select lasttime from timetable where filename = '%s'" % file_path)
    for row in c:
        dblasttime = row[0]
    
    
    if dblasttime:
        
        if dblasttime == lasttime:
            return
        
        c.execute("update timetable set lasttime = %d where filename = '%s'" % (lasttime, file_path))
    else:
        c.execute("insert into timetable(filename, lasttime) values ('%s', %d)" % (file_path, lasttime))
    
    print(file_path)
    
    #ftpサーバーへファイルのアップロードを実行
    try:
        f = open(FROM_DIR + file_path, 'rb')
    except:
        print e
    
    print 'STOR ' + TO_DIR + file_path
    
    #サーバ側のフォルダ作成、移動
    #server_cd( _ftp, file_path )
    
    try:
        _ftp.storbinary('STOR ' + file_path, f)
    except:
        print e
    
    f.close()


def main():
    
    #アップロード先のftpサーバーIP
    _ftp = ftplib.FTP('127.0.0.1')
    #ftpサーバーへのログインID,パスワード
    _ftp.login('gunya', 'password_de_gozaimasu')
    
    _ftp.set_debuglevel(5)
    
    #更新時間比較用のsqliteデータベースをオープンし、テーブルを作成
    con = sqlite3.connect("ftp.db")
    con.execute('create table if not exists timetable(filename text, lasttime integer)')
    
    #更新対象のリストに従い、更新時間の確認とftpサーバーへのアップロード
    for file_path in FILE_LIST:
        upload(con, _ftp, file_path)
    
    _ftp.quit()
    
    con.commit()
    con.close()


if __name__ == '__main__':
    main()


def server_cd( _ftp, path ):
    if path!='HOME':
        stdout = sys.stdout
        for d in path.split('/'):
            sys.stdout = StringIO()
            try:
                _ftp.dir()
            except:
                _ftp.close()
                
            if not d in [line.split(' ').pop()
                         for line in sys.stdout.getvalue().split('\n') if line and line[0]=='d']:
                try:
                    _ftp.mkd(d)
                except:
                    _ftp.close()
            try:        
                _ftp.cwd(d)
            except:
                _ftp.close()
                
            sys.stdout.close()
        sys.stdout = stdout
