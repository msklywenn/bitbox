import sys
import struct

if len(sys.argv) >= 2:
	file = open(sys.argv[1])
	buffer = file.read(164)
	file.close()
	header = struct.unpack("HHIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII", buffer)
	print "Resolution : " + str(header[0])
	print "RPM : " + str(header[1])
	for c in range(8):
		print "> Channel " + str(c)
		print "Timer  : " + str(header[2+c*5+0])
		print "Volume : " + str(header[2+c*5+1])
		print "Duty   : " + str(header[2+c*5+2])
		print "Decay  : " + str(header[2+c*5+3])
		print "Offset : " + str(header[2+c*5+4])
