#pragma once

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace s21 {

template <typename Key, typename Comparator>
class AVLTree {
  // ========================== *Class Node* ==========================
 protected:
  class Node {
   public:
    Key* key;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    // ========================== *Node Constructors* ==========================
   public:
    Node()
        : key(nullptr),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          height(0) {}

    Node(Key& k) : left(nullptr), right(nullptr), parent(nullptr), height(0) {
      key = new Key(k);
    }

    Node(const Key& k)
        : left(nullptr), right(nullptr), parent(nullptr), height(0) {
      key = new Key(k);
    }

    ~Node() {
      if (key) {
        delete key;
        key = nullptr;
      }
    }

    // ========================== *Node Getter* ==========================
   public:
    Key& GetKey() { return *(this->key); }

    Node* GetRight() { return this->right; }

    Node* GetLeft() { return this->left; }

    Node* GetParent() { return this->parent; }
  };

  // ========================== *Class Iterator* ==========================

 public:
  class TreeIterator {
   public:
    using key_type = Key;
    using reference = Key&;
    using pointer = Key*;

   private:
    Node* node_;
    Node* root_;

   public:
    TreeIterator() : node_(nullptr), root_(nullptr) {}
    TreeIterator(Node* node = nullptr, Node* root = nullptr)
        : node_(node), root_(root) {}
    TreeIterator(const TreeIterator&) = default;
    TreeIterator& operator=(const TreeIterator&) = default;
    ~TreeIterator() = default;

    TreeIterator operator+(const size_t value) {
      TreeIterator tmp = *this;
      for (size_t i = 0; i < value; i++) {
        ++tmp;
      }
      return tmp;
    }

    TreeIterator& operator++() {
      if (node_ != nullptr) {
        if (node_->GetRight() != nullptr) {
          node_ = node_->GetRight();
          while (node_->GetLeft() != nullptr) {
            node_ = node_->GetLeft();
          }
        } else {
          Node* parent = node_->GetParent();
          while (parent != nullptr && node_ == parent->GetRight()) {
            node_ = parent;
            parent = parent->GetParent();
          }
          node_ = parent;
        }
        return *this;
      }
      return *this;
    }

    TreeIterator operator++(int) {
      TreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    TreeIterator operator-(const size_t value) {
      TreeIterator tmp = *this;
      for (size_t i = 0; i < value; i++) {
        --tmp;
      }
      return tmp;
    }

    TreeIterator& operator--() {
      if (node_ != nullptr) {
        return go_down();
      } else if (root_ != nullptr) {
        node_ = max_key(root_);
        return *this;
      }
      return go_down();
    }

    TreeIterator operator--(int) {
      TreeIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const TreeIterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const TreeIterator& other) const {
      return node_ != other.node_;
    }

    reference operator*() const { return node_->GetKey(); }

    pointer operator->() const { return &(node_->GetKey()); }

    Node* GetRoot() { return this->root_; }
    Node* GetNode() { return this->node_; }

    // ========================== *Support for Iterator*==================

   private:
    Node* max_key(Node* node) {
      if (node != nullptr) {
        while (node->right != nullptr) {
          return this->max_key(node->right);
        }
        return node;
      }
      return nullptr;
    }

    TreeIterator& go_down() {
      if (node_ != nullptr) {
        if (node_->left != nullptr) {
          node_ = node_->left;
          while (node_->right != nullptr) {
            node_ = node_->right;
          }
        } else {
          Node* parent = node_->parent;
          while (parent != nullptr && node_ == parent->left) {
            node_ = parent;
            parent = parent->parent;
          }
          node_ = parent;
        }
        return *this;
      }
      return *this;
    }
  };

  // ========================== *Class ConstIterarator*======================

  class ConstTreeIterator {
   public:
    using const_key_type = const Key;
    using const_reference = const Key&;
    using const_pointer = const Key*;
    using base = typename AVLTree<Key, Comparator>::TreeIterator;

   private:
    base BaseIt;

   public:
    ConstTreeIterator(Node* node = nullptr, Node* root = nullptr)
        : BaseIt(node, root) {}

    ConstTreeIterator operator+(const size_t value) {
      BaseIt = BaseIt.operator+(value);
      return *this;
    }

    ConstTreeIterator& operator++() {
      BaseIt.operator++();
      return *this;
    }

    ConstTreeIterator operator++(int) {
      ConstTreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ConstTreeIterator operator-(const size_t value) {
      BaseIt = BaseIt.operator-(value);
      return *this;
    }

    ConstTreeIterator& operator--() {
      BaseIt.operator--();
      return *this;
    }

    ConstTreeIterator operator--(int) {
      ConstTreeIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const ConstTreeIterator& other) const {
      return BaseIt.operator==(other.BaseIt);
    }

    bool operator!=(const ConstTreeIterator& other) {
      return BaseIt.operator!=(other.BaseIt);
    }

    const_reference operator*() { return BaseIt.operator*(); }

    const_pointer operator->() { return BaseIt.operator->(); }

    Node* GetRoot() { return BaseIt.GetRoot(); }
    Node* GetNode() { return BaseIt.GetNode(); }
  };

  // ========================== *Class AVLTree realization*=================

 protected:
  Node* root_;
  size_t size_;
  Comparator comparator_;

 public:
  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;

  // ========================== *Tree Constructors* ==========================

  // Default constructor
  AVLTree() : root_(nullptr), size_(0) {}

  // Copy constructor
  AVLTree(const AVLTree& other) { *this = other; }

  // Operator equal copy
  AVLTree& operator=(const AVLTree& other) {
    this->size_ = other.size_;
    if (other.root_ != nullptr) {
      this->root_ = new Node;
      this->root_->parent = nullptr;
      copy_node(this->root_, other.root_);
    }
    return *this;
  }

  // Move constructor
  AVLTree(AVLTree&& other) : root_(nullptr), size_(0) { this->swap(other); }

  // Operator equal move
  AVLTree& operator=(AVLTree&& other) {
    this->swap(other);
    return *this;
  }

  // Destructor
  virtual ~AVLTree() { this->clear(); }

  // ========================== *Tree Getter&Setters*====================

  // root_ Getter
  Node* GetRoot() const { return this->root_; }

  //  ========================== *Tree Modifiers* ==========================

  //  Insert element
  std::pair<iterator, bool> insert(const Key& value) {
    auto check = this->find(value);
    if (check.GetNode() != nullptr) {
      return std::make_pair(check, false);
    } else {
      auto root = this->root_;
      auto res = this->insert_tree(root, value);
      return std::make_pair(iterator(res, root_), true);
    }
  }

  //  Erase, delete element in tree

  void erase(iterator pos) {
    if (pos.GetNode() != nullptr) {
      Node* pos_node = pos.GetNode();
      if (pos_node->left && pos_node->right) {
        Node* tmp_min = find_min_in_right(pos_node->right);
        swap_key(pos_node, tmp_min);
        erase(iterator(tmp_min, root_));
      } else {
        if (pos_node->left || pos_node->right) {
          auto& direction = pos_node->left ? pos_node->left : pos_node->right;
          swap_node(pos_node, direction);
          direction = nullptr;
          this->size_--;
          if (pos_node->parent) {
            pos_node->parent->height--;
            fix_height(pos_node->parent);
            check_fix_bal_factor(pos_node->parent);
          }
        } else if (pos_node->left == nullptr && pos_node->right == nullptr) {
          if (pos_node->GetParent() != nullptr) {
            pos_node->GetParent()->height--;
            if (pos_node->parent->right == pos_node) {
              pos_node->parent->right = nullptr;
            } else {
              pos_node->parent->left = nullptr;
            }
            fix_height(pos_node->parent);
            check_fix_bal_factor(pos_node->parent);
          } else {
            root_ = nullptr;
          }
          delete pos_node;
          pos_node = nullptr;
          this->size_--;
        }
      }
    }
  }

  //  Merge two trees
  virtual void merge(AVLTree<Key, Comparator>& other) {
    AVLTree tmp(other);
    for (auto it = tmp.begin(); it != tmp.end(); it++) {
      if (this->contains(*it) == false) {
        insert_tree(this->root_, *it);
        auto iter_other = other.find(it.GetNode()->GetKey());
        other.erase(iter_other);
      }
    }
  }

  //  Swap two trees
  void swap(AVLTree<Key, Comparator>& other) {
    std::swap(this->root_, other.root_);
    std::swap(this->size_, other.size_);
  }

  //  Clear tree
  void clear() {
    if (this->root_) {
      clear_tree(this->root_);
      this->size_ = 0;
      this->root_ = nullptr;
    }
  }

  // ========================== *Tree Lookup* ==========================

  //  Check duplicates
  bool contains(const Key& key) const {
    auto check = find(key);
    if (check.GetNode() != nullptr) {
      return true;
    } else {
      return false;
    }
  }

  //  Find duplicate
  iterator find(const Key& key) {
    auto iter = this->begin();
    for (; iter != this->end(); iter++) {
      if (comparator_.equal(iter.GetNode()->GetKey(), key)) {
        return iter;
      }
    }
    return iter;
  }

  const_iterator find(const Key& key) const {
    auto iter = this->begin();
    for (; iter != this->end(); iter++) {
      if (comparator_.equal(iter.GetNode()->GetKey(), key)) {
        return iter;
      }
    }
    return iter;
  }

  // ========================== *Tree Capacity* ==========================

  //  Empty
  bool empty() const {
    if (this->GetRoot() == nullptr) {
      return true;
    } else {
      return false;
    }
  }

  //  Size
  size_t size() const { return this->size_; }

  size_t max_size() {
    return std::numeric_limits<size_t>::max() /
           (sizeof(typename AVLTree<Key, Comparator>::Node) + sizeof(Key));
  }

  // ========================== *Iterator* ==========================

  // Begin iterator
  iterator begin() {
    Node* node = this->GetRoot();
    if (node == nullptr) {
      return iterator(nullptr);
    }
    while (node->GetLeft() != nullptr) {
      node = node->GetLeft();
    }
    return iterator(node, root_);
  }

  // Begin iterator
  const_iterator begin() const {
    Node* node = this->GetRoot();
    if (node == nullptr) {
      return const_iterator(nullptr);
    }
    while (node->GetLeft() != nullptr) {
      node = node->GetLeft();
    }
    return const_iterator(node, root_);
  }

  //  End iterator
  iterator end() { return iterator(nullptr, root_); }

  //  End iterator
  const_iterator end() const { return const_iterator(nullptr, root_); }

  // ========================== *Bonus* ==========================

  //  Insert a few elements
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    for (auto element : {std::forward<Args>(args)...}) {
      result.push_back(insert(element));
    }
    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many() {
    return std::vector<std::pair<iterator, bool>>();
  }

  // ========================= *Help functions for testing*//==================

  void import(Node* node, Key* orig, int& i) const {
    if (node != nullptr) {
      orig[i] = *(node->key);
      i++;
      import(node->left, orig, i);
      import(node->right, orig, i);
    }
  }

  // ========================== *Support Functions* ==========================

 protected:
  //  Insert in tree's node
  Node* insert_tree(Node*& node, const Key key) {
    Node* res = nullptr;
    if (node == nullptr) {
      node = new Node(key);
      this->size_++;
      node->parent = nullptr;
      res = node;
      this->root_ = node;
    } else if (comparator_(*(node->key), key)) {
      InsertHelper(node->left, node, res, key);
    } else if (comparator_(key, *(node->key))) {
      InsertHelper(node->right, node, res, key);
    }
    fix_height(node);
    check_fix_bal_factor(node);
    if (!comparator_.equal(*(res->key), key)) {
      res = res->parent;
    }
    return res;
  }

  // Helping function for method "insert"
  void InsertHelper(Node*& node, Node* const node_parent, Node*& res,
                    const Key key) {
    if (node == nullptr) {
      node = new Node(key);
      this->size_++;
      node->parent = node_parent;
      res = node;
    } else {
      res = insert_tree(node, key);
    }
  }

 private:
  // Helping function for method "clear"
  void clear_tree(Node* node) {
    if (node != nullptr) {
      clear_tree(node->GetLeft());
      clear_tree(node->GetRight());
      delete node;
      node = nullptr;
    }
  }

  // Function for copy node 'b' to node 'a'
  void swap_node(Node* a, Node* b) {
    delete a->key;
    a->key = b->key;
    b->key = nullptr;
    a->left = b->left;
    a->right = b->right;
    delete b;
  }

  // Function for swap keys
  void swap_key(Node* a, Node* b) { std::swap(a->key, b->key); }

  // Function for finding minimal key in right subtree
  Node* find_min_in_right(Node* node) {
    return node->left ? find_min_in_right(node->left) : node;
  }

  // Function for check balance & check if it is nessiary
  void check_fix_bal_factor(Node* node) {
    int balance_factor = get_balance_factor(node);
    if (balance_factor > 1) {
      if (get_balance_factor(node->right) == -1) {
        rotate_right(node->right);
        rotate_left(node);
      } else {
        rotate_left(node);
      }
    } else if (balance_factor < -1) {
      if (get_balance_factor(node->left) == 1) {
        rotate_left(node->left);
        rotate_right(node);
      } else {
        rotate_right(node);
      }
    }
  }

  // Function for fixing node's height
  void fix_height(Node* node) {
    if (node != nullptr) {
      node->height =
          std::max(get_height(node->left), get_height(node->right)) + 1;
    }
  }

  // Function for node's right rotate
  void rotate_right(Node* node) {
    swap_key(node, node->left);
    Node* buffer = node->right;
    node->right = node->left;
    if (node->right != nullptr) node->right->parent = node;
    node->left = node->left->left;
    if (node->left != nullptr) node->left->parent = node;
    node->right->left = node->right->right;
    if (node->right->left != nullptr) node->right->left->parent = node->right;
    node->right->right = buffer;
    if (node->right->right != nullptr) node->right->right->parent = node->right;
    fix_height(node->right);
    fix_height(node);
  }

  // Function for node's left rotate
  void rotate_left(Node* node) {
    swap_key(node, node->right);
    Node* buffer = node->left;
    node->left = node->right;
    if (node->left != nullptr) node->left->parent = node;
    node->right = node->right->right;
    if (node->right != nullptr) node->right->parent = node;
    node->left->right = node->left->left;
    if (node->left->right != nullptr) node->left->right->parent = node->left;
    node->left->left = buffer;
    if (node->left->left != nullptr) node->left->left->parent = node->left;
    fix_height(node->left);
    fix_height(node);
  }

  // Function for getting node's height
  int get_height(Node* node) { return (node ? node->height : -1); }

  // Function for getting node's balance factor
  int get_balance_factor(Node* node) {
    return (node ? get_height(node->right) - get_height(node->left) : 0);
  }

  // Function for copy tree
  void copy_node(Node* first, Node* second) {
    if (second != nullptr) {
      first->key = new Key(*(second->key));
      first->height = second->height;
      if (second->left) {
        first->left = new Node;
        first->left->parent = first;
        copy_node(first->left, second->left);
      }
      if (second->right) {
        first->right = new Node;
        first->right->parent = first;
        copy_node(first->right, second->right);
      }
    }
  }
};
}  // namespace s21