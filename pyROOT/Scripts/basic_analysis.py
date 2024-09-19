import ROOT
import sys
import os
import numpy as np


sys.path.append(os.path.abspath('../src/'))

from branches import *
from helpers import *

infile = ROOT.TFile.Open(sys.argv[1], "READ")


fig_dir = "../../Figs/TPCEtaNoCosmic/"

# verbosity level
v = int(sys.argv[2])

if v > 0:
	print("Top Level File Contents:")
	print("")
	infile.ls()
	print("")
	print("")


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
GenieEvtRecTree = infile.Get("GenieEvtRecTree")


if v > 0:
	print("What's inside the recTree:")
	print("")
	recTree.Print()
	print("")
	print("What's inside the GenieEvtRecTree:")
	print("")
	GenieEvtRecTree.Print()
	print("")



# Initialize histos and TNtuples

#h_trk_score = ROOT.TH1D("h_trk_score", )


# Event Loop

if v > 0:
	print("Starting Event Loop ...")
	print("")



trkScore_cuts = [0.3, 0.4, 0.5, 0.6, 0.7]


slc_true_pdgs = []

photon_trk_scores = []

pfp_shw_true_pdgs = []


evCount = 0
for event in recTree:
	if evCount%10 == 0 and v > 0:
		print("Event Count", evCount)

	# Load all branches

	# Pure Truth Info
	mc_br = load_branches(event, mc_branches)
	mc_prim_br = load_branches(event, mc_prim_branches)

	# Slices
	slc_br = load_branches(event, slc_branches)
	slc_mc_br = load_branches(event, slc_mc_branches)
	slc_mc_prim_br = load_branches(event, slc_mc_prim_branches)

	# PFP high level branches
	pfp_br = load_branches(event, pfp_branches)
	
	# reco tracks
	trk_br = load_branches(event, pfp_trk_branches)
	
	# True Track Info
	trk_mc_br = load_branches(event, pfp_trk_mc_branches)
	
	# reco showers
	shw_br = load_branches(event, pfp_shw_branches)

	# True Shower info
	shw_mc_br = load_branches(event, pfp_shw_mc_branches)


	# Finished loading branches
	
	# debugging
	slc_keys = list(slc_br.keys())
	if evCount == 0 and v > 0:
		print("Slice Reco Branches", slc_keys)

	# What are the slice pdg values
	for slc_pdg in slc_br['rec.slc.truth.pdg']:
		slc_true_pdgs.append(slc_pdg)

	trk_keys = list(trk_br.keys())
	shw_keys = list(shw_br.keys())
	num_trks = len(trk_br[trk_keys[0]])
	num_shws = len(shw_br[shw_keys[0]])
	num_shw_mc = len(shw_mc_br["rec.slc.reco.pfp.shw.truth.p.pdg"])
	
	# Loop over the true shower info --> Maybe can see if it indicates pfps that aren't actually showers ????
	for num in range(len(shw_mc_br["rec.slc.reco.pfp.shw.truth.p.pdg"])):
		pfp_shw_true_pdgs.append(shw_mc_br["rec.slc.reco.pfp.shw.truth.p.pdg"][num])
		if shw_mc_br["rec.slc.reco.pfp.shw.truth.p.pdg"][num] == 22:
			photon_trk_scores.append(pfp_br["rec.slc.reco.pfp.trackScore"][num])

	if evCount%10 == 0 and v > 0:
		print("Number of tracks", num_trks)
		print("Number of shower", num_shws)
		print("Number of shw_mc pdgs", num_shw_mc)
		print("")


	# Slice Loop

	for slcID in slc_br["rec.slc.self"]:
		
		if evCount%10 == 0 and v > 0:
			print("Slice Self", slcID)



	# increment the event count before going to the next event
	evCount += 1


# plotting ... 

unique_slc_pdgs = list(set(slc_true_pdgs))

h_slc_true_pdg = ROOT.TH1D("h_slc_true_pdg", "", len(unique_slc_pdgs), 0, len(unique_slc_pdgs))
for num in range(len(unique_slc_pdgs)):
	h_slc_true_pdg.SetBinContent(num + 1, slc_true_pdgs.count(unique_slc_pdgs[num]))
	h_slc_true_pdg.GetXaxis().SetBinLabel(num + 1, str(unique_slc_pdgs[num]))

c = ROOT.TCanvas("c", "c", 700, 500)
h_slc_true_pdg.Draw("HIST")
h_slc_true_pdg.GetXaxis().SetTitle("True Slice PDG")
c.SaveAs(fig_dir+"test_slice_true_pdg.png")


# PFP Shower True PDGs
unique_pfp_shw_true_pdgs = list(set(pfp_shw_true_pdgs))
h_pfp_shw_true_pdg = ROOT.TH1D("h_pfp_shw_true_pdg", "", len(unique_pfp_shw_true_pdgs), 0, len(unique_pfp_shw_true_pdgs))
for num in range(len(unique_pfp_shw_true_pdgs)):
	h_pfp_shw_true_pdg.SetBinContent(num + 1, pfp_shw_true_pdgs.count(unique_pfp_shw_true_pdgs[num]))
	h_pfp_shw_true_pdg.GetXaxis().SetBinLabel(num + 1, str(unique_pfp_shw_true_pdgs[num]))

c = ROOT.TCanvas("c", "c", 700, 500)
h_pfp_shw_true_pdg.SetLineColor(4)
h_pfp_shw_true_pdg.SetLineWidth(2)
h_pfp_shw_true_pdg.Draw("HISTE")
h_pfp_shw_true_pdg.GetXaxis().SetTitle("PFP Shower True PDG")
c.SaveAs(fig_dir+"test_pfp_shw_true_pdg.png")



# Photon Track Score Plotting ...
h_photon_trk_score = ROOT.TH1D("h_photon_trk_score", "", 100, min(photon_trk_scores) - 0.2, 1)
for num in photon_trk_scores:
	h_photon_trk_score.Fill(num)

c = ROOT.TCanvas("c", "c", 700, 500)
h_photon_trk_score.SetStats(0)
h_photon_trk_score.SetLineColor(4)
h_photon_trk_score.SetLineWidth(2)
h_photon_trk_score.GetXaxis().SetTitle("Photon Track Score")
h_photon_trk_score.Draw("HISTE")

line = ROOT.TLine(0.5, 0, 0.5, 1.1*h_photon_trk_score.GetMaximum())
line.SetLineColor(2)
line.SetLineStyle(10)
line.Draw("Same")

c.SaveAs(fig_dir+"test_photon_trk_score.png")


infile.Close()







