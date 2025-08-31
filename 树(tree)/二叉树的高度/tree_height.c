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
    {
        return search(root->left, data);
    }
    else
    {
        return search(root->right, data);
    }
}
// 查找高度，递归，依次找左树，右树，返回1+max（左树深度，右树深度）
int findHeight(treeNode *root)
{
    if (root == NULL)
    {
        return -1;
    }
    int leftMax = findHeight(root->left);
    int rightMax = findHeight(root->right);
    // height = (leftMax >= rightMax) ? leftMax : rightMax;
    return 1 + ((leftMax >= rightMax) ? leftMax : rightMax);
}

// 打印树数据,中序遍历
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
    root = insert(root, 24);
    inorderTraversal(root);
    printf("\nresult1 = %d\n", search(root, 8));
    printf("result1 = %d\n", search(root, 3));
    printf("\n----------------\n");
    printf("height = %d", findHeight(root));
    freeTree(root);
    root = NULL;
    return 0;
}

// 使用迭代的方法
/*
int findHeight(treeNode *root)
{
    if (root == NULL)
        return -1; // 空树的高度为-1

    Queue *queue = createQueue(); // 创建队列用于存储待处理的节点
    enqueue(queue, root); // 将根节点加入队列
    int height = -1; // 初始化高度为-1

    while (!isEmpty(queue)) // 当队列不为空时继续处理
    {
        int levelSize = queue->size; // 获取当前层的节点数量
        height++; // 处理新的一层，高度增加

        // 处理当前层的所有节点
        for (int i = 0; i < levelSize; i++)
        {
            treeNode *node = dequeue(queue); // 从队列中取出一个节点

            // 将该节点的子节点加入队列（下一层）
            if (node->left != NULL)
                enqueue(queue, node->left);
            if (node->right != NULL)
                enqueue(queue, node->right);
        }
    }

   freeQueue(queue); // 释放队列资源
   return height; // 返回计算得到的高度
 }*/
/*
        A
       / \
      B   C
     / \   \
    D   E   F
执行过程：
初始化：队列 = [A], height = -1

处理第0层：
levelSize = 1, height = 0
处理A：出队A，将B、C入队 → 队列 = [B, C]

处理第1层：
levelSize = 2, height = 1
处理B：出队B，将D、E入队 → 队列 = [C, D, E]
处理C：出队C，将F入队 → 队列 = [D, E, F]

处理第2层：
levelSize = 3, height = 2
处理D：出队D，无子节点 → 队列 = [E, F]
处理E：出队E，无子节点 → 队列 = [F]
处理F：出队F，无子节点 → 队列 = []

队列为空，循环结束，返回height = 2
*/