#ifndef PFP_INFO_H
#define PFP_INFO_H



// Standard Library Includes
#include <iostream>
#include <fstream>

// // ROOT Includes
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"


namespace analysis {


class PFPInfo {

public:
        PFPInfo() {}
        ~PFPInfo() {}


	std::string shw_tag = "rec.slc.reco.pfp.shw.";
	std::string trk_tag = "rec.slc.reco.pfp.trk.";

        
	// ------------------ PFP Header Variables ----------------- //
	
	std::string pfp_length_str = "rec.slc.reco.pfp..totarraysize";
	Int_t pfp_length = 1000;

	std::string pfp_slcID_str = "rec.slc.reco.pfp.slcID";
	Int_t *pfp_slcID = new Int_t[pfp_length];
	
	std::string pfp_trackScore_str = "rec.slc.reco.pfp.trackScore";
	Float_t *pfp_trackScore = new Float_t[pfp_length];

	std::string pfp_parent_is_primary_str = "rec.slc.reco.pfp.parent_is_primary";
	Char_t *pfp_parent_is_primary = new Char_t[pfp_length]; 

	std::string pfp_t0_str = "rec.slc.reco.pfp.t0";
	Float_t *pfp_t0 = new Float_t[pfp_length]; 

	// ------------------ Shower Variables ----------------- //
	std::string shw_start_x_str = shw_tag + "start.x";
	Float_t *shw_start_x = new Float_t[pfp_length];

	std::string shw_start_y_str = shw_tag + "start.y";
	Float_t *shw_start_y = new Float_t[pfp_length];
	
	std::string shw_start_z_str = shw_tag + "start.z";
	Float_t *shw_start_z = new Float_t[pfp_length];

	std::string shw_end_x_str = shw_tag + "end.x";
	Float_t *shw_end_x = new Float_t[pfp_length];

	std::string shw_end_y_str = shw_tag + "end.y";
	Float_t *shw_end_y = new Float_t[pfp_length];
	
	std::string shw_end_z_str = shw_tag + "end.z";
	Float_t *shw_end_z = new Float_t[pfp_length];

	std::string shw_dir_x_str = shw_tag + "dir.z";
	Float_t *shw_dir_x = new Float_t[pfp_length];
	
	std::string shw_dir_y_str = shw_tag + "dir.y";
	Float_t *shw_dir_y = new Float_t[pfp_length];
	
	std::string shw_dir_z_str = shw_tag + "dir.z";
	Float_t *shw_dir_z = new Float_t[pfp_length];

	std::string shw_conversion_gap_str = shw_tag + "conversion_gap";
	Float_t *shw_conversion_gap = new Float_t[pfp_length];

	
	std::string shw_bestplane_energy_str = shw_tag + "bestplane_energy";
	Float_t *shw_bestplane_energy = new Float_t[pfp_length];

	std::string shw_bestplane_dEdx_str = shw_tag + "bestplane_dEdx";
	Float_t *shw_bestplane_dEdx = new Float_t[pfp_length];

	// machine learning scores
	std::string shw_razzle_photonScore_str = shw_tag + "razzle.photonScore";
	Float_t *shw_razzle_photonScore = new Float_t[pfp_length];

	std::string shw_razzle_electronScore_str = shw_tag + "razzle.electronScore";
	Float_t *shw_razzle_electronScore = new Float_t[pfp_length];

	std::string shw_razzle_bestScore_str = shw_tag + "razzle.bestScore";
	Float_t *shw_razzle_bestScore = new Float_t[pfp_length];
	
	// ------------- Shower Truth Info ---------------------------------------- //
	std::string shw_truth_tag = shw_tag + "truth.bestmatch.";

	std::string shw_truth_G4ID_str = shw_truth_tag + "G4ID";
	Int_t *shw_truth_G4ID = new Int_t[pfp_length];

	std::string shw_truth_hit_completeness_str = shw_truth_tag + "hit_completeness";
	Float_t *shw_truth_hit_completeness = new Float_t[pfp_length];

