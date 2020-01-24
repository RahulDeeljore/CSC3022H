#ifndef VOLIMAGE_H
#define VOLIMAGE_H

#include <string>
#include <vector>



class VolImage {
	
	private: 
		
		int width, height; 
		std::vector<unsigned char**> slices; 
		
	public: 
		
		VolImage(); //constructor
		~VolImage(); //destructor
		
	
		bool readImages(std::string baseName);
		
		// calcculate difference map 
		void diffmap(int sliceI, int sliceJ, std::string prefix);
		
		// extract slice  
		void extract(int sliceId, std::string prefix);
		
		// number of bytes to store
		int volImageSize(void);
         
      
                // method for extra credit
                void extraCredit(int slice);
};



#endif
