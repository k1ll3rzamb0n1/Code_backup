# COMP/EGMT 155
#
# Plants and animals simulation based on cellular automata

from cell_graphics import *
from cell_space import *
from PA_Cell import *
from random import *
from math import *

# number of simulation frames before a graphics are updated
sim_draw_ratio = 1

# parameters controlling animal population

# ADD YOUR PARAMETERS HERE

# parameters controlling plant population

# ADD YOUR PARAMETERS HERE
abk = .5
adk = .01
pgk = .5
apk = 1


# parameters controlling sun
sun_period = 20
if sun_period > 0.0:
	sun_multiplier = (2.0*pi)/sun_period
else:
	sun_multiplier = 0.0

# simulation controller class
class PlantsAndAnimals:

	# constructor
	def __init__(self, cols, rows, cell_width):

		self.cols = cols
		self.rows = rows
		self.cell_width = cell_width
        
		win_x_size = self.cols * self.cell_width
		win_y_size = self.rows * self.cell_width
		self.win = CellGraphics("Plants and Animals", win_x_size, win_y_size)

		self.lastBoard = CellSpace(self.cols, self.rows)
		self.initBoard(self.lastBoard, 0)
		self.currBoard = CellSpace(self.cols, self.rows)
		self.initBoard(self.currBoard, 1)
		self.sun = 0
		self.time = 0
		
		self.animal_record = []
		self.plant_record = []
		self.sun_record = []
       
	# shutdown simulation and program       
	def close(self):
		self.win.close()

	# pause and wait for a mouse click		
	def pause(self):
		self.win.getMouse()

	# record a mouse click
	def mouseWasClicked(self):
		return self.win.mouseWasClicked()

	# initialize the simulation        
	def initBoard(self, board, mode):
		if mode==0: # empty board
			for row in range(self.rows):
				for col in range(self.cols):
					board.setCell(col,row,PA_Cell(0,0))
		else: # randomized board
			for row in range(self.rows):
				for col in range(self.cols):
					a = 0
					p = 0
					chance = random()
					if chance > 0.9: 
						a = 20
					chance = random()
					if chance > 0.9: 
						p = 20
					board.setCell(col,row,PA_Cell(p,a))

	# one time step in simulation
	# this method implements the primary simulation logic
	def update(self):
		total_animals = 0
		total_plants = 0
		self.time = self.time + 1
		self.sun = 100.0*sin(sun_multiplier*self.time)
		if self.sun < 0: self.sun = 0
		
		# swap the cell buffers
		temp = self.lastBoard
		self.lastBoard = self.currBoard
		self.currBoard = temp
				
		# update new board based on old board
		for row in range(self.rows):
			for col in range(self.cols):
				
				# current populations in this cell
				
				this_cell = self.lastBoard.getCell(col,row)
				p0 = this_cell.getPlantLife()
				a0 = this_cell.getAnimalLife()
				
				# count plants and animals in the neighboring cells

				p1 = p2 = p3 = p4 = 0
				a1 = a2 = a3 = a4 = 0
				# west neighbor
				c=col-1		
				r=row
				if self.lastBoard.validCell(c,r):
					neighbor = self.lastBoard.getCell(c,r)
					p1 = neighbor.getPlantLife()
					a1 = neighbor.getAnimalLife()
				# east neighbor
				c=col+1		
				r=row
				if self.lastBoard.validCell(c,r):
					neighbor = self.lastBoard.getCell(c,r)
					p2 = neighbor.getPlantLife()
					a2 = neighbor.getAnimalLife()
				# north neighbor
				c=col		
				r=row-1
				if self.lastBoard.validCell(c,r):
					neighbor = self.lastBoard.getCell(c,r)
					p3 = neighbor.getPlantLife()
					a3 = neighbor.getAnimalLife()
				# south neighbor
				c=col		
				r=row+1
				if self.lastBoard.validCell(c,r):
					neighbor = self.lastBoard.getCell(c,r)
					p4 = neighbor.getPlantLife()
					a4 = neighbor.getAnimalLife()	
					
