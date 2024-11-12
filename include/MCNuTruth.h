#ifndef MCNU_TRUTH_H
#define MCNU_TRUTH_H



// Standard Library Includes
#include <iostream>
#include <fstream>

// // ROOT Includes
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"


namespace analysis {


class MCNuTruth {

public:
        MCNuTruth() {}
        ~MCNuTruth() {}


	std::string nu_tag = "rec.mc.nu.";
        
	// ------------------ Slice Header Variables ----------------- //
	
	std::string nu_length_str = "rec.mc.nu..length";
	Int_t nu_length = 100;



        std::string nu_genie_mode_str = nu_tag + "genie_mode";
	Short_t *nu_genie_mode = new Short_t[nu_length];
	
	
	std::string iscc_str = nu_tag + "iscc";
	std::string isnc_str = nu_tag + "isnc";
        Char_t *nu_iscc = new Char_t[nu_length];
        Char_t *nu_isnc = new Char_t[nu_length];
	
	

        void setMCNuTruthAddresses(TTree *tree) {
          
	  // Header Slice Info 
	  tree->SetBranchAddress(nu_length_str.c_str(), &nu_length);
	  tree->SetBranchAddress(nu_genie_mode_str.c_str(), nu_genie_mode);
	  tree->SetBranchAddress(iscc_str.c_str(), nu_iscc);
	  tree->SetBranchAddress(isnc_str.c_str(), nu_isnc);

	}


private:
// might not need this


};

} // end namespace analysis

#endif



