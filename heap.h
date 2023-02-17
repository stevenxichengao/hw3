#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap : private std::vector<T>
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
	int n;
	PComparator b;


};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
	n = m;
	b = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty.");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty.");

  }

  std::swap(data[0],data[data.size()-1]);
	data.pop_back();
	int idx = 0;
	T& current = data[idx];
	while(true){
		int temp = idx*n+1;
		if(idx*n+1 >= data.size()) break;
		for(int i = idx*n+2; i <= idx*n+n && i < data.size() ;i++){
			if(b(data[i], data[temp])){
				temp = i;
			}
		}
		if(b(data[temp], data[idx])) {
			std::swap(data[temp], data[idx]);
			idx = temp;
		}
		else break;
	}
	
	
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  data.push_back(item);
  std::size_t idx = data.size()-1;
  while(idx!=0){
    std::size_t parent_idx = (idx-1)/n;
    T& current = data[idx];
    T& parent = data[parent_idx];
    if(b(parent, current)){
      break;
    }
    std::swap(current, parent);
    idx = parent_idx;
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return data.size()==0;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
  return data.size();
}

#endif

