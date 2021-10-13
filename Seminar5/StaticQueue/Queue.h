#pragma once

#include <array>
#include <stdexcept>
#include <string>

class queue_error : public std::runtime_error {
	public:
		queue_error(const std::string& what_arg);	
};

template <typename T, unsigned N>
class Queue {
	
	static_assert(N>0, "Queue must have space for at least one element");

	public:
		Queue();
		Queue(Queue<T, N> const &o);

		void enqueue(T value);	
		T dequeue();
		bool empty() const;
		bool full() const;
		void clear();
		T const& front() const;

		template<unsigned M>
		Queue<T, N+M> copy_and_expand() const;

		template <typename U, unsigned M>
		friend class Queue;

	private:
		size_t head, tail;
		std::array<T, N> elements;
};

#include "Queue.tcc"
