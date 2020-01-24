/**
Consolidation Session: Operator Overloading
We've given you a partial implementation of an n-dimensional vector (of doubles) and
have implemented the six special member functions. Below the nd_vector class definition
is a number of unit tests that have been commented out. These should be re-enabled, compiled and
passed for each operator you overload.

TASKS:
You have to overload the following operators (preferably in order). Remember to specify whether the arguments are
constant references and if the operator is a constant member function (ie. whether it modifies the contents of the nd_vector or not):
 1. postfix ++ operator
 2. prefix ++ operator
 3. += operator with a single double precision value as argument (ie. scalar addition)
 4. += operator with a nd_vector as argument (you may assume the vectors have equal length)
 5. *= operator taking in a single double precision value as argument (ie. scalar multiplication)
 6. - operator (this should negate all the values of a vector "a" if used as follows "nd_vector c = -a"

 The following 3 operators may be defined using previous definitions:
 7. + operator taking in a scalar double value as argument (example usage: "nd_vector c = a + 5.4")
 8. + operator taking in an nd_vector as argument (example usage "nd_vector c = a + b")
 9. * operator taking in a scalar double value as argument (example usage: "nd_vector b = a * 3.4")
 10. [] operator (to be used as an indexing operator, e.g "double b = a[5]"
 11. Overload the "not" operator ("!a") to return the magnitude (of type double) of the vector "a" (where magnitude = sqrt(x^2 + y^2 +...))
 
 The next 3 functions require you to befriend each of the operators and have to be implemented outside the class body
 12. A scalar multiplication operator that will make the following expression compile: "nd_vector a = 3 * b;" where b is a nd_vector
 13. The "<<" stream operator that will serialize the class... ie. that will enable you to write "std::cout << a << std::endl;"
 14. The ">>" stream operator that will read values from a stream into a nd_vector object (e.g my_filestream >> a;)

 If you're unsure of the exact requirements look at the relevant test
*/

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

class nd_vector {
private:
	vector<double> data;
public:
	//Define the big six:
	nd_vector(initializer_list<double> lst):data(lst.size()) {
		copy(lst.begin(),lst.end(),data.begin());
	}
	nd_vector(size_t dim = 0):data(dim){};
	virtual ~nd_vector() = default;
	nd_vector(const nd_vector & rhs) = default;
	nd_vector & operator=(const nd_vector & rhs) = default;
	nd_vector(nd_vector && rhs):data(move(rhs.data)){};
	nd_vector & operator=(nd_vector && rhs){
		if (this != &rhs){
			this->data = move(rhs.data);
			return *this;
		}
	}
	vector<double> get_buffer() const{
		return data;
	}
nd_vector operator++( int ) {
      
         nd_vector T;
         T.data = this->get_buffer();
         
         std::transform(std::begin(data),std::end(data),std::begin(data),[](int x){return x+1;});
         
         return T; 
      }

    nd_vector operator++ () {
		std::transform(std::begin(data),std::end(data),std::begin(data),[](int x){return x+1;});

		nd_vector T;
		T.data = this->get_buffer();
		return T; 
      }

	nd_vector& operator+=(const double& rhs)
	{                          
		for(std::vector<double>::size_type i = 0; i != this->get_buffer().size(); i++) {
    		this->get_buffer()[i] += rhs;
		}

		return *this;
	}

	nd_vector& operator+=(const nd_vector& v){
		if(this->get_buffer().size() != v.get_buffer().size()){
			cerr << "FATAL vector::operator+=(const vector &) size mismatch: " <<
			this->get_buffer().size() << " " << " != " << v.get_buffer().size() << "\n";
			exit(1);
		}
		for(int i = 0; i < this->get_buffer().size(); i++) this->get_buffer()[i] += v.get_buffer()[i];
		return *this;
	}

	nd_vector& operator*=(const double& rhs) 
	{                           
		for(std::vector<double>::size_type i = 0; i != this->get_buffer().size(); i++) {
    		this->get_buffer()[i] *= rhs;
		}

		return *this;
	}

	nd_vector operator- () {
		nd_vector T;
		T.data = this->get_buffer();

		for(int i = 0; i < T.data.size(); i++) T.data[i] = -T.data[i];

		return T; 
	  }

	nd_vector operator+(const double d) {
		nd_vector T;
		T.data = this->get_buffer();

		for(int i = 0; i < T.data.size(); i++) T.data[i] = T.data[i] + d;

		return T; 
	}

