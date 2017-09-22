# -*- coding: utf-8 -*- 
# list comprehension and map 
import time 
import dis

def test(f, name): 
    st = time.time() 
    f() 
    print '%s %ss'%(name, time.time()-st) 

ARR = range(5000000)

def tmap(): 
    map(lambda x:x+1, ARR)

def tlst(): 
    [x+1 for x in ARR]

def loop(): 
    res = []
    for x in ARR:
        res.append(x+1)

dis.dis(tmap)
print '******************'
dis.dis(tlst)
print '******************'
dis.dis(loop)

test(tmap, "map") 
test(tlst, "lst")
test(loop, "loop")
