#pragma once

template<typename T>
class jiterator
{
public:

	using value_type = T;
	using pointer = T*;
	using reference = T&;

public:

	jiterator(T* ptr = nullptr)
	{
		m_ptr = ptr;
	}
	jiterator(const jiterator<T>& iterator) = default;
	~jiterator() {}

	jiterator<T>& operator=(const jiterator<T>& iterator) = default;
	jiterator<T>& operator=(T* ptr)
	{
		m_ptr = ptr;
		return (*this);
	}

	bool operator==(const jiterator<T>& iterator) const
	{
		return (m_ptr == iterator.m_ptr);
	}
	bool operator!=(const jiterator<T>& iterator) const
	{
		return (m_ptr != iterator.m_ptr);
	}

	jiterator<T>& operator++()
	{
		++m_ptr; return (*this);
	}
	jiterator<T>& operator--()
	{
		--m_ptr; return (*this);
	}
	jiterator<T> operator++(int)
	{
		auto temp(*this); ++m_ptr; return temp;
	}
	jiterator<T> operator--(int)
	{
		auto temp(*this); --m_ptr; return temp;
	}

	T& operator*()
	{
		return *m_ptr;
	}
	const T& operator*() const
	{
		return *m_ptr;
	}
	T* operator->()
	{
		return m_ptr;
	}

protected:

	T* m_ptr;
};

template<typename T>
class reverse_jiterator : public jiterator<T>
{
public:

	reverse_jiterator(T* ptr = nullptr) : jiterator<T>(ptr) {}
	reverse_jiterator(const jiterator<T>& iterator)
	{
		this->m_ptr = iterator.ptr;
	}
	reverse_jiterator(const reverse_jiterator<T>& reverse_iterator) = default;
	~reverse_jiterator() {}

	reverse_jiterator<T>& operator=(const reverse_jiterator<T>& reverse_iterator) = default;
	reverse_jiterator<T>& operator=(const jiterator<T>& iterator)
	{
		this->m_ptr = iterator.ptr;
		return (*this);
	}
	reverse_jiterator<T>& operator=(T* ptr)
	{
		this->ptr = ptr; return (*this);
	}

	reverse_jiterator<T>& operator++()
	{
		--this->m_ptr; return (*this);
	}
	reverse_jiterator<T>& operator--()
	{
		++this->m_ptr; return (*this);
	}

	jiterator<T> base()
	{
		jiterator<T> forward_iterator(this->m_ptr);
		++forward_iterator;
		return forward_iterator;
	}
};