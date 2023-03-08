#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include "exceptions.hpp"
#include <cstddef>
#include <functional>

namespace sjtu {

template<typename T, class Compare = std::less<T>>
class priority_queue {
private:
	struct Node {
		Node(T const &_data) : data(_data) {}
		Node *left = nullptr, *right = nullptr;
		size_t dis = 1;
		T data;
	};

public:
	priority_queue() : _rt(nullptr), _size(0) {}
	priority_queue(const priority_queue &other) {
		if (other._rt) _rt = copy_tree(other._rt);
		_size = other._size;
	}

	priority_queue(priority_queue &&other) noexcept : _rt(other._rt), _size(other._size) {
		other._rt = nullptr;
		other._size = 0;
	}
	~priority_queue() {
		if (_rt) release_tree(_rt);
	}
	priority_queue &operator=(const priority_queue &other) {
		if (this == &other) return *this;
		this->~priority_queue();
		new (this) priority_queue{other};
		return *this;
	}

	priority_queue &&operator=(priority_queue &&other) {
		if (this == &other) return *this;
		this->~priority_queue();
		new (this) priority_queue{std::move(other)};
		return *this;
	}

	const T &top() const {
		if (!_rt) throw container_is_empty{};
		return _rt->data;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {
		Node *np = new Node{e};
		try {
			_rt = merge_tree(_rt, np);
		} catch (...) {
			delete np;
			throw;
		}
		++_size;
	}

	void pop() {
		if (!_rt) throw container_is_empty{};
		Node *old = _rt;
		_rt = merge_tree(_rt->left, _rt->right);
		--_size;
		delete old;
	}

	size_t size() const {
		return _size;
	}
	bool empty() const {
		return !_rt;
	}
	void merge(priority_queue &other) {
		if (this == &other) return;
		_rt = merge_tree(_rt, other._rt);
		other._rt = nullptr;
		_size += other._size;
		other._size = 0;
	}

private:
	void release_tree(Node *a) {
		if (a->left) release_tree(a->left);
		if (a->right) release_tree(a->right);
		delete a;
	}

	Node *copy_tree(Node *a) {
		Node *p = new Node{*a};
		if (a->left) p->left = copy_tree(a->left);
		if (a->right) p->right = copy_tree(a->right);
		return p;
	}

	Node *merge_tree(Node *a, Node *b) {
		if (a == nullptr || b == nullptr)
			return a == nullptr ? b : a;
		if (_opt(a->data, b->data)) std::swap(a, b);
		a->right = merge_tree(a->right, b);
		if (!a->left || a->right->dis > a->left->dis) std::swap(a->left, a->right);
		a->dis = a->right ? a->right->dis + 1 : 1;
		return a;
	}

private:
	Node *_rt;
	size_t _size;
	[[no_unique_address]] Compare _opt;
};

}// namespace sjtu

#endif