		nd_vector operator+(const nd_vector& d) {
		nd_vector T;
		T.data = this->get_buffer();

		for(int i = 0; i < T.data.size(); i++) T.data[i] = T.data[i] + d.get_buffer()[i];
			
		return T; 
	}

		nd_vector operator*(const double d) {
		nd_vector T;
		T.data = this->get_buffer();

		for(int i = 0; i < T.data.size(); i++) T.data[i] = T.data[i] * d;

		return T; 
	}

};

	//TODO: implement each of the operators (except for the last 3) here
//TODO:implement scalar * nd_vector, << and >> here

/************************************************************************************************
	TODO:UNCOMMENT THE FOLLOWING UNIT TESTS BIT BY BIT AS YOU IMPLEMENT THE OPERATORS
*************************************************************************************************/

//tests whether two doubles are close to equal
bool is_close(double a, double b, double epsilon=0.0000000000001){
	return abs(a - b) < epsilon;
}

TEST_CASE("Postfix Increment","[PostfixIncrement]"){
	nd_vector a = {1.0, 2.0, 3.0};	
	nd_vector b = a++;
	SECTION("RETURN VALUE"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],1.0));
		REQUIRE(is_close(buf[1],2.0));
		REQUIRE(is_close(buf[2],3.0));
	}
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],2.0));
		REQUIRE(is_close(buf[1],3.0));
		REQUIRE(is_close(buf[2],4.0));
	}
}
TEST_CASE("Prefix Increment","[PrefixIncrement]"){
	nd_vector a = {1.0, 2.0, 3.0};	
	++a;
	auto buf = a.get_buffer();
	REQUIRE(is_close(buf[0],2.0));
	REQUIRE(is_close(buf[1],3.0));
	REQUIRE(is_close(buf[2],4.0));
}

/*TEST_CASE("SCALAR ADDITION ASSIGNMENT","[ScalarAdditionAssignment]"){
	nd_vector a = {1.0, 2.0, 3.0};	
	nd_vector b = a += 5.5;
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],6.5));
		REQUIRE(is_close(buf[1],7.5));
		REQUIRE(is_close(buf[2],8.5));
	}
	SECTION("POST CONDITION VEC b"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],6.5));
		REQUIRE(is_close(buf[1],7.5));
		REQUIRE(is_close(buf[2],8.5));
	}

}

TEST_CASE("VECTOR ADDITION ASSIGNMENT","[VectorAdditionAssignment]"){
	nd_vector a = {1.0, 2.0, 3.0};
	nd_vector b = {2.0, 3.5, 4.0};	
	nd_vector c = a += b;
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],3.0));
		REQUIRE(is_close(buf[1],5.5));
		REQUIRE(is_close(buf[2],7.0));
	}
	SECTION("POST CONDITION VEC b"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],2.0));
		REQUIRE(is_close(buf[1],3.5));
		REQUIRE(is_close(buf[2],4.0));

	}
	SECTION("POST CONDITION VEC c"){
		auto buf = c.get_buffer();
		REQUIRE(is_close(buf[0],3.0));
		REQUIRE(is_close(buf[1],5.5));
		REQUIRE(is_close(buf[2],7.0));
	
	}
}

TEST_CASE("SCALAR MULTIPLY ASSIGNMENT","[ScalarMultiplyAssign]"){
	nd_vector a = {1.0, 2.0, 3.0};	
	nd_vector b = a *= 3.25;
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],1.0*3.25));
		REQUIRE(is_close(buf[1],2.0*3.25));
		REQUIRE(is_close(buf[2],3.0*3.25));
	}
	SECTION("POST CONDITION VEC b"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],1.0*3.25));
		REQUIRE(is_close(buf[1],2.0*3.25));
		REQUIRE(is_close(buf[2],3.0*3.25));
	}

}*/

TEST_CASE("VECTOR NEGATE","[VectorNegate]"){
	nd_vector a = {1.0, 2.0, 3.0};
	nd_vector b = -a;
	SECTION("RETURN VALUE"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],1.0));
		REQUIRE(is_close(buf[1],2.0));
		REQUIRE(is_close(buf[2],3.0));
	}
	SECTION("POST CONDITION VEC a"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],-1.0));
		REQUIRE(is_close(buf[1],-2.0));
		REQUIRE(is_close(buf[2],-3.0));

	}
}

