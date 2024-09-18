import os
import sys

print("Starting an Eta Sim in the TPC with Cosmic Overlay ...")

scratch = "/pnfs/sbnd/scratch/users/aantonak/"

out1 = "eta_tpc_cosmic_test_6000_14Sep2024_gen.root"
out2 = "eta_tpc_cosmic_test_6000_14Sep2024_g4.root"
out3 = "eta_tpc_cosmic_test_6000_14Sep2024_detsim.root"
out4 = "eta_tpc_cosmic_test_6000_14Sep2024_reco1.root"
out5 = "eta_tpc_cosmic_test_6000_14Sep2024_reco2.root"
out6 = "eta_tpc_cosmic_test_6000_14Sep2024_caf.root"


gen_fcl = "prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_eta.fcl"
g4_fcl = "g4_sce.fcl"
detsim_fcl = "detsim_sce.fcl"
reco1_fcl = "reco1_sce.fcl"
reco2_fcl = "reco2_sce.fcl"

caf_fcl = "cafmakerjob_sbnd_sce.fcl"

os.system("lar -c " + gen_fcl + " -n 6000 -o " + scratch+out1)

os.system("lar -c " + g4_fcl     + " -s " + scratch+out1 + " -T "+scratch+out2)
os.system("lar -c " + detsim_fcl + " -s " + scratch+out2 + " -T "+scratch+out3)
os.system("lar -c " + reco1_fcl  + " -s " + scratch+out3 + " -T "+scratch+out4)
os.system("lar -c " + reco2_fcl  + " -s " + scratch+out4 + " -T "+scratch+out5)


#os.system("lar -c " + caf_fcl  + " -s " + scratch+out5 + " -T "+scratch+out6)



print("finised simulating!")



