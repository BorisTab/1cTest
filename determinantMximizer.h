#ifndef INC_1CTEST_DETERMINANTMXIMIZER_H
#define INC_1CTEST_DETERMINANTMXIMIZER_H

struct Point {
    int64_t x = 0;
    int64_t y = 0;
};

/*!
 *  @brief Класс, который найходит максимальный определитель матрицы,
 *  использую отражение подматриц относительно диагоналей
 */
class DeterminantMaximizer {
public:
    /*!
     * @brief Конструктор от сслыки на матрицу, не копирует матрицу
     *
     * @param[in] inputMatrix ссылка на матрицу, для поиска определителя
     */
    explicit DeterminantMaximizer(std::vector<std::vector<double>>& inputMatrix):
            inputMatrix(inputMatrix),
            size(inputMatrix.size()),
            LMatrix(size, std::vector(size, 0.)),
            UMatrix(size, std::vector(size, 0.)),
            maxDet(0) {
    }

    /*!
     * @brief находит определитель матрицы
     *
     * @return Определитель мактрицы
     */
    double Determinant() {
        FindLU(inputMatrix);
        return DiagonalMatrixDet(LMatrix) * DiagonalMatrixDet(UMatrix);
    }

    double findMaxDet() {

    }

private:
    /*!
     * @brief Отражает подматрицу относительно главной диагонали
     *
     * @param matrix матрица, в котрой будет выполнено отражение
     * @param[in] leftUp точка начала диагонали подматрицы
     * @param[in] rightDown точка конца диагонали подматрицы
     */
    static void FlipMainDiag(std::vector<std::vector<double>>& matrix, Point leftUp, Point rightDown) {
        for (size_t i = leftUp.x; i < rightDown.x; ++i) {
            for (size_t j = leftUp.y; j < i; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    /*!
     * @brief Отражает подматрицу относительно побочной диагонали
     *
     * @param matrix матрица, в котрой будет выполнено отражение
     * @param[in] leftDown точка начала диагонали подматрицы
     * @param[in] rightUp точка конца диагонали подматрицы
     */
    static void FlipSideDiag(std::vector<std::vector<double>>& matrix, Point leftDown, Point rightUp) {
        for (size_t i = leftDown.x; i < rightUp.x; ++i) {
            for (size_t j = leftDown.y; j < rightUp.y - i; ++j) {
                std::swap(matrix[i][j], matrix[matrix.size() - j - 1][matrix.size() - i - 1]);
            }
        }
    }

    /*!
     * @brief Копирует матрицу, может скопировать матрицу меньшего размера в матрицу большего размера
     *
     * @param[in] inMatrix
     * @param[out] outMatrix
     */
    static void CopyMatrix(std::vector<std::vector<double>>& inMatrix, std::vector<std::vector<double>>& outMatrix) {
        assert(inMatrix.size() <= outMatrix.size());

        for (size_t i = 0; i < inMatrix.size(); ++i) {
            for (size_t j = 0; j < inMatrix.size(); ++j) {
                outMatrix[i][j] = inMatrix[i][j];
            }
        }
    }

    /*!
     * @brief Делает LU-разложение матрицы
     *
     * @param[in] matrix
     */
    void FindLU(std::vector<std::vector<double>>& matrix) {
        CopyMatrix(matrix, UMatrix);

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = i; j < size; ++j) {
                LMatrix[j][i] = UMatrix[j][i] / UMatrix[i][i];
            }
        }

        for (size_t k = 1; k < size; ++k) {
            for (size_t i = k - 1; i < size; ++i) {
                for (size_t j = i; j < size; ++j) {
                    LMatrix[j][i] = UMatrix[j][i] / UMatrix[i][i];
                }
            }

            for (size_t i = k; i < size; ++i) {
                for (size_t j = k - 1; j < size; ++j) {
                    UMatrix[i][j] = UMatrix[i][j] - LMatrix[i][k - 1] * UMatrix[k - 1][j];
                }
            }
        }
    }

    /*!
     * @brief Находит определитель диагональной матрицы
     *
     * @param[in] matrix
     * @return Определитель диагональной матрицы
     */
    static double DiagonalMatrixDet(std::vector<std::vector<double>>& matrix) {
        double det = 1;

        for (size_t i = 0; i < matrix.size(); ++i) {
            det *= matrix[i][i];
        }

        return det;
    }

private:
    std::vector<std::vector<double>> inputMatrix;
    size_t size;
    std::vector<std::vector<double>> LMatrix;
    std::vector<std::vector<double>> UMatrix;

    size_t maxDet;
};


#endif //INC_1CTEST_DETERMINANTMXIMIZER_H
