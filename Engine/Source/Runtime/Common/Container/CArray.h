#ifndef CARBON_CARRAY
#define CARBON_CARRAY

#include "CIterator.h"
#include <string>

#define	ARRAY_BASECHUNK_SIZE	256

template< class T >
class CArray;

template< class T >
class CArrayIterator : public CIterator<T>
{
public:
	CArrayIterator(const CArray<T>& array)
	{
		m_data = array.m_data;
		m_elementCount = array.m_currentCount;
	}
	CArrayIterator(const CArray<T>* array)
	{
		if (array == 0)
			return;

		m_data = array->m_data;
		m_elementCount = array->m_currentCount;
	}
	~CArrayIterator()
	{
	}

	virtual const T& operator*()
	{
		if (m_currentId < m_elementCount)
		{
			return m_data[m_currentId];
		}

		return T();
	}

	virtual const T& operator++()
	{
		++m_currentId;

		if (m_currentId >= m_elementCount)
			m_currentId = m_elementCount;

		return *this;
	}

	virtual const T& operator--()
	{
		--m_currentId;

		if (m_currentId < 0)
			m_currentId = 0;

		return *this;
	}

	virtual bool IsEnd()
	{
		return m_currentId == m_elementCount;
	}

private:
	int	m_currentId = 0;

	const T* m_data = 0;

	int m_elementCount = 0;
};

template< class T >
class CArray
{
public:
	// constructor & destructor
	CArray()
	{
		Allocate(ARRAY_BASECHUNK_SIZE);
	}
	virtual ~CArray()
	{
		Release();
	}

	// Allocate data
	void	Allocate(int count)
	{
		// release data first
		Release();

		// allocate new data
		m_data = new T[count];

		// update information
		m_totalCount = count;
		m_currentCount = 0;
	}

	// Safe Allocate, the original data won't be lost
	void	SafeAllocate(int count)
	{
		// allocate new data
		T* new_data = new T[count];

		unsigned copy_element = 0;
		if (m_data)
		{
			copy_element = (count < m_currentCount) ? count : m_currentCount;
			unsigned copy_size = copy_element * m_elementSize;
			memcpy_s(new_data, copy_size, m_data, copy_size);
		}

		// release data
		Release();

		// switch data
		m_data = new_data;

		// update information
		m_totalCount = count;
		m_currentCount = copy_element;
	}
	// Allocate new zero data
	void	ZeroAllocate(int count)
	{
		// release data
		Release();

		// allocate new data
		m_data = new T[count];

		// update information
		m_totalCount = count;
		m_currentCount = 0;

		// zero the memory
		memset(m_pData, 0, m_totalCount * m_elementSize);
	}

	// Add one element
	void	Add(const T& element)
	{
		// total count
		if (m_currentCount >= m_totalCount)
			SafeAllocate(m_totalCount << 1);

		m_data[m_currentCount++] = element;
	}
	// Add elements
	void	Add(const T elements[], int count)
	{
		if (count + m_currentCount >= m_totalCount)
			_reAllocateMemory(count + m_currentCount);

		for (int i = 0; i < count; ++i)
			m_data[m_currentCount++] = element[i];
	}

	// Add elements from array
	void	Add(const CArray<T>& elements)
	{
		if (elements.m_currentCount + m_currentCount >= m_totalCount)
			_reAllocateMemory(elements.m_currentCount + m_currentCount);

		for (int i = 0; i < elements.m_currentCount; ++i)
			m_data[m_currentCount++] = element[i];
	}

	// Find a specific element
	int		Find(const T& element) const
	{
		CArrayIterator<T> iterator(*this);
		int index = 0;
		while (iterator.IsEnd() == false)
		{
			if (*iterator == element)
				return index;

			++index;
			iterator++;
		}

		return -1;
	}

	// Whether the array is empty
	bool	IsEmpty() const
	{
		return m_currentCount == 0;
	}

	// [] operator
	T const & __cdecl operator[](int index) const
	{
		return m_data[index];
	}

	// Get Current count
	int		GetCount() const { return m_currentCount; }
	// Get Maximum size
	int		GetSize() const { return m_currentCount * m_elementSize; }
	// Get Maximum count
	int		GetMaxCount() const { return m_totalCount; }
	// Get Maximum size
	int		GetMaxSize() const { return m_totalCount * m_elementSize; }

	// Release Data
	void	Release()
	{
		if (m_data)
		{
			delete[] m_data;
			m_totalCount = 0;
			m_currentCount = 0;
		}
	}

private:
	// base data
	T*		m_data = 0;

	// element size
	int		m_elementSize = sizeof(T);

	// element count
	int		m_totalCount = 0;

	// current element size
	int		m_currentCount = 0;

	// recaculate size
	void	_reAllocateMemory(int count)
	{
		int target_count = (int)m_currentCount;
		if (count + target_count >= m_totalCount)
		{
			do
			{
				if (target_count == 0)
					target_count = ARRAY_BASECHUNK_SIZE;
				else
					target_count <<= 1;

			} while (target_count>count);
		}

		SafeAllocate(target_count);
	}

	template<class T>
	friend class CArrayIterator;
};

#endif