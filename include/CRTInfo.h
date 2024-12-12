#ifndef CRT_INFO_H
#define CRT_INFO_H



// Standard Library Includes
#include <iostream>
#include <fstream>

// // ROOT Includes
#include "TTree.h"
#include "TObject.h"
#include "TVector3.h"


namespace analysis {


class CRTInfo {

public:
        CRTInfo() {}
        ~CRTInfo() {}


	std::string crt_sp_tag = "rec.crt_spacepoints.";
	
	
	std::string crt_sp_length_str = crt_sp_tag+".length";
	Int_t crt_sp_length = 5000;
        
	std::string crt_sp_x_str = crt_sp_tag+"position.x";
	Float_t *crt_sp_x = new Float_t[crt_sp_length];

	std::string crt_sp_y_str = crt_sp_tag+"position.y";
	Float_t *crt_sp_y = new Float_t[crt_sp_length];

	std::string crt_sp_z_str = crt_sp_tag+"position.z";
	Float_t *crt_sp_z = new Float_t[crt_sp_length];

	std::string crt_sp_t_str = crt_sp_tag+"time";
	Float_t *crt_sp_t = new Float_t[crt_sp_length];
	

        void setCRTInfoAddresses(TTree *tree) {
          
	  // Header Slice Info 
	  tree->SetBranchAddress(crt_sp_length_str.c_str(), &crt_sp_length);
	  tree->SetBranchAddress(crt_sp_x_str.c_str(), crt_sp_x);
	  tree->SetBranchAddress(crt_sp_y_str.c_str(), crt_sp_y);
	  tree->SetBranchAddress(crt_sp_z_str.c_str(), crt_sp_z);
	  tree->SetBranchAddress(crt_sp_t_str.c_str(), crt_sp_t);

	}


private:
// might not need this


};

} // end namespace analysis

#endif



