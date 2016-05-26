/*

  AVLTree.hpp

*/



#ifndef __AVL_TREE__HPP__
#define __AVL_TREE__HPP__

#if !defined(__cplusplus) || (__cplusplus < 201103L)
#error "C++11 support is required."
#endif

#include <cstdint>
#include <utility>
#include <iterator>
#include <functional>
#include <iostream>





template<class key_type,
         class mapped_type,
         class key_compare = std::less<key_type>
         >
class AVLTree {

	// Internal data structure.
	struct Node {

		std::pair<const key_type, mapped_type> Mapping;
		Node*  Parent;
		Node*  Left;
		Node*  Right;
		size_t Height;

		// Construct by providing arguments.
		template<class K, class D>
		Node(K&& InitKey,
		     D&& InitData,
		     Node* InitParent,
		     Node* InitLeft,
		     Node* InitRight,
		     size_t InitHeight):
			Mapping( std::forward<K>(InitKey), std::forward<D>(InitData) ),
			Parent( InitParent ),
			Left( InitLeft ),
			Right( InitRight ),
			Height( InitHeight ) {
			;
			}

		// Construct a new tree from an existing tree.
		Node(const Node* Tree, Node* InitParent):
			Mapping( Tree->Mapping ),
			Parent( InitParent ),
			Left( (Tree->Left != nullptr) ? (new Node(Tree->Left, this)) : nullptr ),
			Right( (Tree->Right != nullptr) ? (new Node(Tree->Right, this)) : nullptr ),
			Height( Tree->Height ) {
			;
			}

		~Node() {

			delete Left;
			delete Right;

			}

		static size_t HeightOf(Node* Tree) noexcept {

			return (Tree != nullptr) ? (Tree->Height) : 0;

			};

		template<class K, class D>
		static std::pair<Node*, bool> Insert(Node** PtrToThisNode, Node* Parent, K&& KeyToInsert, D&& DataToInsert, key_compare& );

		// Returns new root of child tree.
		static Node* RightRotate(Node* ) noexcept;
		static Node* LeftRotate(Node* ) noexcept;
		static Node* Begin(Node* ) noexcept;
		static Node* Find(Node* Tree, const key_type& KeyToFind, key_compare& );

		static void Dump(Node* CurrentNode) {

			if( CurrentNode == nullptr ){

				std::cout << "()";
				return;

				}

			std::cout << "((" << (CurrentNode->Mapping).first << ": " << (CurrentNode->Mapping).second << "), ";
			Dump(CurrentNode->Left);
			std::cout << ", ";
			Dump(CurrentNode->Right);
			std::cout << ')';

			}

		};

	Node* Root;
	key_compare Comp;


	// Public stuff.
	public:

	class iterator : public std::iterator<std::bidirectional_iterator_tag, decltype(Node::Mapping)> {

		Node* CurrentNode;

		// This can only be used in member functions of AVLTree.
		iterator(Node* InitPtr):
			CurrentNode( InitPtr ) {
			;
			}

		// It enables AVLTree to call the private constructor.
		friend class AVLTree;

		public:

		iterator():
			CurrentNode( nullptr ) {
			;
			}

		iterator(const iterator& ) = default;
		~iterator() = default;
		iterator& operator=(const iterator& ) = default;

		decltype(Node::Mapping)& operator*(void) const noexcept {

			return (CurrentNode->Mapping);

			}

		decltype(Node::Mapping)* operator->(void) const noexcept {

			return &(CurrentNode->Mapping);

			}

		iterator& operator++(void);
		iterator& operator--(void);

		iterator operator++(int) {

			iterator It(*this);

			++(*this);

			return It;

			}

		iterator operator--(int) {

			iterator It(*this);

			--(*this);

			return It;

			}

		bool operator==(const iterator& RHS) const noexcept {

			return ( (this->CurrentNode) == RHS.CurrentNode );

			}

		bool operator!=(const iterator& RHS) const noexcept {

			return ( (this->CurrentNode) != RHS.CurrentNode );

			}

		};

