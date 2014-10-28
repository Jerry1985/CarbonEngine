#ifndef CARBON_CITERATOR
#define	CARBON_CITERATOR

template< class T >
class CIterator
{
public:
	CIterator(){}
	virtual ~CIterator(){}

	virtual const T& operator*() = 0;

	virtual const T& operator++() = 0;

	virtual const T& operator--() = 0;

	virtual bool IsEnd() = 0;
};

#endif