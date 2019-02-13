
#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <type_traits>
#include <functional>


namespace otusalg
{

using gen_func=std::function<void (std::size_t, std::vector<int>&)>;

/*
	  *sort: random data
	  \sort: descending data
	  /sort: ascending data
	  3sort: ascending, then 3 random exchanges
	  +sort: ascending, then 10 random at the end
	  %sort: ascending, then randomly replace 1% of elements w/ random values
	  ~sort: many duplicates
	  =sort: all equal
	  !sort: worst case scenario
*/

void print_gen_test(std::ostream &os, std::size_t sz=20);

/**
 * Данные от 0 до l перемешаны в случайном порядке
 */
template<typename T>
void gen_type1(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");

	v.clear();
	v.reserve(l);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());
 
	std::shuffle(v.begin(), v.end(), g);
}


/**
 * Случайные данные от 0 до RAND_MAX
 */
template<typename T>
void gen_type2(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	std::srand(std::time(nullptr));
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(std::rand());
	}
}



/**
 * Данные по возрастанию от 0 до l
 */
template<typename T>
void gen_type3(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(i);
	}
}


/**
 * Данные по убыванию от l до 0
 */
template<typename T>
void gen_type4(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	for(std::size_t i=l; i>0; --i)
	{
		v.emplace_back(i-1);
	}
}


/**
 * По возрастанию, затем 3 случайных замены
 */
template<typename T>
void gen_type5(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(i);
	}

	std::vector<T> vv(v.begin(), v.end());
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(vv.begin(), vv.end(), g);

	T tmp;
	for(int i=0; i<3; i++)
	{
		tmp = v[vv[i*2]];
		v[vv[i*2]] = v[vv[i*2+1]];
		v[vv[i*2+1]] = tmp;
	}
}


/**
 * По возрастанию, затем 10 случайных в конце
 */
template<typename T>
void gen_type6(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	for(std::size_t i=0; i<(l - 10); i++)
	{
		v.emplace_back(i);
	}

	std::srand(std::time(nullptr));
	for(int i=0; i<10; i++)
	{
		v.emplace_back(std::rand());
	}
}


/**
 * По возрастанию, затем 1% заменен на случайные числа
 */
template<typename T>
void gen_type7(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(i);
	}

	std::vector<T> vv(v.begin(), v.end());
	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<T> dist(1);
	std::shuffle(vv.begin(), vv.end(), g);

	if(l < 100)
		v[vv[0]] = dist(rd);
	else
	{
		for(std::size_t i=0; i<(l / 100); i++)
		{
			v[vv[i]] = dist(rd);
		}
	}
}


/**
 * Много повторов
 */
template<typename T>
void gen_type8(std::size_t l, std::vector<T> &v, T vmin, T vmax)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	std::random_device rd;
	std::mt19937 g(rd());

	if(vmin >= vmax)
	{
		vmin = 0;
		if(l > 1000) vmax = l / 1000;
	}
	
	std::uniform_int_distribution<T> dist(vmin, vmax);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(dist(rd));
	}
}


/**
 * Все одинаковые
 */
template<typename T>
void gen_type9(std::size_t l, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	
	v.clear();
	v.reserve(l);
	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<T> dist(0);
	auto tmp = dist(rd);
	for(std::size_t i=0; i<l; i++)
	{
		v.emplace_back(tmp);
	}
}



} // namespace otusalg