	std::string shw_truth_hit_purity_str = shw_truth_tag + "hit_purity";
	Float_t *shw_truth_hit_purity = new Float_t[pfp_length];
        


/*
    // Other branches to consider
    "rec.slc.reco.pfp.trk.mcsP.fwdP_muon",
    "rec.slc.reco.pfp.trk.mcsP.bwdP_muon",
    "rec.slc.reco.pfp.trk.mcsP.is_bwd_muon",
    "rec.slc.reco.pfp.trk.mcsP.fwdP_pion",
    "rec.slc.reco.pfp.trk.mcsP.fwdP_proton",
    "rec.slc.reco.pfp.trk.dazzle.otherScore",
    "rec.slc.reco.pfp.trk.dazzle.pdg",

*/
	// ---------------- Track Stuff -------------------------------- //

	std::string trk_start_x_str = trk_tag + "start.x";
	Float_t *trk_start_x = new Float_t[pfp_length];

	std::string trk_start_y_str = trk_tag + "start.y";
	Float_t *trk_start_y = new Float_t[pfp_length];
	
	std::string trk_start_z_str = trk_tag + "start.z";
	Float_t *trk_start_z = new Float_t[pfp_length];

	std::string trk_end_x_str = trk_tag + "end.x";
	Float_t *trk_end_x = new Float_t[pfp_length];

	std::string trk_end_y_str = trk_tag + "end.y";
	Float_t *trk_end_y = new Float_t[pfp_length];

	std::string trk_end_z_str = trk_tag + "end.z";
	Float_t *trk_end_z = new Float_t[pfp_length];

	std::string trk_dir_x_str = trk_tag + "dir.x";
	Float_t *trk_dir_x = new Float_t[pfp_length];

	std::string trk_dir_y_str = trk_tag + "dir.y";
	Float_t *trk_dir_y = new Float_t[pfp_length];

	std::string trk_dir_z_str = trk_tag + "dir.z";
	Float_t *trk_dir_z = new Float_t[pfp_length];

	std::string trk_p_muon_str = trk_tag + "rangeP.p_muon";
	Float_t *trk_p_muon = new Float_t[pfp_length];
	
	std::string trk_p_proton_str = trk_tag + "rangeP.p_proton";
	Float_t *trk_p_proton = new Float_t[pfp_length];

	std::string trk_p_pion_str = trk_tag + "rangeP.p_pion";
	Float_t *trk_p_pion = new Float_t[pfp_length];
	
	std::string trk_muonScore_str = trk_tag + "dazzle.muonScore";
	Float_t *trk_muonScore = new Float_t[pfp_length];

	std::string trk_protonScore_str = trk_tag + "dazzle.protonScore";
	Float_t *trk_protonScore = new Float_t[pfp_length];

	std::string trk_pionScore_str = trk_tag + "dazzle.pionScore";
	Float_t *trk_pionScore = new Float_t[pfp_length];

	std::string trk_bestScore_str = trk_tag + "dazzle.bestScore";
	Float_t *trk_bestScore = new Float_t[pfp_length];
	

	std::string trk_truth_tag = trk_tag + "truth.bestmatch.";
	
	std::string trk_truth_G4ID_str = trk_truth_tag + "G4ID";
	Int_t *trk_truth_G4ID = new Int_t[pfp_length];



	// ----------- CRT Stuff ---------------------------------- //
	
	std::string trk_crtspacepoint_x_str = trk_tag + "crtspacepoint.position.x";
	Float_t *trk_crtspacepoint_x = new Float_t[pfp_length];

	std::string trk_crtspacepoint_y_str = trk_tag + "crtspacepoint.position.y";
	Float_t *trk_crtspacepoint_y = new Float_t[pfp_length];

	std::string trk_crtspacepoint_z_str = trk_tag + "crtspacepoint.position.z";
	Float_t *trk_crtspacepoint_z = new Float_t[pfp_length];


