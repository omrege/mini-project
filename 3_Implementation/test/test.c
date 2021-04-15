#include "unity.h"
#include <calc.h>

/* Modify these two lines according to the project */
#include <calc.h>
#define PROJECT_NAME    "Calculator"

/* Prototypes for all the test functions */
void test_add(void);
void test_subtract(void);
void test_multiply(void);
void test_divide(void);

/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}

/* Start of the application test */
int main()
{
/* Initiate the Unity Test Framework */
  UNITY_BEGIN();

/* Run Test functions */
  RUN_TEST(test_add);
  RUN_TEST(test_subtract);
  RUN_TEST(test_multiply);
  RUN_TEST(test_divide);

  /* Close the Unity Test Framework */
  return UNITY_END();
}

/* Write all the test functions */ 
void test_add(void) {
  TEST_ASSERT_EQUAL(5, addition(1, 4));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(1000, add(900, 100));
}

void test_subtract(void) {
  TEST_ASSERT_EQUAL(10, subtract(9, 1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(999, subtract(100, 91));
}

void test_multiply(void) {
  TEST_ASSERT_EQUAL(0, multiply(0, 1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(100, multiply(20, 5));
}

void test_divide(void) {
  TEST_ASSERT_EQUAL(2, divide(10, 5));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(10, divide(100, 10));
}