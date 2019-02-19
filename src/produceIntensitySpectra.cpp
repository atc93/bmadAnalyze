/* Code containing several function to analyze the tracking results from 
 * BMAD. Started by Antoine Chapelain (antoine.chapelain@cornell.edu) April 2015 */

#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;

int main(int argc, char* argv[]) {

  TString fileName = argv[1];

	// Open ROOT file and associated tree
	TString inRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/"+fileName ;
	TFile *inFile = new TFile(inRootFileName, "UPDATE") ;
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

	TH1D *h_intensity[4][7];

	for ( int i=0; i<4; ++i ) {
		for ( int j=0; j<7; ++j ) {
			TString name = Form("harp%dFiber%d_intensity", i+1, j+1);
			h_intensity[i][j] = new TH1D (name, name, 399960, 0, 499950);
		}
	}


	// Loop over tree entries 
	for (int i=0; i<nentries; ++i) {

		// Get event
		inTree->GetEntry(i) ;

		// Change harp numbering to comply with the rest of the world
		if ( harp == 1 ) harp =2;
		else if ( harp == 2 ) harp =1;
		else if ( harp == 3 ) harp =4;
		else if ( harp == 4 ) harp =3;

		h_intensity[int(harp)-1][int(fiber)-1] -> Fill( time*1E9 ) ;

	}

  for ( int i=0; i<4; ++i ) {
    for ( int j=0; j<7; ++j ) {
			h_intensity[i][j] -> Write();
    }
  }

	// Close Tfile
	inFile->Close();

}
