#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *nestedForLoop(int n)
{
    // 计算所需空间：每个坐标对最多14个字符（包括逗号和空格），
    // 例如 "(10000, 10000), " 是14个字符
    // 加上最后的空字符 '\0'
    int max_pair_length = 14;
    int size = n * n * max_pair_length + 1;

    // 分配内存并初始化为空字符串
    char *res = malloc(size * sizeof(char));
    if (res == NULL)
    {
        return NULL; // 内存分配失败
    }
    res[0] = '\0'; // 初始化为空字符串

    // 使用指针跟踪当前位置，避免重复计算字符串长度
    char *current = res;
    int remaining = size;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // 计算本次写入的长度，留1个字符给最后的'\0'
            int written = snprintf(current, remaining, "(%d, %d), ", i, j);
            if (written >= remaining)
            {
                // 缓冲区不足，处理错误（这里简单返回已构建的部分）
                return res;
            }
            current += written;
            remaining -= written;
        }
    }

    // 移除最后的", "（可选）
    if (current - res >= 2)
    {                 /*
                       1.  每次写入后，current 都指向字符串的结尾（即下次写入的起始位置）。
                       2.  最后，current 指向字符串末尾的 \0。
                       3.  current -= 2; 是为了去掉最后多余的, ，让字符串更美观。
                
                      : 首先指向第一个位置---》写入8个字符--》指针移动8个单位---》指向第9个位置(也就是字符串的末尾 ("\0")）)
                      */
        current -= 2; // 移除最后的 ", "
        *current = '\0';
    }

    return res;
}

int main()
{
    int n = 3;
    char *result = nestedForLoop(n);
    if (result != NULL)
    {
        printf("%s\n", result);
        free(result); // 记得释放内存
        result = NULL;
    }
    return 0;
}