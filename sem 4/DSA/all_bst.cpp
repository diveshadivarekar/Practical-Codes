#include <iostream>

using namespace std;

template<typename T>
class Stack{
    private:
        struct Node {
            T data;
            Node* next;
    
            Node(T data) : data(data), next(nullptr) {}
        };
    
        Node* top = nullptr;
    
    public:
        Stack() {}
    
        T pop(){
            if (top == nullptr) return T(-1);
            T data = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return data;
        }
    
        void push(T data){
            Node* temp = new Node(data);
            temp->next = top;
            top = temp;
        }

        bool isempty() {
            return top == nullptr;
        }
};

template<typename T>
class Queue{
    private:
        struct Node {
            T data;
            Node* next;

            Node(T data) : data(data), next(nullptr) {}
        };
        
        Node* front = nullptr;
        Node* rear = nullptr;
        
    public:
        Queue() {}
        
        T dequeue(){
            if (front == nullptr) return T(-1);
            T data = front->data;
            Node* temp = front;
            front = front->next;
            delete temp;
            if (front == nullptr) rear = nullptr;
            return data;
        }
        
        void enqueue(T data){
            if (rear == nullptr){
                rear = new Node(data);
                front = rear;
            }
            else {
                rear->next = new Node(data);
                rear = rear->next;
            }
        }

        bool isempty(){
            return front == nullptr;
        }
};

template<typename T>
class BST{
    private:
        struct Node {
            T data;
            Node* left;
            Node* right;
            Node(T data) : data(data), left(nullptr), right(nullptr) {}
        };

        Node* root = nullptr;
        
    public:
        BST(T data){
            root = new Node(data);
        }

        void insert(T data){
            Node* temp = root;
            while (true){
                if (data < temp->data){
                    if (temp->left == nullptr){
                        temp->left = new Node(data);
                        break;
                    } else {
                        temp = temp->left;
                    }
                } else {
                    if (temp->right == nullptr){
                        temp->right = new Node(data);
                        break;
                    } else {
                        temp = temp->right;
                    }
                }
            }
        }

        Node* get_root(){
            return root;
        }

        void inorder_recursive(Node* root){
            if (root == nullptr) return;
            inorder_recursive(root->left);
            std::cout << root->data << " ";
            inorder_recursive(root->right);
        }

        void postorder_recursive(Node* root){
            if (root == nullptr) return;
            postorder_recursive(root->left);
            postorder_recursive(root->right);
            std::cout << root->data << " ";
        }

        void preorder_recursive(Node* root){
            if (root == nullptr) return;
            std::cout << root->data << " ";
            preorder_recursive(root->left);
            preorder_recursive(root->right);
        }

        void inorder(){
            Stack<Node*> s;
            Node* current = root;

            while(current != nullptr || !s.isempty()){
                while (current != nullptr){
                    s.push(current);
                    current = current->left;
                }
                current = s.pop();
                std::cout << current->data << " ";
                current = current->right;
            }
        }

        void preorder(){
            Stack<Node*> s;
            s.push(root);

            while(!s.isempty()){
                Node* current = s.pop();
                std::cout << current->data << " ";

                if(current->right) s.push(current->right);
                if(current->left) s.push(current->left);
            }
        }

        void postorder(){
            Stack<Node*> s1,s2;
            s1.push(root);

            while(!s1.isempty()){
                Node* current = s1.pop();
                s2.push(current);

                if(current->left) s1.push(current->left);
                if(current->right) s1.push(current->right);
            }

            while(!s2.isempty()){
                std::cout << s2.pop()->data << " ";
            }
        }

        void bfs(){
            Queue<Node*> q;
            q.enqueue(root);
            while(!q.isempty()){
                Node* current = q.dequeue();
                std::cout << current->data << " ";
                if(current->left) q.enqueue(current->left);
                if(current->right) q.enqueue(current->right);
            }
        }

        friend Node* search_node(Node* node, T data){
            if (node == nullptr || node->data == data) return node;

            if (data > node->data){
                return search_node(node->right, data);
            }else{
                return search_node(node->left, data);
            }
        }

        friend int print_node(Node* node){
            if (node == nullptr) return -1;
            std::cout << "Node Data: " << node->data << std::endl;
            return 0;
        }
};


int main(){
    Stack<int> s;
    s.push(5);
    s.push(6);
    s.push(7);
    std::cout << "Popped element: " << s.pop() << std::endl;
    std::cout << "Popped element: " << s.pop() << std::endl;
    std::cout << std::endl;

    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    std::cout << "Dequeued element: " << q.dequeue() << std::endl;
    std::cout << "Dequeued element: " << q.dequeue() << std::endl;
    std::cout << std::endl;

    BST<int> bst(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);

    std::cout << "Inorder traversal: ";
    bst.inorder_recursive(bst.get_root());
    std::cout << std::endl;

    std::cout << "Postorder traversal: ";
    bst.postorder_recursive(bst.get_root());
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    bst.preorder_recursive(bst.get_root());
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "Inorder traversal (iterative): ";
    bst.inorder();
    std::cout << std::endl;

    std::cout << "Preorder traversal (iterative): ";
    bst.preorder();
    std::cout << std::endl;

    std::cout << "Postorder traversal (iterative): ";
    bst.postorder();
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "Breadth-first search traversal: ";
    bst.bfs();
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "Search node with value 4: ";
    int node_value = 4; // change this to respective search value
    if (print_node(search_node(bst.get_root(),node_value)) < 0){
        std::cout << "Node not found." << std::endl;
    }else{
        std::cout << "Node found." << std::endl;
    }

    std::cout << std::endl;

    print_node(bst.get_root());

    return 0;
}