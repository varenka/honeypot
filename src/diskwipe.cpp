#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

/*

Inputs: ./diskwipe <disk size> <unit of bytes>

EX: ./diskwipe 2 TB

Purpose: Wipe all deleted files from the disk by overwriting every free byte on the drive, thus deleting
anything that has been deleted from the partition table but is still present on the disk

*/

unsigned long long diskSize = 0;
unsigned long long calcBytes(int b, string unit);

string e = "e";

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout << "Inputs: ./diskwipe <disk size> <unit of bytes>" << endl;
		return 0;
	}

	cout << "Secure disk wipe utility copyright(c) 2016 Leo Stone" << endl;

	cout << "Size of disk is " << argv[1] << argv[2] << ", is this correct(y/n)?";
	string in;
	cin >> in;

	if(in == "n" || in == "N")
	{
		cout << "Exiting." << endl;
		return 0;
	}

	diskSize = calcBytes(argv[1], argv[2]);
	unsigned long long fsize = calcBytes(2, "MB");
	cout << "Disk size: " << diskSize << " bytes" << endl;

	cout << "Size of files: " << fsize << endl;

	cout << "Number of files: " << diskSize / calcBytes(2, "MB") << endl;
	cout << "Remainder: " << (diskSize % calcBytes) << endl;

	return 0;
}

//get total number of bytes given unit and number of that unit of bytes
//		(Assume that the input is in bytes, even if 'b' is lowercase since drive capacities are measured in bytes)
unsigned long long calcBytes(int b, string unit)
{
	//TODO: tolower() unit before checking
	if(unit.length() == 0 || unit.length() > 2)
	{
		return -1;
	}

	char u = unit[0];

	if(u == 'b')
	{
		return b;
	}
	else if(u == 'k')
	{
		return b * 1024;
	}
	else if(u == 'm')
	{
		return b * 1024 * 1024;
	}
	else if(u == 'g')
	{
		return b * 1024 * 1024 * 1024;
	}
	else if(u == 't')
	{
		return b * 1024 * 1024 * 1024 * 1024;
	}
	else if(u == 'p')
	{
		return b * 1024 * 1024 * 1024 * 1024 * 1024;
	}
	else
	{
		return -1;
	}
}
