#include<cstdio>
#include<cstdlib>

struct BSTreeNode {
    int m_nValue; // value of node
    BSTreeNode* m_pLeft; // left child of node
    BSTreeNode* m_pRight; // right child of node
    BSTreeNode(int value): m_nValue(value), m_pLeft(NULL), m_pRight(NULL) {}
};

struct StoreStruct {
    BSTreeNode* left;
    BSTreeNode* right;
    StoreStruct(BSTreeNode* l = NULL, BSTreeNode* r = NULL): left(l), right(r) {}
};

void printLinkedList(StoreStruct s)
{
    BSTreeNode* cur = s.left;

    while (cur != NULL) {
        printf("LinkedList left value:%d\n", cur->m_nValue);
        cur = cur->m_pRight;
    }

    cur = s.right;

    while (cur != NULL) {
        printf("LinkedList right value:%d\n", cur->m_nValue);
        cur = cur->m_pLeft;
    }
}

// return head and tail node of double linked list.
StoreStruct change(BSTreeNode* root)
{
    StoreStruct s(root, root);

    if (root == NULL) {
        return s;
    }

    if (root->m_pLeft != NULL) {
        StoreStruct lSub = change(root->m_pLeft);
        root->m_pLeft = lSub.right;

        if (lSub.right != NULL) {
            lSub.right->m_pRight = root;
        }

        s.left = lSub.left;
    }

    if (root->m_pRight != NULL) {
        StoreStruct rSub = change(root->m_pRight);
        root->m_pRight = rSub.left;

        if (rSub.left != NULL) {
            rSub.left->m_pLeft = root;
        }

        s.right = rSub.right;
    }

    return s;
}

void printTree(BSTreeNode* node)
{
    if (node == NULL) {
        return;
    }

    printTree(node->m_pLeft);
    printf("tree value:%d\n", node->m_nValue);
    printTree(node->m_pRight);
}

int main()
{
    BSTreeNode* root = new BSTreeNode(100);
    root->m_pLeft = new BSTreeNode(90);
    root->m_pLeft->m_pLeft = new BSTreeNode(85);
    root->m_pLeft->m_pRight = new BSTreeNode(95);
    root->m_pRight = new BSTreeNode(110);
    root->m_pRight->m_pLeft = new BSTreeNode(105);
    printTree(root);
    StoreStruct s = change(root);
    printLinkedList(s);
    return 0;
}
