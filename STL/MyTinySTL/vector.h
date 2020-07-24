#ifndef MYTINYSTL_VECTOR_H_
#define MYTINYSTL_VECTOR_H_

// 这个头文件包含一个模板类 vector
// vector : 向量

// notes:
//
// 异常保证：
// mystl::vecotr<_Type> 满足基本异常保证，部分函数无异常保证，并对以下函数做强异常安全保证：
//   * emplace
//   * emplace_back
//   * push_back
// 当 std::is_nothrow_move_assignable<_Type>::value == true 时，以下函数也满足强异常保证：
//   * reserve
//   * resize
//   * insert

#include <initializer_list>

#include "iterator.h"
#include "memory.h"
#include "util.h"
#include "exceptdef.h"

namespace mystl
{

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

// 模板类: vector 
// 模板参数 _Type 代表类型
template <class _Type>
class vector
{
	// 编译时静态检查，vector的类型是否为bool
	static_assert(!std::is_same<bool, _Type>::value, "vector<bool> is abandoned in mystl");
public:
	// vector 的嵌套型别定义
	using allocator_type= mystl::allocator<_Type> ;
	using data_allocator= mystl::allocator<_Type> ;

	using value_type = typename allocator_type::value_type;
	using pointer = typename allocator_type::pointer;
	using const_pointer = typename allocator_type::const_pointer;

	using reference = typename allocator_type::reference;
	using const_reference = typename allocator_type::const_reference; 
	using size_type = typename allocator_type::size_type;
	using difference_type = typename allocator_type::difference_type;

	using iterator = value_type *;
	using const_iterator = const value_type *;
	using reverse_iterator = mystl::reverse_iterator<iterator>;
	using const_reverse_iterator = mystl::reverse_iterator<const_iterator>;

	allocator_type get_allocator() { return data_allocator(); }

private:
	iterator _start;  // 表示目前使用空间的头部
	iterator _finish;    // 表示目前使用空间的尾部
	iterator end_of_storage;    // 表示可用储存空间的尾部

public:
	// 构造、复制、移动、析构函数
	// 构造一个空vector（初始大小为16）
	vector() noexcept{ try_init(); }

	// 构造一个size为n的vector，每个元素使用value_type()初始化
	// 该构造函数必须是explicit的
	explicit vector(size_type n){
		fill_init(n, value_type());
	}

  	vector(size_type n, const value_type& value){
		fill_init(n, value); 
	}

  	template <class Iter, typename std::enable_if<
    	mystl::is_input_iterator<Iter>::value, int>::type = 0>
  	vector(Iter first, Iter last){
		// MYSTL_DEBUG调用assert宏断言
    	MYSTL_DEBUG(!(last < first));
    	range_init(first, last);
  	}

	// 拷贝构造函数
  	vector(const vector& rhs){
    	range_init(rhs._start, rhs._finish);
  	}
	// 移动拷贝构造
  	vector(vector&& rhs) noexcept:
		_start(rhs._start),
    	_finish(rhs._finish),
    	end_of_storage(rhs.end_of_storage)
		{
			// 将移后源置为安全状态
			rhs._start = nullptr;
			rhs._finish = nullptr;
			rhs.end_of_storage = nullptr;
  		}

	// 列表初始化构造一个vector
  	vector(std::initializer_list<value_type> ilist){
	    range_init(ilist.begin(), ilist.end());
  	}

	// 
  	vector& operator=(const vector& rhs);
  	vector& operator=(vector&& rhs) noexcept;

	// initializer_list赋值操作符
	// ？？？
  	vector& operator=(std::initializer_list<value_type> ilist){
    	vector tmp(ilist.begin(), ilist.end());
    	swap(tmp);
    	return *this;
  	}

	// 回收资源
  	~vector(){ 
    	destroy_and_recover(_start, _finish, end_of_storage - _start);
    	_start = _finish = end_of_storage = nullptr;
  	}

public:

  	// 迭代器相关操作
  	iterator begin() noexcept { return _start; }
	const_iterator begin() const noexcept{ return _start; }

	iterator end() noexcept{ return _finish; }
	const_iterator end() const noexcept { return _finish; }

	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	const_reverse_iterator rbegin()  const noexcept
		{ return const_reverse_iterator(end()); }

	reverse_iterator rend() noexcept
		{ return reverse_iterator(begin()); }
	const_reverse_iterator rend()    const noexcept 
		{ return const_reverse_iterator(begin()); }

