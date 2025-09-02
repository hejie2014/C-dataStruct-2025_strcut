#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treeNode
{
    int data;
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *parent;
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
    newNode->parent = NULL;
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
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
        root->left->parent = root; // 返回节点时，将上一个节点的parent设为当前节点
    }
    else
    {
        root->right = insert(root->right, data);
        root->right->parent = root; // 返回节点时，将上一个节点的parent设为当前节点
    }
    return root;
}
bool search(treeNode *root, int data)
{
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
        return search(root->right, data);
}
treeNode *searchNode(treeNode *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->data == data)
    {
        return root;
    }
    else if (data < root->data)
    {
        return searchNode(root->left, data);
    }
    else
        return searchNode(root->right, data);
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
// 左子树最大值节点-递归
treeNode *findMaxLeftRecursion(treeNode *root)
{
    if (root->right == NULL)
        return root;
    return findMaxLeftRecursion(root->right);
}
// 右子树最小值节点-递归
treeNode *findMinRightRecursion(treeNode *root)
{
    if (root->left == NULL)
        return root;
    return findMinRightRecursion(root->left);
}
// 中序后继节点
treeNode *inorderAfterNode(treeNode *root, int data)
{
    treeNode *current = searchNode(root, data);
    if (current == NULL)
        return NULL;
    if (current->right != NULL)
        return findMinRight(current->right);
    // 情况2：没有右子树，向上查找直到找到第一个大于当前节点的祖先
    /*
    情况1：节点有右子树
            后继是右子树中最小的节点
            例如：节点15的后继是18（右子树20中最小的节点是18）
    情况2：节点没有右子树
        后继是第一个"左拐"的祖先节点
        需要向上找，直到当前节点是其父节点的左子节点
        例如：节点8的后继是10，因为8是10的左子节点
    */
    treeNode *successor = current->parent;
    // successor != NULL 确保不能一直往上找，不能超过原始的root节点
    // 如果当前节点是父节点的右节点，就一直往上找，直到第一个"左拐"的祖先节点
    while (successor != NULL && current == successor->right)
    {
        current = successor;
        successor = successor->parent;
    }
    return successor; // 可能为 NULL（如果是最大节点）
}
// 中序前继节点--前序节点，就是执行与后继相反的操作
treeNode *inorderFrontNode(treeNode *root, int data)
{
    treeNode *current = searchNode(root, data);
    if (current == NULL)
        return NULL;
    if (current->left != NULL)
        return findMaxLeft(current->left);
    treeNode *successor = current->parent;
    // successor != NULL 确保不能一直往上找，不能超过原始的root节点
    // 如果当前节点是父节点的左节点，就一直往上找，直到第一个"右拐"的祖先节点
    while (successor != NULL && current == successor->left)
    {
        current = successor;
        successor = successor->parent;
    }
    return successor; // 可能为 NULL（如果是最小节点）
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
        return;
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

    printf("\n-----test-parent---------\n");
    printf("Node-root = %p\n", root);
    printf("Node-root->left = %p\n", root->left);   // 10
    printf("Node-root->right = %p\n", root->right); // 20
    printf("Node-root->left->parent = %p\n", root->left->parent);
    printf("Node-root->right->parent = %p\n", root->right->parent);
    printf("Node-root->left->right->parent = %p\n", root->left->right->parent); // 12
    printf("Node-root->right->left->parent = %p\n", root->right->left->parent); // 18

    printf("\n-----test-searchNode---------\n");
    printf("result = %d", searchNode(root, 15)->data);

    printf("\n-----test-min---------\n");
    printf("min = %d\n", findMinRight(root->right)->data);
    printf("min-recursion = %d\n", findMinRightRecursion(root->right)->data);

    printf("\n-----test-max---------\n");
    printf("max = %d\n", findMaxLeft(root->left)->data);
    printf("max-recursion = %d\n", findMaxLeftRecursion(root->left)->data);

    printf("\n-----test-inorderAfterNode---------\n");
    inorderTraversal(root);
    printf("result = %d\n", inorderAfterNode(root, 15)->data);
    printf("result = %d\n", inorderAfterNode(root, 8)->data);
    printf("result = %d\n", inorderAfterNode(root, 10)->data);
    printf("result = %d\n", inorderAfterNode(root, 12)->data);

    printf("\n----------test-inorderFrontNode------\n");
    printf("result = %d", inorderFrontNode(root, 15)->data);
    printf("result = %d", inorderFrontNode(root, 12)->data);
    printf("result = %d", inorderFrontNode(root, 8)); // NULL
    printf("result = %d", inorderFrontNode(root, 20)->data);
    printf("result = %d", inorderFrontNode(root, 25)->data);
    printf("result = %d", inorderFrontNode(root, 28)->data);
    // result = 12 result = 10 result = 0 result = 18 result = 23result = 27
    return 0;
}