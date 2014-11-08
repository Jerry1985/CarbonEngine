#ifndef CARBON_CARRAY
#define CARBON_CARRAY

#include "Platform\Platform.h"
#include "Misc\Assertion.h"

#define	ARRAY_BASECHUNK_SIZE	256

template< class T >
class CArray;

template< class T >
class CArrayIterator
{
public:
	CArrayIterator(const CArray<T>& array)
	{
		CASSERT(array.m_data);

		m_data = array.m_data;
		m_elementCount = array.m_currentCount;
	}
	CArrayIterator(const CArray<T>* array)
	{
		CASSERT(array);

		m_data = array->m_data;
		m_elementCount = array->m_currentCount;
	}
	CArrayIterator(const CArrayIterator<T>& iterator)
	{
		m_data = iterator.m_data;
		m_elementCount = iterator.m_elementCount;
		m_currentId = iterator.m_currentId;
	}
	~CArrayIterator()
	{
	}

	const T& operator*()
	{
		CASSERT(m_currentId < m_elementCount);
		return m_data[m_currentId];
	}

	const CArrayIterator& operator++()
	{
		++m_currentId;

		if (m_currentId >= m_elementCount)
			m_currentId = m_elementCount;

		return (*this);
	}

	CArrayIterator operator++(int)
	{
		CArrayIterator it(*this);

		++m_currentId;
		if (m_currentId >= m_elementCount)
			m_currentId = m_elementCount;

		return it;
	}

	const CArrayIterator& operator--()
	{
		--m_currentId;

		if (m_currentId < 0)
			m_currentId = 0;

		return (*this);
	}

	CArrayIterator operator--(int)
	{
		CIterator it(*this);

		--m_currentId;
		if (m_currentId < 0)
			m_currentId = 0;

		return it;
	}

	bool IsEnd()
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
	CArray(const CArray<T>& array)
	{
		Clone(array);
	}
	virtual ~CArray()
	{
		Release();
	}

	// Allocate data
	void	Allocate(int count)
	{
		CASSERT(count > 0);

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
			m_data[m_currentCount++] = elements[i];
	}

	// Add elements from array
	void	Add(const CArray<T>& elements)
	{
		if (elements.m_currentCount + m_currentCount >= m_totalCount)
			_reAllocateMemory(elements.m_currentCount + m_currentCount);

		for (int i = 0; i < elements.m_currentCount; ++i)
			m_data[m_currentCount++] = element[i];
	}

	// Remove at specific index
	void	Remove(int index)
	{
		if (index >= m_currentCount || index < 0 )
			return;

		--m_currentCount;
		for (int i = index; i < m_currentCount; ++i)
			m_data[i] = m_data[i + 1];
	}

	// Remove at specific index with a count number
	void	Remove(int index, int count)
	{
		if (index >= m_currentCount || index < 0 )
			return;

		m_currentCount = (m_currentCount - count < index) ? index : m_currentcount - count;
		for (int i = index; i < m_currentCount; ++i)
			m_data[i] = m_data[i + count];
	}

	// Replace elements at specific position
	void	Replace(int index, int count, const T* elements)
	{
		CASSERT((count&&elements) || (!count&&!elements));
		CASSERT(index >= 0 && index < m_currentCount);

		int target_count = index + count;
		target_count = (target_count<m_currentCount) ? m_currentCount : target_count;
		if (target_count > m_totalCount)
			_reAllocateMemory(target_count);

		for (int id = index; id < target_count; ++id)
			m_data[id] = elements[id - index];

		m_currentCount = target_count;
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
		CASSERT(index < m_currentCount);

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
			m_data = 0;
			m_totalCount = 0;
			m_currentCount = 0;
		}
	}

	// clone array
	const CArray<T>&	Clone(const CArray<T>& array)
	{
		Release();

		m_currentCount = array.m_currentCount;
		m_totalCount = array.m_totalCount;
		m_data = new T[m_totalCount];

		CASSERT((!m_totalCount&&!array.m_data) || (m_totalCount&&array.m_data));

		if ( m_totalCount )
			memcpy_s(m_data, m_totalCount * m_elementSize, array.m_data, m_totalCount);

		return *this;
	}

	// = operator
	const CArray<T>&	operator = (const CArray<T>& array)
	{
		return Clone(array);
	}

	// append array
	void	Append(const CArray<T>& array)
	{
		CArrayIterator<T> iterator(array);
		while (!iterator.IsEnd())
		{
			Add(*iterator);
			++iterator;
		}
	}

	// Get Data pointer
	const T* const	GetData() const { return m_data; }

	// check if the two arrays are equal
	bool operator == (const CArray<T>& array) const
	{
		if (array.m_currentCount != m_currentCount)
			return false;
		if (array.m_elementSize != m_elementSize)
			return false;

		for (int i = 0; i < m_currentCount; ++i)
		{
			if (m_data[i] != array.m_data[i])
				return false;
		}
		return true;
	}

private:
	// base data
	T*		m_data = 0;

	// element size
	const static int	m_elementSize = sizeof(T);

	// element count
	int		m_totalCount = 0;

	// current element size
	int		m_currentCount = 0;

	// recaculate size
	void	_reAllocateMemory(int count)
	{
		int target_count = (int)m_totalCount;
		if (target_count < count)
		{
			do
			{
				if (target_count == 0)
					target_count = ARRAY_BASECHUNK_SIZE;
				else
					target_count <<= 1;

			} while (target_count < count);
		}

		SafeAllocate(target_count);
	}

	template<class T>
	friend class CArrayIterator;
};

#endif