/* Code containing several function to analyze the tracking results from 
 * BMAD. Started by Antoine Chapelain (antoine.chapelain@cornell.edu) April 2015 */

#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;

int main() {

	// Open ROOT file and associated tree
	TString harpInRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/fiberHarp.root" ;
	TFile *harpInFile = new TFile(harpInRootFileName, "READ") ;
	TH1D *h_harp_time = (TH1D*) harpInFile->Get("h_fr") ;
	TH2D *h_harp_x_hits = (TH2D*) harpInFile->Get("h_harp_x_hits") ;

	TString ghostHarpInRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/fiberHarpPlane.root" ;
	TFile *ghostHarpInFile = new TFile(ghostHarpInRootFileName, "READ") ;
	TH1D *h_ghostHarp_time = (TH1D*) ghostHarpInFile->Get("h_fr") ;
	TH2D *h_ghostHarp_x_hits = (TH2D*) ghostHarpInFile->Get("h_harp_x_hits") ;

	TH1D *h_intensity_ratio = h_harp_time;
	h_intensity_ratio->Divide(h_ghostHarp_time);
	h_intensity_ratio->Scale(100);
	TCanvas c;
	h_intensity_ratio->Draw();
	c.SaveAs("Harp1_intensity_ratio.eps");
	c.SaveAs("Harp1_intensity_ratio.png");

	TH1D *h_beamCent_rec = new TH1D("h_res_cent","resolution centroid", 672, 0, 100128E-9);
	TH1D *h_beamWidth_rec = new TH1D("h_res_width","resolution width", 672, 0, 100128E-9);
	for (int i=1; i<= h_beamCent_rec->GetNbinsX(); ++i) {
		h_harp_x_hits->GetXaxis()->SetRange(i, i);
		h_ghostHarp_x_hits->GetXaxis()->SetRange(i, i);
		cout << h_harp_x_hits->Integral() << endl;
		if (h_harp_x_hits->Integral()<50) continue;
		if ( (fabs(h_ghostHarp_x_hits->GetMean(2)-h_harp_x_hits->GetMean(2))*1000)>1) cout << h_ghostHarp_x_hits->GetMean(2) << " " << h_harp_x_hits->GetMean(2) << endl;
		h_beamCent_rec->SetBinContent(i, (h_ghostHarp_x_hits->GetMean(2)-h_harp_x_hits->GetMean(2))*1000);
		h_beamWidth_rec->SetBinContent(i, (h_ghostHarp_x_hits->GetStdDev(2)-h_harp_x_hits->GetStdDev(2))*1000);

	}

  TString inRootFileName = "/nfs/gm2/data1/achapela/bmadAnalyze/recPerf.root" ;
  TFile *inFile = new TFile(inRootFileName, "RECREATE") ;
	h_intensity_ratio->Write();
	h_beamCent_rec->Write();
	h_beamWidth_rec->Write();


}
