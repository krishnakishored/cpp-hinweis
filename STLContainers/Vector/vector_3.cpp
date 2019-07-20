#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#include<array>

//Recipe 7-2. Storing a Growing Number of Objects
//Listing 7-9.  Reducing the capacity of a vector

int main_vector_shrink_to_fit() {
	std::vector<int32_t> stlVector{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	while (stlVector.size() > 0)
	{
		auto iterator = stlVector.end() - 1;
		stlVector.erase(iterator);

		if ((stlVector.size() * 2) == stlVector.capacity())
		{
			std::cout << "\nShrink to fit" << std::endl;
			stlVector.shrink_to_fit();
		}

		std::cout << "The size is: " << stlVector.size() << std::endl;
		std::cout << "The capacity is: " << stlVector.capacity() << std::endl << std::endl;
	}
	return 0;
}

//Listing 7-6.  A resizing vector - size Vs capacity

int main_Vector_resize() {
	std::vector<int32_t> stlVector{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	std::cout << "The size is: " << stlVector.size() << " ";
	std::cout << "The capacity is: " << stlVector.capacity() << " ";

	stlVector.emplace_back(17);

	std::cout << std::endl<< "After emplace_back() one element" << std::endl;
	std::cout << "The size is: " << stlVector.size() << " ";
	std::cout << "The capacity is: " << stlVector.capacity() << " ";

	//Listing 7 - 7.  Adding elements to arbitrary points in a vector
	std::cout << std::endl << "emplace 100 at position 12: "<<std::endl;
	auto iter = stlVector.begin() + 12;
	stlVector.emplace(iter, 1000);
	for (auto&& elem : stlVector) {
		std::cout << elem << " ";
	}
	//Listing 7-8.  Removing elements from a vector
	std::cout << std::endl << "removing element (erase) at position 15: " << std::endl;
	iter = stlVector.begin() + 15;
	stlVector.erase(iter);
	for (auto&& elem : stlVector) {
		std::cout << elem << " ";
	}
	std::cout << "\n removing all elements of vector: " << std::endl;
	//This will change the size of the vector but not the capacity.
	while (stlVector.size() > 0)
	{
		auto iterator = stlVector.end() - 1;
		stlVector.erase(iterator);
	}
	std::cout << "The size is: " << stlVector.size() << " ";
	std::cout << "The capacity is: " << stlVector.capacity() << " ";

	//Using clear - capactiy remains same
	std::vector<int32_t> stlVector2{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	stlVector2.clear();
	std::cout << "\nThe size is: " << stlVector.size() << " ";
	std::cout << "The capacity is: " << stlVector.capacity() << " ";


	return 0;
}


int main_STLVector()
{
	std::vector<int32_t> stlVector{ 10, 65, 3000, 2, 49 };

	for (uint32_t i = 0; i < stlVector.size(); ++i)
	{
		std::cout << stlVector[i] << " ";
	}
	std::cout <<std::endl<< "size of vector: " << stlVector.size()<<std::endl;
	stlVector.emplace_back(50);
	
	for (auto&& number : stlVector)
	{
		std::cout << number << " ";
	}
	std::cout<<std::endl << "size of vector after emplace_back: " << stlVector.size() << std::endl;
	return 0;
}

//Recipe 7-1. Storing a Fixed Number of Objects
int mainSTLArray() 
{
	const uint32_t numberOfElements{ 5 };
	int32_t normalArray[numberOfElements]{ 10, 65, 3000, 2, 49 };//C-style array
	std::cout<<std::endl << "using for loop: ";
	for (uint32_t i{ 0 }; i < numberOfElements; ++i)
	{
		std::cout<<normalArray[i] << " ";
	}
	std::cout << std::endl<<"using auto & range based loop: ";
	for (auto elem : normalArray) {
		std::cout<< elem << " " ;
	}

	/*
	The major advantage to using the STL array container over C-style arrays is that it allows access to STL iterators and algorithms
	*/
	
	std::array<int32_t, numberOfElements>stlArray{{10, 65, 3000, 2, 49}};
	std::cout << std::endl << "using for loop - STL-Array: ";
	for (uint32_t i{ 0 }; i < numberOfElements; ++i)
	{
		std::cout << stlArray[i] << " ";
	}
	std::cout << std::endl << "using auto & range based loop - STL-Array: ";
	for (auto elem : stlArray) {
		std::cout << elem << " ";
	}


	return 0;
}

int main()
{
	main_vector_shrink_to_fit();
	main_Vector_resize();
	main_STLVector();
	mainSTLArray();
	return 0;
}