	const_iterator         cbegin()  const noexcept 
		{ return begin(); }
	const_iterator         cend()    const noexcept
		{ return end(); }
	const_reverse_iterator crbegin() const noexcept
		{ return rbegin(); }
	const_reverse_iterator crend()   const noexcept
		{ return rend(); }

  	// 容量相关操作
	bool empty()const {return begin()==end();}
	size_type size() const noexcept{return static_cast<size_type>(end()-begin());}

	size_type max_size() const noexcept
	{ return static_cast<size_type>(-1) / sizeof(_Type); }

	size_type capacity() const noexcept{
		return static_cast<size_type>(end_of_storage - _start); 
	}
	void      reserve(size_type n);
	void      shrink_to_fit();

	// 访问元素相关操作
	// 下标操作符重载，返回引用
	reference operator[](size_type n){
		MYSTL_DEBUG(n < size());
		return *(_start + n);
	}
	const_reference operator[](size_type n) const{
		MYSTL_DEBUG(n < size());
		return *(_start + n);
	}
	// 定义at操作函数
	reference at(size_type n){
		THROW_OUT_OF_RANGE_IF(!(n < size()), "vector<_Type>::at() subscript out of range");
		return (*this)[n];
	}
	const_reference at(size_type n) const{
		THROW_OUT_OF_RANGE_IF(!(n < size()), "vector<_Type>::at() subscript out of range");
		return (*this)[n];
	}

	reference front(){
		MYSTL_DEBUG(!empty());
		return *_start;
	}
	const_reference front() const{
		MYSTL_DEBUG(!empty());
		return *_start;
	}
	reference back(){
		MYSTL_DEBUG(!empty());
		return *(_finish - 1);
	}
	const_reference back() const{
		MYSTL_DEBUG(!empty());
		return *(_finish - 1);
	}

	pointer       data()       noexcept { return _start; }
	const_pointer data() const noexcept { return _start; }

	// 修改容器相关操作

	// assign
	void assign(size_type n, const value_type& value){ fill_assign(n, value); }

	template <class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
	void assign(Iter first, Iter last){
		MYSTL_DEBUG(!(last < first));
		copy_assign(first, last, iterator_category(first));
	}

	void assign(std::initializer_list<value_type> il)
	{ copy_assign(il.begin(), il.end(), mystl::forward_iterator_tag{}); }

	// emplace / emplace_back

	template <class... Args>
	iterator emplace(const_iterator pos, Args&& ...args);

	template <class... Args>
	void emplace_back(Args&& ...args);

	// push_back / pop_back

	void push_back(const value_type& value);
	void push_back(value_type&& value)
	{ emplace_back(mystl::move(value)); }

	void pop_back();

  	// insert
	void insert_aux(iterator position,const value_type &value);
	iterator insert(const_iterator pos, const value_type& value);
	iterator insert(const_iterator pos, value_type&& value)
	{ return emplace(pos, mystl::move(value)); }

	// 给定pos处开始，插入n个值为value的元素
	iterator insert(const_iterator pos, size_type n, const value_type& value)
	{
		MYSTL_DEBUG(pos >= begin() && pos <= end());
		return fill_insert(const_cast<iterator>(pos), n, value);
	}

	template <class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
	void     insert(const_iterator pos, Iter first, Iter last)
	{
		MYSTL_DEBUG(pos >= begin() && pos <= end() && !(last < first));
		copy_insert(const_cast<iterator>(pos), first, last);
	}

	// erase / clear
	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);
	void     clear() { erase(begin(), end()); }

	// resize / reverse
	void     resize(size_type new_size) { return resize(new_size, value_type()); }
	void     resize(size_type new_size, const value_type& value);

	void     reverse() { mystl::reverse(begin(), end()); }

	// swap
	void     swap(vector& rhs) noexcept;

private:
	// helper functions

	// initialize / destroy
	void      try_init() noexcept;

	void      init_space(size_type size, size_type cap);

	void      fill_init(size_type n, const value_type& value);
	template <class Iter>
	void      range_init(Iter first, Iter last);

	void      destroy_and_recover(iterator first, iterator last, size_type n);

	// calculate the growth size
	size_type get_new_cap(size_type add_size);

	// assign

	void      fill_assign(size_type n, const value_type& value);

	template <class IIter>
	void      copy_assign(IIter first, IIter last, input_iterator_tag);

