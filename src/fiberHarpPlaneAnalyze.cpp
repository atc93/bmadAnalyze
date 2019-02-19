/* Code containing several function to analyze the tracking results from 
 * BMAD. Started by Antoine Chapelain (antoine.chapelain@cornell.edu) April 2015 */

#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;

int main() {

	// Open ROOT file and associated tree
	TString inRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/harp.root" ;
	TFile *inFile = new TFile(inRootFileName, "UPDATE") ;
	TTree *inTree = (TTree*) inFile->Get("tree") ;

	// Define all the required variables
	Double_t harp, fiber, time, x, px, y, py, z, pz;

	// Assigned the above variables to the tree branches
	inTree->SetBranchAddress("harp",  	&harp) ;
	inTree->SetBranchAddress("time",  	&time) ;
	inTree->SetBranchAddress("x",  &x) ;
	inTree->SetBranchAddress("px",  	&px) ;
	inTree->SetBranchAddress("y",  &y) ;
	inTree->SetBranchAddress("py",  &py) ;
	inTree->SetBranchAddress("z",  &z) ;
	inTree->SetBranchAddress("pz",  &pz) ;

	// Define variable for the TGraph to plot polarization evolution
	int nentries = inTree->GetEntries() ;

	//y Define 1D histogram to plot the Muon detection time at the "fiber harp"
	TH1D *h_mu_t = new TH1D("h_fr","Muon detection time",672,0, 100128E-9) ; // 5 ns bin width
	TH2D *h_harp_x_hits = new TH2D("h_harp_x_hits", "X-profile harp hits", 20000, 0, 100E-6, 20, -0.045, 0.045);

	// Loop over tree entries 
	for (int i=0; i<nentries; ++i) {

		// Get event
		inTree->GetEntry(i) ;

		// Filter
		if (harp!=1) continue;

		// Fill histogram
		h_mu_t->Fill(time) ;
		h_harp_x_hits->Fill(time, x);

	}

	// Plot and save histogram
	TCanvas c;
	h_mu_t->Draw();
	c.SaveAs("MuTime.eps") ;
	c.SaveAs("MuTime.png") ;
	TString outRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/fiberHarpPlane.root" ;
	TFile *outFile = new TFile(outRootFileName, "RECREATE") ;
	h_mu_t->Write();
	h_harp_x_hits->Write();

	// Close Tfile
	outFile->Close();
	inFile->Close();

}
