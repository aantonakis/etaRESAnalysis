import numpy as np
from branches import *



def load_branches(event, brnchs):
	mc_dict = {}
	for br in brnchs:
		mc_dict[br] = getattr(event, br)	
	return mc_dict



