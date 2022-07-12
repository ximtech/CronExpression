#pragma once

#include "BaseTestTemplate.h"
#include "CronExpression.h"


typedef struct CronParseTest {
    const char *pattern;
    CronStatus status;
} CronParseTest;


// Test from: https://github.com/staticlibs/ccronexpr
const char *CRON_EXP_SAME_PARSE_TEST[][2] = {
        {"* * * 2 * *",            "* * * 2 * ?"},
        {"57,59 * * * * *",        "57/2 * * * * *"},
        {"1,3,5 * * * * *",        "1-6/2 * * * * *"},
        {"* * 4,8,12,16,20 * * *", "* * 4/4 * * *"},
        {"* * * * * 0-7",          "* * * * * TUE,WED,THU,FRI,SAT,SUN,MON"},
        {"* * * * * 0",            "* * * * * SUN"},
        {"* * * * * 0",            "* * * * * 7"},
        {"* * * * 1-12 *",         "* * * * FEB,JAN,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC *"},
        {"* * * * 2 *",            "* * * * Feb *"},
        {"*  *  * *  1 *",         "* * * * 1 *"},
};

const CronParseTest CRON_EXP_PATTERN_PARSE_TEST[] = {
        {"* * * * * *",     CRON_OK},
        {"",                CRON_ERROR_EMPTY_STRING},
        {"   ",             CRON_ERROR_EMPTY_STRING},
        {NULL,              CRON_ERROR_EMPTY_STRING},
        {"*",               CRON_ERROR_INVALID_NUMBER_OF_FIELDS},
        {"* * * * * ",      CRON_ERROR_INVALID_NUMBER_OF_FIELDS},
        {"* * * * *",       CRON_ERROR_INVALID_NUMBER_OF_FIELDS},
        {"* * * * * * *",   CRON_ERROR_INVALID_NUMBER_OF_FIELDS},
        {"77 * * * * *",    CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"44-77 * * * * *", CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"* 77 * * * *",    CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"* 44-77 * * * *", CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"* -1-59 * * * *", CRON_ERROR_RANGE_HAS_MORE_THAN_TWO_FIELDS},
        {"* * 27 * * *",    CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"* * 23-28 * * *", CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"* * * 45 * *",    CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"* * * 28-45 * *", CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"0 0 0 25 13 ?",   CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"0 0 0 25 0 ?",    CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"0 0 0 32 12 ?",   CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"* * * * 11-13 *", CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"-5 * * * * *",    CRON_ERROR_RANGE_INVALID_MIN_VALUE},
        {"3-2 */5 * * * *", CRON_ERROR_RANGE_MIN_GREATER_THAN_MAX},
        {"/5 * * * * *",    CRON_ERROR_INVALID_SINGLE_VALUE},
        {"*/0 * * * * *",   CRON_ERROR_INCREMENTER_INVALID_VALUE},
        {"*/-0 * * * * *",  CRON_ERROR_INCREMENTER_INVALID_VALUE},
        {"* 1 1 0 * *",     CRON_ERROR_RANGE_EXCEEDS_MAX},
        {"? * * * * *",     CRON_ERROR_QUESTION_MARK_NOT_ALLOWED},
        {"* ? * * * *",     CRON_ERROR_QUESTION_MARK_NOT_ALLOWED},
        {"* * ? * * *",     CRON_ERROR_QUESTION_MARK_NOT_ALLOWED},
        {"* * * * ? *",     CRON_ERROR_QUESTION_MARK_NOT_ALLOWED},
        {"* * * L+5 * *",   CRON_ERROR_UNRECOGNIZED_CHAR_NEAR_L},
        {"* * * L-35 * *",  CRON_ERROR_LAST_DAY_OFFSET_INVALID},
        {"* * * LZ * *",    CRON_ERROR_UNRECOGNIZED_CHAR_NEAR_L},
        {"* * * L-a * *",   CRON_ERROR_LAST_DAY_OFFSET_INVALID},
        {"* * * aW * *",    CRON_ERROR_INVALID_NEAREST_WEEKDAY_VAlUE},
        {"* * * 32W * *",   CRON_ERROR_INVALID_NEAREST_WEEKDAY_VAlUE},
        {"* * * * * aL",    CRON_ERROR_UNRECOGNIZED_CHAR_NEAR_L},
        {"* * * * * 8L",    CRON_ERROR_INVALID_DAY_OF_WEEK_VALUE_L},
        {"* * * * * a#6",   CRON_ERROR_INVALID_DAY_OF_WEEK_VALUE_HASH},
        {"* * * * * 9#6",   CRON_ERROR_INVALID_DAY_OF_WEEK_VALUE_HASH},
        {"* * * * * 7#-",   CRON_ERROR_INVALID_NUMBER_OF_DAY_OF_MONTH_VALUE_HASH},
        {"* * * * * 7#32",  CRON_ERROR_INVALID_NUMBER_OF_DAY_OF_MONTH_VALUE_HASH},
        {"* * * * * 7#!12", CRON_ERROR_INVALID_NUMBER_OF_DAY_OF_MONTH_VALUE_HASH},
        {"* * * * * 7#",    CRON_ERROR_INVALID_NUMBER_OF_DAY_OF_MONTH_VALUE_HASH},
        {"* 10-a * * * *",  CRON_ERROR_RANGE_INVALID_MAX_VALUE},
        {"* 60-59 * * * *", CRON_ERROR_RANGE_EXCEEDS_MIN},
};