	template <class FIter>
	void      copy_assign(FIter first, FIter last, forward_iterator_tag);

	// reallocate

	template <class... Args>
	void      reallocate_emplace(iterator pos, Args&& ...args);
	void      reallocate_insert(iterator pos, const value_type& value);

	// insert

	iterator  fill_insert(iterator pos, size_type n, const value_type& value);
	template <class IIter>
	void      copy_insert(iterator pos, IIter first, IIter last);

	// shrink_to_fit

	void      reinsert(size_type size);
};

/*****************************************************************************************/

// 复制赋值操作符
template <class _Type>
vector<_Type>& vector<_Type>::operator=(const vector& rhs){
  	if (this != &rhs){ // self-assignment
	  	// !case1,2,3都可以使用case1的方法实现
    	const auto len = rhs.size();
		// case 1: 当前容量不够存放rhs的数据，最快捷的方式：直接生成一个
		// rhs.size()大小的vector，然后swap给this
    	if (len > capacity())
		{ 
			vector tmp(rhs.begin(), rhs.end());
			swap(tmp);
		}
		// case 2: 赋值左侧对象空间足够
    	else if (len<=size())
    	{
			// 直接调用copy复制
     		auto i = mystl::copy(rhs.begin(), rhs.end(), begin());
			// 把原来用不到的部分：[i,_finish)，调用析构函数释放掉
      		data_allocator::destroy(i, _finish);
			// 调整水位
      		_finish = _start + len;
    	}
    	else{ // case 3:
			// step1:调用copy复制
			// step2：调用unitialized_copy
			mystl::copy(rhs.begin(), rhs.begin() + size(), _start);
			mystl::uninitialized_copy(rhs.begin() + size(), rhs.end(), _finish);
			end_of_storage = _finish = _start + len;
    	}
  	}
  	return *this;
}

// 移动赋值操作符
template <class _Type>
vector<_Type>& vector<_Type>::operator=(vector&& rhs) noexcept{
	// 检查self-assignment
	if(this!=&rhs){
		// 回收this指向的内存
		destroy_and_recover(_start, _finish, end_of_storage - _start);
		// 从rhs中接管资源
		_start = rhs._start;
		_finish = rhs._finish;
		end_of_storage = rhs.end_of_storage;
		// 将rhs置于安全的状态（如可析构）
		rhs._start = nullptr;
		rhs._finish = nullptr;
		rhs.end_of_storage = nullptr;
	}
	return *this;
}

// 预留空间大小，当原容量小于要求大小时，才会重新分配
// requeset vector的capacity至少可以包含n个元素
// 1. 如果n大于当前capacity，则container reallocat内存
// 2. otherwise，什么也不用作
// 该函数不能影响vector的size；也不能改变其元素
template <class _Type>
void vector<_Type>::reserve(size_type n){
	if (capacity() < n){
		THROW_LENGTH_ERROR_IF(n > max_size(),
							"n can not larger than max_size() in vector<_Type>::reserve(n)");
		const auto old_size = size();
		// 申请大小为n的内存空间
		auto tmp = data_allocator::allocate(n);
		// 不能影响size；不能改变其中的元素，因此至少要将当前元素copy到新内存空间内
		// 当然，为了性能，最好move过去
		mystl::uninitialized_move(_start, _finish, tmp);
		// 释放旧内存空间
		data_allocator::deallocate(_start, end_of_storage - _start);
		_start = tmp;
		_finish = tmp + old_size;
		end_of_storage = _start + n;
	}
}

// 放弃多余的容量，即减少容量到合适的程度，称为“收缩到合适（shrink-to-fit）
// request 容器将其capacity减少到和其size匹配
// 该操作不可改变其size；不能改变其元素
template <class _Type>
void vector<_Type>::shrink_to_fit()
{
	// 该操作最简单的实现，即重现申请一个当前size大小的内存，将当前资源移过去即可
	if (_finish < end_of_storage)
	{
		reinsert(size());
	}
}

