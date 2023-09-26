# CronExpression

[![tests](https://github.com/ximtech/CronExpression/actions/workflows/cmake-ci.yml/badge.svg?branch=main)](https://github.com/ximtech/CronExpression/actions/workflows/cmake-ci.yml)
[![codecov](https://codecov.io/gh/ximtech/CronExpression/branch/main/graph/badge.svg?token=i7dQ3yGhTj)](https://codecov.io/gh/ximtech/CronExpression)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/0a5a72592b2c4d438331ae980b3953b8)](https://www.codacy.com/gh/ximtech/CronExpression/dashboard)

Cron is a software utility that specifies commands to run on a given schedule. \
Inspired with spring-framework blog
post: [link](https://spring.io/blog/2020/11/10/new-in-spring-5-3-improved-cron-expressions) \
Library provides functionality that describes
in: [link](http://www.quartz-scheduler.org/documentation/quartz-2.3.0/tutorials/crontrigger.html) \
Written in C and designed specifically for embedded devices.

### Features

- No dynamic or static memory allocations
- Time zones and DST rules support
- All Quartz fields support
- Composite quartz field support
- No `time.h` library dependencies
- Full test coverage

### Dependencies

- [GlobalDateTime library](https://github.com/ximtech/GlobalDateTime)
- [StringUtils library](https://github.com/ximtech/StringUtils)

### Trade-offs

- Not all composite quartz fields like: `"0 0 0 1W,15,LW * ?"` is supported
- No year field support

### Add as CPM project dependency

How to add CPM to the project, check the [link](https://github.com/cpm-cmake/CPM.cmake)

```cmake
CPMAddPackage(
        NAME CronExpression
        GITHUB_REPOSITORY ximtech/CronExpression
        GIT_TAG origin/main
)

target_link_libraries(${PROJECT_NAME} CronExpression)
```

```cmake
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
# For Clion STM32 plugin generated Cmake use 
target_link_libraries(${PROJECT_NAME}.elf CronExpression)
```

### Cron structure

- The Cron pattern consists of six or seven space-separated fields

```text
     ┌───────────── second (0-59)
     │ ┌───────────── minute (0 - 59)
     │ │ ┌───────────── hour (0 - 23)
     │ │ │ ┌───────────── day of the month (1 - 31)
     │ │ │ │ ┌───────────── month (1 - 12) (or JAN-DEC)
     │ │ │ │ │ ┌───────────── day of the week (0 - 7)
     │ │ │ │ │ │          (or MON-SUN -- 0 or 7 is Sunday)
     │ │ │ │ │ │
     * * * * * *
```

### Examples of supported expressions

#### Standard Cron

|  **Cron Expression**       |                    **Meaning**                       |
|:--------------------:	     |:-------------------------------------------------:	|
|      `0 0 * * * *`         |           top of every hour of every day             |
|    `*/10 * * * * *`        |                 every ten seconds                    |
|    `0 0 8-10 * * *`        |          8, 9 and 10 o’clock of every day            |
|    `0 0 6,19 * * *`        |           6:00 AM and 7:00 PM every day              |
|   `0 0/30 8-10 * * *`      | 8:00, 8:30, 9:00, 9:30, 10:00 and 10:30 every day    |
| `0 0 9-17 * * MON-FRI`     |         on the hour nine-to-five weekdays            |
|     `0 0 0 25 12 ?`        |          every Christmas Day at midnight             |

#### Macros

- You can use these macros instead of the six-digit value

|     **Macro**        	     |     **Meaning**         	     |
|:--------------------------:|:-----------------------------:|
| `@yearly (or @annually)` 	 | once a year `0 0 0 1 1 *`  	  |
|    `@monthly`        	     | once a month `0 0 0 1 * *` 	  |
|    `@weekly`         	     | once a week `0 0 0 * * 0`  	  |
| `@daily (or @midnight)`  	 |  once a day `0 0 0 * * *`  	  |
|    `@hourly`         	     | once an hour, `0 0 * * * *` 	 |

#### Last Days

| **Cron Expression** 	 |                  **Meaning**                	                  |
|:---------------------:|:--------------------------------------------------------------:|
|  `0 0 0 L * *`     	  |            last day of the month at midnight     	             |
| `0 0 0 L-3 * *`    	  |          third-to-last day of the month at midnight 	          |
|  `0 0 0 * * 5L`    	  |           last Friday of the month at midnight    	            |
| `0 0 0 * * THUL`   	  |           last Thursday of the month at midnight   	           |
| `0 0 0 2,3,L * *`   	 |   on the 2nd, 3rd and last day of the month at midnight   	    |
| `0 0 0 3-8,L * *`   	 | between 3rd and 8th, and last day of the month at midnight   	 |

#### Weekdays

| **Cron Expression** 	|               **Meaning**              	|
|:-------------------:	|:--------------------------------------:	|
|    `0 0 0 1W * *`   	| first weekday of the month at midnight 	|
|    `0 0 0 LW * *`   	| last weekday of the month at midnight  	|

#### Second Friday of the Month

| **Cron Expression** 	|                 **Meaning**                	|
|:-------------------:	|:------------------------------------------:	|
|   `0 0 0 ? * 5#2`   	| the second Friday in the month at midnight 	|
|  `0 0 0 ? * MON#1`  	| the first Monday in the month at midnight  	|


### Usage
```c
 #include "CronExpression.h"

 CronExpression cron;
 CronStatus status = parseCronExpression(&cron, "0 */2 1-4 * * *");
 if (status != CRON_OK) {    // check for error
    printf("ERROR! No: %d\n", status);
    return -1;
 }

 DateTime current = dateTimeNow();
 DateTime next = nextCronDateTime(&cron, &current);
```

### Timezone support and DST rules
```c
 CronExpression cron;
 parseCronExpression(&cron, "0 0 9 * * *");
 TimeZone zone = timeZoneOf("Europe/Amsterdam");    // create time zone

 ZonedDateTime last = zonedDateTimeOf(2021, 3, 27, 9, 0, 0, 0, &zone);   // Amsterdam winter time has 3600s UTC offset, and clock is moved one hour forward 28 march at 01:00 o'clock
 ZonedDateTime actual = nextCronZonedDateTime(&cron, &last);                 // moving from summer to winter time
 ZonedDateTime expected = zonedDateTimeOf(2021, 3, 28, 9, 0, 0, 0, &zone);   // summer time has 7200s UTC offset
 
 assert_true(isDateTimeEquals(&actual.dateTime, &expected.dateTime));   // check that dates calculated correctly
 assert_true(last.offset == 3600);
 assert_true(actual.offset == 7200);
```
