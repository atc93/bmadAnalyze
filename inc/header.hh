#include <TMatrixD.h>
#include <valarray>
#include <TCanvas.h>
#include <TFile.h>
#include <TLatex.h>
#include <TLine.h>
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TF2.h>
#include <THStack.h>
#include "TTree.h"
#include "TROOT.h"
#include "TDirectory.h"
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMinuit.h>
#include "TStyle.h"
#include "TObject.h"
#include "TClass.h"
#include "TKey.h"
#include "TFile.h"
#include "TH1.h"
#include "TSystem.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TLegend.h"
#include "TRandom.h"
#include <bitset>
#include "TColor.h"
#include "TVirtualFFT.h"
#include <TPad.h>
#include "TPaveText.h"
#include "TArrow.h"
#include "TLine.h"
#include <complex>
#include "TMath.h"
#include "math.h"
#include <complex>

#include <vector>
#include <string> 
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
using std::map;
using std::setprecision;
using std::iostream;

using namespace std;

void DrawATLASLabel(TCanvas* _c, TLatex* _g, double _xleft,double _ytop, string _desc);
