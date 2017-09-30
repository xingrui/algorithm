#include<cstdio>
#include<cstdlib>
#include<list>
#include<queue>

struct BSTreeNode {
    int m_nValue; // value of node
    BSTreeNode* m_pLeft; // left child of node
    BSTreeNode* m_pRight; // right child of node
    BSTreeNode* m_pSibling;
    BSTreeNode(int value): m_nValue(value), m_pLeft(NULL), m_pRight(NULL), m_pSibling(NULL) {}
};

BSTreeNode* getNext(BSTreeNode* node)
{
    while (node != NULL) {
        if (node->m_pLeft != NULL) return node->m_pLeft;
        if (node->m_pRight != NULL) return node->m_pRight;
        node = node->m_pSibling;
    }
    return NULL;
}

void addSibling(BSTreeNode* node)
{
    if (node == NULL) return;
    if (node->m_pRight != NULL) {
        node->m_pRight->m_pSibling = getNext(node->m_pSibling);
        addSibling(node->m_pRight);
        if (node->m_pLeft != NULL) {
            node->m_pLeft->m_pSibling = node->m_pRight;
            addSibling(node->m_pLeft);
        }
    } else if (node->m_pLeft != NULL) {
        node->m_pLeft->m_pSibling = getNext(node->m_pSibling);
        addSibling(node->m_pLeft);
    }
}

struct StoreStruct {
    BSTreeNode* node;
    int level;
    StoreStruct(BSTreeNode* n, int l): node(n), level(l) {}
};
void addSiblingUsingQueue(BSTreeNode* root)
{
    if (root == NULL) return;
    std::queue<StoreStruct, std::list<StoreStruct> > aidQueue;
    aidQueue.push(StoreStruct(root, 0));
    while (true) {
        StoreStruct current = aidQueue.front();
        aidQueue.pop();
        if (current.node->m_pLeft != NULL) {
            aidQueue.push(StoreStruct(current.node->m_pLeft, current.level + 1));
        }
        if (current.node->m_pRight != NULL) {
            aidQueue.push(StoreStruct(current.node->m_pRight, current.level + 1));
        }
        if (aidQueue.empty()) break;
        StoreStruct next = aidQueue.front();
        if (current.level == next.level) current.node->m_pSibling = next.node;
    }
}

int getValue(BSTreeNode* node)
{
    if (node == NULL) return 0;
    return node->m_nValue;
}

void printTree(BSTreeNode* node)
{
    if (node == NULL) return;
    printTree(node->m_pLeft);
    printf("tree value:%d sibling value:%d\n", node->m_nValue, getValue(node->m_pSibling));
    printTree(node->m_pRight);
}

int main()
{
    BSTreeNode* root = new BSTreeNode(100);
    root->m_pLeft = new BSTreeNode(90);
    root->m_pLeft->m_pLeft = new BSTreeNode(85);
    root->m_pLeft->m_pRight = new BSTreeNode(95);
    root->m_pLeft->m_pRight->m_pRight = new BSTreeNode(98);
    root->m_pRight = new BSTreeNode(110);
    root->m_pRight->m_pLeft = new BSTreeNode(105);
    root->m_pRight->m_pRight = new BSTreeNode(111);
    root->m_pRight->m_pRight->m_pRight = new BSTreeNode(112);
    root->m_pRight->m_pLeft->m_pLeft = new BSTreeNode(103);
    // addSiblingUsingQueue(root);
    addSibling(root);
    printTree(root);
    return 0;
}
