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
#include "../include/MCNuTruth.h"
#include "../include/ParticleTruth.h"
#include "../include/PFPInfo.h"

using namespace analysis;

//gDebug = 3;

void check_file_integrity(const char* input_file, const char* output_file) {
    
    //extern Int_t gDebug;
    //gDebug = 1;
  
    //Open the input and output ROOT files
    TFile* infile = TFile::Open(input_file, "READ");
    TFile* outfile = new TFile(output_file, "RECREATE");


    //TH1D* hist_tot_pot = new TH1D(); 
    TH1D* hist_tot_pot = (TH1D*)infile->Get("TotalPOT")->Clone("TOTPOT_Clone");

    // Access the event tree
    TTree* event_tree = (TTree*)infile->Get("recTree");
    Long64_t n_entries = event_tree->GetEntries();
    std::cout << "This tree has " << n_entries << " events ..." << std::endl;

    // Classes for grabbing relavent branches

    //SliceInfo slc_truth;
    //slc_truth.setSliceInfoAddresses(event_tree);

    ParticleTruth part_truth;
    part_truth.setParticleTruthAddresses(event_tree);

    //PFPInfo pfp_info;
    //pfp_info.setPFPInfoAddresses(event_tree);
    
    // Header Variables
    UInt_t run = 0;
    UInt_t subrun = 0;
    UInt_t evt = 0;
    //float pot = 0.;
    event_tree->SetBranchAddress("rec.hdr.run", &run);
    event_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
    event_tree->SetBranchAddress("rec.hdr.evt", &evt);
    //event_tree->SetBranchAddress("rec.hdr.pot", &pot);

    int N_cosmics = 0;

    std::cout << "Start Event Loop ..." << std::endl;
    // Start loop over events which are slices in the flat cafs effectively
    int count = 0;
    for (Long64_t i = 0; i < n_entries; ++i) {
      event_tree->GetEntry(i);

      	
      std::cout << std::endl << std::endl << std::endl;
      std::cout << "// ------------------ Processing event ------------------ // " << count << std::endl;
      std::cout << "Run " << run << " subrun " << subrun << " evt " << evt << std::endl;

      count += 1;

    } // end of loop over event tree
    
    std::cout << "Finished Event Loop" << std::endl;
    std::cout << "Number of cosmics " << N_cosmics << std::endl;

    hist_tot_pot->SetDirectory(0);

    outfile->cd();
    
    hist_tot_pot->Write();
    
    std::cout << "Finished Writing Trees" << std::endl;
    outfile->Close();
    infile->Close();

    delete outfile;     // Clean up the output file
    delete infile;      // Clean up the input file

    std::cout << "Finished Closing Files" << std::endl;

} // end of ROOT MACRO




