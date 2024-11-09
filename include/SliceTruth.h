#ifndef SLICE_TRUTH_H
#define SLICE_TRUTH_H



// Standard Library Includes
#include <iostream>
#include <fstream>

// // ROOT Includes
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"


namespace analysis {


class SliceTruth {

public:
        SliceTruth() {}
        ~SliceTruth() {}


	std::string slc_tag = "rec.slc.truth.";
        
	std::string slc_length_str = "rec.slc..length";
	Int_t slc_length = 100;
	
	std::string slc_pdg_str = slc_tag + "pdg";
	int *slc_true_pdg = new int[slc_length];
	
	std::string iscc_str = slc_tag + "iscc";
	std::string isnc_str = slc_tag + "isnc";
        bool *iscc = new bool[slc_length];
        bool *isnc = new bool[slc_length];
	
	std::string slc_x_str = slc_tag + "position.x";
	std::string slc_y_str = slc_tag + "position.y";
	std::string slc_z_str = slc_tag + "position.z";

	// true slice vertex
        float *slc_x = new float[slc_length]; 
	float *slc_y = new float[slc_length]; 
	float *slc_z = new float[slc_length]; 
	
	// nprim in each slice
	std::string slc_nprim_str = slc_tag + "nprim";
	int *nprim = new int[slc_length];


        std::string nprim_tot_str = slc_tag + "prim..totarraysize";	
	int nprim_tot = 500;

	std::string prim_pdg_str = slc_tag + "prim.pdg";
	int *prim_pdg = new int[nprim_tot];


        void setSliceTruthAddresses(TTree *tree) {
          
	  // Header Slice Info 
	  tree->SetBranchAddress(slc_length_str.c_str(), &slc_length);
	  tree->SetBranchAddress(slc_pdg_str.c_str(), slc_true_pdg);
          tree->SetBranchAddress(iscc_str.c_str(), iscc);
          tree->SetBranchAddress(isnc_str.c_str(), isnc);
          tree->SetBranchAddress(slc_x_str.c_str(), slc_x);
          tree->SetBranchAddress(slc_y_str.c_str(), slc_y);
          tree->SetBranchAddress(slc_z_str.c_str(), slc_z);

	  // primary particle info
          tree->SetBranchAddress(nprim_tot_str.c_str(), &nprim_tot);
          tree->SetBranchAddress(slc_nprim_str.c_str(), nprim);
          tree->SetBranchAddress(prim_pdg_str.c_str(), prim_pdg);
	  

	}


private:
// might not need this


};

} // end namespace analysis

#endif



