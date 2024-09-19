import numpy as np
import ROOT
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


def get_prim_eta_indices(slc_idx, slc_mc_br):
	prim_idxs = get_slc_true_prim(slc_idx, slc_mc_br)
	eta_idxs = []
	for idx in prim_idxs:
		if slc_mc_br["rec.slc.truth.prim.pdg"][idx] == 221:
			eta_idxs.append(idx)
	return eta_idxs


def get_prim_pi0_mult(slc_idx, slc_mc_br):
	prim_indices = get_slc_true_prim(slc_idx, slc_mc_br)
	pdgs = [slc_mc_br["rec.slc.truth.prim.pdg"][num] for num in prim_indices]
	return pdgs.count(111)



def is_slc_RES(slc_idx, slc_mc_br):
	if slc_mc_br["rec.slc.truth.genie_mode"][slc_idx] == 1:
		return 1
	return 0



def get_slc_eta_info(slc_idx, slc_mc_br):
	eta_idxs = get_prim_eta_indices(slc_idx, slc_mc_br)
	nuID = slc_mc_br["rec.slc.truth.pdg"][slc_idx]
	mode = slc_mc_br["rec.slc.truth.genie_mode"][slc_idx]
	Npi0 = get_prim_pi0_mult(slc_idx, slc_mc_br)
	E = slc_mc_br["rec.slc.truth.prim.genE"][eta_idxs[0]]
	return [nuID, mode, Npi0, E]


# Histogram Helpers ....



def make_unique_counts_hist(arr, name):
	unique_elements = list(set(arr))
	h = ROOT.TH1D(name, "", len(unique_elements), 0, len(unique_elements))
	for num in range(len(unique_elements)):
		h.SetBinContent(num + 1, arr.count(unique_elements[num]))
		h.GetXaxis().SetBinLabel(num + 1, str(unique_elements[num]))
	return h




