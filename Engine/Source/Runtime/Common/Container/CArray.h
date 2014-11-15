#pragma once

#include "Platform\Platform.h"
#include "Misc\Assertion.h"
#include "Math\Math.h"

#define	ARRAY_BASECHUNK_SIZE		256

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

	const T& operator*() const
	{
		CASSERT(m_currentId < m_elementCount);
		return m_data[m_currentId];
	}

	T& operator*()
	{
		CASSERT(m_currentId < m_elementCount);
		return m_data[m_currentId];
	}

	FORCE_INLINE const CArrayIterator& operator++()
	{
		++m_currentId;

		if (m_currentId >= m_elementCount)
			m_currentId = m_elementCount;

		return (*this);
	}

	FORCE_INLINE CArrayIterator operator++(int)
	{
		CArrayIterator it(*this);

		++m_currentId;
		if (m_currentId >= m_elementCount)
			m_currentId = m_elementCount;

		return it;
	}

	FORCE_INLINE const CArrayIterator& operator--()
	{
		--m_currentId;

		if (m_currentId < 0)
			m_currentId = 0;

		return (*this);
	}

	FORCE_INLINE CArrayIterator operator--(int)
	{
		CIterator it(*this);

		--m_currentId;
		if (m_currentId < 0)
			m_currentId = 0;

		return it;
	}

	FORCE_INLINE bool IsEnd() const
	{
		return m_currentId == m_elementCount;
	}

	FORCE_INLINE int Index() const
	{
		return m_currentId;
	}

