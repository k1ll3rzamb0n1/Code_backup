import random
import math

print "Python Configuration File Generator"

var1 = raw_input("Filename - if not unique will overwrite existing file: ")
print "you entered ", var1
var2 = raw_input("How Many Bodies To Generate: ")
print "you entered ", var2
var3 = raw_input("What distribution: 1) Uniform Cube - 2) Exponential Disk - 3) Gaussian Sphere: ")
print "you entered ", var3

file = open(var1, 'w')
file2 = open("input.conf", 'w')
file.write("{'retain': False}\n")

if(int(var3) == 1):
	for i in xrange(int(var2)):
		x = random.uniform(-500,500)
		y = random.uniform(-500,500)
		z = random.uniform(-500,500)
		vx = random.uniform(0,1)
		vy = random.uniform(0,1)
		vz = random.uniform(0,1)
		string = "{'pos': vector(" + str(x) + "," + str(y) + "," + str(z) + "), 'vel': vector(" + str(vx) + "," + str(vy) + "," + str(vz) + "), 'mass': 15,  'make_trail': True, 'color': (1,1,1)}\n"
		file.write(string)
elif(int(var3) == 2 ):
	for i in xrange(int(var2)):
		if(i == 0):
			x=0
			y=0
			z=0
			mass=100
			vx=0
			vy=0
			vz=0
		else:
			theta = random.uniform(0, 6.28318530718)
			r = random.expovariate(.02)
			
			x=0
			y = r * math.sin(theta)	
			z = r * math.cos(theta)
			
			mass = (r/50)*10;
			
			
			
			vx =  0
			vy = 1.41*mass*(math.cos(z) + math.sin(y))
			vz = 1.41*mass*(-math.sin(z) + math.cos(y))
			
		if(i < int(var2)-1):
			string2 = str(mass) + ",1,0,0,0," + str(vx) + "," + str(vy) + "," + str(vz) + "," + str(x) + "," + str(y) + "," + str(z) + "\n";
		else:
			string2 = str(mass) + ",1,0,0,0," + str(vx) + "," + str(vy) + "," + str(vz) + "," + str(x) + "," + str(y) + "," + str(z);
		string = "{'pos': vector(" + str(x) + "," + str(y) + "," + str(z) + "), 'vel': vector(" + str(vx) + "," + str(vy) + "," + str(vz) + "), 'mass':" + str(mass) +",  'make_trail': True, 'color': (1,1,1)}\n"
		file.write(string)
		file2.write(string2)
elif(int(var3) == 3):
	for i in xrange(int(var2)):
		x = random.gauss(0, 100)
		y = random.gauss(0, 100)
		z = random.gauss(0, 100)
		vx = random.uniform(0,1)
		vy = random.uniform(0,1)
		vz = random.uniform(0,1)
		string = "{'pos': vector(" + str(x) + "," + str(y) + "," + str(z) + "), 'vel': vector(" + str(vx) + "," + str(vy) + "," + str(vz) + "), 'mass': 15,  'make_trail': True, 'color': (1,1,1)}\n"
		file.write(string)
file.close()

closeVar = raw_input("Finished, enter to close");
