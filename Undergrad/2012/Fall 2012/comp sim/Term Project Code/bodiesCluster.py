######################################################################
#
#       N-Body: Gravitational Simulation  (tree code)
#       Done in Visual Python By:
#               - Ryan Bleile
#
#
######################################################################
#imports
from visual import *
from visual.filedialog import get_file
from visual.filedialog import save_file
from visual.controls import *
from visual.graph import *
######################################################################
#
#		Tree Node Class
#
######################################################################
class BHTreeNode(object):
	def __init__(self, parent):
		self.child = dict( ul=None, ur=None, dl=None, dr=None)
		self.parent = parent
		self.Mass = 0
		self.contained_bodies = 0
		self.lower_corner = vector(0,0,0)
		self.upper_corner = vector(0,0,0)
		self.center_line = vector(0,0,0)
		self.center_of_mass = vector(0,0,0)
		self.center_velocity = vector(0,0,0)
		self.Acceleration = vector(0,0,0)
		self.leaf_body = None

def getCenterLine(self):
	return self.center_line
def getLowerCorner(self):
	return self.lower_corner
def getUpperCorner(self):
	return self.upper_corner
#
######################################################################
#
#	Tree Class Functions
#
######################################################################
def setCenterAndMass(self):
	if(self.contained_bodies == 1):
		self.Mass = self.leaf_body.mass*1
		self.center_of_mass = self.leaf_body.pos*1
	elif( self.contained_bodies == 0):
		print str(self.center_line) + " center line node no bodies "
		self.Mass = 0
		self.center_of_mass = self.center_line*1
	elif(self.contained_bodies > 1):
		if(self.child['ul'] != None):
			m1 = self.child['ul'].Mass
			c1 = m1 * self.child['ul'].center_of_mass
		else:
			m1 = 0
			c1 = vector(0,0,0)
		if(self.child['ur'] != None):
			m2 = self.child['ur'].Mass
			c2 = m2 * self.child['ur'].center_of_mass
		else:
			m2 = 0
			c2 = vector(0,0,0)
		if(self.child['dl'] != None):
			m3 = self.child['dl'].Mass
			c3 = m3 * self.child['dl'].center_of_mass
		else:
			m3 = 0
			c3 = vector(0,0,0)
		if(self.child['dr'] != None):
			m4 = self.child['dr'].Mass
			c4 = m4 * self.child['dr'].center_of_mass
		else:
			m4 = 0
			c4 = vector(0,0,0)
		self.Mass = m1+m2+m3+m4
		if(self.Mass == 0):
			error = True
			self.center_of_mass = self.center_line*1
		else:
			self.center_of_mass = (c1+c2+c3+c4) * (1.0/self.Mass)	
	if(self.parent != None):
		setCenterAndMass(self.parent)
######################################################################
#
#		Functions to build tree
#
######################################################################
#
#	Look through all nodes. Find maximum and minimum positions in xy plane. This clustering will only handle bodies on the z=0 plane for now
#		get max x and min x max y and min y and compare through all bodies.
# 		
#	Using information generate root node and its four children.
#	
#	Go through list of bodies and decide which quadrent to place it
#		if no bodies in quadrent update node to be a leaf node with one body
#		if bodies already in quadrent, update number of bodies +1
#			if children nodes already exist navigate down a level and see if bodies is this quadrent...recursive
#			if no children nodes yet build children nodes, generate small list for bodies needing new nodes. place first body already in spot in a sub node. See if you can place body at this level...recursive
#
def deleteFromTree(self):
	if(self.contained_bodies > 1):
		deleteFromTree(self.child['ul'])
		deleteFromTree(self.child['ur'])
		deleteFromTree(self.child['dl'])
		deleteFromTree(self.child['dl'])
	else:
		try:
			del self
		except:
			print "cannot delete self"
