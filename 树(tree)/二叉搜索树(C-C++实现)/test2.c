#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bstNode
{
    int data;
    struct bstNode *left;
    struct bstNode *right;
} bstNode;

bstNode *createNode(int data)
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
        return createNode(data);
    }

    if (data <= root->data)
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
{
    if (root == NULL)
    {
        return false;
    }

    if (root->data == data)
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

bstNode *delete(bstNode *root, int data)
{
    if (root == NULL)
        return root;

    // 查找要删除的节点
    if (data < root->data)
    {
        root->left = delete(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = delete(root->right, data);
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
        // Case 2: 只有一个子节点
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
            bstNode *temp = findMin(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}

void inorderTraversal(bstNode *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

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
        printf("%d Found!\n", data);
    else
        printf("%d Not Found!\n", data);
}

int main()
{
    bstNode *root = NULL;

    // 插入测试数据
    int values[] = {15, 10, 20, 25, 8, 12, 18, 21, 23, 28};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
    {
        root = insert(root, values[i]);
    }

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    // 搜索测试
    result(search(root, 12), 12);
    result(search(root, 3), 3);

    printf("Deleting 20...\n");
    root = delete(root, 20);

    printf("Inorder traversal after deletion: ");
    inorderTraversal(root);
    printf("\n");

    freeTree(root);
    root = NULL;

    return 0;
}