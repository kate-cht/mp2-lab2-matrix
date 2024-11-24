#include "tmatrix.h"

#include <gtest.h>

template<typename T>
class TestTVector :public::testing::Test
{
protected:
	T *arr_norm, *arr_v0, *arr_v1, *arr_sub, *arr_add, *arr_n8;
	TDynamicVector<T> *norm, *v1, *v0, *sub, *add, *vect, *vect1, *vcopy, *n8;
public:
	void SetUp() {
		arr_norm = new T[3]{ 1, 1, 1 };
		norm = new TDynamicVector<T>(arr_norm, 3);

		arr_n8 = new T[3]{ 8, 8, 8 };
		n8 = new TDynamicVector<T>(arr_n8, 3);

		arr_v0 = new T[3]{ 1, 2, 3 };
		v0 = new TDynamicVector<T>(arr_v0, 3);

		arr_v1 = new T[5]{ 1, 2, 3, 4, 5 };
		v1 = new TDynamicVector<T>(arr_v1, 5);

		arr_add = new T[3]{ 2, 3, 4 };
		add = new TDynamicVector<T>(arr_add, 3);
		arr_sub = new T[3]{ 0, 1, 2 };
		sub = new TDynamicVector<T>(arr_sub, 3);


		vcopy = new TDynamicVector<T>(*v1);
	}
	void TearDown()
	{
		delete[] arr_norm;
		arr_norm = nullptr;
		delete[] arr_n8;
		arr_n8 = nullptr;
		delete[] arr_v1;
		arr_v1 = nullptr;
		delete[] arr_v0;
		arr_v0 = nullptr;
		delete[] arr_sub;
		arr_sub = nullptr;
		delete[] arr_add;
		arr_add = nullptr;

		delete v0;
		delete v1;
		delete norm;
		delete add;
		delete sub;
		delete vcopy;
		delete n8;

	}
	void CreateVector()
	{
		TDynamicVector<T> vect(5);
	}
	void CreateVector_maxsize()
	{
		TDynamicVector<T> vect(MAX_VECTOR_SIZE + 1);
	}
	void CreateVector_() 
	{
		TDynamicVector<T> vect(-1);
	}
};

typedef ::testing::Types<int, float, double> types;

TYPED_TEST_CASE(TestTVector, types);

TYPED_TEST(TestTVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(this -> CreateVector());
}

TYPED_TEST(TestTVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(this -> CreateVector_maxsize());
}

TYPED_TEST(TestTVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(this->CreateVector_());
}

TYPED_TEST(TestTVector, can_create_copied_vector)
{
  ASSERT_NO_THROW(this->CreateVector());
}

TYPED_TEST(TestTVector, copied_vector_is_equal_to_source_one)
{
	EXPECT_EQ(*(this->vcopy), *(this->v1));
}

TYPED_TEST(TestTVector, copied_vector_has_its_own_memory)
{
	this->CreateVector();
	EXPECT_NE(this->vect1, this->v1);
}

TYPED_TEST(TestTVector, can_get_size)
{
	EXPECT_EQ(5, (this->v1->size()));
}

TYPED_TEST(TestTVector, can_set_and_get_element)
{
  EXPECT_EQ(2, this->v1->at(1));
}

TYPED_TEST(TestTVector, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(this->v1->at(-1) = 3);
}

TYPED_TEST(TestTVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(this->v1->at(10) = 3);
}

TYPED_TEST(TestTVector, can_assign_vector_to_itself)
{
	*(this->v1) = *(this->v1);
	EXPECT_EQ(*(this->v1), *(this->v1));
}

TYPED_TEST(TestTVector, can_assign_vectors_of_equal_size)
{
	*(this->v0) = *(this->norm);
	EXPECT_EQ(*(this->v0), *(this->norm));
}

TYPED_TEST(TestTVector, assign_operator_change_vector_size)
{
	*(this->v0) = *(this->v1);
	EXPECT_EQ(5, this->v0->size());
}

TYPED_TEST(TestTVector, can_assign_vectors_of_different_size)
{
	*(this->v0) = *(this->v1);
	EXPECT_EQ(*(this->v0), *(this->v1));
}

TYPED_TEST(TestTVector, compare_equal_vectors_return_true)
{
	EXPECT_TRUE(*(this->vcopy) == *(this->v1));
}

TYPED_TEST(TestTVector, compare_vector_with_itself_return_true)
{
	EXPECT_TRUE(*(this->v1) == *(this->v1));
}

TYPED_TEST(TestTVector, vectors_with_different_size_are_not_equal)
{
	EXPECT_FALSE(*(this->v0) == *(this->v1));
}

TYPED_TEST(TestTVector, can_add_scalar_to_vector)
{
	*(this->v0) = *(this->v0) + 1;
	EXPECT_EQ(*(this-> add), *(this->v0));
}

TYPED_TEST(TestTVector, can_subtract_scalar_from_vector)
{
	*(this->v0) = *(this->v0) - 1;
	EXPECT_EQ(*(this->sub), *(this->v0));
}

TYPED_TEST(TestTVector, can_multiply_scalar_by_vector)
{
	EXPECT_EQ(*(this->n8), *(this->norm) * 8);
}

TYPED_TEST(TestTVector, can_add_vectors_with_equal_size)
{
	EXPECT_EQ(*(this->v0) + *(this->norm), *(this->add));
}

TYPED_TEST(TestTVector, cant_add_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*(this->v1) + *(this->norm));
}

TYPED_TEST(TestTVector, can_subtract_vectors_with_equal_size)
{
	EXPECT_EQ(*(this->v0) - *(this->norm), *(this->sub));
}

TYPED_TEST(TestTVector, cant_subtract_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*(this->v1) - *(this->norm));
}

TYPED_TEST(TestTVector, can_multiply_vectors_with_equal_size)
{
	EXPECT_EQ(*(this->norm) * *(this->norm), 3);
}

TYPED_TEST(TestTVector, cant_multiply_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*(this->v1) * *(this->norm));
}