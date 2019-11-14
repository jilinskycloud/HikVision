#include<fstream.h>
#include<iostream.h>
	int main(int argc, char *argv[])
	{
		if(argc!=2)
		{
			cout<<"Syntext error.....!";
			cout<<"Typing should be: create filename"<<endl;
			return(0);
		}
		ofstream outf(argv[1]);
		char line[80];
            cout<<"Enter a string:(Programing should be tarminate by press !')\n";
	do
		{
			cin.getline(line,80);
			outf<<line<<endl;
		}while(*line != '!');
      cout<<"Create the file "<<argv[1]<<" and saved in disk.";
		outf.close();
      return(0);
	}