	// Const iterator.
	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const decltype(Node::Mapping)> {

		iterator It;

		public:

		const_iterator():
			It( nullptr ) {
			;
			}

		const_iterator(const iterator& RHS):
			It( RHS ) {
			;
			}

		const_iterator(const const_iterator& ) = default;
		~const_iterator() = default;
		const_iterator& operator=(const const_iterator& ) = default;

		const decltype(Node::Mapping)& operator*(void) const noexcept {

			return *It;

			}

		const decltype(Node::Mapping)* operator->(void) const noexcept {

			return &(*It);

			}


		const_iterator& operator++(void) {

			++It;

			return (*this);

			}

		const_iterator& operator--(void) {

			--It;

			return (*this);

			}

		const_iterator operator++(int) {

			return (It++);

			}

		const_iterator operator--(int) {

			return (It--);

			}

		bool operator==(const const_iterator& RHS) const noexcept {

			return ( It == RHS.It );

			}

		bool operator!=(const const_iterator& RHS) const noexcept {

			return ( It != RHS.It );

			}

		};


	AVLTree():
		Root(nullptr),
		Comp() {
		;
		}

	AVLTree(const AVLTree& RHS):
		Root( (RHS.Root != nullptr) ? new Node(RHS.Root, nullptr) : 0 ),
		Comp( RHS.Comp ) {
		;
		}

	AVLTree(AVLTree&& RHS):
		Root( RHS.Root ),
		Comp( std::move(RHS.Comp) ){

		RHS.Root = nullptr;

		}

	~AVLTree() {

		delete Root;

		}

	iterator begin(void) {

		return Node::Begin(Root);

		}

	iterator end(void) {

		return nullptr;

		}

	const_iterator begin(void) const {

		return iterator(Node::Begin(Root));

		}

	const_iterator end(void) const {

		return iterator(nullptr);

		}

	iterator find(const key_type& KeyToFind) {

		return Node::Find(Root, KeyToFind, Comp);

		}

	const_iterator find(const key_type& KeyToFind) const {

		return iterator(Node::Find(Root, KeyToFind, Comp));

		}

	template<class K, class D>
	std::pair<iterator, bool> insert(K&& KeyToInsert, D&& DataToInsert);

	AVLTree& operator=(const AVLTree& RHS) {

		if( this != &RHS ) {

			delete Root;

			if( RHS.Root != nullptr )
				Root = new Node(RHS.Root, nullptr);
			else
				Root = nullptr;

			Comp = RHS.Comp;

			}

		return *this;

		}

	template<class K>
	mapped_type& operator[](K&& Index) {

		auto Result = insert(std::forward<K>(Index), mapped_type());
		return (Result.first)->second;

		}

	AVLTree& operator=(AVLTree&& RHS) {

		if( this != &RHS ) {

			delete this->Root;
			this->Root = RHS.Root;
			RHS.Root = nullptr;
			Comp = std::move( RHS.Comp );

			}

		return *this;

		}

	size_t GetHeight(void) const noexcept {

		if( Root == nullptr )
			return 0;

		return Root->Height;

		}

	void Dump(void) const {

		Node::Dump(Root);
		std::cout << std::endl;

		}

	};





template<class key_type,
         class mapped_type,
         class key_compare
         >
auto AVLTree<key_type, mapped_type, key_compare>::iterator::operator++(void) -> iterator& {
	//std::cout<<"+"<<CurrentNode->Height<<std::endl;
	if( CurrentNode == nullptr )
		return (*this);
	else{
		if(CurrentNode->Right==nullptr){
			while(1){
				if(CurrentNode->Parent==nullptr){
					CurrentNode=nullptr;
					break;
				}else {
					if(CurrentNode->Parent->Right==CurrentNode)CurrentNode=CurrentNode->Parent;
					else {
						CurrentNode=CurrentNode->Parent;
						break;
					}
				}
			}
		}else{
			CurrentNode=CurrentNode->Right;
			while(1){
				if(CurrentNode->Left!=nullptr)CurrentNode=CurrentNode->Left;
				else break;
			}
		}
	}
	// TODO: Find the next node in an in-order manner.
	//
	return (*this);

}


