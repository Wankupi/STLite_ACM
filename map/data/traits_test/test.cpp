#include <iostream>
#include <map.hpp>
#include <type_traits>
#include <iomanip>
#include <map>
using std::cout, std::endl;
template<typename T>
struct Catagory {
	constexpr static char name[] = "unknown";
};
template<>
struct Catagory<std::input_iterator_tag> {
	constexpr static char name[] = "input_iterator";
};
template<>
struct Catagory<std::output_iterator_tag> {
	constexpr static char name[] = "output_iterator";
};
template<>
struct Catagory<std::forward_iterator_tag> {
	constexpr static char name[] = "forward_iterator";
};
template<>
struct Catagory<std::bidirectional_iterator_tag> {
	constexpr static char name[] = "bidirectional_iterator";
};
template<>
struct Catagory<std::random_access_iterator_tag> {
	constexpr static char name[] = "random_access_iterator";
};
template<>
struct Catagory<std::contiguous_iterator_tag> {
	constexpr static char name[] = "contiguous_iterator";
};
template<typename T>
constexpr const char *catagory_name = Catagory<T>::name;

template<typename T>
void print_infos() {
	cout << catagory_name<typename T::iterator_category> << '\t';
	cout << std::is_const_v<std::remove_reference_t<typename T::reference>> << '\t';
	cout << std::is_const_v<std::remove_pointer_t<typename T::pointer>> << '\t';
	cout << std::is_signed_v<typename T::difference_type> << '\t';
	using value_type = typename T::value_type;
	cout << std::is_const_v<decltype(value_type::first)> << '\t';
	cout << std::is_const_v<decltype(value_type::second)> << endl;
}

struct A {
	A() = delete;
	A(int) {}
};

int main() {
	cout << std::boolalpha;
	print_infos<std::iterator_traits<std::map<int, int>::iterator>>();
	print_infos<std::iterator_traits<sjtu::map<int, int>::iterator>>();
	print_infos<std::iterator_traits<sjtu::map<int, A>::iterator>>();

	print_infos<std::iterator_traits<std::map<int, int>::const_iterator>>();
	print_infos<std::iterator_traits<sjtu::map<int, int>::const_iterator>>();
	print_infos<std::iterator_traits<sjtu::map<int, A>::const_iterator>>();

	return 0;
}
