#include <stdlib.h>
#include <stdio.h>
#include <iostream>



using namespace std;




class Container {



public:
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;
    virtual void print() = 0;
    virtual ~Container() = default;
};
class Tree: public Container {
public:
    struct Leave{
    public:
        int value;
    	private:
    	int depth;
        Leave *head;
        friend std::ostream &operator<<(std::ostream &os, const Leave &leave){};
        Leave *left;
        Leave *right;
        Leave(int value, Leave *head): value(value), head(head), depth(0), left(nullptr), right(nullptr) {}
        void Clear(Leave *head);
        void CalcDepth(){
        	int ldepth = left != nullptr? left->depth : 0;
    		int rdepth = right != nullptr ? right->depth : 0;
    		depth = (ldepth > rdepth ? ldepth : rdepth) + 1;
        };
        Leave *LittleLeftRotate(){
        	Leave *right = this->right;
    		this->right = right->left;
    		right->left = this;
    		right->head = this->head;
    		this->head = right;
    		CalcDepth();
    		right->CalcDepth();
    		return right;
        };
        Leave *LittleRightRotate(){
        	Leave *left = this->left;
    		this->left = left->right;
    		left->right = this;
    		left->head = this->head;
    		this->head = left;
    		CalcDepth();
    		left->CalcDepth();
    		return left;
        };
        Leave *BigLeftRotate(){
        	right = right->LittleRightRotate();
    		return LittleLeftRotate();
        };
        Leave *BigRightRotate(){
        	left = left->LittleLeftRotate();
    		return LittleRightRotate();
        };
        
        
        
        
        Leave *Insert(int new_value)
        {
        	if (new_value == this->value) 
        	{
    			return this;
    		} 
    		else if (new_value > this->value) 
    		{
        		if (right == nullptr) 
        		{
            		right = new Leave{new_value, this};
        		}
        		else 
        		{
            		right = right->Insert(new_value);
    			};
    		}
    		else
    		{
        		if (left == nullptr) 
        		{
            		left = new Leave{new_value, this};
        		} 
        		else 
        		{
            		left = left->Insert(new_value);
        		}
    		}
    	return Balancing(this);
        };
        
        
        Leave *Balancing(Leave *head)
        {
        	int left_depth = head->left != nullptr ? head->left->depth : 0;
    		int right_depth = head->right != nullptr ? head->right->depth : 0;
    		int balance = right_depth - left_depth;
    		if (balance == -2) 
    		{
        		int ll_depth = head->left->left ? head->left->left->depth : 0;
        		int lr_depth = head->left->right ? head->left->right->depth : 0;
        		if (lr_depth - ll_depth > 0) 
        		{
            		head = head->BigRightRotate();
        		} 
        		else 
        		{
            		head = head->LittleRightRotate();
        		}

    		} 
    		else if (balance == 2)
    		{
        		int rl_depth = head->right->left ? head->right->left->depth : 0;
        		int rr_depth = head->right->right ? head->right->right->depth : 0;
        		if (rr_depth - rl_depth < 0) 
        		{
            		head = head->BigLeftRotate();
        		}
        		else 
        		{
            		head = head->LittleLeftRotate();
        		}
    		} 
    		else 
    		{
    			head->CalcDepth();
    		}
    		return head;    	
        };
        
        
        
        
        const Leave *Find(const int value_to_find)
        {
        	 if (value == value_to_find) 
        	 {
        		return head;
    		 }		
    		 if (value_to_find < value) 
    		 {
        		if (left == nullptr) 
        		{
            		return nullptr;
        		}
        		return left->Find(value_to_find);
			 }
    		 if (right == nullptr) 
    		 {
        		 return nullptr;
    		 }
    		 return right->Find(value_to_find);
        };
        
        
        
        
        Leave *Remove(Leave *head, int value_to_remove)
        {
        	if (head == nullptr) 
        	{
        		return nullptr;
    		}
    		if (head->value != value_to_remove) 
    		{
        		if (value_to_remove > head->value) 
        		{
            		head->right = Remove(head->right, value_to_remove);
        		}
        		else
        		{
            		head->left = Remove(head->left, value_to_remove);
        		}
    		}
    		else
    		{
        		if (head->left == nullptr && head->right == nullptr) 
        		{
            		delete head;
            		return nullptr;
        		}
        		Leave *element_to_swap = head;
        		int left_depth = element_to_swap->left != nullptr ? element_to_swap->left->depth : 0;
        		int right_depth = element_to_swap->right != nullptr ? element_to_swap->right->depth : 0;
        		if (left_depth > right_depth) 
        		{
            		for (element_to_swap = head->left;
                		element_to_swap->right != nullptr; element_to_swap = element_to_swap->right);

        		} 
        		else 
        		{
            		for (element_to_swap = head->right;
                		element_to_swap->left != nullptr; element_to_swap = element_to_swap->left);
        		}
        		int c = element_to_swap->value;
        		element_to_swap->value = head->value;
        		head->value = c;
        		if (left_depth > right_depth) 
        		{
            		head->left =  Remove(head->left, value_to_remove);
        		}
        		else
        		{
            		head->right =  Remove(head->right, value_to_remove);
        		}
    		}
    		return Balancing(head);
        };
        
        friend Tree;
    };
    Tree() : root(nullptr) {};
    void del (Leave* n)
    {
    	if (n->left!=nullptr)
    	{
    	
    		del(n->left);
    	}
    	if (n->right!=nullptr)
    	{
    		del(n->right);
    	}
    	delete n;
    }
    
    ~Tree() override
    {
    	del(root);
    };
    const Leave *Find(const int value_to_find){};
    void insert(int new_value) override{
    	if (root != nullptr) 
    	{
        	root = root->Insert(new_value);
    	}
    	else 
    	{
        root = new Leave{new_value, nullptr};
    	}
    };
    bool exists(int value) override
    {
    	return root->Find(value) != nullptr;
    };
    void remove(int value_to_remove) override
    {
    	root = root->Remove(root, value_to_remove);
    };
    void pr(Leave* n)
    {
    	cout<< n->value;
    	cout<< "  ";
    	if (n->left!=nullptr)
    	{
    		pr(n->left);
    	}
    	if (n->right!=nullptr)
    	{
    		pr(n->right);
    	}
    }
    void print() override{
    	pr(root);
    };
    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);
private:
    Leave *root;
};









int main()

{
    Tree c;
    for(int i = 1; i < 13; i++)
        c.insert(i*i);
        printf(" creation:\n");
    c.print();
   if(c.exists(36))
        cout << "Search for value 25: found" << endl;
    
    c.remove(25);
    cout << " deletion " << endl;
    c.print();
    return 0;
}