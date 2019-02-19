#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;


int main (int argc, char* argv[]) {


	string inTextFileName = argv[1];
  string outDir 		 = argv[2];

	string rootFileName = outDir +"/timeDepMomentsAtEnd.root";
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

	Double_t qfield[19];
	Int_t ient =0;

	tree->Branch("Time_bin",&qfield[0],"Time_Bin/D");
	tree->Branch("time",&qfield[1],"time/D");
	tree->Branch("number",&qfield[2],"number/D");
	tree->Branch("<x>",&qfield[3],"<x>/D");
	tree->Branch("<px>",&qfield[4],"<px>/D");
	tree->Branch("<y>",&qfield[5],"<y>/D");
	tree->Branch("<py>",&qfield[6],"<py>/D");
	tree->Branch("<z>",&qfield[7],"<z>/D");
	tree->Branch("<pz>",&qfield[8],"<pz>/D");
	tree->Branch("<xx>",&qfield[9],"<xx>/D");
	tree->Branch("<x-px>",&qfield[10],"<x-px>/D");
	tree->Branch("<px-px>",&qfield[11],"<px-px>/D");
	tree->Branch("<yy>",&qfield[12],"<yy>/D");
	tree->Branch("<y-py>",&qfield[13],"<y-py>/D");
	tree->Branch("<py-py>",&qfield[14],"<py-py>/D");
	tree->Branch("<zz>",&qfield[15],"<zz>/D");
	tree->Branch("<z-pz>",&qfield[16],"<z-pz>/D");
	tree->Branch("<pz-pz>",&qfield[17],"<pz-pz>/D");
	tree->Branch("<xxx>",&qfield[18],"<xxx>/D");


	if ( !ifstream(inTextFileName).good() ) {
		cout << "Input text file does not exit -- exiting" << endl;
		return 1;
	}
	std::ifstream inFile(inTextFileName);
	std::string line;

	while (std::getline(inFile, line))
	{
		string testFile = line + "/Time_Dep_Moments_at_END.dat";

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
