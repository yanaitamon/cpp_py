#!/usr/bin/env python
# coding: utf-8

import time
import boostpytest

def snooze(_sec, _interval, _times):
    for i in range(3, 1, -1):
        print i
        time.sleep(1.0)
    print 'Start!'
    for i in range(_times):
        if i > 0:
            print '---interval---'
            print chr(7)*2
            time.sleep(_interval)
        print '%s times' % (i + 1)
        
        # ここでboostpytestの監視する関数を呼び出す
        
        print chr(7)
        time.sleep(_sec)
    print 'Finish!!'
    print chr(7) * 4

