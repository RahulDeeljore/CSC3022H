#include "HuffmanNode.h"
#include <memory>

namespace RHLDEE001
{
	//Node constructer
	HuffmanNode::HuffmanNode()
	{
		character = 0;
		freq = 0;
		std::shared_ptr<HuffmanNode> left = nullptr;
		std::shared_ptr<HuffmanNode> right = nullptr;
	}

	//destructer
	HuffmanNode::~HuffmanNode()
	{
		left = nullptr;
		right = nullptr;
		freq = -1;
	}

	void HuffmanNode::setCharacter(char c)
	{
		character = c;
	}

	void HuffmanNode::setFrequency(int f)
	{
		freq = f;
	}



	void HuffmanNode::setLeftChild(HuffmanNode leftChild)
	{

		left =  std::make_shared<HuffmanNode>(leftChild);
	}
	void HuffmanNode::setRightChild(HuffmanNode rightChild)
	{
		right = std::make_shared<HuffmanNode>(rightChild);
	}

	char HuffmanNode::getCharacter()
	{
		return character;
	}

	int HuffmanNode::getFrequency()
	{
		return freq;
	}

	HuffmanNode * HuffmanNode::getLeftChild()
	{
		return left.get();
	}

	HuffmanNode * HuffmanNode::getRightChild()
	{
		return right.get();
	}

	HuffmanNode::HuffmanNode (const HuffmanNode & rhs) //copy constructer
	{
		character = rhs.character;
		freq = rhs.freq;
		left = rhs.left;
		right = rhs.right;
	}

	HuffmanNode::HuffmanNode (HuffmanNode && rhs) //move constructer
	{
		character = rhs.character;
		this->freq = rhs.freq;
		left = rhs.left;
		right = rhs.right;

		rhs.left = nullptr;
		rhs.right = nullptr;
		rhs.freq = -1;

	}
	HuffmanNode& HuffmanNode::operator=(const HuffmanNode & rhs) //Copy Assignment Operators
	{
		if(this != &rhs)
		{
			character = rhs.character;
			freq = rhs.freq;
			left = rhs.left;
			right = rhs.right;
		}
		return *this; // Return a reference to the current object.

	}

	HuffmanNode & HuffmanNode::operator=(HuffmanNode && rhs) //Move Assignment Operators
	{
		if(this != &rhs)
		{
			character = std::move(rhs.character);
			freq = rhs.freq;
			left = rhs.left;
			right = rhs.right;

			rhs.left = nullptr;
			rhs.right = nullptr;
			rhs.freq = -1;
		}

		return *this; // Return a reference to the current object.

	}
}





