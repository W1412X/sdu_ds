# A : 二叉树基础

Submit

Markdown Text

# 描述

创建二叉树类。二叉树的存储结构使用链表。提供操作：前序遍历、中序遍历、后序遍历、层次遍历、计算二叉树结点数目、计算二叉树高度，其中前序遍历要求以递归方式实现，中序遍历、后序遍历要求以非递归方式实现。

# 格式

## 输入格式

第一行为一个数字 n (10<=n<=100000)，表示有这棵树有 n 个节点，编号为 1~n。  
之后 n 行每行两个数字，第 i 行的两个数字 a、b 表示编号为 i 的节点的左孩子节点为 a，右孩子节点为 b，-1 表示该位置没有节点。  
保证数据有效，根节点为 1。

## 输出格式

第一行，n 个数字，表示该树的前序遍历。  
第二行，n 个数字，表示该树的中序遍历。  
第三行，n 个数字，表示该树的后序遍历。  
第四行，n 个数字，表示该树的层次遍历。  
第五行，n 个数字，第 i 个数字表示以 i 节点为根的子树的节点数目。  
第六行，n 个数字，第 i 个数字表示以 i 节点为根的子树的高度。

# 样例 1

## 输入

`5 2 3 4 5 -1 -1 -1 -1 -1 -1`

## 输出

`1 2 4 5 3 4 2 5 1 3 4 5 2 3 1 1 2 3 4 5 5 3 1 1 1 3 2 1 1 1`

# 样例 2

## 输入

`5 3 2 -1 -1 4 5 -1 -1 -1 -1`

## 输出

`1 3 4 5 2 4 3 5 1 2 4 5 3 2 1 1 3 2 4 5 5 1 3 1 1 3 1 2 1 1`

# 样例 3

## 输入

`10 2 -1 4 3 6 -1 5 8 9 7 -1 -1 -1 -1 -1 -1 10 -1 -1 -1`

## 输出

`1 2 4 5 9 10 7 8 3 6 10 9 5 7 4 8 2 6 3 1 10 9 7 5 8 4 6 3 2 1 1 2 4 3 5 8 6 9 7 10 10 9 2 6 4 1 1 1 2 1 6 5 2 4 3 1 1 1 2 1`

## Hint

请仔细读题，注意建树过程。  
  
    
      
      
# B : 二叉树遍历

Submit

Markdown Text

# 描述

接收二叉树前序序列和中序序列(各元素各不相同)，输出该二叉树的后序序列。

# 格式

## 输入格式

输入有三行：  
第一行为数字 n。  
第二行有 n 个数字，表示二叉树的前序遍历。  
第三行有 n 个数字，表示二叉树的中序遍历。

## 输出格式

输出一行，表示该二叉树的后序遍历序列。

# 样例

## 输入

`5 1 2 4 5 3 4 2 5 1 3`

## 输出

`4 5 2 3 1`