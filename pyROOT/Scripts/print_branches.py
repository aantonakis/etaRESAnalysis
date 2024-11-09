import ROOT
import sys
import os
import numpy as np


infile = ROOT.TFile.Open(sys.argv[1], "READ")


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


recTree.Print()


