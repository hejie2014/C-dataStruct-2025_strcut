#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treeNode
{
    int data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;
treeNode *createNode(int data)
{
    treeNode *newNode = malloc(sizeof(treeNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // 赋值
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
treeNode *insert(treeNode *root, int data)
{
    if (root == NULL)
    {
        treeNode *newNode = createNode(data);
        root = newNode;
        return root;
    }
    /*
    一直递归，往下找，直到找到一个叶子节点（把叶子节点看做 root）他的 root->left 为空，开始返回，将新创建的节点返回给他的父节点，这个父节点又作为 root，返回给这个父节点的父节点，这样可以从下往上去修复链表。也就是说，父节点指向下一个节点。
    */
    else if (data <= root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }
    return root;
}
bool search(treeNode *root, int data)
{ // 对于每一个 search 函数来说，递归时，只要函数进行返回，该函数就会直接结束将该值作为上个函数的返回值。
    // 一直传递给最开始的调用函数
    if (root == NULL) // 没有找到数据返回
        return false;
    else if (root->data == data) // 找到数据返回
        return true;
    else if (data < root->data)
        return search(root->left, data); // 数据没有在该节点找到，就一直继续往左找，直到返回
    else
        return search(root->right, data); // 数据没有在该节点找到，就一直继续往右找，直到返回
}
// 前序遍历(先访问数据， 在访问左子树， 最后访问右子树)
void preorderTraversal(treeNode *root)
{
    if (root == NULL)
        return;
    printf("%c ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
// 中序遍历(先访问左子树， 在访问数据， 最后访问右子树)
void inorderTraversal(treeNode *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%c ", root->data);
    inorderTraversal(root->right);
}
// 后序遍历(先访问左子树， 在访问右子树， 最后访问数据)
void postorderTraversal(treeNode *root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c ", root->data);
}
// 释放内存
void freeTree(treeNode *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    treeNode *root = NULL;
    root = insert(root, 'F');
    root = insert(root, 'D');
    root = insert(root, 'J');
    root = insert(root, 'B');
    root = insert(root, 'E');
    root = insert(root, 'G');
    root = insert(root, 'K');
    root = insert(root, 'A');
    root = insert(root, 'C');
    root = insert(root, 'I');
    printf("------前序遍历(preorderTraversal)-----\n");
    preorderTraversal(root); // F D B A C E J G I K

    printf("\n------中序遍历(inorderTraversal)-----\n");
    inorderTraversal(root); // A B C D E F G I J K

    printf("\n------后序遍历(postorderTraversal)-----\n");
    postorderTraversal(root); // A C B E D I G K J F

    freeTree(root);
    root = NULL;

    return 0;
}