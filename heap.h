
#pragma once

#include <vector>
#include <cstddef>
#include <cmath>
#include <iostream>

namespace otusalg
{


template<typename T>
class heap
{
private:
	std::vector<T> v;

public:
	heap()
	{
		// v = std::make_unique(new std::vector<T>);
	}

	heap(heap &h) = delete;
	heap(heap &&h) = delete;

	~heap(){}

	std::size_t parent(std::size_t idx)
	{
		// return std::floor((idx - 1) / 2);
		return ((idx - 1) / 2);
	}

	std::size_t leftChild(std::size_t idx)
	{
		return idx * 2 + 1;
	}

	std::size_t rightChild(std::size_t idx)
	{
		return idx * 2 + 2;
	}

	void drown(std::size_t  idx)
	{
		std::size_t  x = idx;
		std::size_t  largest = idx;
		std::size_t  l = leftChild(x);
		std::size_t  r = rightChild(x);
		T tmp;

		while((l <= v.size()) && (r <= v.size()))
		{
			if(v[l] > v[r])
				largest = l;
			else
				largest = r;

			if(v[x] >= v[largest])
				break;

			tmp = v[x];
			v[x] = v[largest];
			v[largest] = tmp;

			x = largest;
			l = leftChild(x);
			r = rightChild(x);
		}
	}


	template<typename Iter>
	void buildHeap(Iter first, Iter last)
	{
		static_assert(std::is_same<typename std::iterator_traits<Iter>::value_type, T>::value, "Wrong iterator value type");

		v.clear();
		std::copy(first, last, std::back_inserter(v));

		for(int i=((v.size() -1) / 2); i>=0; i--)
		{
			drown(i);
		}
	}


	void remove(std::size_t  idx)
	{
		if(v.size() == 0) 
		{
			return;
		}
		else if(idx < v.size()-1)
		{
			v[idx] = v[v.size()-1];
			v.pop_back();
			drown(idx);
			while((idx > 0) && (v[idx] > v[parent(idx)]))
			{
				idx = parent(idx);
				drown(idx);
			}
		}
		else if(v.size() == 1)
			v.pop_back();
	}


	std::vector<T> getSorted()
	{
		std::vector<T> cpy(v.begin(), v.end());
		std::vector<T> res(v.size());
		int idx = 0;

		while(v.size() > 0)
		{
			res[idx++] = v[0];
			remove(0);
		}

		v = std::move(cpy);
		return res;
	}



	void printHeap_dot(std::ostream &out)
	{
		int l;
		int r;

		out << "digraph g {\n";
		for(int i=0; i<v.size(); i++)
		{
			out << "\"" << v[i] << "\";\n";
			l = leftChild(i);
			r = rightChild(i);
			if(l < v.size())
				out << "\"" << v[i] << "\" -> \"" << v[l] << "\";\n";
			if(r < v.size())
				out << "\"" << v[i] << "\" -> \"" << v[r] << "\";\n";
		}
		out << "}\n";
	}

};



} // namespace otusalg

