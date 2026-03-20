/*
[12] 
Define a File_handle class with a constructor that takes a string argument (the file name),
opens the file in the constructor and closes it in the destructor.
*/

import PPP;
using namespace std;
#include <cstdio>

class File_handle {
	FILE* file;
public:
	explicit File_handle(const string name)
		:file{  } {
		if(fopen_s(&file, name.c_str(), "w")!=0)
			throw exception{ "fopen_s(): Can't open file" };
		if (file == nullptr)
			throw exception{ "Can't open file" };
	}
	~File_handle()
	{
		if (file) {
			fclose(file);
		}
	}
	FILE* get()  { return file; }
};
int main()
try {
	File_handle fle{ "file.txt" };
	fprintf(fle.get(), "Hello, old world!\n");
	fle.~File_handle();
	system("pause");
	return 0;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 2;
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 3;
}