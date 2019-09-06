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
#include <vector>
#endif

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
#endif

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using std::cin;
using std::cout;
using std::vector;



int main_heaps()
{
	vector<int> numbers = {0,1,2,3,4,5,6,7,8,9};

	std::random_shuffle (begin(numbers), end(numbers));
	//{9,8,6,7,4,5,2,0,3,1};
	std::make_heap(begin(numbers),end(numbers));
	
	//print the elements
	numbers.push_back(100);
	std::push_heap(begin(numbers),end(numbers)); //100 9 8 6 7 5 2 0 3 1 4
	for(auto it = begin(numbers);it != end(numbers);it++){
		cout<<*it<<" ";
	}
	std::pop_heap(begin(numbers),end(numbers)); //max elem is swapped with the last - 9 7 8 6 4 5 2 0 3 1 100
	numbers.pop_back();
	std::pop_heap(begin(numbers),end(numbers));
	numbers.pop_back();
	std::pop_heap(begin(numbers),end(numbers));
	numbers.pop_back();
	std::pop_heap(begin(numbers),end(numbers));
	numbers.pop_back();
	std::pop_heap(begin(numbers),end(numbers));
	numbers.pop_back(); //5 4 2 3 0 1
	cout<<"\n";
	for(auto it = begin(numbers);it != end(numbers);it++){
		cout<<*it<<" ";
	}

	return 0;
}


int main_sortings()/* sorting & partitioning */
{
	vector<int> numbers = {0,1,2,3,4,5,6,7,8,9};
	std::random_shuffle (begin(numbers), end(numbers));
	// std::sort(begin(numbers),end(numbers)); // 0 1 2 3 4 5 6 7 8 9
	// std::partial_sort(begin(numbers),begin(numbers)+4,end(numbers)/*,comp*/); //0 1 2 3 9 8 6 5 7 4


	// using default comparison (operator <):
  	// std::nth_element(begin(numbers), begin(numbers)+9, end(numbers));
	// 5 1 4 2 0 3 8 7 6 9

	// std::make_heap(begin(numbers), end(numbers)); //9 6 8 4 1 5 7 3 2 0
	// std::sort_heap(begin(numbers), end(numbers));
	cout<<"\n";
	
	std::partition (begin(numbers),end(numbers),[](int i){return i%2==0;});
	// 8 6 4 2 0 5 7 3 9 1
	
	auto it = std::partition_point(begin(numbers),end(numbers),[](int i){return i%2==0;});
	std::vector<int> odd;
  	odd.assign (begin(numbers),it); //8 6 4 2 0
	// cout<<*it; //5  

	for(auto it = begin(numbers);it != end(numbers);it++){
		cout<<*it<<" ";
	}

	return 0;
}
  

int main_permutations()
{

	vector<int> numbers = {0,1,2,3,4,5,6,7,8,9};
	
	// std::rotate(begin(numbers), begin(numbers)+3, end(numbers)); //3 4 5 6 7 8 9 0 1 2
	
	// obtain a time-based seed:
  	// unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	// std::shuffle (begin(numbers), end(numbers) , std::default_random_engine(seed));
	std::next_permutation(begin(numbers), end(numbers));
	std::next_permutation(begin(numbers), end(numbers)); //0 1 2 3 4 5 6 8 7 9
	std::prev_permutation(begin(numbers), end(numbers)); // 0 1 2 3 4 5 6 7 9 8
	std::reverse(begin(numbers), end(numbers)); //8 9 7 6 5 4 3 2 1 0

	cout<<"\n";
	for(auto it = begin(numbers);it != end(numbers);it++){
		cout<<*it<<" ";
	}


	return 0;
}

int main()
{
	// main_heaps();
	// main_sortings();
	main_permutations();

	return 0;
}