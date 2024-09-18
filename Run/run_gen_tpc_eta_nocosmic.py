import os
import sys


scratch = "/pnfs/sbnd/scratch/users/aantonak/"
persist = "/pnfs/sbnd/persistent/users/aantonak/"


for num in range(Nfiles):
	os.system("lar -c prodgenie_nu_spill_tpc_sbnd_eta.fcl -n 6000")
	os.system("rm *.out")

