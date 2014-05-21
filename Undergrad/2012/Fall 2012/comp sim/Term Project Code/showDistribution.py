from visual import *
from visual.filedialog import get_file
from visual.filedialog import save_file
from visual.controls import *
from visual.graph import *

bodies = []
scene1 = display( title="N-Body Gravity", x=700, y=200, width=500, height=500)
scene1.autoscale = True
density = 1


def newRadius(M):
        global bodies
        return (((4/3)*pi*M*density)**(1.0/3.0))

def getConfig():
	d = {}
	fd = get_file(file_extensions=['.conf'])
	if fd:
		i = 0
		#fd.read() or fd.readlines() 
		for line in fd:
			d = dict(eval(line))
			if i == 0:
					retain = d['retain']
					i+= 1
			else:
				if retain == True:
					temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos']*1, vel=d['vel']*1, acc=vector(0,0,0), mass=d['mass'], color=(.75,.75,.75), retain=10000, radius=newRadius(d['mass'])  )
					bodies.append( temp )
				else:
					temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos']*1, vel=d['vel']*1, acc=vector(0,0,0), mass=d['mass'], color=(.75,.75,.75), retain=10000, radius=newRadius(d['mass'])  )
					bodies.append( temp )
		fd.close()
	del fd
	
getConfig()
var = raw_input("Close")