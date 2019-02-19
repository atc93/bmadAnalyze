/* Code containing several function to analyze the tracking results from 
 * BMAD. Started by Antoine Chapelain (antoine.chapelain@cornell.edu) April 2015 */

#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;

int main() {

	// Open ROOT file and associated tree
	TString frRootFileName 		= "/nfs/gm2/data1/achapela/bmadAnalyze/timeDepMomentsAtEnd.root" ;
	TString truthRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/endOfTracking_phase_space.root" ;

	TFile *frFile = new TFile(frRootFileName, "READ") ;
	TTree *frTree = (TTree*) frFile->Get("tree") ;

	TFile *truthFile = new TFile(truthRootFileName, "READ") ;
	TTree *truthTree = (TTree*) truthFile->Get("tree") ;

	// Define all the required variables
	Double_t time, number;
	Double_t freq, x;

	// Assigned the above variables to the tree branches
	frTree->SetBranchAddress("time",  &time) ;
	frTree->SetBranchAddress("number",  &number) ;

	truthTree->SetBranchAddress("<x>",  &x) ;
	truthTree->SetBranchAddress("freq",  &freq) ;

	//Define 1D histogram to plot the Muon detection time
	TH1D *h_fr 		= new TH1D("fr","Muon detection time",700000,0.5E-3,700) ; 
	TH1D *h_freq 	= new TH1D("freq","Frequency distribution",90,6660,6750) ; 
	TH1D *h_x 		= new TH1D("x","Muon detection time",300, 7112-45, 7112+45) ; 


	// Loop over tree entries 
	int nentries = frTree->GetEntries() ;
	for (int i=0; i<nentries; ++i) {

		// Get event
		frTree->GetEntry(i) ;

		// Fill histogram
		h_fr->Fill(time*1E6, number) ;

	}


	nentries = truthTree->GetEntries() ;
	for (int i=0; i<nentries; ++i) {

		// Get event
		truthTree->GetEntry(i) ;

		// Fill histogram
		h_freq->Fill(freq/1000) ;
		h_x->Fill(7112+x*1000) ;

	}

	// Plot and save histogram
	TString outRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/FR.root" ;
	TFile *outFile = new TFile(outRootFileName, "RECREATE") ;
	h_fr->Write();
	h_freq->Write();
  h_x->Write();

	TGraph g(0);
	for ( int i = 1; i <= h_x->GetNbinsX(); ++ i ) g.SetPoint( i-1, h_x->GetBinCenter(i), h_x->GetBinContent(i) );
	g.Write("r");

	// Close Tfile
	outFile->Close();
	frFile->Close();

}
