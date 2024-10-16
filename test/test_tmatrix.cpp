#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i * j;

	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i * j;

	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);

	m2[2][1] = 0;

	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m1(3);

	EXPECT_EQ(3, m1.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m1(3);

	EXPECT_NE(5, m1[1][1]);

	m1[1][1] = 5;

	EXPECT_EQ(5, m1[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m1(3);

	ASSERT_ANY_THROW(m1.at(-1).at(1) = 5);
	ASSERT_ANY_THROW(m1.at(1).at(-1) = 5);
	ASSERT_ANY_THROW(m1.at(-1).at(-1) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m1(3);

	ASSERT_ANY_THROW(m1.at(3).at(1) = 5);
	ASSERT_ANY_THROW(m1.at(1).at(3) = 5);
	ASSERT_ANY_THROW(m1.at(3).at(3) = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m1(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i * j;

	TDynamicMatrix<int> m2(m1);

	ASSERT_NO_THROW(m1 = m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i * j;

	ASSERT_NO_THROW(m2 = m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3), m2(5);

	ASSERT_NO_THROW(m2 = m1);

	EXPECT_EQ(3, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5), m2(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i * j;

	ASSERT_NO_THROW(m2 = m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(3), m2(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = m2[i][j] = i * j;

	EXPECT_EQ(true, m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i * j;

	EXPECT_EQ(true, m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3), m2(5);

	EXPECT_EQ(false, m1 == m2);
	EXPECT_EQ(true, m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), mr(3), mc(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
		{
			m1[i][j] = i * j;
			m2[i][j] = i * j * 15;

			mc[i][j] = i * j + i * j * 15;
		}

	ASSERT_NO_THROW(mr = m1 + m2);

	EXPECT_EQ(mr, mc);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(5), mr(5);

	ASSERT_ANY_THROW(mr = m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), mr(3), mc(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
		{
			m1[i][j] = i * j;
			m2[i][j] = i * j * 15;

			mc[i][j] = i * j - i * j * 15;
		}

	ASSERT_NO_THROW(mr = m1 - m2);

	EXPECT_EQ(mr, mc);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(5), mr(5);

	ASSERT_ANY_THROW(mr = m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), mr(3), mc(3);

	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
		{
			m1[i][j] = i + j + 2;
			m2[i][j] = (i + 1) * (j + 1);

		}

	mc[0][0] = 20; mc[0][1] = 40; mc[0][2] = 60;
	mc[1][0] = 26; mc[1][1] = 52; mc[1][2] = 78;
	mc[2][0] = 32; mc[2][1] = 64; mc[2][2] = 96;

	ASSERT_NO_THROW(mr = m1 * m2);

	EXPECT_EQ(mr, mc);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(5), mr(5);

	ASSERT_ANY_THROW(mr = m1 * m2);
}
