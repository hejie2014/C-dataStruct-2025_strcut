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
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
treeNode *insert(treeNode *root, int data)
{
    if (root == NULL)
    {
        treeNode *temp = createNode(data);
        root = temp;
        return root;
    }
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
{
    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data < root->data)
    {
        return search(root->left, data);
    }
    else
        return search(root->right, data);
}
int rootValue(treeNode *root)
{
    return root->data;
}
// 查找最小值
int findMin(treeNode *root)
{
    if (root == NULL)
    {
        printf("the tree is empty!\n");
        return -1;
    }
    else if (root->left == NULL) // 多余，直接while循环，当root->left为NULL时不会进入循环
        return root->data;
    else
    {
        while (root->left != NULL)
        {
            root = root->left;
        }
    }
    return root->data;
}
// 查找最大值
int findMax(treeNode *root)
{
    if (root == NULL)
    {
        printf("the tree is empty!\n");
        return -1;
    }
    else if (root->right == NULL) // 多余，直接while循环，当root->right为NULL时不会进入循环
        return root->data;
    else
    {
        while (root->right != NULL)
        {
            root = root->right;
        }
    }
    return root->data;
}
// 使用递归查找最大，最小值
int findMinRecursion(treeNode *root)
{
    if (root == NULL)
    {
        printf("Error: Tree is empty!\n");
        return -1;
    }
    else if (root->left == NULL)
        return root->data;
    return findMinRecursion(root->left);
}
int findMaxRecursion(treeNode *root)
{
    if (root == NULL)
    {
        printf("Error: Tree is empty!\n");
        return -1;
    }
    else if (root->right == NULL)
        return root->data;
    return findMaxRecursion(root->right);
}

// 找到右子树的最小值节点
treeNode *findRightMin(treeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
// 删除节点， 实现与插入类似，递归，找到要删除的值，返回重新链接节点
treeNode *deleteNode(treeNode *root, int data)
{
    if (root == NULL)
        return root;
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
    {
        // 找到要删除的节点
        // Case 1: 没有子节点
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // Case 2: 只有一个子节点(右节点为空)
        else if (root->right == NULL)
        {
            treeNode *temp = root;
            root = root->left;
            free(temp);
            return root;
        }
        // 只有一个子节点(左节点为空)
        else if (root->left == NULL)
        {
            treeNode *temp = root;
            root = root->right;
            free(temp);
            return root;
        }
        // Case 3: 有两个或多个子节点
        else
        {
            // 找出要删除节点的右子树的最小值节点
            treeNode *temp = findRightMin(root->right);
            printf("\nvalue = %d\n", temp->data);
            // 将最小值赋值给要删除的节点；
            root->data = temp->data;
            // 在将右子树中最小值的节点删除，该节点一定是叶子节点，或一个子节点并且左子树为，不可能有多个节点
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
        return;
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
    // root = insert(root, 10);
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
    printf("\n---------test min----------\n");
    printf("min value = %d\n", findMin(root));
    printf("minrec value = %d", findMinRecursion(root));
    printf("\n---------test max----------\n");
    printf("max value = %d\n", findMax(root));
    printf("maxrec value = %d", findMaxRecursion(root));
    printf("\n---------test root----------\n");
    printf("root value = %d", rootValue(root));
    deleteNode(root, 15);
    inorderTraversal(root);
    printf("\n---------test root----------\n");
    printf("root value = %d", rootValue(root));
    freeTree(root);

    root = NULL;
    return 0;
}