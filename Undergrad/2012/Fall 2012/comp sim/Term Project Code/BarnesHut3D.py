######################################################################
#
#       N-Body: Gravitational Simulation 3D  (tree code)
#       Done in Visual Python By:
#               - Ryan Bleile
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
#
class BHTreeNode(object):
	def __init__(self, parent):
		self.child = dict( Q1 = None, Q2 = None, Q3 = None, Q4 = None, Q5 = None, Q6 = None, Q7 = None, Q8 = None)
		self.parent = parent
		self.Mass = 0
		self.contained_bodies = 0
		self.C1 = vector(0,0,0)
		self.C2 = vector(0,0,0)
		self.C3 = vector(0,0,0)
		self.center_point = vector(0,0,0)
		self.center_of_mass = vector(0,0,0)
		self.Acceleration = vector(0,0,0)
		self.leaf_body = None

#
######################################################################
#
#	Tree Class Functions
#
######################################################################
#
def setCenterAndMass(self):
	if(self.contained_bodies == 1):
		self.Mass = self.leaf_body.mass*1
		self.center_of_mass = self.leaf_body.pos*1
	elif( self.contained_bodies == 0):
		self.Mass = 0
		self.center_of_mass = self.center_point*1
	elif(self.contained_bodies > 1):
		if(self.child['Q1'] != None):
			m1 = self.child['Q1'].Mass*1
			c1 = m1 * self.child['Q1'].center_of_mass
		else:
			m1 = 0
			c1 = vector(0,0,0)
		if(self.child['Q2'] != None):
			m2 = self.child['Q2'].Mass
			c2 = m2 * self.child['Q2'].center_of_mass
		else:
			m2 = 0
			c2 = vector(0,0,0)
		if(self.child['Q3'] != None):
			m3 = self.child['Q3'].Mass
			c3 = m3 * self.child['Q3'].center_of_mass
		else:
			m3 = 0
			c3 = vector(0,0,0)
		if(self.child['Q4'] != None):
			m4 = self.child['Q4'].Mass
			c4 = m4 * self.child['Q4'].center_of_mass
		else:
			m4 = 0
			c4 = vector(0,0,0)
		if(self.child['Q5'] != None):
			m5 = self.child['Q5'].Mass*1
			c5 = m5 * self.child['Q5'].center_of_mass
		else:
			m5 = 0
			c5 = vector(0,0,0)
		if(self.child['Q6'] != None):
			m6 = self.child['Q6'].Mass
			c6 = m6 * self.child['Q6'].center_of_mass
		else:
			m6 = 0
			c6 = vector(0,0,0)
		if(self.child['Q7'] != None):
			m7 = self.child['Q7'].Mass
			c7 = m7 * self.child['Q7'].center_of_mass
		else:
			m7 = 0
			c7 = vector(0,0,0)
		if(self.child['Q8'] != None):
			m8 = self.child['Q8'].Mass
			c8 = m8 * self.child['Q8'].center_of_mass
		else:
			m8 = 0
			c8 = vector(0,0,0)	
		self.Mass = m1+m2+m3+m4+m5+m6+m7+m8
		if(self.Mass == 0):
			error = True
			self.center_of_mass = self.center_point*1
		else:
			self.center_of_mass = (c1+c2+c3+c4+c5+c6+c7+c8) * (1.0/self.Mass)	
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
		deleteFromTree(self.child['Q1'])
		deleteFromTree(self.child['Q2'])
		deleteFromTree(self.child['Q3'])
		deleteFromTree(self.child['Q4'])
		deleteFromTree(self.child['Q5'])
		deleteFromTree(self.child['Q6'])
		deleteFromTree(self.child['Q7'])
		deleteFromTree(self.child['Q8'])
	else:
		try:
			del self
		except:
			print "cannot delete self"
