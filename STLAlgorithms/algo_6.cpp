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
#include<numeric> // std::minus
#include <functional> //placeholders
#include<iterator>
#include<array>

using std::cin;
using std::cout;
using std::vector;
using std::array;




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

int main_numeric_algorithms(){
	vector<int> numbers = {10,20,30,30,20,10,10,20};
	cout<<std::count(begin(numbers),end(numbers),10)<<"\n"; //3
	int init = 1000;
	std::cout << '\n';
	cout<< std::accumulate(begin(numbers),end(numbers),init); //1150
	std::cout << '\n';
	cout << std::accumulate (begin(numbers), end(numbers), init, std::minus<int>()); //850
	

 	std::vector<int> v2 = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // or std::vector<int>v(10, 2);
 
    std::cout << "The first 10 even numbers are: ";
    std::partial_sum(v2.begin(), v2.end(), 
                     std::ostream_iterator<int>(std::cout, " "));
					//  2 4 6 8 10 12 14 16 18 20
    std::cout << '\n';
 
    std::partial_sum(v2.begin(), v2.end(), v2.begin(), std::multiplies<int>());
	//  2 4 8 16 32 64 128 256 512 1024
    std::cout << "The first 10 powers of 2 are: ";
    for (auto n : v2) {
        std::cout << n << " ";
    }
    std::cout << '\n';


	std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};
 
    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "Inner product of a and b: " << r1 << '\n'; //21
 
    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<>(), std::equal_to<>()); //2
    std::cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';



	std::vector<int> v {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    std::adjacent_difference(v.begin(), v.end(), v.begin()); //2 2 2 2 2 2 2 2 2 2
 
    for (auto n : v)
        std::cout << n << ' ';
 
    std::cout << '\n';
 
    // Fibonacci 
 
    std::array<int, 10> a2 {1};
 
    adjacent_difference(begin(a2), std::prev(end(a2)), std::next(begin(a2)), std::plus<> {});//1 1 2 3 5 8 13 21 34 55
    copy(begin(a2), end(a2), std::ostream_iterator<int> {std::cout, " "});


	// std::string in = "abcdefgh", out;
    // std::sample(in.begin(), in.end(), std::back_inserter(out),
    //             5, std::mt19937{std::random_device{}()});
    // std::cout << "five random letters out of " << in << " : " << out << '\n';


	return 0;
}

int main_querying_property()
{
	std::vector<int> v(10, 2); 
    std::partial_sum(v.cbegin(), v.cend(), v.begin()); //2 4 6 8 10 12 14 16 18 20
    std::cout << "Among the numbers: ";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
    }
    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                     std::placeholders::_1, 2))) {
        std::cout << "None of them are odd\n";
    }
    struct DivisibleBy
    {
        const int d;
        DivisibleBy(int n) : d(n) {}
        bool operator()(int n) const { return n % d == 0; }
    };
 
    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
        std::cout << "At least one number is divisible by 7\n";
    }
	
	
	return 0;
}

int main()
{
	// main_heaps();
	// main_sortings();
	// main_permutations();
	// main_numeric_algorithms(); 
	main_querying_property();
	
	return 0;
}