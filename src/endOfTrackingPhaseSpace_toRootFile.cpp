#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;


int main (int argc, char* argv[]) {


	string inTextFileName = argv[1];
  string outDir 		 = argv[2];

	string rootFileName = outDir +"/endOfTracking_phase_space.root";
	TFile *ff;

	if ( !ifstream(rootFileName).good() ) {
		ff = new TFile(rootFileName.c_str(),"recreate");
	}
	else {
		cout << "Error: File already exist." << endl;
		return -1;
	}

	TTree *tree = new TTree("tree","tree");
	FILE *fp;
	char buff[400];
	char buf[100];
	char *token;

	ifstream myfile;

	Double_t qfield[29];
	Int_t ient =0;

	tree->Branch("muonID",&qfield[0],"muonID/D");
	tree->Branch("jx",&qfield[1],"jx/D");
	tree->Branch("jy",&qfield[2],"jy/D");
	tree->Branch("x",&qfield[3],"x/D");
	tree->Branch("xp",&qfield[4],"xp/D");
	tree->Branch("y",&qfield[5],"y/D");
	tree->Branch("yp",&qfield[6],"yp/D");
	tree->Branch("z",&qfield[7],"z/D");
	tree->Branch("zp",&qfield[8],"zp/D");
	tree->Branch("t",&qfield[9],"t/D");
	tree->Branch("s",&qfield[10],"s/D");
	tree->Branch("sx",&qfield[11],"sx/D");
	tree->Branch("sy",&qfield[12],"sy/D");
	tree->Branch("sz",&qfield[13],"sz/D");
	tree->Branch("tau",&qfield[14],"tau/D");
	tree->Branch("betaXEx",&qfield[15],"betaXEx/D");
	tree->Branch("betaXEy",&qfield[16],"betaXEy/D");
	tree->Branch("betaXEz",&qfield[17],"betaXEz/D");
	tree->Branch("totTime",&qfield[18],"totTime/D");
	tree->Branch("betaDotBx",&qfield[19],"betaDotBx/D");
	tree->Branch("betaDotBy",&qfield[20],"betaDotBy/D");
	tree->Branch("betaDotBz",&qfield[21],"betaDotBz/D");
	tree->Branch("freq",&qfield[22],"freq/D");
	tree->Branch("<x>",&qfield[23],"<x>/D");
	tree->Branch("<px>",&qfield[24],"<px>/D");
	tree->Branch("<y>",&qfield[25],"<y>/D");
	tree->Branch("<py>",&qfield[26],"<py>/D");
	tree->Branch("<z>",&qfield[27],"<z>/D");
	tree->Branch("<pz>",&qfield[28],"<pz>/D");


	if ( !ifstream(inTextFileName).good() ) {
		cout << "Input text file does not exit -- exiting" << endl;
		return 1;
	}
	std::ifstream inFile(inTextFileName);
	std::string line;

	while (std::getline(inFile, line))
	{
		string testFile = line + "/EndOfTracking_phase_space.dat";

		if ( !ifstream(testFile).good() ) {
			cout << "File does not exist: skipping" << endl;
			continue;
		}

		cout << " File being analyzed: " << testFile << endl;
		fp= fopen(testFile.c_str(),"r");
		fgets(buff,400,fp);

		while(fgets(buff,400,fp))
		{
			//if(!(ient%10000))cout<<"ient:"<<ient<<endl;
			token = strtok(buff," ");
			Int_t ii =0;
			while(token!=NULL)
			{
				sscanf(token,"%lf",&qfield[ii]);
				//if(!(ient%10000)) cout<<qfield[ii]<<" ";
				token =strtok(NULL," ");
				ii++;
			}

			//if(!(ient%10000))cout<<endl;
			tree->Fill();
			ient++;
		}


		fclose(fp);
	}

	tree->Write();
	ff->Close();

	return 0;

}