private:
	int	m_currentId = 0;

	T* m_data = 0;

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
	FORCE_INLINE void	Allocate(int count)
	{
		CASSERT(count > 0);

		// release data first
		Release();

		// allocate new data
		m_data = (T*)::operator new(m_elementSize*count);
		memset(m_data, 0, m_elementSize*count);

		// update information
		m_totalCount = count;
		m_currentCount = 0;
	}

	// Safe Allocate, the original data won't be lost
	FORCE_INLINE void	SafeAllocate(int count)
	{
		CASSERT(count > 0);

		// allocate new data
		T* new_data = (T*)::operator new(m_elementSize*count);
		
		unsigned copy_element = 0;
		if (m_data)
		{
			copy_element = (count < m_currentCount) ? count : m_currentCount;
			unsigned copy_size = copy_element * m_elementSize;
			memcpy_s(new_data, copy_size, m_data, copy_size);
			memset(new_data + copy_element, 0, m_elementSize* Math::Max(0, m_totalCount - (int)copy_element));
		}else
			memset(new_data, 0, m_elementSize*count);

		// release data
		Release();

		// switch data
		m_data = new_data;

		// update information
		m_totalCount = count;
		m_currentCount = copy_element;
	}
	// Allocate new zero data
	FORCE_INLINE void	ZeroAllocate(int count)
	{
		CASSERT(count > 0);

		// release data
		Release();

		// allocate new data
		m_data = (T*)::operator new(m_elementSize*count);
		memset(m_pData, 0, m_totalCount * m_elementSize);

		// update information
		m_totalCount = count;
		m_currentCount = 0;
	}

	// Add one element
	FORCE_INLINE void	Add(const T& element)
	{
		_reAllocateMemory(1 + m_currentCount);

		new (&m_data[m_currentCount++]) T(element);
	}
	FORCE_INLINE void	Add(T&& element)
	{
		// total count
		_reAllocateMemory(1 + m_currentCount);

		new (&m_data[m_currentCount++]) T(element);
	}
	// Add elements
	FORCE_INLINE void	Add(const T elements[], int count)
	{
		CASSERT(count > 0);

		_reAllocateMemory(count + m_currentCount);

		for (int i = 0; i < count; ++i)
			m_data[m_currentCount++] = elements[i];
	}

	// Add elements from array
	FORCE_INLINE void	Add(const CArray<T>& elements)
	{
		_reAllocateMemory(elements.m_currentCount + m_currentCount);

		int to_copy = elements.m_currentCount;
		for (int i = 0; i < to_copy; ++i)
			m_data[m_currentCount++] = elements[i];
	}

	// Add one element
	FORCE_INLINE void	Add(int index, const T& element)
	{
		_reAllocateMemory(1 + m_currentCount);

		_moveMem(index + 1, index);
		new (&m_data[index]) T(element);
		++m_currentCount;
	}
	FORCE_INLINE void	Add(int index, T&& element)
	{
		// total count
		_reAllocateMemory(1 + m_currentCount);

		_moveMem(index + 1, index);
		new (&m_data[index]) T(element);
		++m_currentCount;
	}
	// Add elements
	FORCE_INLINE void	Add(int index, const T elements[], int count)
	{
		CASSERT(count > 0);
		_reAllocateMemory(count + m_currentCount);

		_moveMem(index + count, index);
		for (int i = 0; i < count; ++i)
			m_data[i + index] = elements[i];
		m_currentCount += count;
	}

	// Add elements from array
	FORCE_INLINE void	Add(int index, const CArray<T>& elements)
	{
		// special handling for self-add
		if (&elements == this)
		{
			CArray<T> arr(elements);
			Add(index, arr);
		}
		else
		{
			_reAllocateMemory(elements.m_currentCount + m_currentCount);

			int count = elements.m_currentCount;

			_moveMem(index + count, index);
			for (int i = 0; i < count; ++i)
				m_data[i + index] = elements[i];
			m_currentCount += count;
		}
	}

	// Remove at specific index
	FORCE_INLINE void	Remove(int index)
	{
		CASSERT(index >= m_currentCount || index < 0);

		--m_currentCount;
		_moveMem(index, index + 1);
	}

	// Remove at specific index with a count number
	FORCE_INLINE void	Remove(int index, int count)
	{
		CASSERT(index >= m_currentCount || index < 0);
		
		m_currentCount = Math::Max( 0 , m_currentCount - count );
		_moveMem(index, index + count );
	}

	// Replace elements at specific position
	FORCE_INLINE void	Replace(int index, int count, const T* elements)
	{
		CASSERT((count&&elements) || (!count&&!elements));
		CASSERT(index >= 0 && index < m_currentCount);

		int target_count = index + count;
		target_count = Math::Max(target_count, m_currentCount);
		_reAllocateMemory(target_count);

		for (int id = index; id < target_count; ++id)
			m_data[id] = elements[id - index];

		m_currentCount = target_count;
	}

	// Find a specific element
	FORCE_INLINE int		Find(const T& element) const
	{
		CArrayIterator<T> iterator(*this);
		int index = 0;
		while (iterator.IsEnd() == false)
		{
			if (*iterator == element)
				return iterator->Index();
			iterator++;
		}

		return -1;
	}

	// Reset array
	FORCE_INLINE void	Reset()
	{
		m_currentCount = 0;
	}

	// Whether the array is empty
	FORCE_INLINE bool	IsEmpty() const
	{
		return m_currentCount == 0;
	}

	// [] operator
	FORCE_INLINE T const & __cdecl operator[](int index) const
	{
		CASSERT(index < m_currentCount);

		return m_data[index];
	}

	// Get Current count
	FORCE_INLINE int		GetCount() const { return m_currentCount; }
	// Get Maximum size
	FORCE_INLINE int		GetSize() const { return m_currentCount * m_elementSize; }
	// Get Maximum count
	FORCE_INLINE int		GetMaxCount() const { return m_totalCount; }
	// Get Maximum size
	FORCE_INLINE int		GetMaxSize() const { return m_totalCount * m_elementSize; }

	// Release Data
	FORCE_INLINE void	Release()
	{
		if (m_data)
		{
			::operator delete(m_data);
			m_data = 0;
			m_data = 0;
			m_totalCount = 0;
			m_currentCount = 0;
		}
	}

	// clone array
	FORCE_INLINE const CArray<T>&	Clone(const CArray<T>& array)
	{
		Release();

		m_currentCount = array.m_currentCount;
		m_totalCount = array.m_totalCount;
		m_data = (T*)::operator new (m_totalCount*m_elementSize);

		CASSERT((!m_totalCount&&!array.m_data) || (m_totalCount&&array.m_data));

		for (int i = 0; i < m_currentCount; ++i)
			m_data[i] = array.m_data[i];
		memset(m_data + m_currentCount, 0, Math::Max(m_totalCount - m_currentCount, 0) * m_elementSize);

		return *this;
	}

	// = operator
	FORCE_INLINE const CArray<T>&	operator = (const CArray<T>& array)
	{
		return Clone(array);
	}

	// append array
	FORCE_INLINE void	Append(const CArray<T>& array)
	{
		CArrayIterator<T> iterator(array);
		while (!iterator.IsEnd())
		{
			Add(*iterator);
			++iterator;
		}
	}

	// Get Data pointer
	FORCE_INLINE const T* const	GetData() const { return m_data; }

	// check if the two arrays are equal
	FORCE_INLINE bool operator == (const CArray<T>& array) const
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
	FORCE_INLINE void	_reAllocateMemory(int count)
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

			SafeAllocate(target_count);
		}
	}

	// there is no boundary check in this function, it is the caller's responsibility to make sure of it
	FORCE_INLINE void	_moveMem(int dest_index, int src_index)
	{
		int min_index = Math::Min(dest_index, src_index);
		int total_rest_size = Math::Max(m_currentCount - min_index, 0) * m_elementSize;
		if (total_rest_size)
			memmove_s(m_data + dest_index, total_rest_size, m_data + src_index, total_rest_size);
	}

	template<class T>
	friend class CArrayIterator;
};