def BuildTree():
	global root, buildTree
	try:
		if(root):
			deleteFromTree(root)
	except:
		print "No root defined YET"
	root = BHTreeNode(None)

	xmin = bodies[0].pos.x
	xmax = bodies[0].pos.x
	ymin = bodies[0].pos.y
	ymax = bodies[0].pos.y
	zmin = bodies[0].pos.z
	zmax = bodies[0].pos.z

	for i in range(numBodies):
		if (bodies[i].pos.x < xmin):
			xmin = bodies[i].pos.x
		if(bodies[i].pos.x > xmax):
			xmax = bodies[i].pos.x
		if(bodies[i].pos.y < ymin):
			ymin = bodies[i].pos.y
		if(bodies[i].pos.y > ymax):
			ymax = bodies[i].pos.y
		if(bodies[i].pos.z > zmax):
			zmax = bodies[i].pos.z
		if(bodies[i].pos.z < zmin):
			zmin = bodies[i].pos.z
			
	if(xmin == xmax):
		xmin -= 1
		xmax += 1
	if(ymin == ymax):
		ymin -= 1
		ymax += 1
	if(zmin == zmax):
		zmin -= 1
		zmax += 1

	xmin -= 50
	ymin -= 50
	zmin -= 50
	xmax += 50
	ymax += 50
	zmax += 50

	root.C1.x = xmin*1
	root.C1.y = ymin*1
	root.C1.z = zmin*1

	root.C3.x = xmax*1
	root.C3.y = ymax*1
	root.C3.z = zmax*1
	
	root.C2.x = xmax*1
	root.C2.y = ymin*1
	root.C2.z = zmin*1
	
	halfx = ( xmin + xmax ) * .5
	halfy = ( ymin + ymax ) * .5
	halfz = ( zmin + zmax ) * .5
	
	root.center_point = vector( halfx, halfy, halfz )
	
	del xmin, xmax, ymin, ymax, zmin, zmax
	buildChildren(root)
	
	for i in range(numBodies):
		addOneBodyToTree(root, bodies[i])
	buildTree = False
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
	if(   body.pos.z <= self.center_point.z and body.pos.x <= self.center_point.x and body.pos.y <= self.center_point.y ):
		which_child = 'Q1' #Octrent 1
	elif( body.pos.z <= self.center_point.z and body.pos.x > self.center_point.x and body.pos.y <= self.center_point.y  ):
		which_child = 'Q2' #Octrent 2
	elif( body.pos.z <= self.center_point.z and body.pos.x > self.center_point.x and body.pos.y > self.center_point.y   ):
		which_child = 'Q3' #Octrent 3
	elif( body.pos.z <= self.center_point.z and body.pos.x <= self.center_point.x and body.pos.y > self.center_point.y  ):
		which_child = 'Q4' #Octrent 4
	elif( body.pos.z > self.center_point.z and body.pos.x <= self.center_point.x and body.pos.y <= self.center_point.y  ):
		which_child = 'Q5' #Octrent 5
	elif( body.pos.z > self.center_point.z and body.pos.x > self.center_point.x and body.pos.y <= self.center_point.y   ):
		which_child = 'Q6' #Octrent 6
	elif( body.pos.z > self.center_point.z and body.pos.x > self.center_point.x and body.pos.y > self.center_point.y    ):
		which_child = 'Q7' #Octrent 7
	elif( body.pos.z > self.center_point.z and body.pos.x <= self.center_point.x and body.pos.y > self.center_point.y   ):
		which_child = 'Q8' #Octrent 8
	if(which_child == 'none'):
			print "Error - No child direction found"
	return which_child
# Function to generate the four children for a node	
def buildChildren(self):
	
	#Create Children as Tree Nodes#
	self.child['Q1'] = BHTreeNode(self)
	self.child['Q2'] = BHTreeNode(self)
	self.child['Q3'] = BHTreeNode(self)
	self.child['Q4'] = BHTreeNode(self)
	self.child['Q5'] = BHTreeNode(self)
	self.child['Q6'] = BHTreeNode(self)
	self.child['Q7'] = BHTreeNode(self)
	self.child['Q8'] = BHTreeNode(self)
	#Define Each of the childrens particular characteristics#
	
	setChildrenBoundaries(self)
	
