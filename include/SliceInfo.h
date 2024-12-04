#ifndef SLICE_INFO_H
#define SLICE_INFO_H



// Standard Library Includes
#include <iostream>
#include <fstream>

// // ROOT Includes
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"


namespace analysis {


class SliceInfo {

public:
        SliceInfo() {}
        ~SliceInfo() {}


	std::string slc_tag = "rec.slc.truth.";
        
	// ------------------ Slice Header Variables ----------------- //
	
	std::string slc_length_str = "rec.slc..length";
	Int_t slc_length = 100;


	std::string slc_self_str = "rec.slc.self";
	Int_t *slc_self = new Int_t[slc_length];

        std::string slc_genie_mode_str = slc_tag + "genie_mode";
	Short_t *slc_genie_mode = new Short_t[slc_length];
	
	std::string slc_pdg_str = slc_tag + "pdg";
	int *slc_true_pdg = new int[slc_length];

	std::string slc_parent_pdg_str = slc_tag + "parent_pdg";
	Int_t *slc_parent_pdg = new Int_t[slc_length];

	// I believe this is the MC nu index associated with the slice
	std::string slc_nu_index_str = slc_tag + "index";
	int *slc_nu_index = new int[slc_length];

	std::string slc_resnum_str = slc_tag + "resnum";
	int *slc_resnum = new int[slc_length];
	
	std::string iscc_str = slc_tag + "iscc";
	std::string isnc_str = slc_tag + "isnc";
        Char_t *iscc = new Char_t[slc_length];
        Char_t *isnc = new Char_t[slc_length];

	std::string isvtxcont_str = slc_tag + "isvtxcont";
        Char_t *isvtxcont = new Char_t[slc_length];

	
	std::string slc_x_str = slc_tag + "position.x";
	std::string slc_y_str = slc_tag + "position.y";
	std::string slc_z_str = slc_tag + "position.z";

	// true slice vertex
        float *slc_x = new float[slc_length]; 
	float *slc_y = new float[slc_length]; 
	float *slc_z = new float[slc_length]; 
	
	// ------------------ Primary Particle Variables ----------------- //

	// nprim in each slice
	std::string slc_nprim_str = slc_tag + "nprim";
	int *nprim = new int[slc_length];


        std::string nprim_tot_str = slc_tag + "prim..totarraysize";	
	int nprim_tot = 1000;

	std::string prim_tag = slc_tag + "prim.";

	std::string prim_pdg_str = prim_tag + "pdg";
	int *prim_pdg = new int[nprim_tot];
	
	std::string slc_prim_length_str = prim_tag + ".length";
	int *slc_prim_length = new Int_t[slc_length];
	
	std::string slc_prim_idx_str = prim_tag + ".idx";
	Int_t *slc_prim_idx = new Int_t[slc_length];
	
	std::string prim_parent_str = prim_tag + "parent";
	UInt_t *prim_parent = new UInt_t[nprim_tot];
	
	std::string G4ID_str = prim_tag+"G4ID";
	Int_t *G4ID = new Int_t[nprim_tot];

	std::string cont_tpc_str = prim_tag+"cont_tpc";
	Char_t *cont_tpc = new Char_t[nprim_tot];

	std::string prim_genE_str = prim_tag+"genE";
	float *prim_genE = new float[nprim_tot];
	
	std::string prim_startx_str = prim_tag+"start.x";
	std::string prim_starty_str = prim_tag+"start.y";
	std::string prim_startz_str = prim_tag+"start.z";
	
	std::string prim_endx_str = prim_tag+"end.x";
	std::string prim_endy_str = prim_tag+"end.y";
	std::string prim_endz_str = prim_tag+"end.z";

	float *prim_startx = new float[nprim_tot];
	float *prim_starty = new float[nprim_tot];
	float *prim_startz = new float[nprim_tot];
	
	float *prim_endx = new float[nprim_tot];
	float *prim_endy = new float[nprim_tot];
	float *prim_endz = new float[nprim_tot];
	
	std::string prim_px_str = prim_tag+"genp.x";
	std::string prim_py_str = prim_tag+"genp.y";
	std::string prim_pz_str = prim_tag+"genp.z";
	
	float *prim_px = new float[nprim_tot];
	float *prim_py = new float[nprim_tot];
	float *prim_pz = new float[nprim_tot];

	// ------------------ Primary Daughter Particles ----------------- //

	
	std::string nprim_daughters_str = prim_tag+"daughters..totarraysize";
	int nprim_daughters_tot = 1000;
	
	std::string prim_daughters_str = prim_tag+"daughters";
	UInt_t *prim_daughters = new UInt_t[nprim_daughters_tot];

	// I think the starting daughter index for this primary particle
	std::string prim_daughters_idx_str = prim_tag+"daughters..idx";
	int *prim_daughters_idx = new int[nprim_tot];
	
	// I think the number of daughter particles for this primary particle 
	std::string prim_daughters_length_str = prim_tag+"daughters..length";
	Int_t *prim_daughters_length = new Int_t[nprim_tot];
	

	// --------------- RECO STUFF -------------------------------------- //

	std::string slc_reco_tag = "rec.slc.reco.pfp.";

	std::string slc_nu_score_str = "rec.slc.nu_score";
	Float_t *slc_nu_score = new Float_t[slc_length];
	
	std::string slc_is_clear_cosmic_str = "rec.slc.is_clear_cosmic";
	Char_t *slc_is_clear_cosmic = new Char_t[slc_length];

