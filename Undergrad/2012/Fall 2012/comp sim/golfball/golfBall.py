#import visual python
from visual import *
from visual.graph import *

#Initializing variables and scene

floor = box (pos=(0,-1,0), length=20, height=2, width=20, color=color.green)

dt = 0.01
K = .016252  #calculated from air density and ball mass and ...
g = 9.8
t = 0

#how long to run the for loop
#   (how many seperate simulations to run)
numPlots = 100

funct = gdots(color=color.red)

#6000 RPM
#drag = [ .55, .48, .4, .35, .3, .29 ]
#lift = [ .48, .41, .35, .3, .225, .19 ]

#3000 RPM
drag = [ .41, .38, .3, .28, .27, .27 ]
lift = [ .299, .29, .25, .19, .15, .13 ]

finished = False

def rungeFy(v): #Runge-Kutta Function for Acceleration Y
    theta = vector(v.x,v.y,0).diff_angle(vector(1,0,0))
    return ( K * v.mag2 * (CL(v)*cos(theta) - CD(v)*sin(theta)) - g )
def rungeFx(v): #Runge-Kutta Function for Acceleration X
    theta = vector(v.x,v.y,0).diff_angle(vector(1,0,0))
    return ( - K * v.mag2 * (CD(v)*cos(theta) + CL(v)*sin(theta)))

def extrapolate(value, y1, y2, x1, x2): # Linear Extrapolation
    m = ( y1 - y2 ) / (x2 - x1)
    return m*(value - x1) + y1

def CD(velocity): #drag function
    if velocity.mag < 13:
        return drag[0]
    elif velocity.mag < 20:
        return extrapolate(velocity.mag, drag[0], drag[1], 13, 20)
    elif velocity.mag < 30:
        return extrapolate(velocity.mag, drag[1], drag[2], 20, 30)
    elif velocity.mag < 40:
        return extrapolate(velocity.mag, drag[2], drag[3], 30, 40)
    elif velocity.mag < 60:
        return extrapolate(velocity.mag, drag[3], drag[4], 40, 60)
    elif velocity.mag < 80:
        return extrapolate(velocity.mag, drag[4], drag[5], 60, 80)
    else:
        return drag[5]

def CL(velocity): #lift function
    
    if velocity.mag < 13:
        return lift[0]
    elif velocity.mag < 20:
        return extrapolate(velocity.mag, lift[0], lift[1], 13, 20)
    elif velocity.mag < 30:
        return extrapolate(velocity.mag, lift[1], lift[2], 20, 30)
    elif velocity.mag < 40:
        return extrapolate(velocity.mag, lift[2], lift[3], 30, 40)
    elif velocity.mag < 60:
        return extrapolate(velocity.mag, lift[3], lift[4], 40, 60)
    elif velocity.mag < 80:
        return extrapolate(velocity.mag, lift[4], lift[5], 60, 80)
    else:
        return lift[5]
distanceData = []
angleData = []
velocityData = []
points = []
for i in range(numPlots):

#a
    angleOff = 1+i*.5
    magnitude = 60
#b
#   angleOff = 20
#   magnitude = 50 + 5*i
    angleOffRad = angleOff * (pi/180)

    x = magnitude*cos(angleOffRad)
    y = magnitude*sin(angleOffRad)
    z = 0
    ax = 0
    ay = 0
    az = 0


    ball = sphere (pos=(0,1,0), radius=1, color=color.green, make_trail=True)
    ball.velocity = vector(x,y,z)
    ball.acceleration = vector(ax,ay,az)

    ball2 = sphere (pos=(0,1,0), radius=1, color=color.red, make_trail=True)
    ball2.velocity = vector(x,y,z)
    ball2.acceleration = vector(ax,ay,az)

    balllanded1 = False
    balllanded2 = False
    finished = False
    
    while not finished:
        #Max frames per second
        #rate(50)

        #update Ball Position - Green
        ball.pos = ball.pos + ball.velocity*dt

        #update Ball Position - Red
        ball2.pos = ball2.pos + ball2.velocity*dt

        #Define angle above x-axis
        theta = ball2.velocity.diff_angle(vector(1,0,0))

        #Calculate Accelerations for red ball
        ball2.acceleration.x = - K * ball2.velocity.mag2 * (CD(ball2.velocity)*cos(theta) + CL(ball2.velocity)*sin(theta))
        ball2.acceleration.y = K * ball2.velocity.mag2 * (CL(ball2.velocity)*cos(theta) - CD(ball2.velocity)*sin(theta)) - g

        #Euler Update Velocity Red ball
        ball2.velocity.y = ball2.velocity.y + ball2.acceleration.y*dt
        ball2.velocity.x = ball2.velocity.x + ball2.acceleration.x*dt

        
    #Runge_Kutta 4 Y Velocity Update Green Ball
        
        k1 = rungeFy(ball.velocity)*dt
        k2 = rungeFy(vector(ball.velocity.x, ball.velocity.y + dt*k1/2, ball.velocity.z))*dt
        k3 = rungeFy(vector(ball.velocity.x, ball.velocity.y + dt*k2/2, ball.velocity.z))*dt
        k4 = rungeFy(vector(ball.velocity.x, ball.velocity.y + dt*k3, ball.velocity.z))*dt
        ball.acceleration.y = (1.0/6)*(k1+2*k2+2*k3+k4)
        ball.velocity.y = ball.velocity.y + ball.acceleration.y
    #Runge_Kutta 4 X Velocity Update Green Ball
        k1 = rungeFx(ball.velocity)*dt
        k2 = rungeFx(vector(ball.velocity.x + dt*k1/2, ball.velocity.y, ball.velocity.z))*dt
        k3 = rungeFx(vector(ball.velocity.x + dt*k2/2, ball.velocity.y, ball.velocity.z))*dt
        k4 = rungeFx(vector(ball.velocity.x + dt*k3, ball.velocity.y, ball.velocity.z))*dt
        ball.acceleration.x = (1.0/6)*(k1+2*k2+2*k3+k4)
        ball.velocity.x = ball.velocity.x + ball.acceleration.x

        if ball.pos.y < 0:
            if balllanded1 == False:
                print "Green Ball landed: " + str(ball.pos.x) + " meters away"
                ball.visible = False
                ball.make_trail = False
                balllanded1 = True
        if ball2.pos.y < 0:
            if balllanded2 == False:
                print "Red Ball landed: " + str(ball2.pos.x) + " meters away"
                ball2.visible = False
                ball2.make_trail = False
                balllanded2 = True

        t += dt

        if (balllanded1 & balllanded2):
            finished = True

    print "time till both landed " + str(t) + " seconds"
    print "Angle off: " + str(angleOff)
    print "Starting Magnitude: " + str(magnitude)
    distanceData.append(ball.pos.x)
    angleData.append(angleOff)
    velocityData.append(magnitude)
tempMax = 0
for j in range(numPlots):
    if distanceData[j] > tempMax:
        tempMax = distanceData[j]
    print "Initial angle: " + str(angleData[j])
    print "Distance: " + str(distanceData[j])
    points.append( (angleData[j], distanceData[j]) )
#for j in range(numPlots):
#    if distanceData[j] > tempMax:
#        tempMax = distanceData[j]
#    print "Initial Velocity: " + str(velocityData[j])
#    print "Distance: " + str(distanceData[j])
#    points.append( (velocityData[j], distanceData[j]) )

data = gdots(pos=points, color=color.blue)
funct1 = gcurve(color=color.red)
for x in arange(0., 50.1, 0.1):
    funct1.plot(pos=(x,tempMax))
