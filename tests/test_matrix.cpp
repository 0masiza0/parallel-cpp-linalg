#include <gtest/gtest.h>
#include <../include/Matrix.h>

TEST(Matrix, DefaultConstructors) {
    Matrix<int> empty, default_mat(3, 4);
    ASSERT_EQ(empty.shape(), {0, 0});
    ASSERT_EQ(default_mat.shape(), {3, 4});
}

TEST(Matrix, Constructors) {
    std::vector<int> v1 = {1, 2, 3};
    Matrix<int> m1(v1);
    Matrix<int> m2({1, 2, 3});
    Matrix<int> m3(m1);
    Matrix<int> m4(Matrix<int>({1, 2, 3}));
    for (size_t j = 0; j < 3; ++j) {
        ASSERT_EQ(m1[0][j], v1[j]);
        ASSERT_EQ(m2[0][j], v1[j]);
        ASSERT_EQ(m3[0][j], v1[j]);
        ASSERT_EQ(m4[0][j], v1[j]);
    }

    std::vector<std::vector<int>> v2 = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int> m5(v2);
    Matrix<int> m6(Matrix<int>({{1, 2, 3}, {4, 5, 6}}));

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            ASSERT_EQ(m5[i][j], v2[i][j]);
            ASSERT_EQ(m6[i][j], v2[i][j]);
        }
    }
}

TEST(Matrix, CompareOperators) {
    Matrix<int> empty1, empty2;
    ASSERT_TRUE(empty1 == empty1);
    ASSERT_TRUE(empty1 == empty2);

    ASSERT_FALSE(empty1 != empty1);
    ASSERT_FALSE(empty1 != empty2);

    Matrix<int> matrix1({{1, 2, 3, 4},
                        {5, 6, 7, 8}});
    ASSERT_FALSE(empty1 == matrix1);
    ASSERT_FALSE(matrix1 == empty1);
    ASSERT_TRUE(matrix1 == matrix);

    ASSERT_TRUE(empty1 != matrix1);
    ASSERT_TRUE(matrix1 != empty1);
    ASSERT_FALSE(matrix1 != matrix);

    Matrix<int> matrix2({{1, 2, 3, 4},
                         {5, 6, 7, 9}});
    ASSERT_FALSE(matrix1 == matrix2);

    ASSERT_TRUE(matrix1 != matrix2);
}

TEST(Matrix, PlusOperator) {
    Matrix<int> empty;
    ASSERT_TRUE(empty + empty == empty);

    Matrix<int> matrix1({{1, 2, 3, 4},
                         {5, 6, 7, 8}});
    ASSERT_EQ(matrix1 + matrix1, Matrix<int>({{2, 4, 6, 8}, {10, 12, 14, 16}}));
    Matrix<int> zeroes({{0, 0, 0, 0},
                        {0, 0, 0, 0}});
    ASSERT_EQ(matrix1 + zeroes, matrix1);

    Matrix<int> dif_size_zeroes({0, 0, 0},
                                {0, 0, 0},
                                {0, 0, 0});
    bool caught_error = false;
    try {
        auto tmp = matrix1 + dif_size_zeroes;
        (void)tmp;
    } catch (std::invalid_argument& invalid_argument) {
        ASSERT_EQ(invalid_argument.what(), "Matrixes have different shapes\n");
        caught_error = true;
    }
    ASSERT_TRUE(caught_error);
}

TEST(Matrix, MinusOperator) {
    Matrix<int> empty;
    ASSERT_TRUE(empty - empty == empty);

    Matrix<int> matrix1({{1, 2, 3, 4},
                         {5, 6, 7, 8}});
    Matrix<int> zeroes({{0, 0, 0, 0},
                        {0, 0, 0, 0}});
    ASSERT_EQ(matrix1 - matrix1, zeroes);
    ASSERT_EQ(zeroes - matrix1, Matrix<int>({{-1, -2, -3, -4},
                                             {-5, -6, -7, -8}}));

    Matrix<int> dif_size_zeroes({0, 0, 0},
                                {0, 0, 0},
                                {0, 0, 0});
    bool caught_error = false;
    try {
        auto tmp = matrix1 - dif_size_zeroes;
        (void)tmp;
    } catch (std::invalid_argument& invalid_argument) {
        ASSERT_EQ(invalid_argument.what(), "Matrixes have different shapes\n");
        caught_error = true;
    }
    ASSERT_TRUE(caught_error);
}

TEST(Matrix, MultiplpyOperator) {
    Matrix<int> empty;
    ASSERT_TRUE(empty * empty == empty);

    Matrix<int> matrix1({{1, 2, 3, 4},
                         {5, 6, 7, 8}});
    ASSERT_EQ(matrix1 * matrix1, Matrix<int>({{1, 4, 9, 16},
                                              {25, 36, 49, 64}}));
    Matrix<int> ones({{1, 1, 1, 1},
                        {1, 1, 1, 1}});
    ASSERT_EQ(matrix1 * ones, matrix1);

    Matrix<int> zeroes({{0, 0, 0, 0},
                        {0, 0, 0, 0}});
    ASSERT_EQ(matrix1 * zeroes, zeroes);

    Matrix<int> dif_size({{1, 2, 3},
                {4, 5, 6}});
    bool caught_error = false;
    try {
        auto tmp = matrix1 * dif_size;
        (void)tmp;
    } catch (std::invalid_argument& invalid_argument) {
        ASSERT_EQ(invalid_argument.what(), "Matrixes have different shapes\n");
        caught_error = true;
    }
    ASSERT_TRUE(caught_error);
}

