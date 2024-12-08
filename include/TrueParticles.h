#ifndef TRUE_PARTICLES_H
#define TRUE_PARTICLES_H



// Standard Library Includes
#include <iostream>
#include <fstream>

// // ROOT Includes
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"


namespace analysis {


class TrueParticles {

public:
        TrueParticles() {}
        ~TrueParticles() {}


	std::string part_tag = "rec.true_particles.";
        
	// ------------------ Slice Header Variables ----------------- //
	
	std::string part_length_str = part_tag+".length";
	Int_t part_length = 5000;

        std::string part_pdg_str = part_tag + "pdg";
	Int_t *part_pdg = new Int_t[part_length];

        std::string part_G4ID_str = part_tag + "G4ID";
	Int_t *part_G4ID = new Int_t[part_length];

	std::string part_parent_str = part_tag + "parent";
	UInt_t *part_parent = new UInt_t[part_length];
	
	std::string part_start_process_str = part_tag + "start_process";
	Short_t *part_start_process = new Short_t[part_length];	

        std::string part_interaction_id_str = part_tag + "interaction_id";
	Int_t *part_interaction_id = new Int_t[part_length];


	
        std::string part_cont_tpc_str = part_tag + "cont_tpc";
	Char_t *part_cont_tpc = new Char_t[part_length];

	
        std::string part_crosses_tpc_str = part_tag + "crosses_tpc";
	Char_t *part_crosses_tpc = new Char_t[part_length];

        std::string part_contained_str = part_tag + "contained";
	Char_t *part_contained = new Char_t[part_length];

        std::string part_cryostat_str = part_tag + "cryostat";
	Int_t *part_cryostat = new Int_t[part_length];


        std::string part_genE_str = part_tag + "genE";
	Float_t *part_genE = new Float_t[part_length];
	
        std::string part_px_str = part_tag + "genp.x";
	Float_t *part_px = new Float_t[part_length];
        std::string part_py_str = part_tag + "genp.y";
	Float_t *part_py = new Float_t[part_length];
        std::string part_pz_str = part_tag + "genp.z";
	Float_t *part_pz = new Float_t[part_length];

	
        std::string part_genx_str = part_tag + "gen.x";
	Float_t *part_genx = new Float_t[part_length];
        std::string part_geny_str = part_tag + "gen.y";
	Float_t *part_geny = new Float_t[part_length];
        std::string part_genz_str = part_tag + "gen.z";
	Float_t *part_genz = new Float_t[part_length];


        std::string part_startx_str = part_tag + "start.x";
	Float_t *part_startx = new Float_t[part_length];
        std::string part_starty_str = part_tag + "start.y";
	Float_t *part_starty = new Float_t[part_length];
        std::string part_startz_str = part_tag + "start.z";
	Float_t *part_startz = new Float_t[part_length];

        std::string part_endx_str = part_tag + "end.x";
	Float_t *part_endx = new Float_t[part_length];
        std::string part_endy_str = part_tag + "end.y";
	Float_t *part_endy = new Float_t[part_length];
        std::string part_endz_str = part_tag + "end.z";
	Float_t *part_endz = new Float_t[part_length];
	
        std::string part_endE_str = part_tag + "endE";
	Float_t *part_endE = new Float_t[part_length];


	// Truth timing information
        std::string part_genT_str = part_tag + "genT";
	Float_t *part_genT = new Float_t[part_length];

        std::string part_startT_str = part_tag + "startT";
	Float_t *part_startT = new Float_t[part_length];
	
        std::string part_endT_str = part_tag + "endT";
	Float_t *part_endT = new Float_t[part_length];
	

