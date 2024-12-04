#include <TFile.h>
#include <TNtuple.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

// Custom includes
#include "../include/SliceInfo.h"
#include "../include/PFPInfo.h"

using namespace analysis;

//gDebug = 3;

void pfp_scraper(const char* input_file, const char* output_file) {
    
    //extern Int_t gDebug;
    //gDebug = 1;
  
    //Open the input and output ROOT files
    TFile* infile = TFile::Open(input_file, "READ");
    if (!infile || infile->IsZombie()) {
      std::cerr << "File is a zombie mate" << std::endl;
      return;
    }

    TFile* outfile = new TFile(output_file, "RECREATE");

    //TH1D* hist_tot_pot = new TH1D(); 
    TH1D* hist_tot_pot = (TH1D*)infile->Get("TotalPOT")->Clone("TOTPOT_Clone");

    TNtuple* event_tree_out = new TNtuple("event_tree", "event_tree", "run:subrun:evt:ngenevt");


    TNtuple* pfp_tree = new TNtuple("pfp_tree", "pfp_tree", "run:subrun:evt:slc:trackScore:id:parent:parent_is_primary:t0");

    
    TNtuple* shower_tree1 = new TNtuple("shower_tree1", "shower_tree1", 
					"run:subrun:evt:slc:trackScore:bestplane_energy:dir_x:dir_y:dir_z:start_x:start_y:start_z:end_x:end_y:end_z");

    TNtuple* shower_tree2 = new TNtuple("shower_tree2", "shower_tree2", 
					"run:subrun:evt:slc:conv_gap:razzle_photonScore:razzle_electronScore:razzle_bestScore:bestmatch_G4ID:bestmatch_hit_completeness:bestmatch_hit_purity");

    
    TNtuple* track_tree1 = new TNtuple("track_tree1", "track_tree1", 
					"run:subrun:evt:slc:trackScore:dir_x:dir_y:dir_z:start_x:start_y:start_z:end_x:end_y:end_z");
    
    TNtuple* track_tree2 = new TNtuple("track_tree2", "track_tree2", 
					"run:subrun:evt:slc:p_muon:p_proton:p_pion:dazzle_muonScore:dazzle_protonScore:dazzle_pionScore:dazzle_bestScore:bestmatch_G4ID");


    // Access the event tree
    TTree* event_tree = (TTree*)infile->Get("recTree");
    if (!event_tree) {
      std::cerr << "File doesn't have the tree you are looking for mate!" << std::endl;
      infile->Close();
      return;
    }
    Long64_t n_entries = event_tree->GetEntries();
    std::cout << "This tree has " << n_entries << " events ..." << std::endl;

    // Classes for grabbing relavent branches

    SliceInfo slc_truth;
    slc_truth.setSliceInfoAddresses(event_tree);

    PFPInfo pfp_info;
    pfp_info.setPFPInfoAddresses(event_tree);

    // Header Variables
    UInt_t run;
    UInt_t subrun;
    UInt_t evt;
    UInt_t ngenevt;
    //float pot = 0.;
    event_tree->SetBranchAddress("rec.hdr.run", &run);
    event_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
    event_tree->SetBranchAddress("rec.hdr.evt", &evt);
    event_tree->SetBranchAddress("rec.hdr.ngenevt", &ngenevt);



    std::cout << "Start Event Loop ..." << std::endl;
    // Start loop over events which are slices in the flat cafs effectively
    int count = 0;
    for (Long64_t i = 0; i < n_entries; ++i) {
      event_tree->GetEntry(i);

      	
      //if (count % 10 == 0) {
      std::cout << std::endl << std::endl << std::endl;
      std::cout << "// ------------------ Processing event ------------------ // " << count << std::endl;
      std::cout << "Run " << run << " subrun " << subrun << std::endl;
      std::cout << std::endl;

      std::cout << "Filling the event tree" << std::endl;
      event_tree_out->Fill(
			   run,
			   subrun,
			   evt,
			   ngenevt
			  );

      count += 1;
      //}
      std::cout << std::endl;

      std::cout << "Loop over slices" << std::endl;
      //int nprim_prev = 0;
      for (int s = 0; s < slc_truth.slc_length; ++s) {
	std::cout << std::endl;

	// Loop over the reco pfps --> Should be same number of showers and tracks !!!!

	std::cout << "Starting PFP Loop for Slice Number " << s << " --> Slice Self " << slc_truth.slc_self[s] << std::endl;
	std::cout << "pfp length " << slc_truth.slc_pfp_length[s] << std::endl;
	for (int pfp = slc_truth.slc_pfp_idx[s]; pfp < (slc_truth.slc_pfp_idx[s] + slc_truth.slc_pfp_length[s]); ++pfp) {

	  if (pfp_info.pfp_slcID[pfp] != slc_truth.slc_self[s]) {
	    std::cout << "PROBLEM --> pfp slcID " << pfp_info.pfp_slcID[pfp] << " current slice self " << slc_truth.slc_self[s] << std::endl;
	    break;

	  }

	  pfp_tree->Fill(
	                 run,
			 subrun,
			 evt,
			 slc_truth.slc_self[s],
			 pfp_info.pfp_trackScore[pfp],
			 pfp_info.pfp_id[pfp],
			 pfp_info.pfp_parent[pfp],
			 pfp_info.pfp_parent_is_primary[pfp],
			 pfp_info.pfp_t0[pfp]
			);
		    	 

	  std::cout << "Shower truth G4ID " << pfp_info.shw_truth_G4ID[pfp] << " track G4ID " << pfp_info.trk_truth_G4ID[pfp] << std::endl;
	  shower_tree1->Fill(
			     run,
			     subrun,
			     evt,
                             slc_truth.slc_self[s], 
			     pfp_info.pfp_trackScore[pfp],
			     pfp_info.shw_bestplane_energy[pfp],
			     pfp_info.shw_dir_x[pfp],
			     pfp_info.shw_dir_y[pfp],
			     pfp_info.shw_dir_z[pfp],
			     pfp_info.shw_start_x[pfp],
			     pfp_info.shw_start_y[pfp],
			     pfp_info.shw_start_z[pfp],
			     pfp_info.shw_end_x[pfp],
			     pfp_info.shw_end_y[pfp],
			     pfp_info.shw_end_z[pfp]
	                    );

	  shower_tree2->Fill(
			     run,
			     subrun,
			     evt,
                             slc_truth.slc_self[s], 
			     pfp_info.shw_conversion_gap[pfp],
			     pfp_info.shw_razzle_photonScore[pfp],
			     pfp_info.shw_razzle_electronScore[pfp],
			     pfp_info.shw_razzle_bestScore[pfp],
			     pfp_info.shw_truth_G4ID[pfp],
			     pfp_info.shw_truth_hit_completeness[pfp],
			     pfp_info.shw_truth_hit_purity[pfp]
	                    );

	
	  track_tree1->Fill(
			     run,
			     subrun,
			     evt,
                             slc_truth.slc_self[s], 
			     pfp_info.pfp_trackScore[pfp],
			     pfp_info.trk_dir_x[pfp],
			     pfp_info.trk_dir_y[pfp],
			     pfp_info.trk_dir_z[pfp],
			     pfp_info.trk_start_x[pfp],
			     pfp_info.trk_start_y[pfp],
			     pfp_info.trk_start_z[pfp],
			     pfp_info.trk_end_x[pfp],
			     pfp_info.trk_end_y[pfp],
			     pfp_info.trk_end_z[pfp]
	                    );

	  track_tree2->Fill(
			     run,
			     subrun,
			     evt,
                             slc_truth.slc_self[s],
			     pfp_info.trk_p_muon[pfp],
			     pfp_info.trk_p_proton[pfp],
			     pfp_info.trk_p_pion[pfp],
			     pfp_info.trk_muonScore[pfp],
			     pfp_info.trk_protonScore[pfp],
			     pfp_info.trk_pionScore[pfp],
			     pfp_info.trk_bestScore[pfp],
			     pfp_info.trk_truth_G4ID[pfp]
	                    );


	} // end of loop over reco pfps in this slice

	std::cout << std::endl;

      } // end of slice loop
      
    } // end of loop over event tree
    
    std::cout << "Finished Event Loop" << std::endl;
    event_tree->ResetBranchAddresses();

    hist_tot_pot->SetDirectory(0);
    event_tree_out->SetDirectory(0);
    pfp_tree->SetDirectory(0);
    shower_tree1->SetDirectory(0);    
    shower_tree2->SetDirectory(0);    
    track_tree1->SetDirectory(0);    
    track_tree2->SetDirectory(0);  

    outfile->cd();
    
    hist_tot_pot->Write();
    event_tree_out->Write();
    pfp_tree->Write();
    shower_tree1->Write();
    shower_tree2->Write();
    track_tree1->Write();
    track_tree2->Write();

    std::cout << "Finished Writing Trees" << std::endl;
    outfile->Close();
    infile->Close();

    delete outfile;     // Clean up the output file
    delete infile;      // Clean up the input file

    std::cout << "Finished Closing Files" << std::endl;

} // end of ROOT MACRO




