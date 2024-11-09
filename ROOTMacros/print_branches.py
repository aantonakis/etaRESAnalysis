import ROOT
import sys


infile = ROOT.TFile.Open(sys.argv[1], "READ")

tree = infile.Get("recTree")
tree.Print()

infile.Close()