	void setPFPInfoAddresses(TTree *tree) {
          
	  // PFP Header Info 
	  tree->SetBranchAddress(pfp_length_str.c_str(), &pfp_length);
	  tree->SetBranchAddress(pfp_slcID_str.c_str(), pfp_slcID);
	  tree->SetBranchAddress(pfp_parent_is_primary_str.c_str(), pfp_parent_is_primary);
	  tree->SetBranchAddress(pfp_t0_str.c_str(), pfp_t0);

	  // Shower Stuff
	  tree->SetBranchAddress(shw_start_x_str.c_str(), shw_start_x);
	  tree->SetBranchAddress(shw_start_y_str.c_str(), shw_start_y);
	  tree->SetBranchAddress(shw_start_z_str.c_str(), shw_start_z);
	  tree->SetBranchAddress(shw_end_x_str.c_str(), shw_end_x);
	  tree->SetBranchAddress(shw_end_y_str.c_str(), shw_end_y);
	  tree->SetBranchAddress(shw_end_z_str.c_str(), shw_end_z);
	  tree->SetBranchAddress(shw_dir_x_str.c_str(), shw_dir_x);
	  tree->SetBranchAddress(shw_dir_y_str.c_str(), shw_dir_y);
	  tree->SetBranchAddress(shw_dir_z_str.c_str(), shw_dir_z);
	  tree->SetBranchAddress(shw_conversion_gap_str.c_str(), shw_conversion_gap);
	  tree->SetBranchAddress(shw_bestplane_energy_str.c_str(), shw_bestplane_energy);
	  tree->SetBranchAddress(shw_bestplane_dEdx_str.c_str(), shw_bestplane_dEdx);
	  tree->SetBranchAddress(shw_razzle_photonScore_str.c_str(), shw_razzle_photonScore);
	  tree->SetBranchAddress(shw_razzle_electronScore_str.c_str(), shw_razzle_electronScore);
	  tree->SetBranchAddress(shw_razzle_bestScore_str.c_str(), shw_razzle_bestScore);
	  
	  tree->SetBranchAddress(shw_truth_G4ID_str.c_str(), shw_truth_G4ID);
	  tree->SetBranchAddress(shw_truth_hit_completeness_str.c_str(), shw_truth_hit_completeness);
	  tree->SetBranchAddress(shw_truth_hit_purity_str.c_str(), shw_truth_hit_purity);

	  // Track Stuff
	  tree->SetBranchAddress(trk_start_x_str.c_str(), trk_start_x);
	  tree->SetBranchAddress(trk_start_y_str.c_str(), trk_start_y);
	  tree->SetBranchAddress(trk_start_z_str.c_str(), trk_start_z);
	  tree->SetBranchAddress(trk_end_x_str.c_str(), trk_end_x);
	  tree->SetBranchAddress(trk_end_y_str.c_str(), trk_end_y);
	  tree->SetBranchAddress(trk_end_z_str.c_str(), trk_end_z);
	  tree->SetBranchAddress(trk_dir_x_str.c_str(), trk_dir_x);
	  tree->SetBranchAddress(trk_dir_y_str.c_str(), trk_dir_y);
	  tree->SetBranchAddress(trk_dir_z_str.c_str(), trk_dir_z);
	  tree->SetBranchAddress(trk_p_muon_str.c_str(), trk_p_muon);
	  tree->SetBranchAddress(trk_p_proton_str.c_str(), trk_p_proton);
	  tree->SetBranchAddress(trk_p_pion_str.c_str(), trk_p_pion);
	  tree->SetBranchAddress(trk_muonScore_str.c_str(), trk_muonScore);
	  tree->SetBranchAddress(trk_protonScore_str.c_str(), trk_protonScore);
	  tree->SetBranchAddress(trk_pionScore_str.c_str(), trk_pionScore);
	  tree->SetBranchAddress(trk_bestScore_str.c_str(), trk_bestScore);
	  tree->SetBranchAddress(trk_truth_G4ID_str.c_str(), trk_truth_G4ID);

	  // CRT Stuff
	  tree->SetBranchAddress(trk_crtspacepoint_x_str.c_str(), trk_crtspacepoint_x);
	  tree->SetBranchAddress(trk_crtspacepoint_y_str.c_str(), trk_crtspacepoint_y);
	  tree->SetBranchAddress(trk_crtspacepoint_z_str.c_str(), trk_crtspacepoint_z);


	}


private:
// might not need this


};

} // end namespace analysis

#endif



