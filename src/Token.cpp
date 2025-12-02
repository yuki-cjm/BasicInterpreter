#include "Token.hpp"

#include <iostream>
#include <memory>

TokenStream::TokenStream(std::vector<Token>&& tokens)
    : tokens_(std::move(tokens)), cursor_(0) {}

const std::shared_ptr<Token> TokenStream::peek() const {
  if (cursor_ >= tokens_.size()) {
    return nullptr;
  }
  std::shared_ptr<Token> temp = std::make_shared<Token>(tokens_[cursor_]);
  return temp;
}

const std::shared_ptr<Token> TokenStream::get() {
  const std::shared_ptr<Token> current = peek();
  if (current != nullptr) {
    ++cursor_;
  }
  return current;
}

bool TokenStream::empty() const { return cursor_ >= tokens_.size(); }

void TokenStream::reset() { cursor_ = 0; }

int TokenStream::position() const { return cursor_; }

int TokenStream::size() const { return tokens_.size(); }

void TokenStream::push(Token&& token) { tokens_.push_back(std::move(token)); }

const std::vector<Token>& TokenStream::data() const { return tokens_; }