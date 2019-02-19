#include "../inc/header.hh"

#define Debug 0
const double TWOPI = 2.0 * 3.1415926535897932384626433832795 ;
const double PI    = 3.1415926535897932384626433832795 ;


int main (int argc, char* argv[]) {


	string st_firstDir = argv[1];
  string st_lastDir  = argv[2];
  string filesDir		 = argv[3];

	string rootFileName = "./singleParticleByElement.root";
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

	Double_t qfield[15];
	Int_t ient =0;

	tree->Branch("turn",&qfield[0],"turn/D");
	tree->Branch("element",&qfield[1],"element/D");
	tree->Branch("x",&qfield[2],"x/D");
	tree->Branch("xp",&qfield[3],"xp/D");
	tree->Branch("y",&qfield[4],"y/D");
	tree->Branch("yp",&qfield[5],"yp/D");
	tree->Branch("z",&qfield[6],"z/D");
	tree->Branch("zp",&qfield[7],"zp/D");
	tree->Branch("t",&qfield[8],"t/D");
	tree->Branch("s",&qfield[9],"s/D");
	tree->Branch("stotal",&qfield[10],"stotal/D");
	tree->Branch("state",&qfield[11],"state/D");
	tree->Branch("polx",&qfield[12],"polx/D");
	tree->Branch("poly",&qfield[13],"poly/D");
	tree->Branch("polz",&qfield[14],"polz/D");

	for(int idirect =firstDir; idirect<=lastDir; idirect++)
	{
		string testFile = filesDir + "/" + to_string(idirect) + "/single_particle_by_element.dat";

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
