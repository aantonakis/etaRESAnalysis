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

void extract_true_eta(const char* input_file, const char* output_file) {
    
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

    TNtuple* slc_tree = new TNtuple("slc_tree", "slc_tree", "run:subrun:evt:slc:nu_score:is_clear_cosmic:fmatch_time:fmatch_score:vtx_x:vtx_y:vtx_z");
    TNtuple* slc_truth_tree = new TNtuple("slc_truth_tree", "slc_truth_tree", "run:subrun:evt:slc:mode:pdg:iscc:isnc:vtx_x:vtx_y:vtx_z");

    TNtuple* particle_tree1 = new TNtuple("particle_tree1", "particle_tree1", 
    					 "run:subrun:evt:slc:pdg:G4ID:parent:genE:px:py:pz");
    

    TNtuple* particle_tree2 = new TNtuple("particle_tree2", "particle_tree2", 
    					 "run:subrun:evt:slc:start_x:start_y:start_z:end_x:end_y:end_z");


    TNtuple* daughter_tree1 = new TNtuple("daughter_tree1", "daughter_tree1", "run:subrun:evt:slc:pdg:parent:genE:px:py:pz");
    TNtuple* daughter_tree2 = new TNtuple("daughter_tree2", "daughter_tree2", "run:subrun:evt:slc:start_x:start_y:start_z:end_x:end_y:end_z");

    TNtuple* cosmic_tree1 = new TNtuple("cosmic_tree1", "cosmic_tree1", "run:subrun:evt:pdg:genE:px:py:pz");
    TNtuple* cosmic_tree2 = new TNtuple("cosmic_tree2", "cosmic_tree2", "run:subrun:evt:start_x:start_y:start_z:end_x:end_y:end_z");

    
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

    MCNuTruth nu_truth;
    nu_truth.setMCNuTruthAddresses(event_tree);

    ParticleTruth part_truth;
    part_truth.setParticleTruthAddresses(event_tree);

    PFPInfo pfp_info;
    pfp_info.setPFPInfoAddresses(event_tree);
    
    // Header Variables
    UInt_t run;
    UInt_t subrun;
    UInt_t evt;
    //float pot = 0.;
    event_tree->SetBranchAddress("rec.hdr.run", &run);
    event_tree->SetBranchAddress("rec.hdr.subrun", &subrun);
    event_tree->SetBranchAddress("rec.hdr.evt", &evt);
    //event_tree->SetBranchAddress("rec.hdr.pot", &pot);

    Int_t N_cosmics = 0;


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
        if ( (part_truth.part_interaction_id[t] == -1) && (abs(part_truth.part_pdg[t]) == 13 || abs(part_truth.part_pdg[t]) == 11) ) {

	  N_cosmics += 1;

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
      //int nprim_prev = 0;
      for (int s = 0; s < slc_truth.slc_length; ++s) {
	std::cout << std::endl;
        std::cout << "New Slice: Slice nprim " <<  slc_truth.slc_prim_length[s] << std::endl;
	if (nu_truth.nu_iscc[slc_truth.slc_nu_index[s]]) {std::cout << "ISCC Evaluated to True !!!" << std::endl;}
	//std::cout << "fmatch time " << slc_truth.slc_fmatch_time[s] << " score " << slc_truth.slc_fmatch_score[s] << std::endl;
	slc_tree->Fill(
	               run,
		       subrun,
		       evt,
		       slc_truth.slc_self[s],
		       slc_truth.slc_nu_score[s], 	
		       slc_truth.slc_is_clear_cosmic[s],
		       slc_truth.slc_fmatch_time[s],
		       slc_truth.slc_fmatch_score[s],
		       //1.0,
		       //1.0,
		       slc_truth.slc_vtx_x[s],
		       slc_truth.slc_vtx_y[s],
		       slc_truth.slc_vtx_z[s]
		      );


	slc_truth_tree->Fill(
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

	// Loop over the reco pfps --> Should be same number of showers and tracks !!!!

	std::cout << "Starting PFP Loop for Slice Number " << s << " --> Slice Self " << slc_truth.slc_self[s] << std::endl;
	std::cout << "pfp length " << slc_truth.slc_pfp_length[s] << std::endl;
	for (int pfp = slc_truth.slc_pfp_idx[s]; pfp < (slc_truth.slc_pfp_idx[s] + slc_truth.slc_pfp_length[s]); ++pfp) {

	  if (pfp_info.pfp_slcID[pfp] != slc_truth.slc_self[s]) {
	    std::cout << "PROBLEM --> pfp slcID " << pfp_info.pfp_slcID[pfp] << " current slice self " << slc_truth.slc_self[s] << std::endl;
	    break;

	  }
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


        std::cout << "Loop over Prime Particles --> slice nprim " << slc_truth.nprim[s] << std::endl;
	std::cout << "Prime Index " << slc_truth.slc_prim_idx[s] << std::endl;
	//std::cout << "nprim_prev " << nprim_prev << " slc_prim_idx " << slc_truth.slc_prim_idx[s] << std::endl;
	std::cout << "nprim " << slc_truth.nprim[s] << " slc_prim_length " << slc_truth.slc_prim_length[s] << std::endl; 	
	//for (int pr = nprim_prev; pr < slc_truth.nprim[s] + nprim_prev; ++pr) {
	for (int pr = slc_truth.slc_prim_idx[s]; pr < slc_truth.slc_prim_idx[s] + slc_truth.slc_prim_length[s]; ++pr) {
	  
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
	  //if ((pr + 1) >  (slc_truth.nprim[s] + nprim_prev-1)) {
	  if ((pr + 1) >  (slc_truth.slc_prim_idx[s] + slc_truth.slc_prim_length[s]-1)) {
	    stop = pr;
	  }
	  else {
	    stop = pr + 1;
	  }
	  
	  //std::cout << "pr " << pr << " stop " << stop << std::endl;
	  //std::cout << "Starting index " << slc_truth.prim_daughters_idx[pr] << " number of daughters: stopping index " << slc_truth.prim_daughters_idx[stop] << std::endl; 				
	  //for (int d = slc_truth.prim_daughters_idx[pr]; d < slc_truth.prim_daughters_idx[stop]; ++d) {
	  std::cout << "Starting Prim Daughter index " << slc_truth.prim_daughters_idx[pr] 
						       //<< " number of daughters: stopping index " << slc_truth.prim_daughters_idx[pr] + slc_truth.prim_daughters_length[pr] << std::endl; 				
						       << " number of daughters: stopping index " << slc_truth.prim_daughters_idx[stop] << std::endl; 				
	  for (int d = slc_truth.prim_daughters_idx[pr]; d < slc_truth.prim_daughters_idx[stop]; ++d) {
	  //for (int d = slc_truth.prim_daughters_idx[pr]; d < slc_truth.prim_daughters_idx[pr] + slc_truth.prim_daughters_length[pr]; ++d) {
            //std::cout << "daughter " << slc_truth.prim_daughters[d] << std::endl;
            //std::cout << "G4ID " << part_truth.part_G4ID[d] << std::endl;
	    // Now we need to loop through the true particles to find the G4ID that matches the daughter (track id)
	    for (int p = 0; p < part_truth.part_length; ++p) {

	      if (part_truth.part_G4ID[p] == slc_truth.prim_daughters[d]) {
		std::cout << "daughter pdg " << part_truth.part_pdg[p] << " d " << d << " p " << p << std::endl;
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

	      } // end of check whether 

	    }

	  }
	  std::cout << std::endl;

        } // end of prim loop
	//nprim_prev = slc_truth.nprim[s];

	std::cout << std::endl;

      } // end of slice loop
      
    } // end of loop over event tree
    
    std::cout << "Finished Event Loop" << std::endl;
    std::cout << "Number of cosmics " << N_cosmics << std::endl;
    event_tree->ResetBranchAddresses();

    hist_tot_pot->SetDirectory(0);
    slc_tree->SetDirectory(0);
    slc_truth_tree->SetDirectory(0);
    shower_tree1->SetDirectory(0);    
    shower_tree2->SetDirectory(0);    
    track_tree1->SetDirectory(0);    
    track_tree2->SetDirectory(0);    
    particle_tree1->SetDirectory(0);
    particle_tree2->SetDirectory(0);
    daughter_tree1->SetDirectory(0);
    daughter_tree2->SetDirectory(0);
    cosmic_tree1->SetDirectory(0);    
    cosmic_tree2->SetDirectory(0);    

    outfile->cd();
    
    hist_tot_pot->Write();
    slc_tree->Write();
    slc_truth_tree->Write();
    shower_tree1->Write();
    shower_tree2->Write();
    track_tree1->Write();
    track_tree2->Write();
    particle_tree1->Write();
    particle_tree2->Write();
    daughter_tree1->Write();    
    daughter_tree2->Write();
    cosmic_tree1->Write();
    cosmic_tree2->Write();
    
    std::cout << "Finished Writing Trees" << std::endl;
    outfile->Close();
    infile->Close();

    delete outfile;     // Clean up the output file
    delete infile;      // Clean up the input file

    std::cout << "Finished Closing Files" << std::endl;

} // end of ROOT MACRO