template<class key_type,
         class mapped_type,
         class key_compare
         >
auto AVLTree<key_type, mapped_type, key_compare>::iterator::operator--(void) -> iterator& {
	//std::cout<<"-"<<CurrentNode->Height<<std::endl;
	if( CurrentNode == nullptr )
		return (*this);
	else{
		if(CurrentNode->Left==nullptr){
			while(1){
				if(CurrentNode->Parent==nullptr){
					CurrentNode=nullptr;
					break;
				}else {
					if(CurrentNode->Parent->Left==CurrentNode)CurrentNode=CurrentNode->Parent;
					else {
						CurrentNode=CurrentNode->Parent;
						break;
					}
				}
			}
		}else{
			CurrentNode=CurrentNode->Left;
			while(1){
				if(CurrentNode->Right!=nullptr)CurrentNode=CurrentNode->Right;
				else break;
			}
		}
	}
	// TODO: Find the previous node in an in-order manner.

	return (*this);
}



template<class key_type,
         class mapped_type,
         class key_compare
         >
auto AVLTree<key_type, mapped_type, key_compare>::Node::Begin(Node* CurrentNode) noexcept -> Node* {

		if( CurrentNode == nullptr )
			return CurrentNode;

		Node* Next;

		while( (Next = CurrentNode->Left) != nullptr )
			CurrentNode = Next;

		return CurrentNode;

		}



template<class key_type,
         class mapped_type,
         class key_compare
         >
auto AVLTree<key_type, mapped_type, key_compare>::Node::Find(Node* Tree, const key_type& KeyToFind, key_compare& Comp) -> Node* {
	//std::cout<<"f"<<std::endl;
	Node* CurrentNode = Tree;

	// TODO: Use Comp to find where it located.
	//       You may want to take a look of the implementation of Insert.
	while(1){
		/*
		if(Comp(KeyToFind,(CurrentNode->Mappint).first)){
			if(CurrentNode->Left!=nullptr)CurrentNode=CurrentNode->Left;
			else{
				//CurrentNode=CurrentNode->Left;
				break;
			}
		}else if(CurrentNode->Right!=nullptr)CurrentNode=CurrentNode->Right;
		else{
			//CurrentNode=CurrentNode->Right;
			break;
		}
		*/
		if(CurrentNode==nullptr) break;
		else if(Comp((CurrentNode->Mapping).first,KeyToFind))
			CurrentNode=CurrentNode->Right;
		else if(Comp(KeyToFind,(CurrentNode->Mapping).first))
			CurrentNode=CurrentNode->Left;
		else break;
	}
	return CurrentNode;

}



template<class key_type,
         class mapped_type,
         class key_compare
         >
template<class K, class D>
auto AVLTree<key_type, mapped_type, key_compare>::insert(K&& KeyToInsert, D&& DataToInsert) -> std::pair<iterator, bool> {

	auto Result = Node::Insert(&Root,
	                           nullptr,
	                           std::forward<K>(KeyToInsert),
	                           std::forward<D>(DataToInsert),
	                           Comp);

	return std::pair<iterator, bool>(Result.first, Result.second);

	}



template<class key_type,
         class mapped_type,
         class key_compare
         >
