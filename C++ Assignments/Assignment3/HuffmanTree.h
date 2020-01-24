#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_
#include "HuffmanNode.h"
#include <memory>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <string>

namespace RHLDEE001
{
	//compare class for priority queue
	class Compare
	{
		public:
			//returns true if A has a greater frequency than B
			bool operator()(HuffmanNode a,HuffmanNode b)
				{
						if(a.getFrequency() >= b.getFrequency())
						{
							return true;
						}
						else
						{
							return false;
						}

				}
	};

	class HuffmanTree
	{
		private:
			std::shared_ptr<HuffmanNode> root;
			std::priority_queue<HuffmanNode,std::vector<HuffmanNode>,Compare> priorityQ;
			std::unordered_map<char,std::string> codeTable; //map characters and frequencies

		public:
			HuffmanTree();
			~HuffmanTree();
			void BuildTree(std::unordered_map<char,int> & map); //create huffman tree
			void traverse(HuffmanNode * current, std::string bitString);
			void compression(std::string inputFile, std::string outputFile);





	};

}



#endif