def BuildTree():
	global root
	try:
		if(root):
			deleteFromTree(root)
	except:
		print "No root defined"
	root = BHTreeNode(None)

	xmin = bodies2[0].pos.x
	xmax = bodies2[0].pos.x
	ymin = bodies2[0].pos.y
	ymax = bodies2[0].pos.y

	for i in range(numBodies):
		if (bodies2[i].pos.x < xmin):
			xmin = bodies2[i].pos.x
		if(bodies2[i].pos.x > xmax):
			xmax = bodies2[i].pos.x
		if(bodies2[i].pos.y < ymin):
			ymin = bodies2[i].pos.y
		if(bodies2[i].pos.y > ymax):
			ymax = bodies2[i].pos.y
	
	if(xmin == xmax):
		xmin -= 1
		xmax += 1
	if(ymin == ymax):
		ymin -= 1
		ymax += 1

	root.lower_corner.x = xmin
	root.lower_corner.y = ymin
	root.upper_corner.x = xmax
	root.upper_corner.y = ymax
	
	root.center_line.x = ( xmin + xmax ) * .5
	root.center_line.y = ( ymin + ymax ) * .5
	
	del xmin, xmax, ymin, ymax
	buildChildren(root)
	
	for i in range(numBodies):
		addOneBodyToTree(root, bodies2[i])	
# Function to add a single body to the tree at the passed in node (self = node in tree, body is the passed in body)
def addOneBodyToTree(self, body1):
	self.contained_bodies += 1
	if(self.contained_bodies == 1):
		self.leaf_body = body1
		setCenterAndMass(self)
	elif(self.contained_bodies == 2):
		buildChildren(self)
		which_child1 = whichChild(self, body1)
		which_child2 = whichChild(self, self.leaf_body)
		if(which_child1 == which_child2):
			addTwoBodiesToTree(self.child[which_child1], body1, self.leaf_body)
		else:
			addOneBodyToTree(self.child[which_child1], body1)
			addOneBodyToTree(self.child[which_child2], self.leaf_body)
		self.leaf_body = None
	else:
		which_child = whichChild(self, body1)
		addOneBodyToTree(self.child[which_child], body1)
# Function to determine which nodes in a tree to put two bodies who are at the same level		
def addTwoBodiesToTree(self, body1, body2):
	self.contained_bodies += 2
	buildChildren(self)
	which_child1 = whichChild(self, body1)
	which_child2 = whichChild(self, body2)
	if(which_child1 == which_child2):
		addTwoBodiesToTree(self.child[which_child1], body1, body2)
	else:
		addOneBodyToTree(self.child[which_child1], body1)
		addOneBodyToTree(self.child[which_child2], body2)
# Function to determine which child to put a body in
def whichChild(self, body):
	which_child = 'none'
	if(body.pos.y <= self.center_line.y and body.pos.x <= self.center_line.x):
		which_child = 'dl' #down left
	elif( body.pos.y <= self.center_line.y and body.pos.x >= self.center_line.x):
		which_child = 'dr' #down right
	elif( body.pos.y >= self.center_line.y and body.pos.x <= self.center_line.x):
		which_child = 'ul' #up left
	elif( body.pos.y >= self.center_line.y and body.pos.x >= self.center_line.x):
		which_child = 'ur' #up right
	if(which_child == 'none'):
			print "Error - No child direction found"
	return which_child
# Function to generate the four children for a node	
def buildChildren(self):
	
	#Create Children as Tree Nodes#
	self.child['ul'] = BHTreeNode(self)
	self.child['ur'] = BHTreeNode(self)
	self.child['dl'] = BHTreeNode(self)
	self.child['dr'] = BHTreeNode(self)
	#Define Each of the childrens particular characteristics#
	#Define top left quadrent#
	test = self.child['ul']
	
	setBoundaries(self, self.child['ul'], 'ul')

	setBoundaries(self, self.child['ur'], 'ur')

	setBoundaries(self, self.child['dl'], 'dl')

	setBoundaries(self, self.child['dr'], 'dr')
	
def setBoundaries(parentNode, childNode, quad):
	
	plc = getLowerCorner(parentNode)*1
	puc = getUpperCorner(parentNode)*1
	pcl = getCenterLine(parentNode)*1
	
	if( quad == 'ul'):
		childNode.lower_corner.x = plc.x
		childNode.lower_corner.y = pcl.y
		childNode.upper_corner.x = pcl.x
		childNode.upper_corner.y = puc.y
	elif( quad == 'ur'):
		childNode.lower_corner.x = pcl.x
		childNode.lower_corner.y = pcl.y
		childNode.upper_corner.x = puc.x
		childNode.upper_corner.y = puc.y
	elif( quad == 'dl'):
		childNode.lower_corner.x = plc.x
		childNode.lower_corner.y = plc.y
		childNode.upper_corner.x = pcl.x
		childNode.upper_corner.y = pcl.y
	elif( quad == 'dr'):
		childNode.lower_corner.x = pcl.x
		childNode.lower_corner.y = plc.y
		childNode.upper_corner.x = puc.x
		childNode.upper_corner.y = pcl.y

	childNode.center_line.x = ( childNode.lower_corner.x + childNode.upper_corner.x) * .5
	childNode.center_line.y = ( childNode.lower_corner.y + childNode.upper_corner.y) * .5
	childNode.center_of_mass = childNode.center_line * 1
