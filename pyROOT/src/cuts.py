import numpy as np



def isTPC(vtx):
	if abs(vtx[0]) < 200 and abs(vtx[1]) < 200 and abs(vtx[2]) < 500:
		return True
	return False



