#pragma once

template<typename T, typename Q>
struct myPair
{
	T first;
	Q second;
	myPair(){}
	myPair(const T& x,const Q& y);
};


template<typename T, typename Q>
myPair<T,Q>::myPair(const T& x, const Q& y)
{
	first = x;
	second = y;
}

template<typename T, typename Q>
myPair<T,Q> makePair(const T& x,const Q& y)
{
	myPair<T,Q> pair;
	pair.first = x;
	pair.second = y;
	return pair;
}
