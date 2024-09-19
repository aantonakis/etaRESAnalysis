import ROOT
import sys
import os
import numpy as np


sys.path.append(os.path.abspath('../src/'))

from branches import *
from helpers import *
from labels import *


infile = ROOT.TFile.Open(sys.argv[1], "READ")
fig_dir = "../../Figs/TPCEtaNoCosmic/"


# Get the trees and histos from the input file
hist_tot_pot = infile.Get("TotalPOT")
recTree = infile.Get("recTree")


diphoton_inv_mass = []

# Event Loop

evCount = 0
for event in recTree:
	if evCount%10 == 0:
		print("Event Count", evCount)

	# Load all branches

	# Slices
	slc_br = load_branches(event, slc_branches)

	# PFP high level branches
	pfp_br = load_branches(event, pfp_branches)
	
	# reco tracks
	trk_br = load_branches(event, pfp_trk_branches)
	
	# reco showers
	shw_br = load_branches(event, pfp_shw_branches)

	# Finished loading branches
	
        # Loop over the slices in this event
	for num in range(len(slc_br["rec.slc.self"])):
		shw_idxs = get_showers(slc_br["rec.slc.self"][num], pfp_br, 0.6)	
		#print("Number of Showers", len(shw_idxs))
		# select slices with exactly 2 showers 
		if 1 < len(shw_idxs):
			new_idxs = []
			for idx in shw_idxs:
				if shw_br["rec.slc.reco.pfp.shw.conversion_gap"][idx] > 20:
					new_idxs.append(idx)

			if len(new_idxs) == 2:

				conv1 = shw_br["rec.slc.reco.pfp.shw.conversion_gap"][new_idxs[0]]
				conv2 = shw_br["rec.slc.reco.pfp.shw.conversion_gap"][new_idxs[1]]
				E1 = shw_br["rec.slc.reco.pfp.shw.bestplane_energy"][new_idxs[0]]
				E2 = shw_br["rec.slc.reco.pfp.shw.bestplane_energy"][new_idxs[1]]
				if E1 > 0.05 and E2 > 0.05:
					dir1x = shw_br["rec.slc.reco.pfp.shw.dir.x"][new_idxs[0]]			
					dir1y = shw_br["rec.slc.reco.pfp.shw.dir.y"][new_idxs[0]]			
					dir1z = shw_br["rec.slc.reco.pfp.shw.dir.z"][new_idxs[0]]			
					dir2x = shw_br["rec.slc.reco.pfp.shw.dir.x"][new_idxs[1]]			
					dir2y = shw_br["rec.slc.reco.pfp.shw.dir.y"][new_idxs[1]]			
					dir2z = shw_br["rec.slc.reco.pfp.shw.dir.z"][new_idxs[1]]			
					dir1 = np.array([dir1x, dir1y, dir1z])
					dir2 = np.array([dir2x, dir2y, dir2z])
					costheta = np.dot(dir1, dir2)
					print("E1", E1, "E2", E2)
					print("dir1", dir1)
					print("dir2", dir2)
					print("conv1", conv1)
					print("conv2", conv2)
					print("costheta", costheta)
			
					M = np.sqrt(2*E1*E2*(1 - costheta))

					diphoton_inv_mass.append(M)

	# increment the event count before going to the next event
	evCount += 1


# plotting ... 


h_diphoton_inv_mass = ROOT.TH1D("h_inv_mass", "", 30, 0, 1.1*max(diphoton_inv_mass))
for num in diphoton_inv_mass:
	h_diphoton_inv_mass.Fill(num)

c = ROOT.TCanvas("c", "c", 700, 500)
h_diphoton_inv_mass.SetStats(0)
h_diphoton_inv_mass.SetLineWidth(2)
h_diphoton_inv_mass.SetLineColor(4)
h_diphoton_inv_mass.Draw("HISTE")
h_diphoton_inv_mass.GetXaxis().SetTitle("#M_{#gamma#gamma} [GeV]")
c.SaveAs(fig_dir+"test_simple_diphoton_inv_mass_nocut.png")