#
######
#
#	Defining Tree Method Calculation functions
#
######
#

def TREE_POS_UPDATE(self):
	if( self.contained_bodies > 1 ):
		acceleration_calculation(self.child['dl'], self.child['dr'], self.child['ul'], self.child['ur'], self.Acceleration)
		for i in range(4):
			TREE_POS_UPDATE(self.child[childNodeMap[i]])
	elif( self.contained_bodies == 1 ):
		self.leaf_body.acc = self.Acceleration
		Force_Update_Method(self)

def acceleration_calculation(b1, b2, b3, b4, parent_influence):
	TEMP_BODIES = {0: b1, 1: b2, 2: b3, 3: b4}
	for i in range(4):
		for j in range(3):
			k = j + i + 1
			if( k < 4):
				if(TEMP_BODIES[i].Mass != 0 and TEMP_BODIES[k].Mass != 0):
					TEMP_FORCE = getForceNodes(TEMP_BODIES[i], TEMP_BODIES[k])
					TEMP_BODIES[i].Acceleration += TEMP_FORCE/(TEMP_BODIES[i].Mass*1.0) + parent_influence
					TEMP_BODIES[k].Acceleration -= TEMP_FORCE/(TEMP_BODIES[k].Mass*1.0)
				
def Force_Update_Method(self):
	method = getMethod()
	switch = {1: Euler, 2: Verlet}
	switch[method](self)

def Euler(self):
	bd = self.leaf_body
	bd.vel += bd.acc*dt
	bd.pos += bd.vel*dt
def Verlet(self):
	print "incomplete functionality - verlet is not defined"

def getMethod():
	global integrationMethod
	return integrationMethod
	
def getForceNodes( b1, b2):
	r = b1.center_of_mass - b2.center_of_mass
	return (-G *b1.Mass* b2.Mass * r * (1 / (r.mag**3 + softenCloseRange)))

#
######################################################################
#
#       Drawing Tree
#
######################################################################
#
def drawFullTree():
	for i in range(len(treeCurves)):
		treeCurves[i].visible = False
	del treeCurves[:]
	drawTree(root)
def generateCurve(Node):
	TEMP_CURVE = curve(pos=[(Node.lower_corner.x, Node.lower_corner.y, 0),(Node.lower_corner.x,Node.upper_corner.y, 0),(Node.upper_corner.x,Node.upper_corner.y, 0),(Node.upper_corner.x,Node.lower_corner.y, 0),(Node.lower_corner.x, Node.lower_corner.y, 0) ])
	treeCurves.append( TEMP_CURVE )
	
def drawTree(Node):
	generateCurve(Node)
	if(Node.contained_bodies > 1):
		drawTree(Node.child['ul'])
		drawTree(Node.child['ur'])
		drawTree(Node.child['dl'])
		drawTree(Node.child['dr'])
#
######################################################################
#
#       Defining all functions
#
######################################################################
#
def newRadius(M):
	global bodies
	return (((4/3)*pi*M*density)**(1.0/3.0))
def newPosition(M, i, j):
	global bodies
	return (bodies[i].pos*bodies[i].mass + bodies[j].pos*bodies[j].mass) * (1.0 / M)
def newVelocity(M, i, j):
	global bodies
	return (bodies[i].vel*bodies[i].mass + bodies[j].vel*bodies[j].mass) * (1.0 / float(M))
# check for collisions
def  checkForCollisons():
	global bodies
	i = 0
	j = 0
	while i < len(bodies):
		while j < len(bodies):
			if(i != j):
				r1 = bodies[i].radius
				r2 = bodies[j].radius
				r = bodies[i].pos-bodies[j].pos
				if r.mag <= r1 + r2:
					nmass = (bodies[i].mass + bodies[j].mass)
					ncolor = [ .5*(bodies[i].color[0] + bodies[j].color[0]), .5*(bodies[i].color[1] + bodies[j].color[1]), .5*(bodies[i].color[2] + bodies[j].color[2])  ]
					if retain == True:
						bodies.append( sphere( pos=newPosition(nmass, i ,j), radius=newRadius(nmass), mass=nmass, vel=newVelocity(nmass, i, j), retain=10000, make_trail=True, color=ncolor, acc=vector(0,0,0)) )  
					else:
						bodies.append( sphere( pos=newPosition(nmass, i ,j), radius=newRadius(nmass), mass=nmass, vel=newVelocity(nmass, i, j), make_trail=True, color=ncolor, acc=vector(0,0,0)) )  
					bodies[i].visible = False
					bodies[j].visible = False
					del bodies[j]
					del bodies[i]
					j = len(bodies)
					i = i-1
			j += 1
		i += 1

