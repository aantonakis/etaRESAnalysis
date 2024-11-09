import ROOT
import sys
import os
import numpy as np


sys.path.append(os.path.abspath('../src/'))

from branches import *
from helpers import *

infile = ROOT.TFile.Open(sys.argv[1], "READ")
outfile = ROOT.TFile(sys.argv[2], "RECREATE")


fig_dir = "../../Figs/TPCEtaNoCosmic/"


# Expectation is something like the following ...
"""
 KEY: TDirectoryFile	env;1	env
  KEY: TH1D	TotalPOT;1	TotalPOT
  KEY: TH1D	TotalEvents;1	TotalEvents
  KEY: TTree	recTree;1	recTree
  KEY: TTree	GenieEvtRecTree;1	GenieEvtRecTree
  KEY: TDirectoryFile	metadata;1	metadata
"""

# Get the trees and histos from the input file
hist_tot_pot = infile.Get("TotalPOT")
recTree = infile.Get("recTree")
#GenieEvtRecTree = infile.Get("GenieEvtRecTree")


# Event Loop

slc_true_pdgs = []
num_prim_true_etas_per_slc = []
num_pi0_per_eta = []

slc_tree = ROOT.TNtuple("slc_tree", "slc_tree", "run:subrun:evt:slc:pdg:iscc:isnc:mode:vtx_x:vtx_y:vtx_z")
mc_prim_tree = ROOT.TNtuple("mc_prim_tree", "mc_prim_tree", "slc:pdg:genE:px:py:pz:start_x:start_y:start_z:end_x:end_y:end_z")


evCount = 0
for event in recTree:
	if evCount%10 == 0:
		print("Event Count", evCount)

	# Load all branches

	hdr_br = load_branches(event, hdr_branches)

	run = hdr_br["rec.hdr.run"]
	subrun = hdr_br["rec.hdr.subrun"]
	evt = hdr_br["rec.hdr.evt"]

	if evCount%10 == 0:
		print("run", run, "subrun", subrun, "evt", evt)

	# Pure Truth Info
	mc_br = load_branches(event, mc_branches)
	mc_prim_br = load_branches(event, mc_prim_branches)

	#nu_iscc_vec = mc_br["rec.mc.nu.iscc"]
	#print("len of nu_iscc_vec", len(nu_iscc_vec))
	#print("nu_iscc", nu_iscc_vec)
	

	# Slices
	slc_br = load_branches(event, slc_branches)
	slc_mc_br = load_branches(event, slc_mc_branches)

	slc_vec = slc_br["rec.slc.self"]
	
	slc_pdg_vec = slc_mc_br["rec.slc.truth.pdg"]
	slc_iscc_vec = slc_mc_br["rec.slc.truth.iscc"]
	slc_isnc_vec = slc_mc_br["rec.slc.truth.isnc"]
	slc_mode_vec = slc_mc_br["rec.slc.truth.genie_mode"]
	slc_vtx_x_vec = slc_mc_br["rec.slc.truth.vtx.x"]
	slc_vtx_y_vec = slc_mc_br["rec.slc.truth.vtx.y"]
	slc_vtx_z_vec = slc_mc_br["rec.slc.truth.vtx.z"]


	for num in range(len(slc_pdg_vec)):
		slc = slc_vec[num]	
		slc_pdg = slc_pdg_vec[num]
		slc_iscc = 0
		slc_isnc = 0
		if len(slc_iscc_vec) > 0:
			if slc_iscc_vec[num]:
				slc_iscc = 1
		if len(slc_isnc_vec) > 0:
			if slc_isnc_vec[num]:
				slc_isnc = 1

		slc_mode = slc_mode_vec[num]
		slc_vtx_x = slc_vtx_x_vec[num]
		slc_vtx_y = slc_vtx_y_vec[num]
		slc_vtx_z = slc_vtx_z_vec[num]
		

		slc_tree.Fill(run, subrun, evt, slc, slc_pdg, slc_iscc, slc_isnc, slc_mode, slc_vtx_x, slc_vtx_y, slc_vtx_z)

	#print("Number of nu.prim.pdg", len(mc_prim_br["rec.mc.nu.prim.pdg"]))
	for num in range(len(mc_prim_br["rec.mc.nu.prim.pdg"])):
		#print(mc_prim_br["rec.mc.nu.prim.pdg"][num])
		
		pdg = mc_prim_br["rec.mc.nu.prim.pdg"][num]	
		genE = mc_prim_br["rec.mc.nu.prim.genE"][num]	
		px = mc_prim_br["rec.mc.nu.prim.startp.x"][num]	
		py = mc_prim_br["rec.mc.nu.prim.startp.y"][num]	
		pz = mc_prim_br["rec.mc.nu.prim.startp.z"][num]	
		sx = mc_prim_br["rec.mc.nu.prim.start.x"][num]	
		sy = mc_prim_br["rec.mc.nu.prim.start.y"][num]	
		sz = mc_prim_br["rec.mc.nu.prim.start.z"][num]	
		ex = mc_prim_br["rec.mc.nu.prim.end.x"][num]	
		ey = mc_prim_br["rec.mc.nu.prim.end.y"][num]	
		ez = mc_prim_br["rec.mc.nu.prim.end.z"][num]	

		mc_prim_tree.Fill(slc, pdg, genE, px, py, pz, sx, sy, sz, ex, ey, ez)


	# increment the event count before going to the next event
	evCount += 1

slc_tree.SetDirectory(0)
mc_prim_tree.SetDirectory(0)
hist_tot_pot.SetDirectory(0)
outfile.cd()

hist_tot_pot.Write()
slc_tree.Write()
mc_prim_tree.Write()

outfile.Close()
infile.Close()