// 在 pos 位置就地构造元素，避免额外的复制或移动开销
template <class _Type>
template <class ...Args>
typename vector<_Type>::iterator 
			vector<_Type>::emplace(const_iterator pos, Args&& ...args)
{
	MYSTL_DEBUG(pos >= begin() && pos <= end());

  	iterator xpos = const_cast<iterator>(pos);
  	const size_type n = xpos - _start;
	// 尚有备用空间
  	if (_finish != end_of_storage && xpos == _finish){
		// 由于data_allocator，申请的是raw空间，需要construct构造元素
    	data_allocator::construct(
			mystl::address_of(*_finish),
			mystl::forward<Args>(args)...);
    	++_finish;
  	}
  	else if (_finish != end_of_storage)
  	{
		auto new_end = _finish;
		data_allocator::construct(mystl::address_of(*_finish), *(_finish - 1));
		++new_end;
		mystl::copy_backward(xpos, _finish - 1, _finish);
		*xpos = value_type(mystl::forward<Args>(args)...);
  	}
	else
	{
		reallocate_emplace(xpos, mystl::forward<Args>(args)...);
	}
  	return begin() + n;
}

// 在尾部就地构造元素，避免额外的复制或移动开销
template <class _Type>
template <class ...Args>
void vector<_Type>::emplace_back(Args&& ...args)
{
  if (_finish < end_of_storage)
  {
    data_allocator::construct(mystl::address_of(*_finish), mystl::forward<Args>(args)...);
    ++_finish;
  }
  else
  {
    reallocate_emplace(_finish, mystl::forward<Args>(args)...);
  }
}

// 在尾部插入元素
template <class _Type>
void vector<_Type>::push_back(const value_type& value)
{	// 尚有备用空间
  	if (_finish != end_of_storage){
    	data_allocator::construct(mystl::address_of(*_finish), value);
    	++_finish;// 调整水位
  	}
  	else{
    	reallocate_insert(end(), value);
  	}
}

template<class _Type>
void vector<_Type>::insert_aux(iterator position,const value_type &value){
	if(_finish!=end_of_storage){
		data_allocator::construct(_finish,*(_finish-1));
		++_finish;
		value_type x_copy=value;
		// position之后的元素向后copy
		mystl::copy_backward(position,_finish-2,_finish-1));
		*position=x_copy;
	}
	else{

	}
}

// 弹出尾部元素
template <class _Type>
void vector<_Type>::pop_back()
{
	MYSTL_DEBUG(!empty());
	data_allocator::destroy(_finish - 1);
	--_finish;
}

// 在 pos 处插入元素
template <class _Type>
typename vector<_Type>::iterator
vector<_Type>::insert(const_iterator pos, const value_type& value)
{
  MYSTL_DEBUG(pos >= begin() && pos <= end());
  iterator xpos = const_cast<iterator>(pos);
  const size_type n = pos - _start;
  if (_finish != end_of_storage && xpos == _finish)
  {
    data_allocator::construct(mystl::address_of(*_finish), value);
    ++_finish;
  }
  else if (_finish != end_of_storage)
  {
    auto new_end = _finish;
    data_allocator::construct(mystl::address_of(*_finish), *(_finish - 1));
    ++new_end;
    auto value_copy = value;  // 避免元素因以下复制操作而被改变
    mystl::copy_backward(xpos, _finish - 1, _finish);
    *xpos = mystl::move(value_copy);
  }
  else
  {
    reallocate_insert(xpos, value);
  }
  return _start + n;
}

// 删除 pos 位置上的元素
template <class _Type>
typename vector<_Type>::iterator
vector<_Type>::erase(const_iterator pos)
{
	// 检测删除位置合法性
	MYSTL_DEBUG(pos >= begin() && pos < end());
	iterator xpos = _start + (pos - begin());
	// [start-------------pos----------finish]
	// [pos+1,finish)区间向前move一个单元即可
	mystl::move(xpos + 1, _finish, xpos);
	// 析构掉erase的元素
	data_allocator::destroy(_finish - 1);
	--_finish;	// 调整水位
	return xpos;
}

// 删除[first, last)上的元素
template <class _Type>
typename vector<_Type>::iterator
vector<_Type>::erase(const_iterator first, const_iterator last)
{
	// 检测区间合法性
	MYSTL_DEBUG(first >= begin() && last <= end() && !(last < first));
	// [start----------first--------------last----------finish]
	// 首先应该将[last,finish)区间的元素move到前面
	// 即，move(last,_finish,first)，返回move后的最后一个iterator
	// 然后，destroy调用析构函数，释放多余元素：！本身空间不回收
	const auto n = first - begin();
	iterator r = _start + (first - begin());
	data_allocator::destroy(
		mystl::move(r + (last - first), _finish, r),
		_finish);
	_finish = _finish - (last - first); 	// 调整水位
	return _start + n;
}