# define acceleration from force between two objects
# acceleration of 1 by 2
def getAcc( i, j):
	global bodies
	#radial vector between 1 and 2
	object1 = bodies[i]
	object2 = bodies[j]
	r = object1.pos - object2.pos
	
	return (-G * object2.mass * r * (1 / r.mag**3))
def getAccTotal(index):
	#define temprary acceleration
	tempAcc = vector(0,0,0)
	#sum accelerations from all other bodies in system
	for j in range(numBodies):
		if (index != j):
			tempAcc += getAcc(index, j)
	return tempAcc

def getAccAllReduced():
	global bodies
	for i in range(numBodies):
		for j in range(i+1, numBodies):
			object1 = bodies[i]
			object2 = bodies[j]
			r = object1.pos-object2.pos
			force = (-G*object1.mass*object2.mass*r) /(r.mag**3 + softenCloseRange )

			bodies[i].acc += force*(1.0/object1.mass)
			bodies[j].acc -= force*(1.0/object2.mass)
			del object1
			del object2
			del r
			del force
def eulerIntegrateReduced():
	global bodies
	if(numBodies != 1):
		getAccAllReduced()
		for i in range(numBodies):
			#update velocity and position from acceleration
			bodies[i].vel += bodies[i].acc*dt
			bodies[i].pos += bodies[i].vel*dt
			#reset acc to zero for next update
			bodies[i].acc *= 0
	else:
			bodies[0].pos += bodies[0].vel*dt
def RK2IntegrateReduced():
        global bodies
        if(numBodies != 1):
                initialBodies = bodies
                k1 = range(numBodies)
                k2 = range(numBodies)
                getAccAllReduced()
                for i in range(numBodies):
                        k1[i] = bodies[i].acc*dt
                        bodies[i].vel += k1[i]/2
                        bodies[i].pos += bodies[i].vel*dt
                        bodies[i].acc = vector(0,0,0)
                getAccAllReduced()
                for i in range(numBodies):
                        k2[i] = bodies[i].acc*dt
                bodies = initialBodies
                for i in range(numBodies):
                        bodies[i].vel += k1[i]/2.0 + k2[i]/2.0
                        bodies[i].pos += bodies[i].vel*dt
                        bodies[i].acc = vector(0,0,0)
        else:
                bodies[0].pos += bodies[0].vel*dt
def RK4IntegrateReduced():
        global bodies
        if(numBodies != 1):
                initialBodies = bodies
                k1 = range(numBodies)
                k2 = range(numBodies)
                k3 = range(numBodies)
                k4 = range(numBodies)
                getAccAllReduced()
                for i in range(numBodies):
                        k1[i] = bodies[i].acc*dt
                        bodies[i].vel += k1[i]
                        bodies[i].pos += bodies[i].vel*dt
                        bodies[i].acc = vector(0,0,0)
                getAccAllReduced()
                for i in range(numBodies):
                        k2[i] = bodies[i].acc*dt
                        bodies[i].vel = initialBodies[i].vel + k2[i]
                        bodies[i].pos = initialBodies[i].pos + bodies[i].vel*dt
                        bodies[i].acc = vector(0,0,0)
                getAccAllReduced()
                for i in range(numBodies):
                        k3[i] = bodies[i].acc*dt
                        bodies[i].vel = initialBodies[i].vel + k3[i]
                        bodies[i].pos = initialBodies[i].pos + bodies[i].vel*dt
                        bodies[i].acc = vector(0,0,0)
                getAccAllReduced()
                for i in range(numBodies):
                        k4[i] = bodies[i].acc*dt
                bodies = initialBodies
                for i in range(numBodies):
                        bodies[i].vel += k1[i]/6.0 + k2[i]/3.0 + k3[i]/3.0 + k4[i]/6.0
                        bodies[i].pos += bodies[i].vel*dt
                        bodies[i].acc = vector(0,0,0)
        else:
                bodies[0].pos += bodies[0].vel*dt