// All tests from spring-framework: https://github.com/spring-projects/spring-framework/blob/main/spring-context/src/test/java/org/springframework/scheduling/support/CronExpressionTests.java
const char *CRON_EXP_TEST[][3] = {
        {"* 15 11 * * *",                        "2019-03-09 11:43:00", "2019-03-10 11:15:00"},
        {"*/15 * 1-4 * * *",                     "2012-07-01 09:53:50", "2012-07-02 01:00:00"},
        {"*/15 * 1-4 * * *",                     "2012-07-01 09:53:00", "2012-07-02 01:00:00"},
        {"0 */2 1-4 * * *",                      "2012-07-01 09:00:00", "2012-07-02 01:00:00"},
        {"0 */2 * * * *",                        "2012-07-01 09:00:00", "2012-07-01 09:02:00"},
        {"0 */2 * * * *",                        "2013-07-01 09:00:00", "2013-07-01 09:02:00"},
        {"0 */2 * * * *",                        "2018-09-14 14:24:00", "2018-09-14 14:26:00"},
        {"0 */2 * * * *",                        "2018-09-14 14:25:00", "2018-09-14 14:26:00"},
        {"0 */20 * * * *",                       "2018-09-14 14:24:00", "2018-09-14 14:40:00"},
        {"* * * * * *",                          "2012-07-01 09:00:00", "2012-07-01 09:00:01"},
        {"* * * * * *",                          "2012-12-01 09:00:58", "2012-12-01 09:00:59"},
        {"10 * * * * *",                         "2012-12-01 09:42:09", "2012-12-01 09:42:10"},
        {"11 * * * * *",                         "2012-12-01 09:42:10", "2012-12-01 09:42:11"},
        {"10 * * * * *",                         "2012-12-01 09:42:10", "2012-12-01 09:43:10"},
        {"10-15 * * * * *",                      "2012-12-01 09:42:09", "2012-12-01 09:42:10"},
        {"10-15 * * * * *",                      "2012-12-01 21:42:14", "2012-12-01 21:42:15"},
        {"0 * * * * *",                          "2012-12-01 21:10:42", "2012-12-01 21:11:00"},
        {"0 * * * * *",                          "2012-12-01 21:11:00", "2012-12-01 21:12:00"},
        {"0 11 * * * *",                         "2012-12-01 21:10:42", "2012-12-01 21:11:00"},
        {"0 10 * * * *",                         "2012-12-01 21:11:00", "2012-12-01 22:10:00"},
        {"0 0 * * * *",                          "2012-09-30 11:01:00", "2012-09-30 12:00:00"},
        {"0 0 * * * *",                          "2012-09-30 12:00:00", "2012-09-30 13:00:00"},
        {"0 0 * * * *",                          "2012-09-10 23:01:00", "2012-09-11 00:00:00"},
        {"0 0 * * * *",                          "2012-09-11 00:00:00", "2012-09-11 01:00:00"},
        {"0 0 0 * * *",                          "2012-09-01 14:42:43", "2012-09-02 00:00:00"},
        {"0 0 0 * * *",                          "2012-09-02 00:00:00", "2012-09-03 00:00:00"},
        {"* * * 10 * *",                         "2012-10-09 15:12:42", "2012-10-10 00:00:00"},
        {"* * * 10 * *",                         "2012-10-11 15:12:42", "2012-11-10 00:00:00"},
        {"0 0 0 * * *",                          "2012-09-30 15:12:42", "2012-10-01 00:00:00"},
        {"0 0 0 * * *",                          "2012-10-01 00:00:00", "2012-10-02 00:00:00"},
        {"0 0 0 * * *",                          "2012-08-30 15:12:42", "2012-08-31 00:00:00"},
        {"0 0 0 * * *",                          "2012-08-31 00:00:00", "2012-09-01 00:00:00"},
        {"0 0 0 * * *",                          "2012-10-30 15:12:42", "2012-10-31 00:00:00"},
        {"0 0 0 * * *",                          "2012-10-31 00:00:00", "2012-11-01 00:00:00"},
        {"0 0 0 1 * *",                          "2012-10-30 15:12:42", "2012-11-01 00:00:00"},
        {"0 0 0 1 * *",                          "2012-11-01 00:00:00", "2012-12-01 00:00:00"},
        {"0 0 0 1 * *",                          "2010-12-31 15:12:42", "2011-01-01 00:00:00"},
        {"0 0 0 1 * *",                          "2011-01-01 00:00:00", "2011-02-01 00:00:00"},
        {"0 0 0 31 * *",                         "2011-10-30 15:12:42", "2011-10-31 00:00:00"},
        {"0 0 0 1 * *",                          "2011-10-30 15:12:42", "2011-11-01 00:00:00"},
        {"* * * * * 2",                          "2010-10-25 15:12:42", "2010-10-26 00:00:00"},
        {"* * * * * 2",                          "2010-10-20 15:12:42", "2010-10-26 00:00:00"},
        {"* * * * * 2",                          "2010-10-27 15:12:42", "2010-11-02 00:00:00"},
        {"55 5 * * * *",                         "2010-10-27 15:04:54", "2010-10-27 15:05:55"},
        {"55 5 * * * *",                         "2010-10-27 15:05:55", "2010-10-27 16:05:55"},
        {"55 * 10 * * *",                        "2010-10-27 09:04:54", "2010-10-27 10:00:55"},
        {"55 * 10 * * *",                        "2010-10-27 10:00:55", "2010-10-27 10:01:55"},
        {"* 5 10 * * *",                         "2010-10-27 09:04:55", "2010-10-27 10:05:00"},
        {"* 5 10 * * *",                         "2010-10-27 10:05:00", "2010-10-27 10:05:01"},
        {"55 * * 3 * *",                         "2010-10-02 10:05:54", "2010-10-03 00:00:55"},
        {"55 * * 3 * *",                         "2010-10-03 00:00:55", "2010-10-03 00:01:55"},
        {"* * * 3 11 *",                         "2010-10-02 14:42:55", "2010-11-03 00:00:00"},
        {"* * * 3 11 *",                         "2010-11-03 00:00:00", "2010-11-03 00:00:01"},
        {"0 0 0 29 2 *",                         "2007-02-10 14:42:55", "2008-02-29 00:00:00"},
        {"0 0 0 29 2 *",                         "2008-02-29 00:00:00", "2012-02-29 00:00:00"},
        {"0 0 7 ? * MON-FRI",                    "2009-09-26 00:42:55", "2009-09-28 07:00:00"},
        {"0 0 7 ? * MON-FRI",                    "2009-09-28 07:00:00", "2009-09-29 07:00:00"},
        {"0 30 23 30 1/3 ?",                     "2010-12-30 00:00:00", "2011-01-30 23:30:00"},
        {"0 30 23 30 1/3 ?",                     "2011-01-30 23:30:00", "2011-04-30 23:30:00"},
        {"0 30 23 30 1/3 ?",                     "2011-04-30 23:30:00", "2011-07-30 23:30:00"},
        {"0 0 0 13 * FRI",                       "2018-07-31 11:47:14", "2019-09-13 00:00:00"},
        {"0 15 12 */10 1-8 5",                   "2021-04-30 12:14:59", "2021-05-21 12:15:00"},
        {"@yearly",                              "2022-10-10 00:00:00", "2023-01-01 00:00:00"},
        {"@annually",                            "2022-10-10 00:00:00", "2023-01-01 00:00:00"},
        {"@monthly",                             "2022-10-10 00:00:00", "2022-11-01 00:00:00"},
        {"@weekly",                              "2022-10-10 00:00:00", "2022-10-16 00:00:00"},
        {"@daily",                               "2022-10-10 00:00:00", "2022-10-11 00:00:00"},
        {"@midnight",                            "2022-10-10 00:00:00", "2022-10-11 00:00:00"},
        {"@hourly",                              "2022-10-10 00:00:00", "2022-10-10 01:00:00"},
        {"0 0 0 L * *",                          "2008-01-04 00:00:00", "2008-01-31 00:00:00"},
        {"0 0 0 L * *",                          "2008-01-31 00:00:00", "2008-02-29 00:00:00"},
        {"0 0 0 L * *",                          "2008-02-29 00:00:00", "2008-03-31 00:00:00"},
        {"0 0 0 L * *",                          "2008-03-31 00:00:00", "2008-04-30 00:00:00"},
        {"0 0 0 L-3 * *",                        "2008-01-04 15:50:00", "2008-01-28 00:00:00"},
        {"0 0 0 L-3 * *",                        "2008-01-28 15:50:00", "2008-02-26 00:00:00"},
        {"0 0 0 L-3 * *",                        "2008-02-26 15:50:00", "2008-03-28 00:00:00"},
        {"0 0 0 L-3 * *",                        "2008-03-28 15:50:00", "2008-04-27 00:00:00"},
        {"0 0 0 LW * *",                         "2008-01-04 16:30:00", "2008-01-31 00:00:00"},
        {"0 0 0 LW * *",                         "2008-01-31 16:30:00", "2008-02-29 00:00:00"},
        {"0 0 0 LW * *",                         "2008-02-29 16:30:00", "2008-03-31 00:00:00"},
        {"0 0 0 LW * *",                         "2008-03-31 16:30:00", "2008-04-30 00:00:00"},
        {"0 0 0 LW * *",                         "2008-04-30 16:30:00", "2008-05-30 00:00:00"},
        {"0 0 0 LW * *",                         "2008-05-30 16:30:00", "2008-06-30 00:00:00"},
        {"0 0 0 LW * *",                         "2008-06-30 16:30:00", "2008-07-31 00:00:00"},
        {"0 0 0 LW * *",                         "2008-07-31 16:30:00", "2008-08-29 00:00:00"},
        {"0 0 0 LW * *",                         "2008-08-29 16:30:00", "2008-09-30 00:00:00"},
        {"0 0 0 LW * *",                         "2008-09-30 16:30:00", "2008-10-31 00:00:00"},
        {"0 0 0 LW * *",                         "2008-10-31 16:30:00", "2008-11-28 00:00:00"},
        {"0 0 0 LW * *",                         "2008-11-28 16:30:00", "2008-12-31 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-01-04 00:00:00", "2008-01-25 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-01-25 00:00:00", "2008-02-29 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-02-29 00:00:00", "2008-03-28 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-03-28 00:00:00", "2008-04-25 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-04-25 00:00:00", "2008-05-30 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-05-30 00:00:00", "2008-06-27 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-06-27 00:00:00", "2008-07-25 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-07-25 00:00:00", "2008-08-29 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-08-29 00:00:00", "2008-09-26 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-09-26 00:00:00", "2008-10-31 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-10-31 00:00:00", "2008-11-28 00:00:00"},
        {"0 0 0 * * 5L",                         "2008-11-28 00:00:00", "2008-12-26 00:00:00"},
        {"0 0 0 15W * ?",                        "2020-01-01 00:00:00", "2020-01-15 00:00:00"},
        {"0 0 0 15W * ?",                        "2020-01-15 00:00:00", "2020-02-14 00:00:00"},
        {"0 0 0 15W * ?",                        "2020-02-14 00:00:00", "2020-03-16 00:00:00"},
        {"0 0 0 15W * ?",                        "2020-03-16 00:00:00", "2020-04-15 00:00:00"},
        {"0 0 0 1W * ?",                         "2019-12-31 00:00:00", "2020-01-01 00:00:00"},
        {"0 0 0 1W * ?",                         "2020-01-01 00:00:00", "2020-02-03 00:00:00"},
        {"0 0 0 1W * ?",                         "2020-02-03 00:00:00", "2020-03-02 00:00:00"},
        {"0 0 0 1W * ?",                         "2020-03-02 00:00:00", "2020-04-01 00:00:00"},
        {"0 0 0 31W * ?",                        "2020-01-01 00:00:00", "2020-01-31 00:00:00"},
        {"0 0 0 31W * ?",                        "2020-01-31 00:00:00", "2020-03-31 00:00:00"},
        {"0 0 0 31W * ?",                        "2020-03-31 00:00:00", "2020-07-31 00:00:00"},
        {"0 0 0 31W * ?",                        "2020-07-31 00:00:00", "2020-08-31 00:00:00"},
        {"0 0 0 31W * ?",                        "2020-08-31 00:00:00", "2020-10-30 00:00:00"},
        {"0 0 0 31W * ?",                        "2020-10-31 00:00:00", "2020-12-31 00:00:00"},
        {"0 0 0 ? * 5#2",                        "2020-01-01 00:00:00", "2020-01-10 00:00:00"},
        {"0 0 0 ? * 5#2",                        "2020-01-10 00:00:00", "2020-02-14 00:00:00"},
        {"0 0 0 ? * 5#2",                        "2020-02-14 00:00:00", "2020-03-13 00:00:00"},
        {"0 0 0 ? * 5#2",                        "2020-03-13 00:00:00", "2020-04-10 00:00:00"},
        {"0 0 0 ? * FRI#2",                      "2020-01-01 00:00:00", "2020-01-10 00:00:00"},
        {"0 0 0 ? * FRI#2",                      "2020-01-10 00:00:00", "2020-02-14 00:00:00"},
        {"0 0 0 ? * FRI#2",                      "2020-02-14 00:00:00", "2020-03-13 00:00:00"},
        {"0 0 0 ? * FRI#2",                      "2020-03-13 00:00:00", "2020-04-10 00:00:00"},
        {"0 0 0 ? * 3#5",                        "2020-01-01 00:00:00", "2020-01-29 00:00:00"},
        {"0 0 0 ? * 3#5",                        "2020-01-29 00:00:00", "2020-04-29 00:00:00"},
        {"0 0 0 ? * 3#5",                        "2020-04-29 00:00:00", "2020-07-29 00:00:00"},
        {"0 0 0 ? * 3#5",                        "2020-07-29 00:00:00", "2020-09-30 00:00:00"},
        {"0 0 0 ? * 3#5",                        "2020-09-30 00:00:00", "2020-12-30 00:00:00"},
        {"0 0 * L * *",                          "2021-01-30 00:01:00", "2021-01-31 00:00:00"},
        {"0 0 * L * *",                          "2021-01-31 01:00:00", "2021-01-31 02:00:00"},
        {"0 0 * L-1 * *",                        "2021-01-29 00:00:01", "2021-01-30 00:00:00"},
        {"0 0 * L-1 * *",                        "2021-01-30 01:00:00", "2021-01-30 02:00:00"},
        {"0 0 * 1W * *",                         "2021-01-31 00:01:00", "2021-02-01 00:00:00"},
        {"0 0 * 1W * *",                         "2021-02-01 01:00:00", "2021-02-01 02:00:00"},
        {"0 0 * LW * *",                         "2021-01-28 00:01:00", "2021-01-29 00:00:00"},
        {"0 0 * LW * *",                         "2021-01-29 01:00:00", "2021-01-29 02:00:00"},
        {"0 0 * ? * FRI#5",                      "2021-01-28 00:01:00", "2021-01-29 00:00:00"},
        {"0 0 * ? * FRI#5",                      "2021-01-29 01:00:00", "2021-01-29 02:00:00"},
        {"0 0 * ? * FRIL",                       "2021-01-28 00:01:00", "2021-01-29 00:00:00"},
        {"0 0 * ? * FRIL",                       "2021-01-29 01:00:00", "2021-01-29 02:00:00"},
        {"0 0 0 ? * SUN-FRI",                    "2021-02-25 15:00:00", "2021-02-26 00:00:00"},
        {"0 0 0 ? * SUN-FRI",                    "2021-02-26 00:00:00", "2021-02-28 00:00:00"},
        {"3-57 13-28 17,18 1,15 3-12 6#1",       "2022-09-15 17:44:11", "2022-10-01 17:13:03"},
        {"*/28 56 22 */6 * *",                   "2022-02-27 08:00:42", "2022-03-01 22:56:00"},

        // Additional test cases
        {"0 0 0 L * WED",                        "2008-08-12 00:00:00", "2008.12.31 00:00:00"},
        {"0 0 0 LW * *",                         "2008-08-12 00:00:00", "2008.08.29 00:00:00"},
        {"0 0 0 L * *",                          "2008-08-12 00:00:00", "2008.08.31 00:00:00"},
        {"0 0 0 16W * *",                        "2008-08-12 00:00:00", "2008.08.15 00:00:00"},
        {"0 0 0 L-6 * *",                        "2008-08-12 00:00:00", "2008.08.25 00:00:00"},
        {"0 0 0 * * 2L",                         "2008-08-12 00:00:00", "2008.08.26 00:00:00"},
        {"0 0 0 * * 6#2",                        "2008-08-12 00:00:00", "2008.09.13 00:00:00"},
        {"0 0 0 25 12 ?",                        "2008-08-12 00:00:00", "2008.12.25 00:00:00"},
        {"0 0/30 8-10 ? * *",                    "2008-08-12 00:00:00", "2008.08.12 08:00:00"},
        {"0 0 6,19 ? * *",                       "2008-08-12 00:00:00", "2008-08-12 06:00:00"},
        {"0 0 9-17 * * MON-FRI",                 "2008-08-12 00:00:00", "2008-08-12 09:00:00"},
        {"0 30 11 ? * 6#2",                      "2008-08-12 00:00:00", "2008-09-13 11:30:00"},
        {"0 0 0 * 3 2L",                         "2008-08-12 00:00:00", "2009-03-31 00:00:00"},
        {"0 15 10 ? * 6L",                       "2008-08-12 00:00:00", "2008-08-30 10:15:00"},
        {"0 0 0 1W * *",                         "2008-08-12 00:00:00", "2008-09-01 00:00:00"},
        {"0 0 0 ? * 5#2",                        "2008-08-12 00:00:00", "2008-09-12 00:00:00"},
        {"0 0 0 ? * MON#1",                      "2008-08-12 00:00:00", "2008-09-01 00:00:00"},
        {"32 22/5 * ? * SUN-FRI",                "2008-08-12 00:00:00", "2008-08-12 00:22:32"},
        {"0 15 10 ? * 6#3",                      "2008-08-12 00:00:00", "2008-08-16 10:15:00"},
        {"0 0 0 ? * 0L",                         "2022-06-12 00:00:00", "2022-06-26 00:00:00"},
        {"0 0 0 29 2 6L",                        "2008-02-12 00:00:00", "2020-02-29 00:00:00"},
        {"0 0/5 14,18,19 ? JAN,MAR,sEp mon-FRI", "2008-02-12 00:00:00", "2008-03-03 14:00:00"},
        {"0 0/5 14,18,19 ? JAN,MAR,sEp mon-FRI", "2008-03-03 14:00:00", "2008-03-03 14:05:00"},
        {"0 0/5 14,18,19 ? JAN,MAR,sEp mon-FRI", "2008-04-03 14:00:00", "2008-09-01 14:00:00"},
        {"0 0 0 29 2 6",                         "2022-04-03 14:00:00", "2048-02-29 00:00:00"}, // long range
};


