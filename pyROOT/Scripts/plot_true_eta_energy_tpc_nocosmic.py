import ROOT
import sys
import os
import numpy as np
sys.path.append(os.path.abspath('../src/'))
from branches import *
from helpers import *
from labels import *

infile = ROOT.TFile.Open(sys.argv[1], "READ")
Nbins = int(sys.argv[2])

fig_dir = "../../Figs/TPCEtaNoCosmic/"
# Get the trees and histos from the input file
hist_tot_pot = infile.Get("TotalPOT")
recTree = infile.Get("recTree")

nu_arr = []
mode_arr = []
Npi0_arr = []
E_arr = []

# Event Loop
for event in recTree:
	# Load all branches
	# Slices
	slc_br = load_branches(event, slc_branches)
	slc_mc_br = load_branches(event, slc_mc_branches)
	
	for num in range(len(slc_br["rec.slc.self"])):
		nEta = get_true_eta_mult(num, slc_mc_br)
		if nEta > 0:
			# [nu, mode, Npi0, E]
			eta_info = get_slc_eta_info(num, slc_mc_br)
			nu_arr.append(eta_info[0])
			mode_arr.append(eta_info[1])
			Npi0_arr.append(eta_info[2])
			E_arr.append(eta_info[3])

# End event Loop

h_eta_energy_all = ROOT.TH1D("h_eta_energy_all", "", Nbins, 0, max(E_arr))
unique_modes = list(set(mode_arr))
h_energy_list = [ROOT.TH1D("h_energy_mode"+str(unique_modes[num]), "", Nbins, 0, max(E_arr)) for num in range(len(unique_modes))]
for num in range(len(E_arr)):
	h_eta_energy_all.Fill(E_arr[num])
	h_energy_list[unique_modes.index(mode_arr[num])].Fill(E_arr[num])

leg = ROOT.TLegend(0.5, 0.5, 0.85, 0.85)
leg.SetBorderSize(0)
for num in range(len(unique_modes)):
	h_energy_list[num].SetLineWidth(2)
	h_energy_list[num].SetLineColor(interaction_code_colors[unique_modes[num]])
	leg.AddEntry(h_energy_list[num], interaction_codes[unique_modes[num]])


c = ROOT.TCanvas("c", "c", 700, 500)
h_eta_energy_all.SetStats(0)
h_eta_energy_all.GetXaxis().SetTitle("True Eta Energy [GeV]")
h_eta_energy_all.GetYaxis().SetTitle("Counts")
h_eta_energy_all.SetLineColor(1)
h_eta_energy_all.SetLineWidth(2)
h_eta_energy_all.Draw("HISTE")
for h in h_energy_list:
	h.Draw("HISTE Same")
leg.Draw("Same")
c.SaveAs(fig_dir+"test_true_eta_energy.png")



