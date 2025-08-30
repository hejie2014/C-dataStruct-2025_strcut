#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新节点
TreeNode *createNode(int value)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入节点
TreeNode *insert(TreeNode *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }

    return root;
}

// ...existing code...
// 返回子树中的最小（最左）节点
TreeNode *findMin(TreeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

// 递归删除，返回删除操作后子树的根（调用者要更新父指针或根）
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;

    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // 找到要删除的节点
        // 情况1：无子节点（叶子）
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // 情况2：只有右子节点
        else if (root->left == NULL)
        {
            TreeNode *r = root->right;
            free(root);
            return r;
        }
        // 情况3：只有左子节点
        else if (root->right == NULL)
        {
            TreeNode *l = root->left;
            free(root);
            return l;
        }
        // 情况4：左右子节点都存在，使用右子树的最小节点（中序后继）
        else
        {
            TreeNode *succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
    }
    return root;
}
// 中序遍历
void inorderTraversal(TreeNode *root)
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
void freeTree(TreeNode *root)
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
    TreeNode *root = NULL;

    // 构建二叉搜索树
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    root = insert(root, 55);
    root = insert(root, 65);

    printf("原始树的中序遍历: ");
    inorderTraversal(root);
    printf("\n");

    // 找到右子树的最小值节点并置为NULL
    root = deleteNode(root, 50);

    printf("操作后的中序遍历: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}