def setChildrenBoundaries(self):
	
	C1 = self.C1*1
	C2 = self.C2*1
	C3 = self.C3*1
	CP = self.center_point*1
	
	child1 = self.child['Q1']
	child2 = self.child['Q2']
	child3 = self.child['Q3']
	child4 = self.child['Q4']
	child5 = self.child['Q5']
	child6 = self.child['Q6']
	child7 = self.child['Q7']
	child8 = self.child['Q8']

	#Child 1 BOX
	
	child1.C1 = C1*1
	child1.C2 = C1*1
	child1.C2.x = CP.x*1
	child1.C3 = CP*1
	child1.center_point = centerPointCalculation(child1.C1, child1.C2, child1.C3)
	
	#Child 2 BOX
	
	child2.C1 = child1.C2*1
	child2.C2 = C2*1
	child2.C3 = CP*1
	child2.C3.x = C2.x*1
	child2.center_point = centerPointCalculation(child2.C1, child2.C2, child2.C3)
	
	#Child 3 BOX
	
	child3.C1 = CP*1
	child3.C1.z = C1.z*1
	child3.C2 = C2*1
	child3.C2.y = CP.y*1
	child3.C3 = C3*1
	child3.C3.z = CP.z*1
	child3.center_point = centerPointCalculation(child3.C1, child3.C2, child3.C3)
	
	#Child 4 BOX
	
	child4.C1 = C1*1
	child4.C1.y = CP.y*1
	child4.C2 = child3.C1*1 
	child4.C3 = CP*1
	child4.C3.y = C3.y*1
	child4.center_point = centerPointCalculation(child4.C1, child4.C2, child4.C3)
	
	#Child 5 BOX
	
	child5.C1 = C1*1
	child5.C1.z = CP.z*1
	child5.C2 = child1.C2*1
	child5.C2.z = CP.z*1	
	child5.C3 = CP*1
	child5.C3.z = C3.z*1
	child5.center_point = centerPointCalculation(child5.C1, child5.C2, child5.C3)
	
	#Child 6 BOX
	
	child6.C1 = child5.C2*1
	child6.C2 = C2*1
	child6.C2.z = CP.z*1 
	child6.C3 = C3*1
	child6.C3.y = CP.y*1
	child6.center_point = centerPointCalculation(child6.C1, child6.C2, child6.C3)
	
	#Child 7 BOX
	
	child7.C1 = CP*1
	child7.C2 = CP*1
	child7.C2.x = C3.x*1
	child7.C3 = C3*1
	child7.center_point = centerPointCalculation(child7.C1, child7.C2, child7.C3)
	
	#Child 8 BOX
	
	child8.C1 = CP*1
	child8.C1.x = C1.x*1
	child8.C2 = CP*1
	child8.C3 = C3*1
	child8.C3.x = CP.x*1
	child8.center_point = centerPointCalculation(child8.C1, child8.C2, child8.C3)


def centerPointCalculation(point1, point2, point3):
	centerx = (point1.x + point2.x) * 0.5
	centery = (point2.y + point3.y) * 0.5
	centerz = (point1.z + point3.z) * 0.5
	return vector(centerx, centery, centerz)
#
######
#
#	Defining Tree Method Calculation functions
#
######
#

def TREE_POS_UPDATE(self):
	if( self.contained_bodies > 1 ):
		acceleration_calculation(self.child['Q1'], self.child['Q2'], self.child['Q3'], self.child['Q4'], self.child['Q5'], self.child['Q6'], self.child['Q7'], self.child['Q8'], self.Acceleration)
		for i in range(8):
			TREE_POS_UPDATE(self.child[childNodeMap[i]])
	elif( self.contained_bodies == 1 ):
		self.leaf_body.acc = self.Acceleration
		Force_Update_Method(self)

def acceleration_calculation(b1, b2, b3, b4, b5, b6, b7, b8, parent_influence):
	TEMP_BODIES = {0: b1, 1: b2, 2: b3, 3: b4, 4: b5, 5: b6, 6: b7, 7: b8}
	for i in range(8):
		for j in range(7):
			k = j + i + 1
			if( k < 8):
				if(TEMP_BODIES[i].Mass != 0 and TEMP_BODIES[k].Mass != 0):
					TEMP_FORCE = getForceNodes(TEMP_BODIES[i], TEMP_BODIES[k])
					TEMP_BODIES[i].Acceleration += (TEMP_FORCE/(TEMP_BODIES[i].Mass*1.0) + parent_influence)
					TEMP_BODIES[k].Acceleration -= (TEMP_FORCE/(TEMP_BODIES[k].Mass*1.0) + parent_influence)
				