template<class K, class D>
auto AVLTree<key_type, mapped_type, key_compare>::Node::Insert(Node** PtrToThisNode, Node* Parent, K&& KeyToInsert, D&& DataToInsert, key_compare& Comp) -> std::pair<Node*, bool> {

	Node* ThisNode = *PtrToThisNode;

	// We found where to insert the data.
	if( ThisNode == nullptr ) {

		ThisNode = new Node(std::forward<K>(KeyToInsert),
		                    std::forward<D>(DataToInsert),
		                    Parent,
		                    nullptr,
		                    nullptr,
		                    1
		                    );

		// Fix parent's pointer to the new node and return where it's inserted.
		return std::pair<Node*, bool>(*PtrToThisNode = ThisNode, true);

		}

	std::pair<Node*, bool> InsertResult;

	// If the data shall be placed in left child.
	if( Comp(KeyToInsert, (ThisNode->Mapping).first) ) {

		InsertResult = Insert(&(ThisNode->Left),
		                      ThisNode,
		                      std::forward<K>(KeyToInsert),
		                      std::forward<D>(DataToInsert),
		                      Comp);

		size_t LeftHeight = Node::HeightOf(ThisNode->Left);
		size_t RightHeight = Node::HeightOf(ThisNode->Right);

		// If left child is higher.
		if( LeftHeight >= RightHeight + 2 ) {

			Node* LeftNode = ThisNode->Left;

			if( Node::HeightOf(LeftNode->Left) < Node::HeightOf(LeftNode->Right) )
				ThisNode->Left = LeftNode = LeftRotate(LeftNode);

			*PtrToThisNode = ThisNode = RightRotate(ThisNode);

			}
		// Already balanced. No need to rotate.
		else
			ThisNode->Height = 1 + std::max(LeftHeight, RightHeight);

		}
	// If the data shall be placed in right tree.
	else if( Comp((ThisNode->Mapping).first, KeyToInsert) ) {

		InsertResult = Insert(&(ThisNode->Right),
		                      ThisNode,
		                      std::forward<K>(KeyToInsert),
		                      std::forward<D>(DataToInsert),
		                      Comp);

		size_t LeftHeight = Node::HeightOf(ThisNode->Left);
		size_t RightHeight = Node::HeightOf(ThisNode->Right);

		// If right child is higher.
		if( RightHeight >= LeftHeight + 2 ){

			Node* RightNode = ThisNode->Right;

			if( Node::HeightOf(RightNode->Left) > Node::HeightOf(RightNode->Right) )
				ThisNode->Right = RightNode = RightRotate(RightNode);

			*PtrToThisNode = ThisNode = LeftRotate(ThisNode);

			}
		// Already balanced. No need to rotate.
		else
			ThisNode->Height = 1 + std::max(LeftHeight, RightHeight);

		}
	// Found.
	else {

		InsertResult.first = ThisNode;
		InsertResult.second = false;

		}

	return InsertResult;

	}



template<class key_type,
         class mapped_type,
         class key_compare
         >
auto AVLTree<key_type, mapped_type, key_compare>::Node::LeftRotate(Node* ThisNode) noexcept -> Node* {
  	//std::cout<<"lr"<<std::endl;
	// TODO: Right rotate the tree and return the new root.i
	//       The height of modified trees should also be fixed accordingly.
	if(ThisNode->Right==nullptr)return ThisNode;
	/* if(ThisNode->Parent!=nullptr)ThisNode->Parent->Right=ThisNode->Right;
	ThisNode->Right->Parent=ThisNode->Parent;
	ThisNode->Parent=ThisNode->Right;
	ThisNode->Right=ThisNode->Parent->Left;
	if(ThisNode->Right!=nullptr)ThisNode->Right->Parent=ThisNode;
	ThisNode->Parent->Left=ThisNode;
	ThisNode=ThisNode->Parent;
	*/
	Node* p=ThisNode->Parent,*t=ThisNode,*r=ThisNode->Right,*l=ThisNode->Right->Left;
	if(p!=nullptr&&p->Right==t)p->Right=r;
	else if(p!=nullptr)p->Left=r;
	r->Parent=p;
	t->Parent=r;
	r->Left=t;
	t->Right=l;
	if(l!=nullptr)l->Parent=t;
	ThisNode=r;
	//r->Height=max(HeightOf(),)
	if(ThisNode->Left!=nullptr){
		if(ThisNode->Left->Left!=nullptr){
			if(ThisNode->Left->Right!=nullptr)ThisNode->Left->Height=ThisNode->Left->Left->Height>ThisNode->Left->Right->Height?ThisNode->Left->Left->Height+1:ThisNode->Left->Right->Height+1;
			else ThisNode->Left->Height=ThisNode->Left->Left->Height+1;
			if(ThisNode->Right!=nullptr)ThisNode->Height=ThisNode->Left->Height>ThisNode->Right->Height?ThisNode->Left->Height+1:ThisNode->Right->Height+1;
			else ThisNode->Height=ThisNode->Left->Height+1;
		}else{
			if(ThisNode->Left->Right!=nullptr)ThisNode->Left->Height=ThisNode->Left->Right->Height+1;
			else ThisNode->Left->Height=1;
			if(ThisNode->Right!=nullptr)ThisNode->Height=ThisNode->Left->Height>ThisNode->Right->Height?ThisNode->Left->Height+1:ThisNode->Right->Height+1;
			else ThisNode->Height=ThisNode->Left->Height+1;

		}

	}
	//ThisNode->Left->Height=ThisNode->Left->Left->Height>ThisNode->Left->Right->Height?ThisNode->Left->Left->Height+1:ThisNode->Left->Right->Height+1;
	//ThisNode->Height=ThisNode->Left->Height>ThisNode->Right->Height?ThisNode->Left->Height+1:ThisNode->Right->Height+1;
	return ThisNode;

	}