bool checkArraysEquals(const uint8_t *a, const uint8_t *b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void checkCronEquals(CronExpression one, CronExpression two) {
    assert_true(checkArraysEquals(one.seconds, two.seconds, 8));
    assert_true(checkArraysEquals(one.minutes, two.minutes, 8));
    assert_true(checkArraysEquals(one.hours, two.hours, 3));
    assert_true(checkArraysEquals(one.daysOfMonth, two.daysOfMonth, 4));
    assert_true(checkArraysEquals(one.months, two.months, 2));
    assert_true(checkArraysEquals(one.daysOfWeek, two.daysOfWeek, 1));
    assert_true(checkArraysEquals(one.quartzOptions, two.quartzOptions, 4));
}

static MunitResult testCronSamePattern(const MunitParameter params[], void *testString) {
    CronExpression one;
    CronExpression two;
    for (int i = 0; i < ARRAY_SIZE(CRON_EXP_SAME_PARSE_TEST); i++) {
        printf("Test case %d: [%s] [%s]\n", i + 1, CRON_EXP_SAME_PARSE_TEST[i][0], CRON_EXP_SAME_PARSE_TEST[i][1]);
        CronStatus status1 = parseCronExpression(&one, CRON_EXP_SAME_PARSE_TEST[i][0]);
        CronStatus status2 = parseCronExpression(&two, CRON_EXP_SAME_PARSE_TEST[i][1]);
        assert_true(status1 == CRON_OK);
        assert_true(status2 == CRON_OK);
        checkCronEquals(one, two);
    }
    return MUNIT_OK;
}

static MunitResult testCronInvalidPattern(const MunitParameter params[], void *testString) {
    CronExpression one;
    for (int i = 0; i < ARRAY_SIZE(CRON_EXP_PATTERN_PARSE_TEST); i++) {
        printf("Test case %d: [%s]\n", i + 1, CRON_EXP_PATTERN_PARSE_TEST[i].pattern);
        CronStatus status = parseCronExpression(&one, CRON_EXP_PATTERN_PARSE_TEST[i].pattern);
        assert_true(status == CRON_EXP_PATTERN_PARSE_TEST[i].status);
    }
    return MUNIT_OK;
}

static MunitResult testCronNextDateTime(const MunitParameter params[], void *testString) {
    CronExpression one;
    DateTimeFormatter formatter;
    parseDateTimePattern(&formatter, "yyyy-MM-dd HH:mm:ss");
    for (int i = 0; i < ARRAY_SIZE(CRON_EXP_TEST); i++) {
        const char *pattern = CRON_EXP_TEST[i][0];
        printf("Test case %d: [%s]\n", i + 1, pattern);
        CronStatus status = parseCronExpression(&one, pattern);
        assert_true(status == CRON_OK);

        DateTime initial = parseToDateTime(CRON_EXP_TEST[i][1], &formatter);
        DateTime expected = parseToDateTime(CRON_EXP_TEST[i][2], &formatter);

        DateTime test = nextCronDateTime(&one, &initial);
        assert_true(isDateTimeEquals(&test, &expected));
        assert_true(test.date.weekDay == expected.date.weekDay);
    }
    return MUNIT_OK;
}

static MunitResult testCronNextZonedDateTime(const MunitParameter params[], void *testString) {
    CronExpression cron;
    parseCronExpression(&cron, "0 0 9 * * *");
    TimeZone zone = timeZoneOf("Europe/Amsterdam");
    {

        ZonedDateTime last = zonedDateTimeOf(2021, 3, 27, 9, 0, 0, 0, &zone);   // 3600
        ZonedDateTime expected = zonedDateTimeOf(2021, 3, 28, 9, 0, 0, 0, &zone);   // 7200
        ZonedDateTime actual = nextCronZonedDateTime(&cron, &last);
        assert_true(isDateTimeEquals(&actual.dateTime, &expected.dateTime));
        assert_true(last.offset == 3600);
        assert_true(actual.offset == 7200);
    }
    {
        ZonedDateTime last = zonedDateTimeOf(2021, 10, 30, 9, 0, 0, 0, &zone);  // 7200
        ZonedDateTime expected = zonedDateTimeOf(2021, 10, 31, 9, 0, 0, 0, &zone);   // 3600
        ZonedDateTime actual = nextCronZonedDateTime(&cron, &last);
        assert_true(isDateTimeEquals(&actual.dateTime, &expected.dateTime));
        assert_true(last.offset == 7200);
        assert_true(actual.offset == 3600);
    }
    return MUNIT_OK;
}


static MunitTest cronTests[] = {
        {.name =  "Test parseCronExpression() - should correctly parse same cron string\n", .test = testCronSamePattern},
        {.name =  "Test parseCronExpression() - should fail for invalid pattern\n", .test = testCronInvalidPattern},
        {.name =  "Test nextCronDateTime() - should correctly find next date\n", .test = testCronNextDateTime},
        {.name =  "Test nextCronZonedDateTime() - should correctly find next date with daylight saving\n", .test = testCronNextZonedDateTime},
        END_OF_TESTS
};

static const MunitSuite cronTestSuite = {
        .prefix = "Cron: ",
        .tests = cronTests,
        .suites = NULL,
        .iterations = 1,
        .options = MUNIT_SUITE_OPTION_NONE
};