#pragma once
#include <iostream>

template<typename T>
class Pointer
{
	template<typename U>
	friend class Pointer;

	int* m_ref_count;
	T*	 m_object;

public:
	Pointer() :
		m_ref_count(NULL),
		m_object(NULL)
	{
	}

	Pointer(T* obj) :
		m_ref_count(new int(1)),
		m_object(obj)
	{
	}

private:
	Pointer(int* ref_count, T* obj):
		m_ref_count(ref_count),
		m_object(obj)
	{
		increaseRefCount();
	}

public:
	Pointer(const Pointer<T>& other) :
		m_ref_count(other.m_ref_count),
		m_object(other.m_object)
	{
		increaseRefCount();
	}
		
	Pointer(Pointer<T>&& other) noexcept:
		m_ref_count(other.m_ref_count),
		m_object(other.m_object)
	{
		other.m_ref_count = NULL;
		other.m_object = NULL;
	}

	~Pointer()
	{
		if (decreaseRefCount())
		{
			delete m_ref_count;
			delete m_object;
		}
	}
	
	Pointer<T>& operator=(const Pointer<T>& other)
	{
		if (this != &other)
		{
			if (decreaseRefCount())
			{
				delete m_ref_count;
				delete m_object;
			}

			m_ref_count = other.m_ref_count;
			m_object = other.m_object;

			increaseRefCount();
		}

		return *this;
	}

	operator bool()
	{
		return *this != NULL;
	}

	template<typename U>
	operator Pointer<U>()
	{
		static_assert(std::is_convertible<T*, U*>::value,
			"Upcast is only allowed implicitly");

		return Pointer<U>(m_ref_count, static_cast<U*>(m_object));
	}

	template<typename U>
	Pointer<U> downCast()
	{
		static_assert(std::is_convertible<U*, T*>::value,
			"Downcast is only allowed for thios function");

		U* casted = dynamic_cast<U*>(m_object);

		if (casted != NULL)
		{
			return Pointer<U>(m_ref_count, casted);
		}
		else
		{
			return Pointer<U>();
		}
	}

	template<typename U>
	bool operator==(const Pointer<U>& other)
	{
		return m_object == other.m_object;
	}

	template<typename U>
	bool operator!=(const Pointer<U>& other)
	{
		return m_object != other.m_object;
	}

	template<typename U>
	bool operator==(U* object)
	{
		return m_object == object;
	}

	template<typename U>
	bool operator!=(U* object)
	{
		return m_object != object;
	}

	T* operator->()
	{
		return m_object;
	}

	T& operator*()
	{
		return *m_object;
	}

	T* get() const
	{
		return m_object;
	}

private:
	void increaseRefCount()
	{
		if (m_ref_count != NULL)
		{
			*m_ref_count += 1;
		}
	}

	// Return true if ref count = 0
	bool decreaseRefCount()
	{
		if (m_ref_count != NULL)
		{
			*m_ref_count -= 1;

			return (*m_ref_count == 0);
		}

		return false;
	}
};
