#include <iostream>
#include <vector>
#include <stdio.h>
#include <array>
using namespace std;
enum Color
{
    BLACK,
    RED,
    LEAF
};
struct Node
{
    int data = 0;
    Node *parent = NULL;
    Node *left = NULL;
    Node *right = NULL;
    Color color;
    Node(int data = 0, Color color = RED)
    {
        this->data = data;
        this->color = color;
        if (color == RED || color == BLACK)
        {
            right = new Node(0, LEAF);
            left = new Node(0, LEAF);
            right->parent = this;
            left->parent = this;
            this->right = right;
            this->left = left;
        }
    }
};

class Red_Black_Tree
{
public:
    Node root;
    Red_Black_Tree(int data) : root(data, BLACK) {}

    void insert(int data)
    {
        Node *trace = &this->root;
        Node *temp;
        bool isleft = false;
        while (true)
        {
            if (data < trace->data)
            {
                temp = trace;
                if (trace->color == LEAF)
                {
                    isleft = true;
                    break;
                }
                trace = trace->left;
                trace->parent = temp;
            }
            else if (data > trace->data)
            {
                temp = trace;
                if (trace->color == LEAF)
                {
                    isleft = false;
                    break;
                }
                trace = trace->right;
                trace->parent = temp;
            }
            else
            {
                cout << "Data already exists" << endl;
                return;
            }
        }
        Node *new_node = new Node(data, RED);
        if (isleft)
        {
            temp->left = new_node;
        }
        else
        {
            temp->right = new_node;
        }
        new_node->parent = temp;
        if (temp->color == RED)
        {
            double_red(*new_node);
        }
    }
    array<Node *, 3> rank_of_three(Node *a, Node *b, Node *c)
    {
        if (a->data < b->data && b->data < c->data)
        {
            return {c, b, a};
        }
        else if (a->data < c->data && c->data < b->data)
        {
            return {b, c, a};
        }
        else if (b->data < a->data && a->data < c->data)
        {
            return {c, a, b};
        }
        else if (b->data < c->data && c->data < a->data)
        {
            return {a, b, c};
        }
        else if (c->data < a->data && a->data < b->data)
        {
            return {b, a, c};
        }
    }

    void double_red(Node node)
    {
        Node *uncle;
        if (node.parent->parent->left == node.parent)
        {
            uncle = node.parent->parent->right;
        }
        else
        {
            uncle = node.parent->parent->left;
        }
        if (node.parent->color == true && uncle->color == true)
        { // change color
            node.parent->color = BLACK;
            uncle->color = BLACK;
            if (node.parent->parent->parent == NULL)
                return;
            node.parent->parent->color = RED;
            if (node.parent->parent->parent->color == RED)
            {
                double_red(*node.parent->parent);
            }
            else
            { // change structure, color
                array<Node *, 3> rank = rank_of_three(node.parent, &node, uncle);
                rank[0]->parent = node.parent->parent;
                rank[1]->parent = rank[0];
                rank[2]->parent = rank[0];
                rank[0]->left = rank[1];
                rank[0]->right = rank[2];
                rank[0]->color = BLACK;
                rank[1]->color = RED;
                rank[2]->color = RED;
            }
        }
    }
    void find_node(int data)
    {
        Node *trace = &this->root;
        Node *temp;
        int i = 1;

        while (true)
        {
            cout << i << "Node" << trace->color << trace->data << endl;
            if (trace->color == LEAF)
            {
                cout << "Data not found" << endl;
                return;
            }
            else if (data > trace->data)
            {
                trace = trace->right;
            }
            else if (data < trace->data)
            {
                trace = trace->left;
            }
            else
            {
                cout << data << "Data found" << endl;
            }
            i++;
        }
    }
};

int main()
{
    int data = 0;
    cout << "Enter the data of the root node: ";
    cin >> data;
    int cmd = 0;
    Red_Black_Tree RedBlackTree = Red_Black_Tree(data);
    while (true)
    {
        cout << "0: insert, 1: find, 2: exit" << endl;
        cin >> cmd;
        if (cmd == 0)
        {
            cin >> data;
            RedBlackTree.insert(data);
        }
        else if (cmd == 1)
        {
            cin >> data;
            RedBlackTree.find_node(data);
        }
        else if (cmd == 2)
        {
            break;
        }
    }
    return 0;
}
