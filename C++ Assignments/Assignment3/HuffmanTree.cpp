
#include "HuffmanTree.h"
#include "HuffmanNode.h"
#include <queue>
#include <iomanip>
#include <fstream>

namespace RHLDEE001
{
	HuffmanTree::HuffmanTree()
	{
		std::shared_ptr<HuffmanNode> root = nullptr;

	}

	HuffmanTree::~HuffmanTree()
	{
		root = nullptr;
	}


	//creates Huffman tree
	void HuffmanTree::BuildTree(std::unordered_map<char,int> & map)
	{
		using namespace std;

		//loops through map
		for(auto iterator : map)
		{
				//creates a node from info obtained from map and a shared pointer to it
				HuffmanNode node;
				shared_ptr<HuffmanNode> nodePtr = make_shared<HuffmanNode>(node);
				node.setCharacter(iterator.first);
				node.setFrequency(iterator.second);
				priorityQ.push(node); //adds node to priority queue

		}



		while(priorityQ.size() >1)
		{
			HuffmanNode tempA = priorityQ.top();
			priorityQ.pop();
			HuffmanNode tempB = priorityQ.top();
			priorityQ.pop();

			HuffmanNode tempTotal; //parent node
			tempTotal.setCharacter(0);
			tempTotal.setFrequency(tempA.getFrequency() + tempB.getFrequency());
			tempTotal.setLeftChild(tempA); //set left child node
			tempTotal.setRightChild(tempB); //set right child node
			priorityQ.push(tempTotal);




		}

		root = make_shared<HuffmanNode>(priorityQ.top());
		traverse(root.get(),"");
	
	}

	//recursive method to obtain bit strings of each character
	void HuffmanTree::traverse(HuffmanNode * current, std::string bitString)
	{
		using namespace std;
		if(current)
		{
			traverse(current->getLeftChild(), bitString + "0");
			//checks if current is not a parent node
			if(current->getCharacter() != 0)
			{

				cout << current->getCharacter() << " character bitstream is " << bitString << endl;
				codeTable[current->getCharacter()] = bitString; //add to bit string table
			}
			traverse(current->getRightChild(), bitString + "1");
		}
	}

	void HuffmanTree::compression(std::string inputFile, std::string outputFile)
	{
		using namespace std;

		int numChars;
		int numOneZero;
		ofstream output; //file writer
		output.open (outputFile + ".hdr"); //open/create new file

		ifstream input (inputFile); //read input file
		char c;

		while(input.get(c))
		{
			numChars ++;
			string bit = codeTable[c].c_str();
			output << bit;
			numOneZero += bit.length();
			cout << bit << ": " << bit.length() <<endl;
		}

		input.close();


		output.open (outputFile + ".hdr"); //open/create new file
		output<< "Size: " << codeTable.size() << endl; //print number of hash codes
		//iterate through map and print character followed by corresponding code
		for(auto iterator : codeTable)
		{
			output << iterator.first << ": " << iterator.second << endl;

		}
		output.close(); //close file

		//print out compression ratio
		double compression = numOneZero/(numChars*8);
		cout << "Compression ratio: " << compression << endl;


	}

	
}