# define integration methods for gravitation
        # Euler - Runge-Kutta (2/4) - Cluster ?
        
def eulerIntegrate():

        if(numBodies != 1):
                #get acceleration for each body
                for i in range(numBodies):
                        bodies[i].acc = getAccTotal(i)
                #update velocity and position based on grabbed acceleration
                for i in range(numBodies):
                        bodies[i].vel = bodies[i].vel + bodies[i].acc*dt
                        bodies[i].pos = bodies[i].pos + bodies[i].vel*dt
        else:
                bodies[0].pos = bodies[0].pos + bodies[0].vel*dt

def RK2Integrate():
        if(numBodies !=1):
                for i in range(numBodies):
                        initialVelocity = bodies[i].vel
                        initialPosition = bodies[i].pos

                        k1 = getAccTotal(i)*dt

                        bodies[i].vel += k1/2
                        bodies[i].pos += bodies[i].vel*dt

                        k2 = getAccTotal(i)*dt

                        bodies[i].vel = initialVelocity
                        bodies[i].pos = initialPosition

                        bodies[i].vel += ( k1/2 + k2/4)
                for i in range(numBodies):
                        bodies[i].pos += bodies[i].vel*dt
        else:
                bodies[0].pos = bodies[0].pos + bodies[0].vel*dt
def RK4Integrate():
        if(numBodies != 1):
                for i in range(numBodies):
                        initialVelocity = bodies[i].vel
                        initialPosition = bodies[i].pos
                        
                        k1 = getAccTotal(i)*dt

                        bodies[i].vel += k1/2
                        bodies[i].pos += bodies[i].vel*dt

                        k2 = getAccTotal(i)*dt

                        bodies[i].vel = initialVelocity
                        bodies[i].pos = initialPosition
                        bodies[i].vel += k2/2
                        bodies[i].pos += bodies[i].vel*dt

                        k3 = getAccTotal(i)*dt

                        bodies[i].vel = initialVelocity
                        bodies[i].pos = initialPosition
                        bodies[i].vel += k3/2
                        bodies[i].pos += bodies[i].vel*dt

                        k4 = getAccTotal(i)*dt

                        bodies[i].vel = initialVelocity
                        bodies[i].pos = initialPosition

                        bodies[i].vel += ( k1/6 + k2/3 + k3/3 + k4/6 )
                for i in range(numBodies):
                        bodies[i].pos += bodies[i].vel*dt
                        
        else:
                bodies[0].pos = bodies[0].pos + bodies[0].vel*dt


#Button commands
def changeEuler():
        global integrationMethod
        integrationMethod = 1
        alg1Text.visible = True
        alg2Text.visible = False
        alg3Text.visible = False
def changeRK2():
        global integrationMethod
        integrationMethod = 2
        alg2Text.visible = True
        alg1Text.visible = False
        alg3Text.visible = False
def changeRK4():
        global integrationMethod
        integrationMethod = 3
        alg3Text.visible = True
        alg2Text.visible = False
        alg1Text.visible = False
def toggleReduced():
        global reduced
        global integrationMethod
        if (reduced == True):
                integrationMethod -= 3
                alg4Text.visible = False
                reduced = False
        else:
                integrationMethod += 3
                alg4Text.visible=True
                reduced = True
                
                

######################################################################

# Set Constants
dt = .01
density = 10
G = 1
integrationMethod = 1
retain = True
reduced = False
#global dictionary to go between 0,1,2,3 and ul, ur, dl, dr values
childNodeMap = {0: 'ul', 1: 'ur', 2: 'dl', 3: 'dr'}		
# Soften radius of objects at very close range by this amount aka minimum allowed distance
softenCloseRange = .001
# Initialize Global Variables in the System
def initializeScene():
	c = controls( title="Choose Algorithm", x=350, height=350, width=350, range=150) # Create controls window
	# Create a button in the controls window:
	b1 = button( pos=(-30,65), width=120, height=60, text='Euler', action=lambda: changeEuler() )
	b2 = button( pos=(-30,0), width=120, height=60, text='Runge-Kutta 2', action=lambda: changeRK2() )
	b3 = button( pos=(-30,-65), width=120, height=60, text='Runge-Kutta 4', action=lambda: changeRK4() )
	t1 = toggle(pos = (70, 0), text0='Not-Reduced', text1='Reduced', action=lambda: toggleReduced())
	Alg = display( title="Algorithm Running", x=700, height=200, width=1000, range=5)
	Alg.autoscale = True
	alg1Text = text(display=Alg, text='Euler', align='center', depth=-0.3, color=color.green)
	alg2Text = text(display=Alg, text='Runge-Kutta 2', align='center', depth=-0.3, color=color.green)
	alg2Text.visible = False
	alg3Text = text(display=Alg, text='Runge-Kutta 4', align='center', depth=-0.3, color=color.green)
	alg3Text.visible = False
	alg4Text = text(display=Alg, text='Reduced', align='center', depth=-0.3, color=color.yellow, pos=(0, -1.2, 0))
	alg4Text.visible=False

	scene1 = display( title="N-Body Gravity", x=700, y=200, width=500, height=500)
	scene1.autoscale = True

	#Comment this out to see visualization of planetary motion. Uncomment for simulation runs needing to produce data
	#scene1.visible = False



	## Make Scene Red Blue 3D
	#scene1.stereo = 'redcyan'
