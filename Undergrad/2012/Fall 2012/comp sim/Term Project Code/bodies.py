#
#       N-Body: Gravitational Simulation
#       Done in Visual Python By:
#               - Ryan Bleile
#
#

#imports
from visual import *
from visual.filedialog import get_file
from visual.filedialog import save_file
from visual.controls import *
from visual.graph import *

######################################################################
#
#       Defining all function at the top
#
######################################################################

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
                        force = (-G*object1.mass*object2.mass*r) /(r.mag**3)

                        bodies[i].acc += force*(1.0/object1.mass)
                        bodies[j].acc -= force*(1.0/object2.mass)
def eulerIntegrateReduced():
        global bodies
        if(numBodies != 1):
                getAccAllReduced()
                for i in range(numBodies):
                        #update velocity and position from acceleration
                        bodies[i].vel += bodies[i].acc*dt
                        bodies[i].pos += bodies[i].vel*dt
                        #reset acc to zero for next update
                        bodies[i].acc = vector(0,0,0)
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

# Initialize Global Variables in the System

bodies = []
time = [0]

        
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

## Get Configuration From File
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
                                temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos'], vel=d['vel'], acc=vector(0,0,0), mass=d['mass'], color=d['color'], retain=10000, radius=newRadius(d['mass'])  )
                                bodies.append( temp )
                        else:
                                temp = sphere(make_trail=d['make_trail'], display=scene1, pos=d['pos'], vel=d['vel'], acc=vector(0,0,0), mass=d['mass'], color=d['color'], radius=newRadius(d['mass'])  )
                                bodies.append( temp )
        fd.close()

numBodies = len(bodies)
                        
finished = False
t = 0
calculations = 0
error = 0

print integrationMethod

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

