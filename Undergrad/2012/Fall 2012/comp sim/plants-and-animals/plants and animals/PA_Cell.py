# COMP/EMGT 155
#
# A PA_Cell stores the plant and animal life in one cell

class PA_Cell:
	def __init__(self, p, a):
		self.plant_life = p
		self.animal_life = a

	def setPlantLife(self, value):
		self.plant_life = value
        
	def getPlantLife(self):
		return self.plant_life
 
	def setAnimalLife(self, value):
		self.animal_life = value
         
	def getAnimalLife(self):
		return self.animal_life
        
	def getColor(self):
		plant_density = int(255*(self.plant_life/10.0))
		if (plant_density > 255): 
			plant_density = 255
		animal_density = int(255*(self.animal_life/10.0))
		if (animal_density > 255): 
			animal_density = 255			
		return(animal_density, plant_density, 0)