## Get Configuration From File ##

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
					temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos'], vel=d['vel'], acc=vector(0,0,0), mass=d['mass'], color=(1,0,0), retain=10000, radius=newRadius(d['mass'])  )
					temp2 = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos']*1, vel=d['vel']*1, acc=vector(0,0,0), mass=d['mass'], color=(.75,.75,.75), retain=10000, radius=newRadius(d['mass'])  )
					bodies.append( temp )
					bodies2.append( temp2 )
				else:
					temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos'], vel=d['vel'], acc=vector(0,0,0), mass=d['mass'], color=(1,0,0), radius=newRadius(d['mass'])  )
					temp2 = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos']*1, vel=d['vel']*1, acc=vector(0,0,0), mass=d['mass'], color=(.75,.75,.75), retain=10000, radius=newRadius(d['mass'])  )
					bodies.append( temp )
					bodies2.append( temp2 )
		fd.close()
	del fd

#Global Variables
bodies = []
bodies2 = []
treeCurves = []
time = [0]
numBodies = len(bodies)                  
finished = False
t = 0
calculations = 0
error = 0

def mainLoop():
	#fileWrite = save_file()
	#fileWrite.write("#NumberSteps \tError \tComputations\n")
	while not finished:
			if integrationMethod == 1:
					eulerIntegrate()
					calculations += numBodies*numBodies + 2*numBodies
					error += dt
			elif integrationMethod == 2:
					RK2Integrate()
					calculations += 2*numBodies*numBodies + 5*numBodies
					error = error + (dt*dt)
			elif integrationMethod == 3:
					RK4Integrate()
					calculations += 4*numBodies*numBodies + 12*numBodies
					error += dt*dt*dt*dt
			elif integrationMethod == 4:
					eulerIntegrateReduced()
					calculations += .5*numBodies*numBodies + 2*numBodies
					error += dt
			elif integrationMethod == 5:
					RK2IntegrateReduced()
					calculations += numBodies*numBodies + 4*numBodies
					error += dt*dt
			else:
					RK4IntegrateReduced()
					calculations += 2*numBodies*numBodies + 12*numBodies
					error += dt*dt*dt*dt
			checkForCollisons()
			numBodies = len(bodies)
			#fileWrite.write(str(t) + "\t" + str(error) + "\t" + str(calculations) + "\n")
	#       time.append(time[t]+dt)
	## Comment out this if statement for continuous runs
	##        t += 1
	##        if(t >= 1000):
	##                finished = True
	##                print "finished"
	##                print error
					
	#fileWrite.close()
	scene2 = display( title="Calculated information" )
	calcText1 = text(display=scene2, text="Number of Floating Point Operations", depth=-.01, color=color.red, align="center", pos=(0,1.5,0))
	calcText2 = text(display=scene2, text=str(calculations), depth=-.01, color=color.red, align="center", pos=(0,0,0))
	calcText3 = text(display=scene2, text="Order of Error", depth = -.01, color=color.red, align="center", pos=(0,-1.5,0))
	calcText4 = text(display=scene2, text=str(error), depth=-.01, color=color.red, align="center", pos=(0,-3,0))

	print "NOFPO: " + str( calculations )
	print "error: " + str(error)

scene1 = display( title="N-Body Gravity", x=700, y=200, width=500, height=500)
scene1.autoscale = True
getConfig()
numBodies = len(bodies)
BuildTree()
integrationMethod = 1 # Euler Integration
while(True):
	BuildTree()
	drawFullTree()
	TREE_POS_UPDATE(root)
	eulerIntegrateReduced()