// 重置容器大小
// 如果当前容器的n小于当前size，容器的元素将会只保留前n个元素
// 如果n大于size，容器将会insert足够多值为value的元素以使得size扩展到n
// 如果n大于capacity，reallocation
template <class _Type>
void vector<_Type>::resize(size_type new_size, const value_type& value)
{
	if (new_size < size()){
		// 只保留前n个元素
		erase(begin() + new_size, end());
	}
	else{
		// 后两种情况直接调用insert即可
		insert(end(), new_size - size(), value);
	}
}

// 与另一个 vector 交换
template <class _Type>
void vector<_Type>::swap(vector<_Type>& rhs) noexcept
{
	if (this != &rhs)	// 自交换检测
	{
		mystl::swap(_start, rhs._start);
		mystl::swap(_finish, rhs._finish);
		mystl::swap(end_of_storage, rhs.end_of_storage);
	}
}

/*****************************************************************************************/
// helper function

// try_init 函数，若分配失败则忽略，不抛出异常
// 初始分配16大小的内存
template <class _Type>
void vector<_Type>::try_init() noexcept
{
	try
	{
		// 初始分配16大小的空间
		_start = data_allocator::allocate(16);
		_finish = _start;
		end_of_storage = _start + 16;
	}
	catch (...)
	{
		_start = nullptr;
		_finish = nullptr;
		end_of_storage = nullptr;
	}
}

// init_space 函数
// 申请cap大小的raw空间
template <class _Type>
void vector<_Type>::init_space(size_type size, size_type cap)
{
	try
	{
		_start = data_allocator::allocate(cap);
		_finish = _start + size;
		end_of_storage = _start + cap;
	}
	catch (...)
	{
		_start = nullptr;
		_finish = nullptr;
		end_of_storage = nullptr;
		throw;
	}
}

// fill_init 函数
// 1. 申请一定空间，该空间capacity一定要大于n---> 调用init_space申请一个size为n，capacity为 init_size raw空间
// 2. 由于是raw空间，因此最好采用unitialized_fill_n
template <class _Type>
void vector<_Type>::
fill_init(size_type n, const value_type& value)
{
	const size_type init_size = mystl::max(static_cast<size_type>(16), n);
	init_space(n, init_size);
	mystl::uninitialized_fill_n(_start, n, value);
}

// range_init 函数
// 和fill_init思想类似，先确定申请空间的大小
// 然后使用copy构造
template <class _Type>
template <class Iter>
void vector<_Type>::range_init(Iter first, Iter last)
{
	const size_type init_size = mystl::max(static_cast<size_type>(last - first),
											static_cast<size_type>(16));
	init_space(static_cast<size_type>(last - first), init_size);
	mystl::uninitialized_copy(first, last, _start);
}

// destroy_and_recover 函数
// 实现资源的回收：1。调用析构函数2.调用deallocate函数释放内存
template <class _Type>
void vector<_Type>::
destroy_and_recover(iterator first, iterator last, size_type n)
{
	data_allocator::destroy(first, last);
	data_allocator::deallocate(first, n);
}

// get_new_cap 函数
template <class _Type>
typename vector<_Type>::size_type 
vector<_Type>::
get_new_cap(size_type add_size)
{
	const auto old_size = capacity();
	THROW_LENGTH_ERROR_IF(old_size > max_size() - add_size,
							"vector<_Type>'s size too big");
	if (old_size > max_size() - old_size / 2)
	{
		return old_size + add_size > max_size() - 16
		? old_size + add_size : old_size + add_size + 16;
	}
	const size_type new_size = old_size == 0
		? mystl::max(add_size, static_cast<size_type>(16))
		: mystl::max(old_size + old_size / 2, old_size + add_size);
	return new_size;
}

// fill_assign 函数
template <class _Type>
void vector<_Type>::
fill_assign(size_type n, const value_type& value)
{
	if (n > capacity())
	{
		vector tmp(n, value);
		swap(tmp);
	}
	else if (n > size())
	{
		mystl::fill(begin(), end(), value);
		_finish = mystl::uninitialized_fill_n(_finish, n - size(), value);
	}
	else
	{
		erase(mystl::fill_n(_start, n, value), _finish);
	}
}

// copy_assign 函数
template <class _Type>
template <class IIter>
void vector<_Type>::
copy_assign(IIter first, IIter last, input_iterator_tag)
{
  	auto cur = _start;
	for (; first != last && cur != _finish; ++first, ++cur)
	{
		*cur = *first;
	}
	if (first == last)
	{
		erase(cur, _finish);
	}
	else
	{
		insert(_finish, first, last);
	}
}

