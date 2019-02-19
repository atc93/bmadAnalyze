/* Code containing several function to analyze the tracking results from 
 * BMAD. Started by Antoine Chapelain (antoine.chapelain@cornell.edu) April 2015 */

#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;

void PolarizationTracking_XZ_Plane(TString inRootFileName, TGraphErrors& GraphErr) {

	cout << "plouplou" << endl;
	// Open ROOT file and associated tree
	TFile *inFile = new TFile(inRootFileName) ;
	TTree *inTree = (TTree*) inFile->Get("tr") ;

	// Define all the required variables
	Double_t turn, mu_x, mu_px, mu_y, mu_py, mu_z, mu_pz,time, s, stot, state, muon, mu_polx, mu_poly, mu_polz ;
	TVector3 VecPolXZ ; // There is a hack: using component X and Y as X and Z for the g-2 geometry.
	Double_t PolOrientation ;

	// Assigned the above variables to the tree branches
	inTree->SetBranchAddress("t",  	&time) ;
	inTree->SetBranchAddress("polx", &mu_polx) ;
	inTree->SetBranchAddress("poly", &mu_poly) ;
	inTree->SetBranchAddress("polz", &mu_polz) ;
	cout << "plouplou" << endl;

	// Define variable for the TGraph to plot polarization evolution
	int nentries = inTree->GetEntries() ;
	int nSamples = -1;
	int entries = 100000;
	cout << "plouplou" << endl;
	double inDataX[entries], inDataY[entries], inDataDX[entries], inDataDY[entries] ;
	cout << "plouplou" << endl;

	cout << "hehe" << endl;
	// Loop over tree entries 
	for (int i=0; i<nentries; ++i) {

		// Get event
		inTree->GetEntry(i) ;
		++nSamples;

		// Time: x-axis
		inDataX[nSamples]= time ;

		// Total polarization
			// Reset the polarization vector to default value in case something goes wrong with the tree values
			VecPolXZ.SetXYZ(-999., -999., 0.) ;
			PolOrientation = -999. ;
			// Get the polarization values from the tree
			VecPolXZ.SetXYZ(mu_polz, mu_polx, 0.) ; // z is like the standard x-axis: i.e. if pol along z cos(angle)=1
			cout << mu_polz << endl;
			PolOrientation = VecPolXZ.Phi() ;
			if (PolOrientation<0) PolOrientation += TWOPI ;
			inDataY[nSamples] = cos(PolOrientation) ;
		  //cout << turn << " " << std::setprecision(9) << i << " " << time << " " << cos(PolOrientation) << endl;

	} // for (int i=0; i<nentries; i++) 

	// Set error to 0
  for (int i=0; i<nSamples; i++) {
    inDataDX[i] = 0.;
    inDataDY[i] = 0.;
  }


	GraphErr = TGraphErrors(nSamples, inDataX, inDataY, inDataDX, inDataDY);
	/*TH2D h = TH2D("h_PolAngle","Polarization Angle in the X-Z plane", 100, 0, 0.00015, 50, -1.1, 1.1);
	TCanvas c;
	GraphErr = TGraphErrors(nentries-1, inDataX, inDataY, inDataDX, inDataDY);
	h.Draw() ;
	GraphErr.Draw("same");
	c.SaveAs("lala.eps") ;*/

}

int CompareTwoPolarization_XZ_Plane () {

	int nFile = 3 ;
	int runOnFile = 3;
	TString inRootFileName[nFile] ;
	inRootFileName[0] = "single_particle_by_element_noOffset_100000turns.root" ;
	//inRootFileName[1] = "single_particle_by_element_offset0.2pct_100000turns.root" ;
	inRootFileName[1] = "single_particle_by_element_offset0.2pct_100000turns_rel1e-5_abs1e-6.root" ;
	inRootFileName[2] = "single_particle_by_element_offset-0.2pct_100000turns_rel1e-5_abs1e-6.root" ;
	//inRootFileName[2] = "single_particle_by_element_offset-0.2pct_100000turns.root" ;
  TGraphErrors GraphErr[nFile];

		for (int i=0; i<runOnFile; i++) {cout <<"heho" << endl;PolarizationTracking_XZ_Plane(inRootFileName[i], (TGraphErrors&) GraphErr[i]) ;}
		cout <<"heho" << endl;
		//if (runOnFile!=0) {
			gStyle->SetOptStat(0);
			TCanvas c;
			TH2D h = TH2D("h_PolAngle","Polarization Angle #theta in the X-Z plane, red: magic P, blue: 0.2\% offset, purple: -0.2\% offset", 1000, 0.0139900000000,0.014002000000, 5000, -1.1, 1.1);
			//TH2D h = TH2D("h_PolAngle","mu_polx, red: magic P, blue: +0.2\% offset, purple: -0.2\% offset", 1000, 0.01470000, 0.0149, 5000, -1.1, 1.1);
			h.GetXaxis()->SetTitle("Time [s]") ;
			h.GetYaxis()->SetTitle("cos(#theta)") ;
			h.Draw() ;
  		GraphErr[0].SetLineWidth(2);
  		GraphErr[0].SetMarkerStyle(21);
  		GraphErr[0].SetMarkerColor(2);
  		GraphErr[0].SetLineColor(2);
  		GraphErr[1].SetLineWidth(2);
  		GraphErr[1].SetMarkerStyle(21);
  		GraphErr[1].SetMarkerColor(4);
  		GraphErr[1].SetLineColor(4);
  		GraphErr[2].SetLineWidth(2);
  		GraphErr[2].SetMarkerStyle(21);
  		GraphErr[2].SetMarkerColor(6);
  		GraphErr[2].SetLineColor(6);
			GraphErr[0].Draw("same");
			GraphErr[1].Draw("same");
			GraphErr[2].Draw("same");
			c.SaveAs("lala.eps") ;
		//}
	
	return 0;

}
