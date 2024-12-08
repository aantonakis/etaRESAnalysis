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


//using namespace analysis;

//gDebug = 3;

void crt_header_scraper(const char* input_file, const char* output_file) {
    
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

    TNtuple* event_tree_out = new TNtuple("crt_event_tree", "crt_event_tree", "run:subrun:evt:ngenevt:n_h:n_sp:n_t:n_sbnd_t");



    // Access the event tree
    TTree* event_tree = (TTree*)infile->Get("recTree");
    if (!event_tree) {
      std::cerr << "File doesn't have the tree you are looking for mate!" << std::endl;
      infile->Close();
      return;
    }
    Long64_t n_entries = event_tree->GetEntries();
    std::cout << "This tree has " << n_entries << " events ..." << std::endl;


    // Header Variables
    UInt_t run;
    UInt_t subrun;
    UInt_t evt;
    UInt_t ngenevt;
    Int_t n_h;
    Int_t n_sp;
    Int_t n_t;
    Int_t n_sbnd_t;

    //float pot = 0.;
    event_tree->SetBranchAddress("rec.hdr.run", &run);
    event_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
    event_tree->SetBranchAddress("rec.hdr.evt", &evt);
    event_tree->SetBranchAddress("rec.hdr.ngenevt", &ngenevt);
    event_tree->SetBranchAddress("rec.ncrt_hits", &n_h);
    event_tree->SetBranchAddress("rec.ncrt_spacepoints", &n_sp);
    event_tree->SetBranchAddress("rec.ncrt_tracks", &n_t);
    event_tree->SetBranchAddress("rec.nsbnd_crt_tracks", &n_sbnd_t);

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
			   ngenevt,
			   n_h,
			   n_sp,
			   n_t,
			   n_sbnd_t
			  );

      count += 1;
      //}
      std::cout << std::endl;

    } // end of loop over event tree
    
    std::cout << "Finished Event Loop" << std::endl;
    event_tree->ResetBranchAddresses();

    hist_tot_pot->SetDirectory(0);
    event_tree_out->SetDirectory(0);

    outfile->cd();
    
    hist_tot_pot->Write();
    event_tree_out->Write();

    std::cout << "Finished Writing Trees" << std::endl;
    outfile->Close();
    infile->Close();

    delete outfile;     // Clean up the output file
    delete infile;      // Clean up the input file

    std::cout << "Finished Closing Files" << std::endl;

} // end of ROOT MACRO




