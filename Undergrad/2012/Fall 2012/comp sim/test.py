from visual import *

scene.width = 800
scene.height = 600

scene.autoscale = 0
scene.range = (100, 100, 100)
scene.center = (0, 40, 0)

ball = sphere(pos=(0,100,0), radius=10, material=materials.earth)
ground = box(pos=(0,-1,0), size=(100,2,100))

g = 9.8 # m/s
seconds = 0
dt = .01

finished = False
while not finished:
    rate(100)   # go thru the loop no more than 100 times / sec
    seconds += dt

    # position equation: y(t) = y0 + v0*t + .5 *a * t**2
    ballHeight = 100 - .5 * g * seconds**2

    ball.pos = vector(0, ballHeight, 0)

    if ballHeight <= 10:
        finished = True
        print("seconds to drop:" + str(seconds)) 