	/*
        std::string part_visE_0_0_str = part_tag + "plane.0.0.visE";
	Float_t *part_visE_0_0 = new Float_t[part_length];

        std::string part_visE_0_1_str = part_tag + "plane.0.1.visE";
	Float_t *part_visE_0_1 = new Float_t[part_length];
	
        std::string part_visE_0_2_str = part_tag + "plane.0.2.visE";
	Float_t *part_visE_0_2 = new Float_t[part_length];


        std::string part_visE_1_0_str = part_tag + "plane.0.0.visE";
	Float_t *part_visE_1_0 = new Float_t[part_length];

        std::string part_visE_1_1_str = part_tag + "plane.0.1.visE";
	Float_t *part_visE_1_1 = new Float_t[part_length];
	
        std::string part_visE_1_2_str = part_tag + "plane.0.2.visE";
	Float_t *part_visE_1_2 = new Float_t[part_length];
	*/

	// Daughter Info
	/*	
	std::string daughters_length_str = part_tag+"daughters..totarraysize";
	Int_t daughters_length = 5000;

        std::string part_daughters_length_str = part_tag + "daughters..length";
	Int_t *part_daughters_length = new Int_t[part_length];

        std::string part_daughters_idx_str = part_tag + "daughters..idx";
	Int_t *part_daughters_idx = new Int_t[part_length];

        std::string part_daughters_str = part_tag + "daughters";
	UInt_t *part_daughters = new UInt_t[daughters_length];
	*/

        void setTrueParticlesAddresses(TTree *tree) {
          
	  // Header Slice Info 
	  tree->SetBranchAddress(part_length_str.c_str(), &part_length);
	  tree->SetBranchAddress(part_pdg_str.c_str(), part_pdg);
	  tree->SetBranchAddress(part_G4ID_str.c_str(), part_G4ID);
	  tree->SetBranchAddress(part_parent_str.c_str(), part_parent);
	  tree->SetBranchAddress(part_start_process_str.c_str(), part_start_process);
	  tree->SetBranchAddress(part_interaction_id_str.c_str(), part_interaction_id);
	  
	  
	  tree->SetBranchAddress(part_cont_tpc_str.c_str(), part_cont_tpc);
	  tree->SetBranchAddress(part_crosses_tpc_str.c_str(), part_crosses_tpc);
	  tree->SetBranchAddress(part_contained_str.c_str(), part_contained);
	  tree->SetBranchAddress(part_cryostat_str.c_str(), part_cryostat);
	  

	  tree->SetBranchAddress(part_genE_str.c_str(), part_genE);
	  tree->SetBranchAddress(part_endE_str.c_str(), part_endE);
	  
	  tree->SetBranchAddress(part_px_str.c_str(), part_px);
	  tree->SetBranchAddress(part_py_str.c_str(), part_py);
	  tree->SetBranchAddress(part_pz_str.c_str(), part_pz);

	  tree->SetBranchAddress(part_genx_str.c_str(), part_genx);
	  tree->SetBranchAddress(part_geny_str.c_str(), part_geny);
	  tree->SetBranchAddress(part_genz_str.c_str(), part_genz);
	  
	  tree->SetBranchAddress(part_startx_str.c_str(), part_startx);
	  tree->SetBranchAddress(part_starty_str.c_str(), part_starty);
	  tree->SetBranchAddress(part_startz_str.c_str(), part_startz);
	  
	  tree->SetBranchAddress(part_endx_str.c_str(), part_endx);
	  tree->SetBranchAddress(part_endy_str.c_str(), part_endy);
	  tree->SetBranchAddress(part_endz_str.c_str(), part_endz);

	  // Truth timing
	  tree->SetBranchAddress(part_genT_str.c_str(), part_genT);
	  tree->SetBranchAddress(part_startT_str.c_str(), part_startT);
	  tree->SetBranchAddress(part_endT_str.c_str(), part_endT);
	  

	  // Daughter stuff
	  //tree->SetBranchAddress(daughters_length_str.c_str(), &daughters_length);
	  //tree->SetBranchAddress(part_daughters_length_str.c_str(), part_daughters_length);
	  //tree->SetBranchAddress(part_daughters_idx_str.c_str(), part_daughters_idx);
	  //tree->SetBranchAddress(part_daughters_str.c_str(), part_daughters);
	


	}


private:
// might not need this


};

} // end namespace analysis

#endif



