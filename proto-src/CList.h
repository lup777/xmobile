//CList.h
#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdint.h>
#include <stdlib.h>

#define ENABLE_SERIAL

#ifndef ENABLE_SERIAL
#include <iostream>
//using namespace std;
#else
#include "CSerial.h"
#endif


template <typename T>
class CList_elem
{
 public:
  void init(T data);
  void setPrev(CList_elem<T>* p) {
    prev_ = p;
  }
  void setNext(CList_elem<T>* p) {
    next_ = p;
  }

  CList_elem<T>* next() {
    return next_;
  }

  CList_elem<T>* prev() {
    return prev_;
  }

  T data() {
    return data_;
  }

  bool is_last() {return isLast;}
  void set_last(bool ke) {isLast = ke;}
  
 private:
  CList_elem<T>* next_;
  CList_elem<T>* prev_;
  T data_;
  bool isLast;
  
  CList_elem();
};

template <typename T> class list;

template <typename T>
class list_iterator
{
  friend class list<T>;
  
 private:
  list_iterator<T>(T* p);
  list_iterator<T>(CList_elem<T>* elem);
  CList_elem<T>* elem_;
  
 public:
  list_iterator<T>(list_iterator& it);
  list_iterator<T>& operator++();
  list_iterator<T>();

  list_iterator<T>& operator=(const list_iterator<T>& it);
  T operator*() const;
  bool operator!=(const list_iterator<T>& it1);

  bool operator==(const list_iterator<T>& it1);
};
template <typename T>
bool list_iterator<T>::operator!=(const list_iterator<T>& it1) {
  return (elem_ != it1.elem_);
}

template <typename T>
bool list_iterator<T>::operator==(const list_iterator<T>& it1) {
  return (elem_ == it1.elem_);
}

template <typename T>
T list_iterator<T>::operator*() const {
  return elem_->data();
}

template <typename T>
list_iterator<T>& list_iterator<T>::operator=(const list_iterator<T>& it) {
  if(this != &it)
    elem_ = it.elem_;
  
  return *this;
}

template <typename T>
list_iterator<T>& list_iterator<T>::operator++() {
  if(elem_->next() != NULL)
    elem_ = elem_->next();
  return *this;
}

template <typename T>
list_iterator<T>::list_iterator()
: elem_(NULL) {}

template <typename T>
list_iterator<T>::list_iterator(CList_elem<T>* elem)
: elem_(elem) {}

template <typename T>
list_iterator<T>::list_iterator(list_iterator& it) {
  elem_ = it.elem_;
}



template <typename T>
class list
{
 public:
  typedef list_iterator<T> iterator;
  
  list();
  void push_back(T& data);
  T back();
  void clear();
  T pop_back();
  uint8_t size();

  uint8_t size_;

  void set_head(CList_elem<T>* head_);
  void set_tail(CList_elem<T>* tail_);
  CList_elem<T>* head();
  CList_elem<T>* tail();

  list<T>::iterator begin() {
    return it_head_;
  };
  
  list<T>::iterator end() {
    return it_end_;
  };

 private:
  iterator it_head_;
  iterator it_tail_;
  iterator it_end_;
  CList_elem<T>* head_;
  CList_elem<T>* tail_;
  CList_elem<T>* past_end_elem_;
};

template <typename T>
CList_elem<T>* list<T>::head() {
  return head_;
}

template <typename T>
CList_elem<T>* list<T>::tail() {
  return tail_;
}

template <typename T>
void list<T>::set_head(CList_elem<T>* head) {
  head_ = head;
  head_->set_last(false);
}

template <typename T>
void list<T>::set_tail(CList_elem<T>* tail) {
  tail_ = tail;
  tail_->set_last(true);
}

template <typename T>
void CList_elem<T>::init(T data)
{
  next_ = NULL;
  prev_ = NULL;
  data_ = data;
}

template <typename T>
list<T>::list()
  : head_(NULL)
  , tail_(NULL)
  , size_(0) {
#ifdef ENABLE_SERIAL
    //Serial.println("list<T>::list()");
#else
    std::cout << "list<T>::list()" << std::endl;
#endif
    //create past-end-elem
    past_end_elem_ = (CList_elem<T>*)malloc(sizeof(CList_elem<T>));

    past_end_elem_->set_last(true);
    it_end_ = iterator(past_end_elem_);
}

template <typename T>
void list<T>::push_back(T& data) {
  CList_elem<T>* p_new_elem = (CList_elem<T>*)malloc(sizeof(CList_elem<T>));

  if(p_new_elem == NULL) {
#ifdef ENABLE_SERIAL
    //Serial.println("malloc FAILED !");
#else
    std::cout << "malloc FAILED" << std::endl;
#endif
    return;
  }

  if(size_ == 0) {
    head_ = p_new_elem;
  }
  
  CList_elem<T>* p_old_tail = tail_;
  if(p_old_tail != NULL)
    p_old_tail->setNext(p_new_elem);
  
  p_new_elem->init(data);
  p_new_elem->setPrev(p_old_tail);
  p_new_elem->setNext(past_end_elem_);
  
  set_tail(p_new_elem);
  it_head_ = iterator(head_);
  it_tail_ = iterator(tail_);
  size_ += 1;
  
#ifndef ENABLE_SERIAL
  std::cout << "push_back: size = " << (unsigned int)size_ << std::endl;
#endif
}

template <typename T>
T list<T>::back() {
  return tail_->data();
}

template <typename T>
void list<T>::clear() {
  while(size_ != 0) {
    pop_back();
  }
}

template <typename T>
T list<T>::pop_back() {
  if(size_ <= 0) {
#ifdef ENABLE_SERIAL
    //Serial.println("pop_back, but list has zero size");
#else
    std::cout << "pop_back: size = " << (unsigned int)size_ << std::endl;
#endif
    return T();
  }
  else if(size_ == 1) {
    T data = head_->data();
    free(head_);
    head_ = NULL;
    tail_ = NULL;
    size_ -= 1;
    return data;
  }
  else {
    T data = tail_->data();
    CList_elem<T>* new_tail = tail_->prev();
      
    if(tail_->prev() == NULL) {
#ifdef ENABLE_SERIAL
      //Serial.println("ERROR: pop_back: tail_->prev() == NULL");
#else
      std::cout << "ERROR: pop_back: tail_->prev() == NULL" << std::endl;
#endif
    }
    
    free(tail_);
    tail_ = new_tail;
    size_ -= 1;
    return data;
  }
}

template <typename T>
uint8_t list<T>::size() {
  return size_;
}

#endif //__CLIST_H__