	std::string slc_fmatch_time_str = "rec.slc.fmatch.time";
	Float_t *slc_fmatch_time = new Float_t[slc_length];

	std::string slc_fmatch_score_str = "rec.slc.fmatch.score";
	Float_t *slc_fmatch_score = new Float_t[slc_length];
	
	std::string slc_vtx_x_str = "rec.slc.vertex.x";
	Float_t *slc_vtx_x = new Float_t[slc_length];

	std::string slc_vtx_y_str = "rec.slc.vertex.y";
	Float_t *slc_vtx_y = new Float_t[slc_length];

	std::string slc_vtx_z_str = "rec.slc.vertex.z";
	Float_t *slc_vtx_z = new Float_t[slc_length];

	std::string slc_pfp_length_str = slc_reco_tag + ".length";
	Int_t *slc_pfp_length = new Int_t[slc_length];

	std::string slc_pfp_idx_str = slc_reco_tag + ".idx";
	Int_t *slc_pfp_idx = new Int_t[slc_length];

	//std::string slc_npfp_str = slc_reco_tag + "npfp";
	//ULong64_t *slc_npfp = new ULong64_t[slc_length];
	

        void setSliceInfoAddresses(TTree *tree) {
          
	  // Header Slice Info 
	  tree->SetBranchAddress(slc_length_str.c_str(), &slc_length);
	  tree->SetBranchAddress(slc_self_str.c_str(), slc_self);
	  tree->SetBranchAddress(slc_genie_mode_str.c_str(), slc_genie_mode);
	  tree->SetBranchAddress(slc_pdg_str.c_str(), slc_true_pdg);
	  tree->SetBranchAddress(slc_parent_pdg_str.c_str(), slc_parent_pdg);
	  tree->SetBranchAddress(slc_nu_index_str.c_str(), slc_nu_index);
	  tree->SetBranchAddress(slc_resnum_str.c_str(), slc_resnum);
          tree->SetBranchAddress(iscc_str.c_str(), iscc);
          tree->SetBranchAddress(isnc_str.c_str(), isnc);
          tree->SetBranchAddress(isvtxcont_str.c_str(), isvtxcont);
          tree->SetBranchAddress(slc_x_str.c_str(), slc_x);
          tree->SetBranchAddress(slc_y_str.c_str(), slc_y);
          tree->SetBranchAddress(slc_z_str.c_str(), slc_z);

	  // primary particle info
          tree->SetBranchAddress(nprim_tot_str.c_str(), &nprim_tot);
          tree->SetBranchAddress(slc_nprim_str.c_str(), nprim);
          tree->SetBranchAddress(slc_prim_length_str.c_str(), slc_prim_length);
          tree->SetBranchAddress(slc_prim_idx_str.c_str(), slc_prim_idx);
          tree->SetBranchAddress(prim_pdg_str.c_str(), prim_pdg);
          tree->SetBranchAddress(prim_parent_str.c_str(), prim_parent);
          tree->SetBranchAddress(G4ID_str.c_str(), G4ID);
          tree->SetBranchAddress(cont_tpc_str.c_str(), cont_tpc);
          tree->SetBranchAddress(prim_genE_str.c_str(), prim_genE);
          tree->SetBranchAddress(prim_startx_str.c_str(), prim_startx);
          tree->SetBranchAddress(prim_starty_str.c_str(), prim_starty);
          tree->SetBranchAddress(prim_startz_str.c_str(), prim_startz);
          tree->SetBranchAddress(prim_endx_str.c_str(), prim_endx);
          tree->SetBranchAddress(prim_endy_str.c_str(), prim_endy);
          tree->SetBranchAddress(prim_endz_str.c_str(), prim_endz);
          tree->SetBranchAddress(prim_px_str.c_str(), prim_px);
          tree->SetBranchAddress(prim_py_str.c_str(), prim_py);
          tree->SetBranchAddress(prim_pz_str.c_str(), prim_pz);
	  

	  // primary daughter branches
          tree->SetBranchAddress(nprim_daughters_str.c_str(), &nprim_daughters_tot);
          tree->SetBranchAddress(prim_daughters_str.c_str(), prim_daughters);
          tree->SetBranchAddress(prim_daughters_idx_str.c_str(), prim_daughters_idx);


	  // RECO STUFF 
          tree->SetBranchAddress(slc_nu_score_str.c_str(), slc_nu_score);
          tree->SetBranchAddress(slc_is_clear_cosmic_str.c_str(), slc_is_clear_cosmic);
          tree->SetBranchAddress(slc_fmatch_time_str.c_str(), slc_fmatch_time);
          tree->SetBranchAddress(slc_fmatch_score_str.c_str(), slc_fmatch_score);
	  tree->SetBranchAddress(slc_vtx_x_str.c_str(), slc_vtx_x);
          tree->SetBranchAddress(slc_vtx_y_str.c_str(), slc_vtx_y);
          tree->SetBranchAddress(slc_vtx_z_str.c_str(), slc_vtx_z);
          tree->SetBranchAddress(slc_pfp_length_str.c_str(), slc_pfp_length);
          tree->SetBranchAddress(slc_pfp_idx_str.c_str(), slc_pfp_idx);
          //tree->SetBranchAddress(slc_npfp_str.c_str(), slc_npfp);



	}


private:
// might not need this


};

} // end namespace analysis

#endif



