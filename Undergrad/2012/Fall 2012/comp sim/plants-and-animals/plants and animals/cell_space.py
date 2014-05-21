# COMP155
#
# A CellSpace is a 2D matrix of numbers.

class CellSpace:
	def __init__(self, cols, rows):
		self.cols = cols
		self.rows = rows
		self.cells = [0]*(cols*rows)

	def setCell(self, col, row, value):
		if self.validCell(col, row):
			self.cells[row*self.cols+col] = value

	def getCell(self, col, row):
		if self.validCell(col, row):
			return self.cells[row*self.cols+col]
		else:
			return None

	def getCols(self):
		return self.cols
    
	def getRows(self):
		return self.rows

	def setAllCells(self, value):
		for c in range(self.cols):
			for r in range(self.rows):
				self.setCell(c,r,value)
                
	def validCell(self, col, row):
		return (col>=0) and (row>=0) and (col<self.cols) and (row<self.rows)