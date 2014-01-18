import math
def sin(x):
    B = 5215 # int((4.0/math.pi)*4096)
    C = -1660 # int((-4.0/(math.pi*math.pi))*4096)
    Q = 3174 # 0.775
    P = 922 # 0.225
    y = (B*x + ((C*x)>>12)*abs(x))>>12
    y = (((P * (((y * abs(y))>>12) - y))>>12) + y)
    return y


n = 200
for x in xrange(n):
    i = -math.pi + x/100.0*math.pi
    
    print "==== " + str(i)
    print "fixed : " + str(int(sin(int(i*4096.0))))
    print "math  : " + str(int(math.sin(i)*4096.0))
    