def Force_Update_Method(self):
	method = getMethod()
	switch = {1: Euler, 2: Verlet}
	switch[method](self)

def Euler(self):
	global buildTree
	bd = self.leaf_body
	bd.vel += bd.acc*dt
	bd.pos += bd.vel*dt
	if( bd.pos.x < self.C1.x or bd.pos.x > self.C2.x or bd.pos.y < self.C2.y or bd.pos.y > self.C3.y or bd.pos.z < self.C1.z or bd.pos.z > self.C3.z): 
		buildTree = True
	setCenterAndMass(self)
	
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
	TEMP_CURVE = curve(pos=[(Node.C1.x, Node.C1.y, Node.C1.z),(Node.C2.x, Node.C2.y, Node.C2.z),(Node.C2.x, Node.C3.y, Node.C2.z),(Node.C1.x, Node.C3.y, Node.C1.z),(Node.C1.x, Node.C1.y, Node.C1.z),(Node.C1.x, Node.C1.y, Node.C3.z),(Node.C1.x, Node.C3.y, Node.C3.z),(Node.C1.x, Node.C3.y, Node.C1.z),(Node.C1.x, Node.C3.y, Node.C3.z),(Node.C3.x, Node.C3.y, Node.C3.z),(Node.C2.x, Node.C3.y, Node.C2.z),(Node.C2.x, Node.C2.y, Node.C2.z),(Node.C2.x, Node.C2.y, Node.C3.z),(Node.C3.x, Node.C3.y, Node.C3.z),(Node.C2.x, Node.C2.y, Node.C3.z),(Node.C1.x, Node.C1.y, Node.C3.z)])
	treeCurves.append( TEMP_CURVE )
	
def drawTree(Node):
	generateCurve(Node)
	if(Node.contained_bodies > 1):
		drawTree(Node.child['Q1'])
		drawTree(Node.child['Q2'])
		drawTree(Node.child['Q3'])
		drawTree(Node.child['Q4'])
		drawTree(Node.child['Q5'])
		drawTree(Node.child['Q6'])
		drawTree(Node.child['Q7'])
		drawTree(Node.child['Q8'])

######################################################################

def newRadius(M):
        global bodies
        return (((4/3)*pi*M*density)**(1.0/3.0))

######################################################################

# Set Constants
dt = .01
density = 5
G = 1
integrationMethod = 1
retain = True
reduced = False
#global dictionary to go between 0,1,2,3 and ul, ur, dl, dr values
childNodeMap = {0: 'Q1', 1: 'Q2', 2: 'Q3', 3: 'Q4', 4: 'Q5', 5: 'Q6', 6: 'Q7', 7: 'Q8'}		
# Soften radius of objects at very close range by this amount aka minimum allowed distance
softenCloseRange = 1
# Initialize Global Variables in the System

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
					temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos']*1, vel=d['vel']*1, acc=vector(0,0,0), mass=d['mass'], color=(.75,.75,.75), retain=10000, radius=newRadius(d['mass'])  )
					bodies.append( temp )
				else:
					temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos']*1, vel=d['vel']*1, acc=vector(0,0,0), mass=d['mass'], color=(.75,.75,.75), retain=10000, radius=newRadius(d['mass'])  )
					bodies.append( temp )
		fd.close()
	del fd

#Global Variables
bodies = []
treeCurves = []
time = [0]
numBodies = len(bodies)                  
finished = False
t = 0
calculations = 0
error = 0
buildTree = True

scene1 = display( title="N-Body Gravity", x=700, y=200, width=500, height=500)
scene1.autoscale = True
getConfig()
numBodies = len(bodies)
BuildTree()
drawFullTree()
wait = raw_input("Enter to continue")
integrationMethod = 1 # Euler Integration
treesBuilt = 0
while(t < 10000):
	if(buildTree == True):
		BuildTree()
		drawFullTree()
		treesBuilt+=1
	TREE_POS_UPDATE(root)
	t+=1
	print "t :"
	print t
	print "trees: "
	print treesBuilt