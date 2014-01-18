import math
import sys

def cos(deg):
	return math.cos(math.radians(deg))

def sin(deg):
	return math.sin(math.radians(deg))

def fixed12(value):
	return int(value*(2**12))

fov = 50.0
ratio = 256.0/192.0
near = 0.1
far = 40.0

f = cos(fov/2.0)/sin(fov/2.0)

m00 = f / ratio
m11 = f
m22 = (near+far)/(near-far)
m23 = -1.0
m32 = (2.0*near*far)/(near-far)

print "fov =	" + str(fov)
print "ratio =	" + str(ratio)
print "near =	" + str(near)
print "far =	" + str(far)
print ""
print str(fixed12(m00)) + "	0,	0,	0"
print "0,	" + str(fixed12(m11)) + ",	0,	0"
print "0,	0,	" + str(fixed12(m22)) + ",	" + str(fixed12(m23))
print "0,	0,	" + str(fixed12(m32)) + ",	0"

sys.stdin.readline()
