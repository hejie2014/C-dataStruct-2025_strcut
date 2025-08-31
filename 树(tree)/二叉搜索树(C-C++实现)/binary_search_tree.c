#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bstNode
{
    int data;
    struct bstNode *left;
    struct bstNode *right;
} bstNode;

bstNode *creatNode(int data)
{
    bstNode *newNode = malloc(sizeof(bstNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
bstNode *insert(bstNode *root, int data)
{
    if (root == NULL)
    {
        bstNode *temp = creatNode(data);
        root = temp;
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
bool search(bstNode *root, int data)
{ // 对于每一个 search 函数来说，递归时，只要函数进行返回，该函数就会直接结束将该值作为上个函数的返回值。
    // 一直传递给最开始的调用函数
    if (root == NULL) // 没有找到数据返回
    {
        return false;
    }
    else if (root->data == data) // 找到数据返回
    {
        return true;
    }
    else if (data < root->data) // 数据没有在该节点找到，就一直继续往左找，直到返回
        return search(root->left, data);
    else
        return search(root->right, data); // 数据没有在该节点找到，就一直继续往右找，直到返回
}
bstNode *searchValue(bstNode *root)
{
    if (root->left == NULL)
        return root;
    searchValue(root->left);
}

// 找到右子树的最小值节点
bstNode *findMin(bstNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
bstNode *searchPosition(bstNode *root, int data)
{ // 对于每一个 search 函数来说，递归时，只要函数进行返回，该函数就会直接结束将该值作为上个函数的返回值。
    // 一直传递给最开始的调用函数
    if (root == NULL) // 没有找到数据返回
    {
        return NULL;
    }
    else if (root->data == data) // 找到数据返回
    {
        return root;
    }
    else if (data <= root->data) // 数据没有在该节点找到，就一直继续往左找，直到返回
        return searchPosition(root->left, data);
    else
        return searchPosition(root->right, data); // 数据没有在该节点找到，就一直继续往右找，直到返回
}
// 删除节点， 实现与插入类似，递归，找到要删除的值，返回重新链接节点
bstNode *deleteNode(bstNode *root, int data)
{
    if (root == NULL)
    {
        // printf("the tree is empty!\n");
        return root;
    }
    // 查找要删除的节点，当前函数返回的节点地址，作为上一个函数的链接
    // 数据比当前节点的值要小，就去左边寻找
    if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    // 数据比当前节点的值要大，就去右边寻找
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        // 找到要删除的节点
        // Case 1: 没有子节点
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        // Case 1: 只有一个子节点(左节点为空)
        else if (root->left == NULL)
        {
            bstNode *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            bstNode *temp = root;
            root = root->left;
            free(temp);
        }
        // Case 3: 有两个子节点
        else
        {
            // 找出要删除节点的右子树的最小值节点
            bstNode *temp = findMin(root->right);
            printf("value = %d\n", temp->data);
            // 将最小值赋值给要删除的节点；
            // 在将右子树中最小值的节点删除，该节点一定是叶子节点，或一个子节点并且左子树为，不可能有多个节点
            // 修复该删除节点的右子树，所以传入的root是root->right
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

// 中序遍历
void inorderTraversal(bstNode *root)
{
    if (root == NULL)
        return;
    else
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
// 释放内存
void freeTree(bstNode *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
void result(bool res, int data)
{
    if (res)
        printf("\n%d Found!\n", data);
    else
        printf("\n%d Not Found!\n", data);
}
int main()
{
    bstNode *root = NULL;
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 8);
    root = insert(root, 12);
    root = insert(root, 18);
    root = insert(root, 21);
    root = insert(root, 23);
    root = insert(root, 28);
    root = insert(root, 27);
    inorderTraversal(root);
    result(search(root, 12), 12);
    result(search(root, 3), 3);

    printf("-------test delete------\n");
    // inorderTraversal(root);
    root = deleteNode(root, 15);
    inorderTraversal(root);
    bstNode *temp = searchPosition(root, 20);
    printf("\nvalue = %d\n", temp->left); // 地址为NULL
    printf("value = %p\n", temp->left);
    freeTree(root);
    root = NULL;

    return 0;
}