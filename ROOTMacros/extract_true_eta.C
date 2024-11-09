#include <TFile.h>
#include <TNtuple.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


void extract_true_eta(const char* input_file, const char* output_file) {
  
    //Open the input and output ROOT files
    TFile* infile = TFile::Open(input_file, "READ");
    TFile* outfile = new TFile(output_file, "RECREATE");


    TNtuple* slc_tree = new TNtuple("slc_tree", "slc_tree", "run:subrun:ev:slc:pdg:iscc:isnc:mode:Q2:vtx_x:vtx_y:vtx_z");
    //TNtuple* nu_tree = new TNtuple("nu_tree", "nu_tree", "slc:pdg:E");
    //TNtuple* prim_tree = new TNtuple("prim_tree", "prim_tree", "slc:pdg:mode:genE:x:y:z:inTPC");
    //TNtuple* nu_prim_tree = new TNtuple("nu_prim_tree", "nu_prim_tree", 
    //					"slc:pdg:genE:start_x:start_y:start_z:end_x:end_y:end_z:px:py:pz");


    // Access the event tree
    TTree* event_tree = (TTree*)infile->Get("recTree");
    Long64_t n_entries = event_tree->GetEntries();
    std::cout << "This tree has " << n_entries << " events ..." << std::endl;


    // Header Variables
    UInt_t run = 0;
    UInt_t subrun = 0;
    UInt_t evt = 0;
    float pot = 0.;
    event_tree->SetBranchAddress("rec.hdr.run", &run);
    event_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
    event_tree->SetBranchAddress("rec.hdr.evt", &evt);
    event_tree->SetBranchAddress("rec.hdr.pot", &pot);

// ------------------------- Slice Branches --------------------------------------------------- //

    // Slice Position --> Maybe the true Neutrino Vertex ?
    Float_t slc_x;
    Float_t slc_y;
    Float_t slc_z;
    event_tree->SetBranchAddress("rec.slc.truth.position.x", &slc_x);
    event_tree->SetBranchAddress("rec.slc.truth.position.y", &slc_y);
    event_tree->SetBranchAddress("rec.slc.truth.position.z", &slc_z);
    
    Int_t slc_id;
    event_tree->SetBranchAddress("rec.slc.self", &slc_id);

    Int_t slc_pdg;
    event_tree->SetBranchAddress("rec.slc.truth.pdg", &slc_pdg);
    
    Char_t slc_iscc;
    event_tree->SetBranchAddress("rec.slc.truth.iscc", &slc_iscc);
    
    Char_t slc_isnc;
    event_tree->SetBranchAddress("rec.slc.truth.isnc", &slc_isnc);

    Short_t slc_genie_mode;
    event_tree->SetBranchAddress("rec.slc.truth.genie_mode", &slc_genie_mode);
    
    Float_t slc_Q2;
    event_tree->SetBranchAddress("rec.slc.truth.Q2", &slc_Q2);
    
    Int_t slc_nprim;
    event_tree->SetBranchAddress("rec.slc.truth.nprim", &slc_nprim);
    
    Int_t slc_parent_pdg;
    event_tree->SetBranchAddress("rec.slc.truth.parent_pdg", &slc_parent_pdg);
       
    Float_t slc_vtx_x;
    Float_t slc_vtx_y;
    Float_t slc_vtx_z;
    event_tree->SetBranchAddress( "rec.slc.truth.vtx.x", &slc_vtx_x);
    event_tree->SetBranchAddress( "rec.slc.truth.vtx.y", &slc_vtx_y);
    event_tree->SetBranchAddress( "rec.slc.truth.vtx.z", &slc_vtx_z);

    Float_t slc_time;
    event_tree->SetBranchAddress( "rec.slc.truth.time", &slc_time);
// ------------------------- Prim Branches --------------------------------------------------- //

    /*
    std::vector<Char_t>* prim_cont_tpc;
    event_tree->SetBranchAddress("rec.slc.truth.prim.cont_tpc", &prim_cont_tpc);
    
    std::vector<Float_t>* prim_genE;
    event_tree->SetBranchAddress("rec.slc.truth.prim.genE", &prim_genE);
    
    std::vector<Int_t>* prim_interaction_id;
    event_tree->SetBranchAddress("rec.slc.truth.prim.interaction_id", &prim_interaction_id);
   
    std::vector<Int_t>* prim_pdg;
    event_tree->SetBranchAddress("rec.slc.truth.prim.pdg", &prim_pdg);
    
    std::vector<Int_t>* prim_G4ID;
    event_tree->SetBranchAddress("rec.slc.truth.prim.G4ID", &prim_G4ID);
    */


// ------------------------- Nu Prim Branches --------------------------------------------------- //
    /*
    Float_t nu_prim_start_x = -999.;
    Float_t nu_prim_start_y = -999.;
    Float_t nu_prim_start_z = -999.;
    event_tree->SetBranchAddress("rec.mc.nu.prim.start.x", &nu_prim_start_x);
    event_tree->SetBranchAddress("rec.mc.nu.prim.start.y", &nu_prim_start_y);
    event_tree->SetBranchAddress("rec.mc.nu.prim.start.z", &nu_prim_start_z);

    Float_t nu_prim_end_x = -999.;
    Float_t nu_prim_end_y = -999.;
    Float_t nu_prim_end_z = -999.;
    event_tree->SetBranchAddress("rec.mc.nu.prim.end.x", &nu_prim_end_x);
    event_tree->SetBranchAddress("rec.mc.nu.prim.end.y", &nu_prim_end_y);
    event_tree->SetBranchAddress("rec.mc.nu.prim.end.z", &nu_prim_end_z);
    
    Int_t nu_prim_pdg = 0;
    event_tree->SetBranchAddress("rec.mc.nu.prim.pdg", &nu_prim_pdg); 
    Float_t nu_prim_genE = -999.;
    event_tree->SetBranchAddress("rec.mc.nu.prim.genE", &nu_prim_genE);
    Float_t nu_prim_px = -999.;
    event_tree->SetBranchAddress("rec.mc.nu.prim.startp.x", &nu_prim_px);
    Float_t nu_prim_py = -999.;
    event_tree->SetBranchAddress("rec.mc.nu.prim.startp.y", &nu_prim_py);
    Float_t nu_prim_pz = -999.;
    event_tree->SetBranchAddress("rec.mc.nu.prim.startp.z", &nu_prim_pz);
    */

    std::cout << "Start Slice Loop ..." << std::endl;
    // Start loop over events which are slices in the flat cafs effectively
    int count = 0;
    for (Long64_t i = 0; i < n_entries; ++i) {
      event_tree->GetEntry(i);

      if (count % 10 == 0) {
        std::cout << "Processing event " << count << std::endl;
        std::cout << "Run " << run << " subrun " << subrun << " pot " << pot << std::endl;

        count += 1;
      }

      //"run:subrun:ev:slc:pdg:iscc:isnc:mode:Q2:vtx_x:vtx_y:vtx_z"
      slc_tree->Fill(run, subrun, evt, slc_id, slc_pdg, slc_iscc, slc_isnc, slc_genie_mode, slc_Q2, slc_vtx_x, slc_vtx_y, slc_vtx_z);

      std::cout << "Filled Slice tree" << std::endl;
      /*
      nu_prim_tree->Fill(slc_id, 
			 nu_prim_pdg, 
			 nu_prim_genE, 
	                 nu_prim_start_x,	      
	                 nu_prim_start_y,	      
	                 nu_prim_start_z,
	                 nu_prim_end_x,	      
	                 nu_prim_end_y,	      
	                 nu_prim_end_z,
			 nu_prim_px,	      
			 nu_prim_py,	      
			 nu_prim_pz	      
			);	      
      */
      std::cout << "Filled the nu_prim_tree" << std::endl;
   
    } // end of loop over event tree
    slc_tree->SetDirectory(0);
    //nu_prim_tree->SetDirectory(0);
    
    outfile->cd();
    
    slc_tree->Write();
    //nu_prim_tree->Write();
    
    outfile->Close();
    infile->Close();

} // end of ROOT MACRO