// 用 [first, last) 为容器赋值
template <class _Type>
template <class FIter>
void vector<_Type>::
copy_assign(FIter first, FIter last, forward_iterator_tag)
{
  const size_type len = mystl::distance(first, last);
  if (len > capacity())
  {
    vector tmp(first, last);
    swap(tmp);
  }
  else if (size() >= len)
  {
    auto new_end = mystl::copy(first, last, _start);
    data_allocator::destroy(new_end, _finish);
    _finish = new_end;
  }
  else
  {
    auto mid = first;
    mystl::advance(mid, size());
    mystl::copy(first, mid, _start);
    auto new_end = mystl::uninitialized_copy(mid, last, _finish);
    _finish = new_end;
  }
}

// 重新分配空间并在 pos 处就地（in-place）构造元素
template <class _Type>
template <class ...Args>
void vector<_Type>::
reallocate_emplace(iterator pos, Args&& ...args)
{
  const auto new_size = get_new_cap(1);
  auto new_begin = data_allocator::allocate(new_size);
  auto new_end = new_begin;
  try
  {
    new_end = mystl::uninitialized_move(_start, pos, new_begin);
    data_allocator::construct(mystl::address_of(*new_end), mystl::forward<Args>(args)...);
    ++new_end;
    new_end = mystl::uninitialized_move(pos, _finish, new_end);
  }
  catch (...)
  {
    data_allocator::deallocate(new_begin, new_size);
    throw;
  }
  destroy_and_recover(_start, _finish, end_of_storage - _start);
  _start = new_begin;
  _finish = new_end;
  end_of_storage = new_begin + new_size;
}

// 重新分配空间并在 pos 处插入元素
template <class _Type>
void vector<_Type>::reallocate_insert(iterator pos, const value_type& value)
{
	const auto new_size = get_new_cap(1);
	auto new_begin = data_allocator::allocate(new_size);
	auto new_end = new_begin;
	const value_type& value_copy = value;
	try
	{
		new_end = mystl::uninitialized_move(_start, pos, new_begin);
		data_allocator::construct(mystl::address_of(*new_end), value_copy);
		++new_end;
		new_end = mystl::uninitialized_move(pos, _finish, new_end);
	}
	catch (...)
	{
		data_allocator::deallocate(new_begin, new_size);
		throw;
	}
	destroy_and_recover(_start, _finish, end_of_storage - _start);
	_start = new_begin;
	_finish = new_end;
	end_of_storage = new_begin + new_size;
}

// fill_insert 函数
// 从pos处开始插入n个值为value的元素
template <class _Type>
typename vector<_Type>::iterator 
		vector<_Type>::fill_insert(
			iterator pos, 
			size_type n,
			const value_type& value)
{
	// 检查插入位置
	MYSTL_DEBUG(pos>=begin()&&pos>=end());
	if (n == 0)
		return pos;
	const size_type xpos = pos - _start;
	const value_type value_copy = value;  // 避免被覆盖
	// 如果备用空间大于等于增加的空间
	if (static_cast<size_type>(end_of_storage - _finish) >= n)
	{ 
		const size_type after_elems = _finish - pos;
		auto old_end = _finish;
		if (after_elems > n)
		{
			// finish后面的空间是raw空间，应使用unintialized_copy，
			// 将finish前n个元素后移到原finish开始处n个位置
			mystl::uninitialized_copy(_finish - n, _finish, _finish);
			_finish += n; // 调整水位
			// 将来[pos,old_end-n)的元素的move后移即可
			mystl::move_backward(pos, old_end - n, old_end);
			// 空出来的空间上construct n个元素
			mystl::uninitialized_fill_n(pos, n, value_copy);
		}
		else
		{	// [start-----pos-----finish***********end_of_storage]
			// 后面空出来的n-(finish-pos)个位置先填充上value_copy
			_finish = // 这里的水位已经发生改变
				mystl::uninitialized_fill_n(_finish, n - after_elems, value_copy);
			// [start-----pos-----old_end-----finish******end_of_storage]
			// 再将pos------finish原元素move到改变后的finish起始处
			_finish = mystl::uninitialized_move(pos, old_end, _finish);
			// 填充
			mystl::uninitialized_fill_n(pos, after_elems, value_copy);
		}
  	}
  	else
	{ 	// 如果备用空间不足
		// 申请capacity+n个大小的空间
		const auto new_size = get_new_cap(n);
		auto new_begin = data_allocator::allocate(new_size);
		auto new_end = new_begin;
		try
		{
			// [start,pos)位置的元素move到_new_begin起始处
			new_end = mystl::uninitialized_move(_start, pos, new_begin);
			// [new_end,)填充n个value元素
			new_end = mystl::uninitialized_fill_n(new_end, n, value);
			// 再加其余的元素move过来
			new_end = mystl::uninitialized_move(pos, _finish, new_end);
		}
		catch (...)
		{
			destroy_and_recover(new_begin, new_end, new_size);
			throw;
		}
		// 回收原资源
		data_allocator::deallocate(_start, end_of_storage - _start);
		_start = new_begin;
		_finish = new_end;
		end_of_storage = _start + new_size;
	}
	return _start + xpos;
}

