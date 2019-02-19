/* Code containing several function to analyze the tracking results from 
 * BMAD. Started by Antoine Chapelain (antoine.chapelain@cornell.edu) April 2015 */

#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;

int main() {

	// Open ROOT file and associated tree
	TString inRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/fiberMuonPositron.root" ;
	TFile *inFile = new TFile(inRootFileName, "READ") ;
	TTree *inTree = (TTree*) inFile->Get("tree") ;

	// Define all the required variables
	Double_t harp, fiber, time, x, px, y, py, z, pz;

	// Assigned the above variables to the tree branches
	inTree->SetBranchAddress("harp",  	&harp) ;
	inTree->SetBranchAddress("fiber",  &fiber) ;
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
	const double fiberPos[4][16] = {
    {-45., -40.3, -38.0, -27.3, -25.1, -14.3, -12.2, -1.3, 0.9, 11.7, 13.7, 24.6, 26.9, 37.6, 39.7, 45}, // Y-profile at 180 deg
    {-45., -39.3, -38.3, -26.3, -25.2, -13.3, -12.3, -0.3, 0.8, 12.7, 13.7, 25.7, 26.8, 38.7, 39.7, 45}, // X-profile at 180 deg
    {-45., -37.9, -37.1, -25.0, -24.1, -12.0, -11.1, 1.0, 1.9, 14.0, 14.8, 27.0, 27.9, 40.0, 40.8, 45}, // Y-profile at 270 deg -- CAVEAT
    {-45., -39.2, -38.6, -26.2, -25.5, -13.2, -12.6, -0.2, 0.5, 12.8, 13.4, 25.9, 26.5, 38.8, 39.7, 45}}; // X-profile at 270 deg

	TH1D *h_harp1_intensity = new TH1D("h_harp1_intensity", "Y-profile harp 180", 3333, 0, 499950);
	TH1D *h_harp2_intensity = new TH1D("h_harp2_intensity", "X-profile harp 180", 3333, 0, 499950);
	TH1D *h_harp3_intensity = new TH1D("h_harp3_intensity", "Y-profile harp 270", 3333, 0, 499950);
	TH1D *h_harp4_intensity = new TH1D("h_harp4_intensity", "X-profile harp 270", 3333, 0, 499950);

	// Loop over tree entries 
	for (int i=0; i<nentries; ++i) {

		// Get event
		inTree->GetEntry(i) ;

		if ( harp == 1 ) h_harp1_intensity -> Fill( time*1E9 );
		if ( harp == 2 ) h_harp2_intensity -> Fill( time*1E9 );
		if ( harp == 3 ) h_harp3_intensity -> Fill( time*1E9 );
		if ( harp == 4 ) h_harp4_intensity -> Fill( time*1E9 );

	}

	// Plot and save histogram
	TCanvas c;
	TString outRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/test.root" ;
	TFile *outFile = new TFile(outRootFileName, "RECREATE") ;
	h_harp1_intensity->Write();
	h_harp2_intensity->Write();
	h_harp3_intensity->Write();
	h_harp4_intensity->Write();

	// Close Tfile
	outFile->Close();
	inFile->Close();

}
