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
#include "../include/TrueParticles.h"

using namespace analysis;

//gDebug = 3;

void true_particles_scraper(const char* input_file, const char* output_file) {
    
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
    TNtuple* part_tree1 = new TNtuple("part_tree1", "part_tree1", "run:subrun:evt:G4ID:pdg:parent:interaction_id:cont_tpc:crosses_tpc:contained:cryostat");
    TNtuple* part_tree2 = new TNtuple("part_tree2", "part_tree2", "run:subrun:evt:genE:px:py:pz:genx:geny:genz:endE");
    TNtuple* part_tree3 = new TNtuple("part_tree3", "part_tree3", "run:subrun:evt:start_x:start_y:start_z:end_x:end_y:end_z");

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

    TrueParticles part_info;
    part_info.setTrueParticlesAddresses(event_tree);
    
    // Header Variables
    UInt_t run;
    UInt_t subrun;
    UInt_t evt;
    UInt_t ngenevt;
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

      std::cout << "Fill the particle Trees" << std::endl;
      std::cout << "There are " << part_info.part_length << " particles" << std::endl;
      for (int p = 0; p < part_info.part_length; ++p) {
        
    	//TNtuple* part_tree1 = new TNtuple("part_tree1", "part_tree1", "run:subrun:evt:G4ID:pdg:parent:interaction_id:cont_tpc:crosses_tpc:contained:cryostat");
    	//TNtuple* part_tree2 = new TNtuple("part_tree2", "part_tree2", "genE:px:py:pz:genx:geny:genz:endE:start_x:start_y:start_z:end_x:end_y:end_z")

	//std::cout << "cont_tpc " << part_info.part_cont_tpc[p] << std::endl;
        
        part_tree1->Fill(
		         run,
		         subrun,
		         evt,
		         part_info.part_G4ID[p],
		         part_info.part_pdg[p],
		         part_info.part_parent[p],
		         part_info.part_interaction_id[p],
		         part_info.part_cont_tpc[p],
		         part_info.part_crosses_tpc[p],
		         part_info.part_contained[p],
		         part_info.part_cryostat[p]
		        );

        part_tree2->Fill(
		         run,
		         subrun,
		         evt,
		         part_info.part_genE[p],
		         part_info.part_px[p],
		         part_info.part_py[p],
		         part_info.part_pz[p],
		         part_info.part_genx[p],
		         part_info.part_geny[p],
		         part_info.part_genz[p],
		         part_info.part_endE[p]
		        );
        
	part_tree3->Fill(
		         run,
		         subrun,
		         evt,
		         part_info.part_startx[p],
		         part_info.part_starty[p],
		         part_info.part_startz[p],
		         part_info.part_endx[p],
		         part_info.part_endy[p],
		         part_info.part_endz[p]
		        );


      } // end of particle loop in this event
      
    } // end of loop over event tree
    
    std::cout << "Finished Event Loop" << std::endl;
    event_tree->ResetBranchAddresses();

    hist_tot_pot->SetDirectory(0);
    event_tree_out->SetDirectory(0);
    part_tree1->SetDirectory(0);
    part_tree2->SetDirectory(0);
    part_tree3->SetDirectory(0);

    outfile->cd();
    
    hist_tot_pot->Write();
    event_tree_out->Write();
    part_tree1->Write();    
    part_tree2->Write();    
    part_tree3->Write();    


    std::cout << "Finished Writing Trees" << std::endl;
    outfile->Close();
    infile->Close();

    delete outfile;     // Clean up the output file
    delete infile;      // Clean up the input file

    std::cout << "Finished Closing Files" << std::endl;

} // end of ROOT MACRO