// copy_insert 函数
// 将pos
template <class _Type>
template <class IIter>
void vector<_Type>::copy_insert(iterator pos, IIter first, IIter last)
{
	if (first == last)
		return;
	const auto n = mystl::distance(first, last);
	if ((end_of_storage - _finish) >= n)
	{ // 如果备用空间大小足够
		const auto after_elems = _finish - pos;
		auto old_end = _finish;
		if (after_elems > n)
		{
			_finish = mystl::uninitialized_copy(_finish - n, _finish, _finish);
			mystl::move_backward(pos, old_end - n, old_end);
			mystl::uninitialized_copy(first, last, pos);
		}
		else
		{
			auto mid = first;
			mystl::advance(mid, after_elems);
			_finish = mystl::uninitialized_copy(mid, last, _finish);
			_finish = mystl::uninitialized_move(pos, old_end, _finish);
			mystl::uninitialized_copy(first, mid, pos);
		}
	}
	else
	{ // 备用空间不足
		const auto new_size = get_new_cap(n);
		auto new_begin = data_allocator::allocate(new_size);
		auto new_end = new_begin;
		try
		{
			new_end = mystl::uninitialized_move(_start, pos, new_begin);
			new_end = mystl::uninitialized_copy(first, last, new_end);
			new_end = mystl::uninitialized_move(pos, _finish, new_end);
		}
		catch (...)
		{
			destroy_and_recover(new_begin, new_end, new_size);
			throw;
		}
		data_allocator::deallocate(_start, end_of_storage - _start);
		_start = new_begin;
		_finish = new_end;
		end_of_storage = _start + new_size;
	}
}

// reinsert 函数
template <class _Type>
void vector<_Type>::reinsert(size_type size)
{
  auto new_begin = data_allocator::allocate(size);
	try
	{
		mystl::uninitialized_move(_start, _finish, new_begin);
	}
	catch (...)
	{
		data_allocator::deallocate(new_begin, size);
		throw;
	}
	data_allocator::deallocate(_start, end_of_storage - _start);
	_start = new_begin;
	_finish = _start + size;
	end_of_storage = _start + size;
}

/*****************************************************************************************/
// 重载比较操作符

template <class _Type>
bool operator==(const vector<_Type>& lhs, const vector<_Type>& rhs)
{
	// 先比较两个vector的大小，再调用algorithm中的equal函数
	return lhs.size() == rhs.size() &&
		mystl::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class _Type>
bool operator<(const vector<_Type>& lhs, const vector<_Type>& rhs)
{
	// 基于字典序比较
  	return mystl::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), lhs.end());
}

template <class _Type>
bool operator!=(const vector<_Type>& lhs, const vector<_Type>& rhs)
{
	// 调用==操作符
	return !(lhs == rhs);
}

template <class _Type>
bool operator>(const vector<_Type>& lhs, const vector<_Type>& rhs)
{
  	return rhs < lhs;
}

template <class _Type>
bool operator<=(const vector<_Type>& lhs, const vector<_Type>& rhs)
{
  	return !(rhs < lhs);
}

template <class _Type>
bool operator>=(const vector<_Type>& lhs, const vector<_Type>& rhs)
{
  	return !(lhs < rhs);
}

// 重载 mystl 的 swap
template <class _Type>
void swap(vector<_Type>& lhs, vector<_Type>& rhs)
{
  	lhs.swap(rhs);
}

} // namespace mystl
#endif // !MYTINYSTL_VECTOR_H_

