#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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
        return newNode;
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
// 找到右子树的最小值
treeNode *subtreeRightMin(treeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
// 找到左子树的最大值
treeNode *subtreeLeftMax(treeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
// 递归找到左右子树的最大最小值
treeNode *findMaxLeft(treeNode *root)
{
    if (root->right == NULL)
        return root;
    return findMaxLeft(root->right);
}
treeNode *findMinRight(treeNode *root)
{
    if (root->left == NULL)
        return root;
    return findMaxLeft(root->left);
}
// 查找高度，递归，依次找左树，右树，返回1+max（左树深度，右树深度）
int findHeight(treeNode *root)
{
    if (root == NULL)
    {
        return -1;
    }
    int maxLeft = findHeight(root->left);
    int maxRight = findHeight(root->right);
    return 1 + ((maxLeft >= maxRight) ? maxLeft : maxRight);
}

bool isSubtreeLesser(treeNode *root, int value)
{
    if (root == NULL)
        return true;
    if (root->data > value)
        return false;
    return isSubtreeLesser(root->left, value) && isSubtreeLesser(root->right, value);
}
bool isSubtreeGreater(treeNode *root, int value)
{
    if (root == NULL)
        return true;
    if (root->data < value)
        return false;
    return isSubtreeGreater(root->left, value) && isSubtreeGreater(root->right, value);
}
// 方法1： 让左子树的所有值小于root节点，让右子树的所有值大于root节点，复杂度大，不推荐
bool isBinarySearchTree(treeNode *root)
{
    if (root == NULL)
    {
        return true;
    }
    if (isSubtreeLesser(root->left, root->data) && isSubtreeGreater(root->right, root->data) && isBinarySearchTree(root->left) && isBinarySearchTree(root->right))
        return true;
    else
        return false;
}

// 方法2； 使用判断节点是否在范围之内；
bool isBstUtil(treeNode *root, int minValue, int maxValue)
{
    if (root == NULL)
        return true;
    if (root->data > minValue && root->data < maxValue && isBstUtil(root->left, minValue, root->data) && isBstUtil(root->right, root->data, maxValue))
        return true;
    else
        return false;
}
bool isBst(treeNode *root)
{
    return isBstUtil(root, INT_MIN, INT_MAX);
}

// 方法3：中序遍历验证 对于二叉搜索树，中序遍历应该产生一个升序序列
bool isBstHelper(treeNode *root, treeNode **prev)
{
    if (root == NULL)
        return true;
    // 先检查左子树
    if (!isBstHelper(root->left, prev))
        return false; // 不满足函数就会提前终止，返回false；

    if (*prev != NULL && root->data < (*prev)->data)
        return false;

    // 指向下一个节点
    *prev = root;
    return isBstHelper(root->right, prev);
}
bool isBSTInorder(treeNode *root)
{
    treeNode *prev = NULL;           // 初始化前一个节点指针为NULL
    return isBstHelper(root, &prev); // 调用辅助函数
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
{
    if (root == NULL)
    {
        return;
    }
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

    printf("\n-----------test------\n");
    printf("max = %d\n", subtreeLeftMax(root->left)->data);
    printf("min = %d\n", subtreeRightMin(root->right)->data);

    printf("\n-----------testrev------\n");
    printf("max = %d\n", findMaxLeft(root->left)->data);
    printf("min = %d\n", findMinRight(root->right)->data);

    printf("\n-----------testisBinary---------\n");
    printf("result_root = %d\n", isBinarySearchTree(root));
    printf("result_root_isbst = %d\n", isBst(root));
    printf("result_root_isbstinorder = %d\n", isBSTInorder(root));

    treeNode *test = createNode(12);
    test->left = createNode(13);
    test->left->left = createNode(3);
    test->right = createNode(14);
    inorderTraversal(test);
    printf("result_test = %d\n", isBinarySearchTree(test));
    printf("result_test_isbst = %d\n", isBst(test));
    printf("result_test_isbstinorder = %d\n", isBSTInorder(test));

    printf("\n-----------testHeight---------\n");
    printf("height = %d\n", findHeight(root));
    printf("height_test = %d\n", findHeight(test));
    freeTree(root);
    freeTree(test);
    root = NULL;

    return 0;
}