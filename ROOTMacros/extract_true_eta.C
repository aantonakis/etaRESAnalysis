#include <TFile.h>
#include <TNtuple.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "../include/SliceTruth.h"
#include "../include/MCNuTruth.h"
#include "../include/ParticleTruth.h"

using namespace analysis;

void extract_true_eta(const char* input_file, const char* output_file) {
  
    //Open the input and output ROOT files
    TFile* infile = TFile::Open(input_file, "READ");
    TFile* outfile = new TFile(output_file, "RECREATE");


    //TH1D* hist_tot_pot = new TH1D(); 
    TH1D* hist_tot_pot = (TH1D*)infile->Get("TotalPOT");

    TNtuple* slc_tree = new TNtuple("slc_tree", "slc_tree", "run:subrun:evt:slc:mode:pdg:iscc:isnc:vtx_x:vtx_y:vtx_z");

    //TNtuple* slc_tree = new TNtuple("slc_tree", "slc_tree", "run:subrun:evt:slc:mode:slc_pdg:x:y:z")
    TNtuple* particle_tree1 = new TNtuple("particle_tree1", "particle_tree1", 
    					 "run:subrun:evt:slc:pdg:G4ID:parent:genE:px:py:pz");
    

    TNtuple* particle_tree2 = new TNtuple("particle_tree2", "particle_tree2", 
    					 "run:subrun:evt:slc:start_x:start_y:start_z:end_x:end_y:end_z");


    TNtuple* daughter_tree1 = new TNtuple("daughter_tree1", "daughter_tree1", "run:subrun:evt:slc:pdg:parent:genE:px:py:pz");
    TNtuple* daughter_tree2 = new TNtuple("daughter_tree2", "daughter_tree2", "run:subrun:evt:slc:start_x:start_y:start_z:end_x:end_y:end_z");

    TNtuple* cosmic_tree1 = new TNtuple("cosmic_tree1", "cosmic_tree1", "run:subrun:evt:pdg:genE:pc:py:pz");
    TNtuple* cosmic_tree2 = new TNtuple("cosmic_tree2", "cosmic_tree2", "run:subrun:evt:start_x:start_y:start_z:end_x:end_y:end_z");


    // Access the event tree
    TTree* event_tree = (TTree*)infile->Get("recTree");
    Long64_t n_entries = event_tree->GetEntries();
    std::cout << "This tree has " << n_entries << " events ..." << std::endl;


    SliceTruth slc_truth;
    slc_truth.setSliceTruthAddresses(event_tree);

    MCNuTruth nu_truth;
    nu_truth.setMCNuTruthAddresses(event_tree);

    ParticleTruth part_truth;
    part_truth.setParticleTruthAddresses(event_tree);


    // Header Variables
    UInt_t run;
    UInt_t subrun;
    UInt_t evt;
    //float pot = 0.;
    event_tree->SetBranchAddress("rec.hdr.run", &run);
    event_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
    event_tree->SetBranchAddress("rec.hdr.evt", &evt);
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

      count += 1;
      //}
      std::cout << "Number of slices in this event " << slc_truth.slc_length << std::endl;
      std::cout << "Number of mc neutrinos in this event " << nu_truth.nu_length << std::endl;
      std::cout << "Number of true particles in this event " << part_truth.part_length << std::endl;
      std::cout << "Number of primary daughters in this event " << slc_truth.nprim_daughters_tot << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;

      for (int nu = 0; nu < nu_truth.nu_length; ++nu) {std::cout << "MC Nu Mode " << nu_truth.nu_genie_mode[nu] << std::endl;}

      std::cout << "Fill the cosmic trees" << std::endl;
      for (int t = 0; t < part_truth.part_length; ++t) {
        // interaction id == -1 for cosmic particles
        if (part_truth.part_interaction_id[t] == -1) {
	  cosmic_tree1->Fill(
	                     run,
		             subrun,
		             evt,
			     part_truth.part_pdg[t],
			     part_truth.part_genE[t],
			     part_truth.part_px[t],
			     part_truth.part_py[t],
			     part_truth.part_pz[t]
	                    );	

	  cosmic_tree2->Fill(
	                     run,
		             subrun,
		             evt,
			     part_truth.part_genx[t],
			     part_truth.part_geny[t],
			     part_truth.part_genz[t],
			     part_truth.part_endx[t],
			     part_truth.part_endy[t],
			     part_truth.part_endz[t]
	                    );	
				
	}   
      } // end of loop over cosmics
      std::cout << "Loop over slices" << std::endl;
      int nprim_prev = 0;
      for (int s = 0; s < slc_truth.slc_length; ++s) {
	std::cout << std::endl;
        std::cout << "New Slice: Slice nprim " << slc_truth.nprim[s] << std::endl;
	if (nu_truth.nu_iscc[slc_truth.slc_nu_index[s]]) {std::cout << "ISCC Evaluated to True !!!" << std::endl;}

	/*
	// check if the slice is a cosmic and look through the true particles ...
	if (slc_truth.slc_true_pdg[s] == -1) {
	  std::cout << "WE HAVE A COSMIC !!! ---> LOOK AT  TRUE PARTICLES ..." << std::endl;
	  std::cout << "Slice Self " << slc_truth.slc_self[s]  << " Slice Parent PDG "<< slc_truth.slc_parent_pdg[s] << std::endl;
	  for (int t = 0; t < part_truth.part_length; ++t) {
	    if (part_truth.part_pdg[t] == 13 || part_truth.part_pdg[t] == -13) {
	      std::cout << "part pdg " << part_truth.part_pdg[t] 
		        << " parent "  << part_truth.part_parent[t] 
			<< " G4ID "    << part_truth.part_G4ID[t] 
			<< " start_process " << part_truth.part_start_process[t] 
			<< " interaction_id " << part_truth.part_interaction_id[t] << std::endl; 
	    }
	  }

	}
	*/

	//"run:subrun:evt:slc:mode:pdg:vtx_x:vtx_y:vtx_z"
	slc_tree->Fill(
	               run,
		       subrun,
		       evt,
		       slc_truth.slc_self[s],
		       slc_truth.slc_genie_mode[s],
		       slc_truth.slc_true_pdg[s],
		       nu_truth.nu_iscc[slc_truth.slc_nu_index[s]],
		       nu_truth.nu_isnc[slc_truth.slc_nu_index[s]],
		       slc_truth.slc_x[s],
		       slc_truth.slc_y[s],
		       slc_truth.slc_z[s]
		      );        

        std::cout << "Loop over Prime Particles " << slc_truth.nprim[s] << std::endl;
	
	for (int pr = nprim_prev; pr < slc_truth.nprim[s] + nprim_prev; ++pr) {
	  //std::cout << "pr index " << pr << std::endl;
	  //std::cout << "mode " << slc_truth.slc_genie_mode[s] << " pdg " << slc_truth.prim_pdg[pr] << " parent " << slc_truth.prim_parent[pr] << std::endl; 	  
	  //std::cout << "genE " << slc_truth.prim_genE[pr] << " start_x " << slc_truth.prim_startx[pr] << " end_x " <<  slc_truth.prim_endx[pr] << " px " << slc_truth.prim_px[pr] << std::endl; 

          //run:subrun:evt:slc:mode:pdg:parent:genE:start_x:start_y:start_z:end_x:end_y:end_z:px:py:pz
	  
	  particle_tree1->Fill(
			      run,
			      subrun,
			      evt,
                              slc_truth.slc_self[s], 
                              slc_truth.prim_pdg[pr], 
                              slc_truth.G4ID[pr], 
                              slc_truth.prim_parent[pr], 
                              slc_truth.prim_genE[pr], 
                              slc_truth.prim_px[pr], 
                              slc_truth.prim_py[pr], 
                              slc_truth.prim_pz[pr] 
			      ); 
	  
	  particle_tree2->Fill(
			      run,
			      subrun,
			      evt,
                              slc_truth.slc_self[s], 
                              slc_truth.prim_startx[pr], 
                              slc_truth.prim_starty[pr], 
                              slc_truth.prim_startz[pr], 
                              slc_truth.prim_endx[pr], 
                              slc_truth.prim_endy[pr], 
                              slc_truth.prim_endz[pr]
			      ); 

	  std::cout << std::endl;
          std::cout << "Primary Particle " << pr << " pdg " << slc_truth.prim_pdg[pr] << std::endl;
	  std::cout << "Loop over daughter particles of this primary" << std::endl;
	  //std::cout << "Starting index " << slc_truth.prim_daughters_idx[pr] << " number of daughters " << slc_truth.prim_daughters_length[pr] << std::endl; 				
	  
	  int stop = 0;
	  if ((pr + 1) >  (slc_truth.nprim[s] + nprim_prev-1)) {
	    stop = pr;
	  }
	  else {
	    stop = pr + 1;
	  }
	  std::cout << "pr " << pr << " stop " << stop << std::endl;
	  std::cout << "Starting index " << slc_truth.prim_daughters_idx[pr] << " number of daughters: stopping index " << slc_truth.prim_daughters_idx[stop] << std::endl; 				
	  for (int d = slc_truth.prim_daughters_idx[pr]; d < slc_truth.prim_daughters_idx[stop]; ++d) {
            //std::cout << "daughter " << slc_truth.prim_daughters[d] << std::endl;
            //std::cout << "G4ID " << part_truth.part_G4ID[d] << std::endl;
	    // Now we need to loop through the true particles to find the G4ID that matches the daughter (track id)
	    for (int p = 0; p < part_truth.part_length; ++p) {

	      if (part_truth.part_G4ID[p] == slc_truth.prim_daughters[d]) {
		std::cout << "daughter pdg " << part_truth.part_pdg[p] << " d " << d << " p " << p << std::endl;
		//"run:subrun:evt:slc:pdg:parent:genE:px:py:pz"
		daughter_tree1->Fill(
				    run,
				    subrun,
				    evt,
			            slc_truth.slc_self[s],	
				    part_truth.part_pdg[p],
				    slc_truth.G4ID[pr],
				    part_truth.part_genE[p],
				    part_truth.part_px[p],
				    part_truth.part_py[p],
				    part_truth.part_pz[p]
			            );

		
		daughter_tree2->Fill(
				    run,
				    subrun,
				    evt,
			            slc_truth.slc_self[s],
				    part_truth.part_genx[p],	
				    part_truth.part_geny[p],	
				    part_truth.part_genz[p],	
				    part_truth.part_endx[p],	
				    part_truth.part_endy[p],	
				    part_truth.part_endz[p]	
			            );
		// break because some pi0's end up having an eta daughter with the same G4ID as a gamma ???
		break;

	      }

	    }

	  }
	  std::cout << std::endl;

        } // end of prim loop
	nprim_prev = slc_truth.nprim[s];

	std::cout << std::endl;

      } // end of slice loop
      
    } // end of loop over event tree
    
    std::cout << "Finished Event Loop" << std::endl;

    hist_tot_pot->SetDirectory(0);
    slc_tree->SetDirectory(0);
    particle_tree1->SetDirectory(0);
    particle_tree2->SetDirectory(0);
    daughter_tree1->SetDirectory(0);
    daughter_tree2->SetDirectory(0);
    cosmic_tree1->SetDirectory(0);    
    cosmic_tree2->SetDirectory(0);    


    outfile->cd();
    
    hist_tot_pot->Write();
    slc_tree->Write();
    particle_tree1->Write();
    particle_tree2->Write();
    daughter_tree1->Write();    
    daughter_tree2->Write();    
    cosmic_tree1->Write();
    cosmic_tree2->Write();

    outfile->Close();
    infile->Close();

} // end of ROOT MACRO




