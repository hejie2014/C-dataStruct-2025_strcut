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
        return search(root->left, data);
    else
    {
        return search(root->right, data);
    }
}
treeNode *searchNode(treeNode *root, int data)
{
    if (root == NULL)
        return NULL;
    else if (root->data == data)
        return root;
    else if (data < root->data)
        return searchNode(root->left, data);
    else
    {
        return searchNode(root->right, data);
    }
}
// 左子树最大值节点
treeNode *findMaxLeft(treeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
// 左子树最大值节点-递归
treeNode *findMaxLeftRecursion(treeNode *root)
{
    if (root->right == NULL)
    {
        return root;
    }
    return findMaxLeftRecursion(root->right);
}
// 右子树最小值节点
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
// 右子树最小值节点-递归
treeNode *findMinRightRecursion(treeNode *root)
{
    if (root->left == NULL)
    {
        return root;
    }
    return findMinRightRecursion(root->left);
}

// 中序后继节点
treeNode *inorderAfterNode(treeNode *root, int data)
{
    treeNode *current = searchNode(root, data);
    if (current == NULL)
    {
        return NULL;
    }
    // 如果当前节点有右子树，那么他下一个中序后继节点就是右子树的最小值的那个节点
    if (current->right != NULL)
    {
        return findMinRight(current->right);
    }
    // 找数据的同时，使用两个指针记录每个节点以及节点的父节点
    else
    { // successor 子节点， parent 父节点
        treeNode *successor = NULL;
        treeNode *parent = root;
        while (parent != current)
        { // successor与parent的位置会相差一代
          // 直到parent移动到当前节点，那么successor就会是当前节点的父节点
          // 比较值的大小就是类似insert函数，先找到对应的路线，通过比较值就能知道该往左走还是右走。
          // 当节点往左走时，才会更新successor节点，一旦往走就意味着这是successor节点的左子树，那么一直往右走，就不用更新successor节点（该中继后续节点就是他们的祖先successor节点），
            if (current->data < parent->data)
            {
                successor = parent;
                parent = parent->left;
            }
            else
            {
                parent = parent->right;
            }
        }
        return successor;
    }
}
/*
    前序节点，就是执行与后继相反的操作
1.如果有左子树，返回左子树的最大值的节点
2. 比较数据确定路线，往左走节点不更新， 只有往右走才更新节点
*/
// 中序前继节点
treeNode *inorderFrontNode(treeNode *root, int data)
{
    treeNode *current = searchNode(root, data);
    if (current == NULL)
    {
        return NULL;
    }
    // 如果当前节点有左子树，那么他下一个中序后继节点就是左子树的最大值的那个节点
    if (current->left != NULL)
    {
        return findMaxLeft(current->left);
    }
    // 找数据的同时，使用两个指针记录每个节点以及节点的父节点
    else
    { // successor 子节点， parent 父节点
        treeNode *successor = NULL;
        treeNode *parent = root;
        while (parent != current)
        { // successor与parent的位置会相差一代
          // 直到parent移动到当前节点，那么successor就会是当前节点的父节点
          // 比较值的大小就是类似insert函数，先找到对应的路线，通过比较值就能知道该往左走还是右走。
          // 当节点往右走时，才会更新successor节点，一旦往右走就意味着这是successor节点的右子树，那么一直往左走，就不用更新successor节点（该中继后续节点就是他们的祖先successor节点），
            if (current->data > parent->data)
            {
                successor = parent;
                parent = parent->right;
            }
            else
            {
                parent = parent->left;
            }
        }
        return successor;
    }
}
// 中序遍历
void inorderTraversal(treeNode *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);  // 先打印右节点
    printf("%d ", root->data);     //  在打印当前节点
    inorderTraversal(root->right); // 最后打印右节点
}

// 释放内存
void freeTree(treeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    // 先释放左右节点， 在释放当前节点，如果先释放当前节点，会丢失左右节点
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
    // root = insert(root, 24);
    printf("\n------中序遍历(inorderTraversal)-----\n");
    inorderTraversal(root); // 8 10 12 15 18 20 21 23 25 27 28

    printf("\n---------test-max-left---------------\n");
    // 传入节点不同，导致参考点发生改变，所以计算的值就有所区别；
    printf("max = %d\n", findMaxLeft(root)->data);
    printf("max-recursion = %d\n", findMaxLeftRecursion(root->left)->data);

    printf("\n---------test-min-right---------------\n");
    printf("min = %d\n", findMinRight(root)->data);
    printf("min-recursion = %d\n", findMinRightRecursion(root->right)->data);
    // 8 10 12 15 18 20 21 23 25 27 28
    printf("\n----------test-inorderAfterNode------\n");
    printf("result = %d", inorderAfterNode(root, 15)->data);
    printf("result = %d", inorderAfterNode(root, 12)->data);
    printf("result = %d", inorderAfterNode(root, 8)->data);
    printf("result = %d", inorderAfterNode(root, 10)->data);
    printf("result = %d", inorderAfterNode(root, 20)->data);
    printf("result = %d", inorderAfterNode(root, 25)->data);
    printf("result = %d", inorderAfterNode(root, 28)); // NULL
    // result = 18 result = 15 result = 10 result = 21 result = 27
    printf("\n----------test-inorderFrontNode------\n");
    printf("result = %d", inorderFrontNode(root, 15)->data);
    printf("result = %d", inorderFrontNode(root, 12)->data);
    printf("result = %d", inorderFrontNode(root, 8)); // NULL
    printf("result = %d", inorderFrontNode(root, 20)->data);
    printf("result = %d", inorderFrontNode(root, 25)->data);
    printf("result = %d", inorderFrontNode(root, 28)->data);
    // result = 12 result = 10 result = 0 result = 18 result = 23result = 27
    freeTree(root);
    root = NULL;
    return 0;
}