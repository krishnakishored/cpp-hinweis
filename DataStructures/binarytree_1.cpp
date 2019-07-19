// https://thispointer.com/binary-tree-traversal-with-strategy-design-pattern-and-open-closed-principle/
// TASK        =    BINARY TREE TRAVERSAL     +    ACTION ON NODE

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STACK
#define STACK
#include<stack>
#endif

using std::stack;
using std::cout;
using std::endl;

/*
In this combination of BINARY TREE TRAVERSAL and ACTION, the ACTION remains open for extension but BINARY TREE TRAVERSAL remains closed for modification. 
Thus it fit exactly with the “open-closed principle” i.e. Software entities like classes, modules and functions should be open for extension but closed for modifications. 
*/

/*
Intent of  strategy design pattern: 
“Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from the clients that use it.” 
 
Here in our example Strategy is NodeVisitor and BTTraversal is the algorithm that uses this strategy.

Based on the concrete implementation of Strategy result of BTTraversal algorithm will vary. 
*/

typedef struct node
{
    int value;
    node *pLeft;
    node *pRight;
    node(int val)
    {
        value = val;
        pLeft = NULL;
        pRight = NULL;
    }
} node;

node *createTree(int left, int val, int right)
{
    node *pNode = new node(val);
    pNode->pLeft = new node(left);
    pNode->pRight = new node(right);
    return pNode;
}

class NodeVisitor;
class DisplayVisitor;

// Base Class : NodeVisitor It Specifies the signature of Strategy i.e. action to be taken on each node.
class NodeVisitor
{
  public:
    virtual void beforeVisitingLeftChild(node *pNode) {}
    virtual void beforeVisitingRightChild(node *pNode) {}
    virtual void afterVisitingLeftChild(node *pNode) {}
    virtual void afterVisitingRightChild(node *pNode) {}
    virtual void visit(node *pNode) = 0;
};

//Action : It just displays the node on console.
class DisplayVisitor : public NodeVisitor
{
  public:
    void visit(node *pNode)
    {
        std::cout << pNode->value << "  ";
    }
};

// Action : It displays the expression on console.
class ExpressionVisitor : public NodeVisitor
{
  public:
    void beforeVisitingLeftChild(node *pNode)
    {
        std::cout << "( ";
    }
    void afterVisitingRightChild(node *pNode)
    {
        std::cout << ") ";
    }
    void visit(node *pNode)
    {
        if (pNode->value == '+')
            std::cout << "+ ";
        else if (pNode->value == '-')
            std::cout << "- ";
        else if (pNode->value == '*')
            std::cout << "* ";
        else
            std::cout << pNode->value << " ";
    }
};

class MirrorCreator : public NodeVisitor
{
  public:
    void visit(node *pNode)
    {
        node *pTemp = pNode->pLeft;
        pNode->pLeft = pNode->pRight;
        pNode->pRight = pTemp;
    }
};

// Action : It just counts each visiting node.
class CountingVisitor : public NodeVisitor
{
    int count;

  public:
    CountingVisitor()
    {
        count = 0;
    }
    void visit(node *pNode)
    {
        count++; //check if not null???
    }
    int getCount()
    {
        return count;
    }
};

/*
Base Class : BTTraversal -  This class acts as the base class of Traversal Algorithms. 
*/
class BTTraversal
{
    NodeVisitor *mPNodeVisitor;

  public:
    BTTraversal()
    {
        mPNodeVisitor = new DisplayVisitor();
    }

    // It contains a pure virtual function traverse that accepts a pointer of NodeVisitor class.
    virtual void traverse(node *pNode, NodeVisitor *pNodeVisitor) = 0;
    // Its implementation in derived classes will use this NodeVisitor pointer as a strategy to visit each node.
    // Based on the strategy (NodeVisitor * ) passed inside the traverse function result of traversal algorithm will vary.

    void traverse(node *pNode)
    {
        traverse(pNode, mPNodeVisitor);
    }
};



