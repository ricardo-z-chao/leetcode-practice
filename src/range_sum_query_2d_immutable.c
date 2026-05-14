/**
 * @brief LeetCode 304. 二维区域和检索 - 矩阵不可变
 * @link https://leetcode-cn.com/problems/range-sum-query-2d-immutable/
 * @note 在构造函数中计算前缀和，优化查询效率
 */

#include "leetcode/range_sum_query_2d_immutable.h"

#include <stdlib.h>

/**
 * @brief 构造函数，计算前缀和
 * @param[in] matrix 输入的二维矩阵
 * @param[in] matrixSize 矩阵的行数
 * @param[in] matrixColSize 矩阵的列数组
 * @return 返回构造的对象
 */
NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
  /* 这里构造前缀和二位数组需要多一行一列，并且首行首列需要填充为零 */
  NumMatrix* numMatrix = (NumMatrix*)malloc(sizeof(NumMatrix));
  int rows = matrixSize + 1, cols = matrixColSize[0] + 1;
  int** sum = malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    sum[i] = calloc(cols, sizeof(int));
  }
  for (int i = 1; i < rows; i++) {
    for (int j = 1; j < cols; j++) {
      sum[i][j] = sum[i][j - 1] + sum[i - 1][j] + matrix[i - 1][j - 1] - sum[i - 1][j - 1];
    }
  }
  numMatrix->sum = sum;
  numMatrix->rows = rows;
  numMatrix->cols = cols;
  return numMatrix;
}

/**
 * @brief 查询指定区域的和
 * @param[in] obj 构造的对象
 * @param[in] row1 区域的起始行
 * @param[in] col1 区域的起始列
 * @param[in] row2 区域的结束行
 * @param[in] col2 区域的结束列
 * @return 返回指定区域的和
 */
int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
  int** sum = obj->sum;
  return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1] - sum[row1][col2 + 1] + sum[row1][col1];
}

/**
 * @brief 释放构造的对象
 * @param[in] obj 构造的对象
 */
void numMatrixFree(NumMatrix* obj) {
  for (int i = 0; i < obj->rows; i++) {
    free(obj->sum[i]);
  }
  free(obj->sum);
  free(obj);
}
