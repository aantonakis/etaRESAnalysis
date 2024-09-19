hdr_branches = ["rec.hdr.run", "rec.hdr.subrun", "rec.hdr.pot"]

mc_branches = [
    "rec.mc.nu.E",
    "rec.mc.nu.position.x",
    "rec.mc.nu.position.y",
    "rec.mc.nu.position.z",
    "rec.mc.nu.pdg",
    "rec.mc.nu.iscc",
    "rec.mc.nu.genie_inttype",
    "rec.mc.nu.genie_mode",
    "rec.mc.nu.momentum.x",
    "rec.mc.nu.momentum.y",
    "rec.mc.nu.momentum.z",
    "rec.mc.nu.nneutron", "rec.mc.nu.npiminus", "rec.mc.nu.npiplus", "rec.mc.nu.npizero", "rec.mc.nu.nproton", 
    "rec.mc.nu.nprim",
    "rec.mc.nu.genweight",
    "rec.mc.nu.time",
    "rec.mc.nu.parent_dcy_mode",
    "rec.mc.nu.parent_pdg",
    "rec.mc.nu.Q2", "rec.mc.nu.q0", "rec.mc.nu.q0_lab", "rec.mc.nu.t", "rec.mc.nu.w", "rec.mc.nu.bjorkenX", "rec.mc.nu.inelasticityY"
]


mc_prim_branches = [
    "rec.mc.nu.prim.pdg", "rec.mc.nu.prim.genE",
    "rec.mc.nu.prim.start.x", "rec.mc.nu.prim.start.y", "rec.mc.nu.prim.start.z",
    "rec.mc.nu.prim.end.x","rec.mc.nu.prim.end.y","rec.mc.nu.prim.end.z",
    "rec.mc.nu.prim.startp.x","rec.mc.nu.prim.endp.x",
    "rec.mc.nu.prim.startp.y","rec.mc.nu.prim.endp.y",
    "rec.mc.nu.prim.startp.z", "rec.mc.nu.prim.endp.z",
    "rec.mc.nu.prim.startE",
    "rec.mc.nu.prim.end_process", "rec.mc.nu.prim.start_process"                 
]

slc_branches = [
    "rec.slc.self",
    "rec.slc.charge",
    "rec.slc.truth.pdg",
    "rec.slc.producer",
    "rec.slc.nu_score",
    "rec.slc.is_clear_cosmic",
    "rec.slc.vertex.x", "rec.slc.vertex.y", "rec.slc.vertex.z",
    "rec.slc.tmatch.eff", "rec.slc.tmatch.pur", "rec.slc.tmatch.index",
    "rec.slc.fmatch.score", "rec.slc.fmatch.time",

    "rec.slc.nu_pdg",
    "rec.slc.primary..length",
    "rec.slc.primary..totarraysize",
    "rec.slc.primary",
    "rec.slc.primary..idx",
]

slc_mc_branches = [

    "rec.slc.truth.E",
    "rec.slc.truth.position.x",
    "rec.slc.truth.position.y",
    "rec.slc.truth.position.z",
    "rec.slc.truth.pdg",
    "rec.slc.truth.iscc",
    "rec.slc.truth.genie_mode",
    "rec.slc.truth.Q2",
    "rec.slc.truth.baseline",
    "rec.slc.truth.eccqe",
    "rec.slc.truth.index",
    "rec.slc.truth.is_numucc_primary",
    "rec.slc.truth.iscc",
    "rec.slc.truth.isnc",
    "rec.slc.truth.nneutron",
    "rec.slc.truth.npiplus",
    "rec.slc.truth.npiminus",
    "rec.slc.truth.npizero",
    "rec.slc.truth.nproton",
    "rec.slc.truth.nprim",
    "rec.slc.truth.parent_dcy_mode",
    "rec.slc.truth.parent_pdg",
    "rec.slc.truth.pdg",
    "rec.slc.truth.prim..length",
    "rec.slc.truth.prim.G4ID",
    "rec.slc.truth.prim.cont_tpc",
    "rec.slc.truth.prim.contained",
    "rec.slc.truth.prim.genE",
    "rec.slc.truth.prim.interaction_id",
    "rec.slc.truth.prim.pdg",
    "rec.slc.truth.prim.length",
    "rec.slc.truth.prim.daughters",
    "rec.slc.truth.prim.daughters..length",
    "rec.slc.truth.prim.daughters..idx",
    "rec.slc.truth.prim.daughters..totarraysize",
    "rec.slc.truth.vtx.x","rec.slc.truth.vtx.y","rec.slc.truth.vtx.z",
    "rec.slc.truth.time",
]

slc_mc_prim_branches = [
    "rec.slc.truth.prim.genE",
    "rec.slc.truth.prim.pdg",
]

