#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "HuffmanTree.h"



int main(int argc, char* argv[])
{
	using namespace std;
	RHLDEE001::HuffmanTree huffmantree = RHLDEE001::HuffmanTree();	//Huffman Tree
	std::unordered_map<char,int> map; //map characters and frequencies

	string inputFilePath = string(argv[1]); //input file. Type cast char to string


	string outputFilePath = string(argv[2]); //output file. Type cast char to string

	ifstream input (inputFilePath); //read input file
	char c;

	if(input.is_open())
	{
		while(input.get(c))
		{

			map[c] += 1; //insert character into map

		}

		huffmantree.BuildTree(map);
		cout << inputFilePath << " " << string(argv[2]) << endl;
		huffmantree.compression(inputFilePath, outputFilePath);



	}
	input.close(); //close input


}

