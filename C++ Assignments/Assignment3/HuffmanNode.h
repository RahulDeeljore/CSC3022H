#ifndef HUFFMANNODE_H_
#define HUFFMANNODE_H_
#include <memory>

namespace RHLDEE001
{
	class HuffmanNode
	{

	private:
		char character; //character stored in node
		int freq; //Frequency of occurrence
		std::shared_ptr<HuffmanNode> left; //left node
		std::shared_ptr<HuffmanNode> right; //right node

	public:
		HuffmanNode();
		~HuffmanNode();
		void setCharacter(char c);
		void setFrequency(int f);
		void setLeftChild(HuffmanNode leftChild);
		void setRightChild(HuffmanNode rightChild);
		char getCharacter();
		int getFrequency();
		HuffmanNode * getLeftChild();
		HuffmanNode * getRightChild();
		HuffmanNode (const HuffmanNode & rhs); //copy constructer
		HuffmanNode (HuffmanNode && rhs); //move constructer
		HuffmanNode & operator=(const HuffmanNode & rhs); //Copy Assignment Operators
		HuffmanNode & operator=(HuffmanNode && rhs); //Move Assignment Operators






	};
}




#endif