pfp_trk_branches = [
    "rec.slc.reco.pfp.trk.start.x", "rec.slc.reco.pfp.trk.start.y", "rec.slc.reco.pfp.trk.start.z",
    "rec.slc.reco.pfp.trk.end.x", "rec.slc.reco.pfp.trk.end.y", "rec.slc.reco.pfp.trk.end.z",
    "rec.slc.reco.pfp.trk.dir.x", "rec.slc.reco.pfp.trk.dir.y", "rec.slc.reco.pfp.trk.dir.z",
    "rec.slc.reco.pfp.trk.phi", "rec.slc.reco.pfp.trk.costh",
    "rec.slc.reco.pfp.trk.len",
    "rec.slc.reco.pfp.trk.rangeP.p_muon",
    "rec.slc.reco.pfp.trk.mcsP.fwdP_muon",
    "rec.slc.reco.pfp.trk.mcsP.bwdP_muon",
    "rec.slc.reco.pfp.trk.mcsP.is_bwd_muon",
    "rec.slc.reco.pfp.trk.rangeP.p_pion",
    "rec.slc.reco.pfp.trk.mcsP.fwdP_pion",
    "rec.slc.reco.pfp.trk.rangeP.p_proton",
    "rec.slc.reco.pfp.trk.mcsP.fwdP_proton",
    "rec.slc.reco.pfp.trk.bestplane",
#    "rec.slc.reco.pfp.trk.dazzle.bestScore",
#    "rec.slc.reco.pfp.trk.dazzle.muonScore",
#    "rec.slc.reco.pfp.trk.dazzle.otherScore",
#    "rec.slc.reco.pfp.trk.dazzle.pdg",
#    "rec.slc.reco.pfp.trk.dazzle.pionScore",
#    "rec.slc.reco.pfp.trk.dazzle.protonScore",
]

pfp_branches = ["rec.slc.reco.pfp.trackScore", "rec.slc.reco.pfp.ndaughters", "rec.slc.reco.pfp.slcID"]

pfp_trk_chi2_branches = [
    "rec.slc.reco.pfp.trk.chi2pid.2.chi2_kaon", "rec.slc.reco.pfp.trk.chi2pid.2.chi2_muon", "rec.slc.reco.pfp.trk.chi2pid.2.chi2_pion", "rec.slc.reco.pfp.trk.chi2pid.2.chi2_proton",
    "rec.slc.reco.pfp.trk.chi2pid.1.chi2_kaon", "rec.slc.reco.pfp.trk.chi2pid.1.chi2_muon", "rec.slc.reco.pfp.trk.chi2pid.1.chi2_pion", "rec.slc.reco.pfp.trk.chi2pid.1.chi2_proton",
    "rec.slc.reco.pfp.trk.chi2pid.0.chi2_kaon", "rec.slc.reco.pfp.trk.chi2pid.0.chi2_muon", "rec.slc.reco.pfp.trk.chi2pid.0.chi2_pion", "rec.slc.reco.pfp.trk.chi2pid.0.chi2_proton",
]

pfp_trk_mc_branches_names = [
    "interaction_id",
    "parent",
    "pdg",
    "G4ID",
    "end_process",
    "start_process",
    "startE",
    "start.x", "start.y", "start.z",
    "startp.x", "startp.y", "startp.z",
    "end.x", "end.y", "end.z",
    "endp.x", "endp.y", "endp.z",
    "genp.x", "genp.y", "genp.z",
    "genE",
    "length",
    "cont_tpc",
]
pfp_trk_mc_branches = ["rec.slc.reco.pfp.trk.truth.p." + n for n in pfp_trk_mc_branches_names]

stub_branches = [
    "rec.slc.reco.stub.vtx.x",
    "rec.slc.reco.stub.vtx.y",
    "rec.slc.reco.stub.vtx.z",
    "rec.slc.reco.stub.end.x",
    "rec.slc.reco.stub.end.y",
    "rec.slc.reco.stub.end.z",
    "rec.slc.reco.stub.efield_vtx",
    "rec.slc.reco.stub.efield_end",
    "rec.slc.reco.stub.pfpid",
    "rec.slc.reco.stub.truth.p.pdg",
    "rec.slc.reco.stub.truth.p.genE",
    "rec.slc.reco.stub.truth.p.interaction_id",
]

stub_plane_branches = [
    "rec.slc.reco.stub.planes.p",
    "rec.slc.reco.stub.planes.hit_w",
    "rec.slc.reco.stub.planes.vtx_w",
    "rec.slc.reco.stub.planes.pitch",
    "rec.slc.reco.stub.planes.trkpitch",
]

stub_hit_branches = [
    "rec.slc.reco.stub.planes.hits.charge",
    "rec.slc.reco.stub.planes.hits.ontrack",
    "rec.slc.reco.stub.planes.hits.wire",
]

pandora_branches = ["rec.slc.reco.pfp.trackScore"]
cnn_branches = [
    "rec.slc.reco.pfp.cnnscore.michel", "rec.slc.reco.pfp.cnnscore.endmichel", "rec.slc.reco.pfp.cnnscore.nclusters",
    "rec.slc.reco.pfp.cnnscore.noise", "rec.slc.reco.pfp.cnnscore.shower", "rec.slc.reco.pfp.cnnscore.track"
]


pfp_shw_branches_names = [
    "razzle.photonScore",
    "razzle.electronScore",
    "razzle.bestScore",
    "start.x",
    "start.y",
    "start.z",
    "dir.x",
    "dir.y",
    "dir.z",
    "conversion_gap",
    "bestplane_energy",
    "bestplane_dEdx",

]
pfp_shw_branches = ["rec.slc.reco.pfp.shw." + n for n in pfp_shw_branches_names]

pfp_shw_mc_branches_names = [
    "pdg",
    "G4ID",
    "genE",
    "start.x",
    "start.y",
    "start.z",
    "end.x",
    "end.y",
    "end.z",

]

pfp_shw_mc_branches = ["rec.slc.reco.pfp.shw.truth.p." + n for n in pfp_shw_mc_branches_names]


# TODO --> Finish putting all the branches
reco_branches = {
    "slc_branches":slc_branches,
    "pfp_branches":pfp_branches,
    "pfp_trk_branches":pfp_trk_branches,
    "pfp_shw_branches":pfp_shw_branches,

}