// Derived Class : PostOrderTraversal Specifies the Post-Order Binary Tree Traversal
class PostOrderTraversal : public BTTraversal
{
  public:
    void traverse(node *pNode, NodeVisitor *pNodeVisitor)
    {
        if (pNode == NULL)
            return;

        pNodeVisitor->beforeVisitingLeftChild(pNode);
        traverse(pNode->pLeft, pNodeVisitor);
        pNodeVisitor->afterVisitingLeftChild(pNode);

        pNodeVisitor->beforeVisitingRightChild(pNode);
        traverse(pNode->pRight, pNodeVisitor);
        pNodeVisitor->afterVisitingRightChild(pNode);

        pNodeVisitor->visit(pNode);
    }
};

// Derived Class : InOrderTraversal Specifies the In-Order Binary Tree Traversal
class InOrderTraversal : public BTTraversal
{
  public:
    void traverse(node *pNode, NodeVisitor *pNodeVisitor)
    {
        if (pNode == NULL)
            return;

        pNodeVisitor->beforeVisitingLeftChild(pNode);
        traverse(pNode->pLeft, pNodeVisitor);
        pNodeVisitor->afterVisitingLeftChild(pNode);

        pNodeVisitor->visit(pNode);

        pNodeVisitor->beforeVisitingRightChild(pNode);
        traverse(pNode->pRight, pNodeVisitor);
        pNodeVisitor->afterVisitingRightChild(pNode);
    }
};

// Derived Class : PreOrderTraversal Specifies the Pre-Order Binary Tree Traversal
class PreOrderTraversal : public BTTraversal
{
  public:
    void traverse(node *pNode, NodeVisitor *pNodeVisitor)
    {
        if (nullptr == pNode)
            return;

        pNodeVisitor->visit(pNode);

        pNodeVisitor->beforeVisitingLeftChild(pNode);
        traverse(pNode->pLeft, pNodeVisitor);
        pNodeVisitor->afterVisitingLeftChild(pNode);

        pNodeVisitor->beforeVisitingRightChild(pNode);
        traverse(pNode->pRight, pNodeVisitor);
        pNodeVisitor->afterVisitingRightChild(pNode);
    }
};

class NonRecursivePreOrderTraversal: public BTTraversal
{
  public:
    void traverse(node *pNode, NodeVisitor *pNodeVisitor)
    {
        while (1)
        {
            while (pNode)
            {
                //visit  the current node
                pNodeVisitor->visit(pNode);
                m_stack.push(pNode); 
                //add to stack if a left subtree exists
                pNodeVisitor->beforeVisitingLeftChild(pNode);
                pNode = pNode->pLeft;
                pNodeVisitor->afterVisitingLeftChild(pNode);
            }
            if (m_stack.empty())
            {
                break;
            }
            //visited the left subtree and current node,
            pNode = m_stack.top();
            m_stack.pop();
            // now visit to right subtree
            pNodeVisitor->beforeVisitingRightChild(pNode);
            pNode = pNode->pRight;
            pNodeVisitor->afterVisitingRightChild(pNode);
        }
    }

  private:
    stack<node *> m_stack;
    // stack<node&> m_stack;
};

class NonRecursiveInOrderTraversal: public BTTraversal
{
  public:
    void traverse(node *pNode, NodeVisitor *pNodeVisitor)
    {
        while (1)
        {
            while (pNode)
            {
                m_stack.push(pNode); 
                //add to stack if a left subtree exists
                pNodeVisitor->beforeVisitingLeftChild(pNode);
                pNode = pNode->pLeft;
                pNodeVisitor->afterVisitingLeftChild(pNode);
            }
            if (m_stack.empty())
            {
                break;
            }
            //visited the left subtree and current node,
            pNode = m_stack.top();
            m_stack.pop();

            //visit  the current node
            pNodeVisitor->visit(pNode);

            // now visit to right subtree
            pNodeVisitor->beforeVisitingRightChild(pNode);
            pNode = pNode->pRight;
            pNodeVisitor->afterVisitingRightChild(pNode);
        }
    }

  private:
    stack<node*> m_stack; 
};

