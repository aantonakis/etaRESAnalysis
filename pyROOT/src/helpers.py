import numpy as np
from branches import *


# make a dictionary of branch values for a particular event
def load_branches(event, brnchs):
	mc_dict = {}
	for br in brnchs:
		mc_dict[br] = getattr(event, br)	
	return mc_dict


# Get all of the pfp indices associated with a slice
def get_slice_pfps(sliceID, pfp_br):
	pfp_slices = pfp_br["rec.slc.reco.pfp.slcID"]
	return [i for i, x in enumerate(pfp_slices) if x == sliceID]	



# get all showers in a slice based on a track score
def get_showers(sliceID, pfp_br, score):
	pfps = get_slice_pfps(sliceID, pfp_br)
	shw_indices = []
	for idx in pfps:
		if pfp_br["rec.slc.reco.pfp.trackScore"][idx] < score:
			shw_indices.append(idx)

	return shw_indices


# return all of the true primary indices associated with this slice
def get_slc_true_prim(slc_idx, slc_mc_br):
	prim_indices = []
	nprim = slc_mc_br['rec.slc.truth.nprim']
	prim_start = 0
	for num in range(0, slc_idx):
		prim_start += nprim[num]
	
	for num in range(nprim[slc_idx]):
		prim_indices.append(prim_start + num)
	
	return prim_indices


def get_true_eta_mult(slc_idx, slc_mc_br):
	prim_indices = get_slc_true_prim(slc_idx, slc_mc_br)
	pdgs = [slc_mc_br["rec.slc.truth.prim.pdg"][num] for num in prim_indices]
	return pdgs.count(221)


