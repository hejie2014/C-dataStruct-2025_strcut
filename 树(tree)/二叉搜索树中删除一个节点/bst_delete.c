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
    if (root == NULL)
    {
        return false;
    }
    else if (root->data == data)
    {
        return true;
    }
    else if (data < root->data)
    {
        return search(root->left, data);
    }
    else
    {
        return search(root->right, data);
    }
}
// 找到右子树的最小节点
treeNode *findMinRight(treeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
// 找到右子树的最小节点-递归
treeNode *findMinRightRecursion(treeNode *root)
{
    if (root->left == NULL)
        return root;
    return findMinRightRecursion(root->left);
}
// 删除树节点
// 删除节点， 实现与插入类似，递归，找到要删除的值，返回重新链接节点
treeNode *deleteNode(treeNode *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    // 查找要删除的节点，当前函数返回的节点地址，作为上一个函数的链接
    // 数据比当前节点的值要小，就去左边寻找
    else if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    // 数据比当前节点的值要大，就去右边寻找
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    { // 找到了数据
        // case 1: 没有左右节点， 也就是叶子节点
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        // case 2:只有一个子节点(左节点为空)
        else if (root->left == NULL)
        {
            treeNode *temp = root;
            root = root->right;
            free(temp);
        }
        // case 2: 只有一个子节点(右节点为空)
        else if (root->right == NULL)
        {
            treeNode *temp = root;
            root = root->left;
            free(temp);
        }
        else
        { // case 3: 有两个或多个子节点
            // 找出要删除节点的右子树的最小值节点
            treeNode *temp = findMinRight(root->right);
            // 将最小值赋值给要删除的节点；
            root->data = temp->data;
            // 使用root = deleteNode(root, temp->data);会进入死循环
            // 1. 因为你先赋值了，把root传入，刚进入函数，这个root就是我们要删除的节点
            // 2. 进入else 有进入右子树找到最小节点，又把root传入。一直循环，永远无法删除节点。
            // 需要从当前节点的右子树去找到最小节点并删除；
            /*问题分析:
                 root = deleteNode(root, temp->data);
                当你执行 root->data = temp->data 后，当前节点的值已经变成了右子树最小值
                然后用 root = deleteNode(root, temp->data) 去删除这个值
                但此时 root 节点就是包含这个值的节点，函数又会重新进入 else 分支
                这样就会无限循环：找最小值 -> 赋值 -> 删除 -> 找最小值...
                正确做法: 应该在右子树中删除那个最小值节点：
            */
            // 在将右子树中最小值的节点删除，该节点一定是叶子节点，或一个子节点并且左子树为NULL，不可能有多个节点
            // 修复该删除节点的右子树，所以传入的root是root->right
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

// 中序遍历
void inorderTraversal(treeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}
// 释放内存
void freeTree(treeNode *root)
{ // 先释放左子树，在释放右子树，最后释放root
    // 先释放root,那么就找不到左子树与右子树了，所以root最后释放
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main()
{
    treeNode *root = NULL;
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
    inorderTraversal(root);                     // 8 10 12 15 18 20 21 23 25 27 28
    printf("\nresult = %d\n", search(root, 3)); // result = 0
    printf("result = %d\n", search(root, 8));   // result = 1
    printf("\n--------------test-min-right-------\n");
    printf("result = %d\n", findMinRight(root->right->right)->data);
    printf("result_Recursion = %d\n", findMinRightRecursion(root->right->right)->data);

    printf("---------test-delete-function--------\n");
    root = deleteNode(root, 15);
    inorderTraversal(root);
    free(root);
    root = NULL;
    return 0;
}
