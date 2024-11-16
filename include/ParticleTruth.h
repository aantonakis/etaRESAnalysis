#ifndef PARTICLE_TRUTH_H
#define PARTICLE_TRUTH_H



// Standard Library Includes
#include <iostream>
#include <fstream>

// // ROOT Includes
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"


namespace analysis {


class ParticleTruth {

public:
        ParticleTruth() {}
        ~ParticleTruth() {}


	std::string part_tag = "rec.true_particles.";
        
	// ------------------ Slice Header Variables ----------------- //
	
	std::string part_length_str = part_tag+".length";
	Int_t part_length = 1000;

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

        std::string part_endx_str = part_tag + "end.x";
	Float_t *part_endx = new Float_t[part_length];
        std::string part_endy_str = part_tag + "end.y";
	Float_t *part_endy = new Float_t[part_length];
        std::string part_endz_str = part_tag + "end.z";
	Float_t *part_endz = new Float_t[part_length];
	
	
	

        void setParticleTruthAddresses(TTree *tree) {
          
	  // Header Slice Info 
	  tree->SetBranchAddress(part_length_str.c_str(), &part_length);
	  tree->SetBranchAddress(part_pdg_str.c_str(), part_pdg);
	  tree->SetBranchAddress(part_G4ID_str.c_str(), part_G4ID);
	  tree->SetBranchAddress(part_parent_str.c_str(), part_parent);
	  tree->SetBranchAddress(part_start_process_str.c_str(), part_start_process);
	  tree->SetBranchAddress(part_interaction_id_str.c_str(), part_interaction_id);
	  tree->SetBranchAddress(part_genE_str.c_str(), part_genE);
	  tree->SetBranchAddress(part_px_str.c_str(), part_px);
	  tree->SetBranchAddress(part_py_str.c_str(), part_py);
	  tree->SetBranchAddress(part_pz_str.c_str(), part_pz);
	  tree->SetBranchAddress(part_genx_str.c_str(), part_genx);
	  tree->SetBranchAddress(part_geny_str.c_str(), part_geny);
	  tree->SetBranchAddress(part_genz_str.c_str(), part_genz);
	  tree->SetBranchAddress(part_endx_str.c_str(), part_endx);
	  tree->SetBranchAddress(part_endy_str.c_str(), part_endy);
	  tree->SetBranchAddress(part_endz_str.c_str(), part_endz);

	}


private:
// might not need this


};

} // end namespace analysis

#endif



