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
#include "../include/CRTInfo.h"

using namespace analysis;

//gDebug = 3;

void crt_scraper(const char* input_file, const char* output_file) {
    
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
    TNtuple* crt_tree = new TNtuple("crt_tree", "crt_tree", "run:subrun:evt:x:y:z:t");


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

    CRTInfo crt_info;
    crt_info.setCRTInfoAddresses(event_tree);
    
    // Header Variables
    UInt_t run;
    UInt_t subrun;
    UInt_t evt;
    UInt_t ngenevt;    

    event_tree->SetBranchAddress("rec.hdr.run", &run);
    event_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
    event_tree->SetBranchAddress("rec.hdr.evt", &evt);
    event_tree->SetBranchAddress("rec.hdr.ngenevt", &ngenevt);
    //event_tree->SetBranchAddress("rec.hdr.pot", &pot);

    std::cout << "Start Event Loop ..." << std::endl;
    // Start loop over events which are slices in the flat cafs effectively
    int count = 0;
    for (Long64_t i = 0; i < n_entries; ++i) {
      event_tree->GetEntry(i);

      	
      //if (count % 10 == 0) {
      std::cout << std::endl << std::endl << std::endl;
      std::cout << "// ------------------ Processing event ------------------ // " << count << std::endl;
      std::cout << "Run " << run << " subrun " << subrun << std::endl;

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

      std::cout << "Fill the CRT Trees" << std::endl;
      for (int c = 0; c < crt_info.crt_sp_length; ++c) {
        
        crt_tree->Fill(
		       run,
		       subrun,
		       evt,
		       crt_info.crt_sp_x[c],
		       crt_info.crt_sp_y[c],
		       crt_info.crt_sp_z[c],
		       crt_info.crt_sp_t[c]
		      );

      } // end of CRT loop in this event
      
    } // end of loop over event tree
    
    std::cout << "Finished Event Loop" << std::endl;
    event_tree->ResetBranchAddresses();

    hist_tot_pot->SetDirectory(0);
    event_tree_out->SetDirectory(0);
    crt_tree->SetDirectory(0);

    outfile->cd();
    
    hist_tot_pot->Write();
    event_tree_out->Write();
    crt_tree->Write();    


    std::cout << "Finished Writing Trees" << std::endl;
    outfile->Close();
    infile->Close();

    delete outfile;     // Clean up the output file
    delete infile;      // Clean up the input file

    std::cout << "Finished Closing Files" << std::endl;

} // end of ROOT MACRO




