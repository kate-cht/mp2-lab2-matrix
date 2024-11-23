#include "tmatrix.h"

#include <gtest.h>

template<typename T>
class TestTVector :public::testing::Test
{
protected:
	T *arr_norm, *arr_v0, *arr_v1, *arr_sub, *arr_add;
	TDynamicVector<T> *norm, *v1, *v0, *sub, *add, *vect;
public:
	void SetUp() {
		this->arr_norm = new T[3]{ 1, 1, 1 };
		this->norm = new TDynamicVector<T>(arr_norm, 3);

		this->arr_v0 = new T[3]{ 1, 2, 3 };
		this->v0 = new TDynamicVector<T>(arr_v0, 3);

		this->arr_v1 = new T[5]{ 1, 2, 3, 4, 5 };
		this->v1 = new TDynamicVector<T>(arr_v1, 5);

		this->arr_add = new T[3]{ 2, 3, 4 };
		this->add = new TDynamicVector<T>(arr_add, 3);
		this->arr_sub = new T[3]{ 0, 1, 2 };
		this->sub = new TDynamicVector<T>(arr_sub, 3);

	}
	void TearDown()
	{
		delete[] this->arr_norm;
		delete[] this->arr_v1;
		delete[] this->arr_v0;
		delete[] this->arr_sub;
		delete[] this->arr_add;

		this->arr_v1 = nullptr;
		this->arr_v0 = nullptr;
		this->arr_norm = nullptr;
		this->arr_add = nullptr;
		this->arr_sub = nullptr;
		delete this->vect;
		delete this->v0;
		delete this->v1;
		delete this->norm;
		delete this->add;
		delete this->sub;

	}
	void CreateVector(size_t size = 1)
	{
		if (size == 1 || size == 5)
			this->vect = new TDynamicVector<T>(*v1);
		else this->vect = new TDynamicVector<T>(size);
	}
	
};

typedef ::testing::Types<int, float, double> types;

TYPED_TEST_CASE(TestTVector, types);

TYPED_TEST(TestTVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(this -> CreateVector(5));
}

TYPED_TEST(TestTVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(this -> CreateVector(MAX_VECTOR_SIZE + 1));
  
}

TYPED_TEST(TestTVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(this->CreateVector(-5));

}

TYPED_TEST(TestTVector, can_create_copied_vector)
{
  ASSERT_NO_THROW(this->CreateVector());

}

TYPED_TEST(TestTVector, copied_vector_is_equal_to_source_one)
{
	this->CreateVector(5);
	EXPECT_EQ(*(this-> vect), *(this->v1));
}

TYPED_TEST(TestTVector, copied_vector_has_its_own_memory)
{
	this->CreateVector(5);
	EXPECT_NE(this->vect, this->v1);
}

TYPED_TEST(TestTVector, can_get_size)
{
  EXPECT_EQ(5, this->v1->size());
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
	this->CreateVector(10);
	*(this->v1) = *(this->vect);
	EXPECT_EQ(10, this->v1->size());
}

TYPED_TEST(TestTVector, can_assign_vectors_of_different_size)
{
	this->CreateVector(8);
	*(this->v1) = *(this->vect);
	EXPECT_EQ(*(this->v1), *(this->vect));
}

TYPED_TEST(TestTVector, compare_equal_vectors_return_true)
{
	this->CreateVector(5);
	EXPECT_TRUE(*(this->vect) == *(this->v1));
}

TYPED_TEST(TestTVector, compare_vector_with_itself_return_true)
{
	EXPECT_TRUE(*(this->v1) == *(this->v1));
}

TYPED_TEST(TestTVector, vectors_with_different_size_are_not_equal)
{
	this->CreateVector(10);
	EXPECT_FALSE(*(this->v1) == *(this->vect));
}

TYPED_TEST(TestTVector, can_add_scalar_to_vector)
{
	this->CreateVector(3);
	*(this->vect) = *(this->v0) + 1;
	EXPECT_EQ(*(this-> add), *(this->vect));
	
}

TYPED_TEST(TestTVector, can_subtract_scalar_from_vector)
{
	this->CreateVector(3);
	*(this->vect) = *(this->v0) - 1;
	EXPECT_EQ(*(this->sub), *(this->vect));
}

TYPED_TEST(TestTVector, can_multiply_scalar_by_vector)
{
	this->CreateVector(3);
	*(this->vect) = *(this->norm) * 8;
	EXPECT_EQ(*(this->vect), *(this->norm) * 8);
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