//ToDo: needs cleanup
class NonRecursivePostOrderTraversal: public BTTraversal
{
  public:
    void traverse(node *pNode, NodeVisitor *pNodeVisitor)
    {
        while (1)
        {
            if (pNode)
            {
                m_stack.push(pNode);
                //add to stack if a left subtree exists
                pNodeVisitor->beforeVisitingLeftChild(pNode);
                pNode = pNode->pLeft;
                pNodeVisitor->afterVisitingLeftChild(pNode);
            }
            else
            {
                if (m_stack.empty())
                {
                    // stack is empty
                    return;
                }
                else if (m_stack.top()->pRight == nullptr)
                {
                    pNode = m_stack.top();
                    m_stack.pop();
                    pNodeVisitor->visit(pNode);
                    if (pNode == m_stack.top()->pRight)
                    {
                        pNodeVisitor->visit(m_stack.top());
                        m_stack.pop();
                    }
                }
                if(!m_stack.empty()){
                    pNodeVisitor->beforeVisitingRightChild(pNode);
                    pNode = m_stack.top()->pRight;
                    pNodeVisitor->afterVisitingRightChild(pNode);
                }
                else
                    pNode = nullptr;
            }
        }
    }

  private:
    stack<node*> m_stack; 
};

int main_binaryTree()
{
    node *pRoot = createTree(4, 8, 9);
    // pRoot->pLeft->pLeft = createTree(1, 2, 3);
    // pRoot->pLeft->pRight = createTree(5, 6, 7);

    DisplayVisitor *pDisplay = new DisplayVisitor();
    

    BTTraversal *pNonRecursivePreOrderTraversal = new NonRecursivePreOrderTraversal();
    cout<<endl<<"Non Recursive PreOrder:"<<" ";
    pNonRecursivePreOrderTraversal->traverse(pRoot,pDisplay);


    BTTraversal *pNonRecursiveInOrderTraversal = new NonRecursiveInOrderTraversal();
    cout<<endl<<"Non Recursive InOrder:"<<" ";
    pNonRecursiveInOrderTraversal->traverse(pRoot,pDisplay);

    cout<<endl<<"Non Recursive PostOrder:"<<" ";
    BTTraversal *pNonRecursivePostOrderTraversal = new NonRecursivePostOrderTraversal();
    pNonRecursivePostOrderTraversal->traverse(pRoot,pDisplay);


    // Converting tree into mirror image
    cout<<endl<<"Mirror:"<<" ";
    MirrorCreator *pMrrCreator = new MirrorCreator();
    pNonRecursivePreOrderTraversal->traverse(pRoot, pMrrCreator);
    pNonRecursivePreOrderTraversal->traverse(pRoot,pDisplay);//display the mirrored tree


    return 0;
}


int main_BinaryTree_Recursion()
{
    node *pRoot = createTree(4, 8, 9);
    pRoot->pLeft->pLeft = createTree(1, 2, 3);
    pRoot->pLeft->pRight = createTree(5, 6, 7);

    // Default NodeVisitor i.e. DisplayVisitor will be used to display the elements of tree using inorder
    BTTraversal *pInOrderTraversal = new InOrderTraversal();
    pInOrderTraversal->traverse(pRoot);
    std::cout << std::endl;

    // DisplayVisitor will be used to display the elements of tree using inorder
    NodeVisitor *pVisitor = new DisplayVisitor();
    pInOrderTraversal->traverse(pRoot, pVisitor);
    std::cout << std::endl;

    // Counting the number of nodes using In order Traversal
    CountingVisitor *pCountingVisitor = new CountingVisitor();
    pInOrderTraversal->traverse(pRoot, pCountingVisitor);
    std::cout << "Total Nodes in tree = " << pCountingVisitor->getCount() << std::endl;

    // Converting tree into mirror image
    MirrorCreator *pMrrCreator = new MirrorCreator();
    BTTraversal *pPreOrderTraversal = new PreOrderTraversal();
    pPreOrderTraversal->traverse(pRoot, pMrrCreator);

    // Default NodeVisitor i.e. DisplayVisitor will be used to display the elements of tree using in order
    pInOrderTraversal->traverse(pRoot);
    std::cout << std::endl;

    node *pExpRoot = createTree('-', '+', 2);
    pExpRoot->pLeft->pLeft = createTree(1, '+', 3);
    pExpRoot->pLeft->pRight = createTree(5, '+', 7);

    // Displaying expression with brackets using Expression Visitor through In Order Traversal
    NodeVisitor *pExpVisitor = new ExpressionVisitor();
    pInOrderTraversal->traverse(pExpRoot, pExpVisitor);
    std::cout << std::endl;
    return 0;
}


int main()
{
    main_BinaryTree_Recursion();
    main_binaryTree();
    return 0;
}