# COMP/EGMT 155
#
# cell_graphics.py: A window that draws rectangles.

import Tkinter
tk = Tkinter
_root = tk.Tk()
_root.withdraw()

class CellGraphics(tk.Canvas):

	def __init__(self, title="Cell Graphics", width=200, height=200):
		master = tk.Toplevel(_root)
		master.protocol("WM_DELETE_WINDOW", self.close)
		tk.Canvas.__init__(self, master, width=width, height=height)
		self.master.title(title)
		self.pack()
		master.resizable(0,0)
		self.mousePoint = None
		self.bind("<Button-1>", self._onClick)
		self.config(bg="black")

		self.draw_config = {}
		self.draw_config["outline"] = "black"
		self.draw_config["width"] = "1"
		self.draw_config["fill"] = "red"
		_root.update()

	def close(self):
		self.master.destroy()
		self.quit()
		_root.update()
       
	def getMouse(self):
		self.mousePoint = None
		while self.mousePoint == None:
			self.update()
		return self.mousePoint
	def mouseWasClicked(self):
		return self.mousePoint != None
       
	def _onClick(self, e):
		self.mousePoint = (e.x, e.y)
	def drawCell(self, x, y, dx, dy, color):
		color_code = "#%02x%02x%02x" % (color[0], color[1], color[2])
		self.draw_config["fill"] = color_code    
		self.create_rectangle(x, y, x+dx, y+dy,self.draw_config)
		_root.update()