template<class key_type,
         class mapped_type,
         class key_compare
         >
auto AVLTree<key_type, mapped_type, key_compare>::Node::RightRotate(Node* ThisNode) noexcept -> Node* {
	// std::cout<<"rr"<<std::endl;
	// TODO: Left rotate the tree and return the new root.
	//       The height of modified trees should also be fixed accordingly.
	if(ThisNode->Left==nullptr)return ThisNode;
	/*if(ThisNode->Parent!=nullptr)ThisNode->Parent->Left=ThisNode->Left;
	ThisNode->Left->Parent=ThisNode->Parent;
	ThisNode->Parent=ThisNode->Left;
	ThisNode->Left=ThisNode->Parent->Right;
	if(ThisNode->Left!=nullptr)ThisNode->Left->Parent=ThisNode;
	ThisNode->Parent->Right=ThisNode;
	ThisNode=ThisNode->Parent;
	*/

	Node* p=ThisNode->Parent,*t=ThisNode,*r=ThisNode->Left,*l=ThisNode->Left->Right;
	if(p!=nullptr&&p->Right==t)p->Right=r;
	else if(p!=nullptr)p->Left=r;
	r->Parent=p;
	t->Parent=r;
	r->Right=t;
	t->Left=l;
	if(l!=nullptr)l->Parent=t;
	ThisNode=r;

	if(ThisNode->Right!=nullptr){
		if(ThisNode->Right->Right!=nullptr){
			if(ThisNode->Right->Left!=nullptr)ThisNode->Right->Height=ThisNode->Right->Right->Height>ThisNode->Right->Left->Height?ThisNode->Right->Right->Height+1:ThisNode->Right->Left->Height+1;
			else ThisNode->Right->Height=ThisNode->Right->Right->Height+1;
			if(ThisNode->Left!=nullptr)ThisNode->Height=ThisNode->Right->Height>ThisNode->Left->Height?ThisNode->Right->Height+1:ThisNode->Left->Height+1;
			else ThisNode->Height=ThisNode->Right->Height+1;
		}else{
			if(ThisNode->Right->Left!=nullptr)ThisNode->Right->Height=ThisNode->Right->Left->Height+1;
			else ThisNode->Right->Height=1;
			if(ThisNode->Left!=nullptr)ThisNode->Height=ThisNode->Right->Height>ThisNode->Left->Height?ThisNode->Right->Height+1:ThisNode->Left->Height+1;
			else ThisNode->Height=ThisNode->Right->Height+1;
		}
	}
	//ThisNode->Right->Height=ThisNode->Right->Right->Height>ThisNode->Right->Left->Height?ThisNode->Right->Right->Height+1:ThisNode->Right->Left->Height+1;
	//ThisNode->Height=ThisNode->Right->Height>ThisNode->Left->Height?ThisNode->Right->Height+1:ThisNode->Left->Height+1;

	return ThisNode;

	}





#endif