TEST_CASE("SCALAR ADDITION","[ScalarAddition]"){
	nd_vector a = {1.0, 2.0, 3.0};	
	nd_vector b = a + 5.5;
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],1.0));
		REQUIRE(is_close(buf[1],2.0));
		REQUIRE(is_close(buf[2],3.0));
	}
	SECTION("POST CONDITION VEC b"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],6.5));
		REQUIRE(is_close(buf[1],7.5));
		REQUIRE(is_close(buf[2],8.5));
	}

}

TEST_CASE("VECTOR ADDITION","[VectorAddition]"){
	nd_vector a = {1.0, 2.0, 3.0};
	nd_vector b = {2.0, 3.5, 4.0};	
	nd_vector c = a + b;
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],1.0));
		REQUIRE(is_close(buf[1],2.0));
		REQUIRE(is_close(buf[2],3.0));
	}
	SECTION("POST CONDITION VEC b"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],2.0));
		REQUIRE(is_close(buf[1],3.5));
		REQUIRE(is_close(buf[2],4.0));

	}
	SECTION("POST CONDITION VEC c"){
		auto buf = c.get_buffer();
		REQUIRE(is_close(buf[0],3.0));
		REQUIRE(is_close(buf[1],5.5));
		REQUIRE(is_close(buf[2],7.0));

	}

}

TEST_CASE("SCALAR MULTIPLY","[ScalarMultiply]"){
	nd_vector a = {1.0, 2.0, 3.0};	
	nd_vector b = a * 3.25;
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],1.0));
		REQUIRE(is_close(buf[1],2.0));
		REQUIRE(is_close(buf[2],3.0));
	
	}
	SECTION("RETURN VAL"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],1.0*3.25));
		REQUIRE(is_close(buf[1],2.0*3.25));
		REQUIRE(is_close(buf[2],3.0*3.25));
	}
}

/*TEST_CASE("INDEXING OPERATOR","[IndexingOperator]"){
	nd_vector a = {1.0, 2.0, 3.0};
	REQUIRE(is_close(a[0],1.0));
	REQUIRE(is_close(a[1],2.0));
	REQUIRE(is_close(a[2],3.0));
}

TEST_CASE("MAGNITUDE OPERATOR","[MagnitudeOperator]"){
	nd_vector a = {1.6,0.4,2.7,4.8,3.4};
	double mag = !a;
	SECTION("POST CONDITION VEC a"){
		REQUIRE(is_close(a[0],1.6));
		REQUIRE(is_close(a[1],0.4));
		REQUIRE(is_close(a[2],2.7));
		REQUIRE(is_close(a[3],4.8));
		REQUIRE(is_close(a[4],3.4));
	}
	SECTION("RETURN VALUE"){
		REQUIRE(is_close(mag,6.67907179,0.00001)); //test accurate up to p=5
	}
}
TEST_CASE("SCALAR MULTIPLICATION WITH SCALAR FIRST","[ScalarMultVecOperator]"){
	nd_vector a = {1.0, 2.0, 3.0};	
	nd_vector b = 3.25 * a;
	SECTION("POST CONDITION VEC a"){
		auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0],1.0));
		REQUIRE(is_close(buf[1],2.0));
		REQUIRE(is_close(buf[2],3.0));
	
	}
	SECTION("RETURN VAL"){
		auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0],1.0*3.25));
		REQUIRE(is_close(buf[1],2.0*3.25));
		REQUIRE(is_close(buf[2],3.0*3.25));
	}

}
TEST_CASE("STREAM OPERATOR <<","[StreamOp<<]"){
	nd_vector a = {1.4, 5.2, 4.8, 2.95};
	nd_vector b = {6.23,4.12};
	ostringstream serialized;
	serialized << a << " " << b;
	REQUIRE(serialized.str() == "1.4 5.2 4.8 2.95 6.23 4.12");
}
TEST_CASE("STREAM OPERATOR >>","[StreamOp>>]"){
	nd_vector a;
	istringstream data("1.4 5.2 4.8 2.95");
	data >> a;
	REQUIRE(is_close(a[0],1.4));
	REQUIRE(is_close(a[1],5.2));
	REQUIRE(is_close(a[2],4.8));
	REQUIRE(is_close(a[3],2.95));
}*/
