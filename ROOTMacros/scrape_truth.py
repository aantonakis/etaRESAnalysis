import ROOT
import sys


infile = ROOT.TFile.Open(sys.argv[1], "READ")

tree = infile.Get("recTree")
#tree.Print()

for event in tree:
	nu_prim_pdg = getattr(event, "rec.mc.nu.prim.pdg")
	print(nu_prim_pdg)



infile.Close()


