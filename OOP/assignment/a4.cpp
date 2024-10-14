#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 5;
int array1[MAX] = {10,20,30,40,50};
int array2[MAX];

const string filename = "output.dat";

int main(){
	ofstream ofile;
	ofile.open(filename,ios::trunc | ios::binary);
	
	try {
		ofile.write((char*)&array1, sizeof(array1));
	}catch (exception& e){
		cerr << "error writing to file";
	}
	ofile.close();
	
	ifstream ifile;
	ifile.open(filename ,ios::binary);
	
	try{
		ifile.read((char*)&array2, sizeof(array2));
	}catch (exception& e){
		cerr << "error reading from file";
	}
	ifile.close();
	
	for (int i = 0 ; i < MAX; i++){
		cout << array2[i] << endl;
	}
	
	return 0;	
}