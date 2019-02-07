
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
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

	using namespace std::placeholders;
	using restype=measure<std::chrono::microseconds>::type;

	// otusalg::print_gen_test(std::cout, 30);

	std::vector<int> v;
	std::vector<int> sizes {10000, 20000, 32768, 65536, 131072, 262144, 524288, 1048576};
	// std::vector<otusalg::gen_func> func_vec;
	std::vector<otusalg::gen_func> func_vec
		{
			std::bind(&otusalg::gen_type1<int>, _1, _2), 
			std::bind(&otusalg::gen_type2<int>, _1, _2),
			std::bind(&otusalg::gen_type3<int>, _1, _2), 
			std::bind(&otusalg::gen_type4<int>, _1, _2), 
			std::bind(&otusalg::gen_type5<int>, _1, _2), 
			std::bind(&otusalg::gen_type6<int>, _1, _2), 
			std::bind(&otusalg::gen_type7<int>, _1, _2), 
			std::bind(&otusalg::gen_type8<int>, _1, _2), 
			std::bind(&otusalg::gen_type9<int>, _1, _2) 
		};

	int alg_cnt = 1;   // Количество тестируемых алгоритмов
	int sample_cnt = sizes.size() * func_vec.size() * alg_cnt;

	std::vector<std::vector<std::vector<restype>>> vres(sizes.size(), std::vector<std::vector<restype>>(func_vec.size(), std::vector<restype>(alg_cnt, 0)));

	std::cout << "Sample: " << std::setw(5) << sample_cnt << "\r" << std::flush;

	for(int i=0; i<sizes.size(); i++)
	{

		for(int j=0; j<func_vec.size(); j++)
		{
			func_vec[j](sizes[i], v);
			vres[i][j][0] = measure<std::chrono::microseconds>::execution([&]()
			{
				std::sort(v.begin(), v.end(), std::less<int>());
			});
			
			std::cout << "Sample: " << std::setw(5) << --sample_cnt << "\r" << std::flush;
		}
	}

	std::cout << std::endl;


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

