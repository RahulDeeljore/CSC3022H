
#ifndef IMAGE_H_
#define IMAGE_H_

#include <memory>
namespace RHLDEE001	
{
    class Image
    {
         private:
         int width, height;
         std::unique_ptr<unsigned char[]> data;

         public:

         class iterator
         {
             private:
             unsigned char *ptr;
             // grant private access to Image class functions
             friend class Image;
             // construct only via Image class (begin/end)

             iterator(unsigned char *p) : ptr(p){}

             public:


             //copy construct is public
             iterator(const iterator & rhs) : ptr(rhs.ptr) {}
             // define overloaded ops: *, ++, --, =


             // other methods for iterator
             iterator & operator++()
             {
                 //this->ptr+= 1;
            	 ptr++;
                 return *this;
             }

             iterator operator++(int)
			  {
				 iterator temp = *this;
            	 ptr++;
				  return temp;
			  }
             iterator & operator--()
             {
                this->ptr -= 1;
                return *this;
             }

             unsigned char & operator* ()
             {
                return *ptr;
             }



             iterator & operator=(const iterator & rhs)
             {
                 if(this != &rhs)
                 {
                     this->ptr = rhs.ptr;
                 }

                 return *this;
             }

             bool operator!=(const iterator & rhs)
             {
                 if(this->ptr != rhs.ptr)
                 {
                     return true;
                 }

                 else
                 {
                     return false;
                 }

             }

         };


         Image(); //constructor
         ~Image(); //destructor
         Image (Image & rhs); //copy constructor
         Image (Image && rhs); //move constructer
         Image & operator=(Image & rhs); //Copy Assignment Operators
         Image & operator=(Image && rhs); //Move Assignment Operators
         // define begin()/end() to get iterator to start and
         // "one-past" end.
         Image::iterator begin(void)
         {
             return iterator(data.get());
         }



         Image::iterator end (void)
         {
             return iterator(data.get() + (width * height));
         }

         //overloaded operators
         Image operator+ (Image & rhs);
         Image operator- (Image & rhs);
         Image operator! ();
         Image operator/ (Image & rhs);
         Image operator* (int f);


         //load and save images
         void load(std::string fileName);
         void save(std::string fileName);
    };

}


#endif // IMAGE

