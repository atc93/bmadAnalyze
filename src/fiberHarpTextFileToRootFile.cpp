#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;


int main (int argc, char* argv[]) {


	string st_firstDir = argv[1];
  string st_lastDir  = argv[2];
  string filesDir		 = argv[3];

	string rootFileName = filesDir +"/fiber.root";
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
	int firstDir = stoi(st_firstDir);
	int lastDir = stoi(st_lastDir);

	ifstream myfile;

	Double_t qfield[11];
	Int_t ient =0;

	tree->Branch("harp",&qfield[0],"harp/D");
	tree->Branch("fiber",&qfield[1],"fiber/D");
	tree->Branch("time",&qfield[2],"time/D");
	tree->Branch("s",&qfield[3],"s/D");
	tree->Branch("x",&qfield[4],"x/D");
	tree->Branch("px",&qfield[5],"px/D");
	tree->Branch("y",&qfield[6],"y/D");
	tree->Branch("py",&qfield[7],"py/D");
	tree->Branch("z",&qfield[8],"z/D");
	tree->Branch("pz",&qfield[9],"pz/D");
	tree->Branch("thickness",&qfield[10],"thickness/D");

	for(int idirect =firstDir; idirect<=lastDir; idirect++)
	{
		string testFile = filesDir + "/" + to_string(idirect) + "/fiber_hits.dat";

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