# ADD YOUR SIMULATION RULES HERE

#Rules Start

#define pgk (plant growth constant), apk (animal eating plants constant), abk (animal birth constant), adk (animal death constant)

				Growthp0 = pgk*(self.sun + .01)*(p0 + .25*p1 + .25*p2 + .25*p3 + .25*p4)
				Deathp0 = a0*apk

				Growtha0 = abk*a0 + int(random()*1000)%2
				Deatha0 = adk*a0
					
				a0 += Growtha0 - Deatha0
				p0 += Growthp0 - Deathp0

				if (p0 < 0):
					p0 = 0
				elif (p0 > 255):
					p0 = 255
				if (a0 < 0):
					a0=0

				if (p0 == 0):
					c = col-1
					r = row
					if self.lastBoard.validCell(c,r):
						neighbor = self.currBoard.getCell(c,r)
						newa = a1 + (1/4)*a0
						neighbor.setAnimalLife(newa)
					c = col+1
					r = row
					if self.lastBoard.validCell(c,r):
						neighbor = self.currBoard.getCell(c,r)
						newa = a2 + (1/4)*a0
						neighbor.setAnimalLife(newa)
					c = col
					r = row+1
					if self.lastBoard.validCell(c,r):
						neighbor = self.currBoard.getCell(c,r)
						newa = a3 + (1/4)*a0
						neighbor.setAnimalLife(newa)
					c = col
					r = row-1					
					if self.lastBoard.validCell(c,r):
						neighbor = self.currBoard.getCell(c,r)
						newa = a4 + (1/4)*a0
						neighbor.setAnimalLife(newa)
					a0 = 0
					
				#
				#
				#
				#
				#
				

				#Rules End
				
				# store new populations
				this_cell = self.currBoard.getCell(col,row)
				this_cell.setPlantLife(p0)	
				this_cell.setAnimalLife(a0)
				
				# accumulate total populations
				total_animals = total_animals + a0
				total_plants = total_plants + p0
				
		self.animal_record.append(total_animals)
		self.plant_record.append(total_plants)
		self.sun_record.append(self.sun)

	# update the graphics								
	def show(self):
		y = 0.0
		w = self.cell_width
		for row in range(self.rows):
			x = 0.0
			for col in range(self.cols):
				if (row==0) and (col==0):
					sun_saturtation = int(255*(self.sun/100))
					color = (sun_saturtation, sun_saturtation, 0)
				else:
					color = self.currBoard.getCell(col,row).getColor()
				self.win.drawCell(x,y,w,w,color)
				x = x+w
			y = y+w
	
	# write recorded data to a file for plotter
	def saveFile(self, filename, data):
		ofile = open(filename, "w")
		min = data[0]
		max = data[0]
		for x in data:
			if (x<min): min = x
			if (x>max): max = x
		ofile.write("%d, %d, %d, %d\n" % (1, min, len(data), max))
		ofile.write("%d\n" % len(data))
		i = 1
		for x in data:
			ofile.write("%d, %d\n" % (i, x))
			i = i + 1
		ofile.close()
		
	# store recorded populations for plotter
	def storeResults(self):
		self.saveFile("animals.txt", self.animal_record)
		self.saveFile("plants.txt", self.plant_record)
		self.saveFile("sun.txt", self.sun_record)

# main program

draw_counter = 0
life = PlantsAndAnimals(20, 20, 20)
while True:
  # draw when needed
	if (draw_counter == 0):
		life.show()
	draw_counter = draw_counter + 1
	if (draw_counter >= sim_draw_ratio):
		draw_counter = 0

	# shutdown when mouse is clicked
	if life.mouseWasClicked():
		life.storeResults()
		break
	
	# move simulation forward one time step.
	life.update()
	
life.close()





