
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>

#include "mergesort.h"
#include "quicksort.h"
#include "generators.h"

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	// typedef typename TimeT::rep type;
	using type = typename TimeT::rep;

	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
							(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};



int main(int argc, char const *argv[])
{

	// otusalg::print_gen_test(std::cout, 30);

	std::vector<int> v;
	std::vector<int> sizes {10000, 20000, 32768, 65536, 131072, 262144, 524288, 1048576};
	std::vector<otusalg::gen_func> func_vec 
		{
			otusalg::gen_type1, 
			otusalg::gen_type2, 
			otusalg::gen_type3, 
			otusalg::gen_type4, 
			otusalg::gen_type5, 
			otusalg::gen_type6, 
			otusalg::gen_type7, 
			otusalg::gen_type8, 
			otusalg::gen_type9 
		};

	std::vector<measure<std::chrono::microseconds>::type> vres(sizes.size());

	for(auto sz : sizes)
	{
		for(auto func : func_vec)
		{
			func(sz, v);
			vres[sz.cnt] = measure<std::chrono::microseconds>::execution([&]()
			{
				std::sort(v.begin(), v.end());
			});
		}
	}

	// if(argc > 1)
	// {
	// 	std::cout << "'" << argv[1] << "'\n";

	// 	std::vector<int> v;
	// 	std::ifstream fs;
	// 	fs.open(argv[1], std::ios::in);
 
	// 	if(fs.is_open())
	// 	{
	// 		read_data(fs, v);
	// 		fs.close();

	// 		std::cout << "merge_sort: " << measure<std::chrono::microseconds>::execution([&]()
	// 			{
	// 				otusalg::merge_sort(v, std::less<int>());
	// 			}) << " us\n";

	// 		if(std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector sorted\n";
	// 		else std::cout << "vector NOT sorted\n";
	// 		std::cout << std::endl;

	// 		// std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	// 		fs.open(argv[1]);
	// 		read_data(fs, v);
	// 		fs.close();

	// 		std::cout << "merge_sort_mt: " << measure<std::chrono::microseconds>::execution([&]()
	// 			{
	// 				otusalg::merge_sort_mt(v, std::less<int>());
	// 			}) << " us\n";

	// 		if(std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector sorted\n";
	// 		else std::cout << "vector NOT sorted\n";
	// 		std::cout << std::endl;

	// 	}
	// 	else
	// 	{
	// 		std::cout << "File '" << argv[1] << "' does not exist" << std::endl;
	// 	}
	// }

	return 0;
}

