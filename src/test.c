#include <string.h>
#include "s21_string.h"
#include <check.h>
#include <stdlib.h>

START_TEST(memchar_test_1)
{
    unsigned char str [9] = "123456789";
    ck_assert_mem_eq(memchr(str, '5', 9), s21_memchr(str, '5', 9), 9);
}
END_TEST

Suite *create_str_suite(void)
{
    Suite *str_suite = suite_create("s21_str_suite");
    TCase *tcase_memchar = tcase_create("memchr_test_case");
    
    tcase_add_test(tcase_memchar, memchar_test_1);
    
    suite_add_tcase(str_suite, tcase_memchar);
    
    return str_suite;
}

int main(void) {
    Suite *str_suite = create_str_suite();
    SRunner *suite_runner = srunner_create(str_suite);
    
    srunner_run_all(suite_runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return (failed_count != 0)? EXIT_FAILURE : EXIT_SUCCESS;
}