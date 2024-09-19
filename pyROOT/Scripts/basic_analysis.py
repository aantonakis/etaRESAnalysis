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

num_prim_true_etas_per_slc = []


# 2D histo to hold the eff vs purity of the slice truth matching
h_2d_slc_pur_eff = ROOT.TH2D("h_2d_slc_pur_eff", "", 11, 0, 1.1, 11, 0, 1.1)
h_2d_slc_pur_eff.GetXaxis().SetTitle("Slice TMatch Eff")
h_2d_slc_pur_eff.GetYaxis().SetTitle("Slice TMatch Pur")

N_tmatch_slices = 0

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
	
	# Loop over the slice info:
	for num in range(len(slc_br["rec.slc.tmatch.eff"])):
		if slc_br["rec.slc.tmatch.eff"][num] < 0 or slc_br["rec.slc.tmatch.pur"][num] < 0:
			print("Strange: Negative Pur or Eff ???????????")
		N_tmatch_slices += 1
		h_2d_slc_pur_eff.Fill(slc_br["rec.slc.tmatch.eff"][num], slc_br["rec.slc.tmatch.pur"][num])


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




	for num in range(len(slc_br["rec.slc.self"])):
		nEta = get_true_eta_mult(num, slc_mc_br)
		num_prim_true_etas_per_slc.append(nEta)




	# Slice Loop

	for slcID in slc_br["rec.slc.self"]:
		
		if evCount%10 == 0 and v > 0:
			print("Slice Self", slcID)



	# increment the event count before going to the next event
	evCount += 1


# plotting ... 

print("Debugging ...")
print("Number of tmatch slices", N_tmatch_slices)
print("Number of true slice pdgs", len(slc_true_pdgs))
print("")

unique_slc_pdgs = list(set(slc_true_pdgs))

h_slc_true_pdg = ROOT.TH1D("h_slc_true_pdg", "", len(unique_slc_pdgs), 0, len(unique_slc_pdgs))
for num in range(len(unique_slc_pdgs)):
	h_slc_true_pdg.SetBinContent(num + 1, slc_true_pdgs.count(unique_slc_pdgs[num]))
	h_slc_true_pdg.GetXaxis().SetBinLabel(num + 1, str(unique_slc_pdgs[num]))

c = ROOT.TCanvas("c", "c", 700, 500)
h_slc_true_pdg.SetLineWidth(2)
h_slc_true_pdg.Draw("HIST")
h_slc_true_pdg.GetXaxis().SetTitle("True Slice PDG")
c.SaveAs(fig_dir+"test_slice_true_pdg.png")


c = ROOT.TCanvas("c", "c", 700, 500)
h_2d_slc_pur_eff.SetStats(0)
h_2d_slc_pur_eff.Draw("Colz")
c.SaveAs(fig_dir+"test_slice_tmatch_eff_vs_pur.png")

# Number of True Prime Etas per Slice
unique_num_prim_etas_per_slice = list(set(num_prim_true_etas_per_slc))

h_slc_true_num_prim_etas = ROOT.TH1D("h_slc_true_num_prim_etas", "", len(unique_num_prim_etas_per_slice), 0, len(unique_num_prim_etas_per_slice))
for num in range(len(unique_num_prim_etas_per_slice)):
	h_slc_true_num_prim_etas.SetBinContent(num + 1, num_prim_true_etas_per_slc.count(unique_num_prim_etas_per_slice[num]))
	h_slc_true_num_prim_etas.GetXaxis().SetBinLabel(num + 1, str(unique_num_prim_etas_per_slice[num]))

c = ROOT.TCanvas("c", "c", 700, 500)
h_slc_true_num_prim_etas.SetLineWidth(2)
h_slc_true_num_prim_etas.Draw("HIST")
h_slc_true_num_prim_etas.GetXaxis().SetTitle("True Number of Prime Etas Per Slice")
c.SaveAs(fig_dir+"test_slice_true_num_prim_etas.png")



# PFP Shower True PDGs
unique_pfp_shw_true_pdgs = list(set(pfp_shw_true_pdgs))
h_pfp_shw_true_pdg = ROOT.TH1D("h_pfp_shw_true_pdg", "", len(unique_pfp_shw_true_pdgs), 0, len(unique_pfp_shw_true_pdgs))
for num in range(len(unique_pfp_shw_true_pdgs)):
	h_pfp_shw_true_pdg.SetBinContent(num + 1, pfp_shw_true_pdgs.count(unique_pfp_shw_true_pdgs[num]))
	h_pfp_shw_true_pdg.GetXaxis().SetBinLabel(num + 1, str(unique_pfp_shw_true_pdgs[num]))

c = ROOT.TCanvas("c", "c", 700, 500)
h_pfp_shw_true_pdg.SetStats(0)
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







