//
// A simple tool to update the user bash profile 
// It's compiled to retrieve safely the current location
//

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "exepath.hh"

using namespace std;


static bool save()
{
	const char* cmd = "cp $HOME/.bash_profile $HOME/.bash_profile.faustsave";
	int ret = system (cmd);
	return ret == 0;
}

static bool bash_update(const char* location)
{
	stringstream update;
	update << "cat <<! >> $HOME/.bash_profile" << endl;
	update << "\n# Setting PATH for Faust" << endl;
	update << "# The original version is saved in .bash_profile.faustsave" << endl;
	update << "PATH=" << location << ":\\$PATH" << endl;
	update << "export PATH" << endl;
	update << "!" << endl;
	int ret = system (update.str().c_str());
	return ret == 0;
}

int main(int argc, char *argv[])
{
	string location = exepath::get (argv[0]);
	string path = location + "bin";

	save();
	if (bash_update (path.c_str()))
		cout << "User path updated with " << path << endl;
	else 
		cerr << "system cmd failed" << endl;
	return 0;
}
