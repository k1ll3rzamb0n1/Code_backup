# COMP/EGMT 155
#
# Program to create a graphical plot of functions
# stored as points read from a text file.
#
# This program will plot the output from the 
# plants_and_animals.py program.

from graphics import *
from string import *

#---------------------------------------------------
# Function to transform a point in the
# function's coordinate system to a point
# in the graphics window's coordinate system.

def transformPoint(p, x_min, y_min, x_max, y_max):
    x = p.getX()
    y = p.getY()
    if (x_max==x_min):
    	x = 1
    else:
    	x = (x-x_min)/(x_max-x_min)
    if (y_max==y_min):
    	y = 1
    else:	
    	y = (y-y_min)/(y_max-y_min)
    x = x*win_x_size
    y = (1.0 - y)*win_y_size
    return Point(x,y)

#---------------------------------------------------
# Function to plot a graph from points stored
# in a text file.

def plot(filename, color):
    # open the text file and read the number of points
    infile = open(filename, "r")
    s = split(infile.readline(), ",")
    x_min = float(s[0])
    y_min = float(s[1])
    x_max = float(s[2])
    y_max = float(s[3])
    num_points = int(infile.readline())

    # for each point:
    for i in range(num_points):

        # read line of text containing point and
        # parse it into x and y values
        s = infile.readline()
        (s1, s2) = split(s, ",")
        x = float(s1)
        y = float(s2)

        # transform the point into the graphics
        # window coordinates
        p = transformPoint(Point(x,y), x_min, y_min, x_max, y_max)

        # Draw a circle to represent a transformed point
        c = Circle(p, 2)
        c.setFill(color)
        c.setOutline(color)
        c.draw(win)

#---------------------------------------------------
# main program

# define global parameters 
win_x_size = 600.0
win_y_size = 300.0

# create a graphics window
win = GraphWin("Plotter", win_x_size, win_y_size)

# plot data from three text files in different colors
plot("animals.txt", "red")
plot("plants.txt", "green")
plot("sun.txt", "blue")

# wait for a mouse click and then close the graphics
win.getMouse()
win.close()





