#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

std::string* ULListStr::getValAtLoc(size_t loc) const {
  if (head_ == nullptr) {
    return nullptr;
  }

  Item* temp = head_;
  size_t count_ini = 0;

  while (temp != nullptr) {
    size_t count = temp->last - temp->first;

    if (loc < count_ini + count) {
      size_t num = loc - count_ini;
      return &(temp->val[temp->first + num]);
    }

    count_ini += count;
    temp = temp->next;
  }

  return nullptr;
}

std::string const & ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}

void ULListStr::push_back(const std::string& val) {
  if (head_ == nullptr && tail_ == nullptr) {
    Item* temp = new Item();
    temp->prev = nullptr;
    temp->next = nullptr;
    head_ = temp;
    tail_ = temp;
    size_+= 1;
    temp->first = 0;
    temp->last = 1;
    temp->val[temp->first] = val;
    return;
  }

  if (tail_->last != ARRSIZE) {
    tail_->val[tail_->last] = val;
    tail_->last += 1;
    size_ += 1;
    return;
  }
  else {
    Item* temp = new Item();
    Item* oldTail = tail_;
    temp->prev = oldTail;
    oldTail->next = temp;
    temp->next = nullptr;
    tail_ = temp;
    size_ += 1;
    temp->first = 0;
    temp->last = 1;
    temp->val[temp->first] = val;
    return;
  }

}

void ULListStr::pop_back() {
  if (tail_ == nullptr) {
    return;
  }

  size_t count = tail_->last - tail_->first;

  if (count > 1) {
    tail_->val[tail_->last - 1] = "";
    tail_->last -= 1;
    size_ -= 1;
    return;
  }
  else {
    if (tail_->prev != nullptr) {
      Item* temp = tail_;
      tail_ = tail_->prev;
      tail_->next = nullptr;
      size_ -= 1;
      delete temp;
      return;
    }
    else {
      delete tail_;
      size_ -= 1;
      tail_ = nullptr;
      head_ = nullptr;
      return;
    }
  }

}

void ULListStr::push_front(const std::string& val) {
  if (head_ == nullptr && tail_ == nullptr) {
    Item* temp = new Item();
    temp->prev = nullptr;
    temp->next = nullptr;
    head_ = temp;
    tail_ = temp;
    size_+= 1;
    temp->first = ARRSIZE - 1;
    temp->last = ARRSIZE;
    temp->val[temp->first] = val;
    return;
  }

  if (head_->first > 0) {
    head_->val[head_->first - 1] = val;
    head_->first -= 1;
    size_ += 1;
    return;
  }
  else {
    Item* temp = new Item();
    Item* oldhead = head_;
    temp->prev = nullptr;
    temp->next = oldhead;
    oldhead->prev = temp;
    head_ = temp;
    size_ += 1;
    temp->first = ARRSIZE - 1;
    temp->last = ARRSIZE;
    temp->val[temp->first] = val;
    return;
  }

}

void ULListStr::pop_front() {
  if (head_ == nullptr) {
    return;
  }

  size_t count = head_->last - head_->first;

  if (count > 1) {
    head_->val[head_->first] = "";
    head_->first += 1;
    size_ -= 1;
    return;
  }
  else {
    if (head_->next != nullptr) {
      Item* temp = head_;
      head_ = head_->next;
      head_->prev = nullptr;
      size_ -= 1;
      delete temp;
      return;
    }
    else {
      delete head_;
      size_ -= 1;
      tail_ = nullptr;
      head_ = nullptr;
      return;
    }
  }

}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
