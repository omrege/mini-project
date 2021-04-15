
                    switch (*pch)
                    {
                        case 'd':
                        case 'i':
                            {
                                const int number = va_arg(va, int);
                                UnityPrintNumber((UNITY_INT)number);
                                break;
                            }
#ifndef UNITY_EXCLUDE_FLOAT_PRINT
                        case 'f':
                        case 'g':
                            {
                                const double number = va_arg(va, double);
                                UnityPrintFloat((UNITY_DOUBLE)number);
                                break;
                            }
#endif
                        case 'u':
                            {
                                const unsigned int number = va_arg(va, unsigned int);
                                UnityPrintNumberUnsigned((UNITY_UINT)number);
                                break;
                            }
                        case 'b':
                            {
                                const unsigned int number = va_arg(va, unsigned int);
                                const UNITY_UINT mask = (UNITY_UINT)0 - (UNITY_UINT)1;
                                UNITY_OUTPUT_CHAR('0');
                                UNITY_OUTPUT_CHAR('b');
                                UnityPrintMask(mask, (UNITY_UINT)number);
                                break;
                            }
                        case 'x':
                        case 'X':
                        case 'p':
                            {
                                const unsigned int number = va_arg(va, unsigned int);
                                UNITY_OUTPUT_CHAR('0');
                                UNITY_OUTPUT_CHAR('x');
                                UnityPrintNumberHex((UNITY_UINT)number, 8);
                                break;
                            }
                        case 'c':
                            {
                                const int ch = va_arg(va, int);
                                UnityPrintChar((const char *)&ch);
                                break;
                            }
                        case 's':
                            {
                                const char * string = va_arg(va, const char *);
                                UnityPrint(string);
                                break;
                            }
                        case '%':
                            {
                                UnityPrintChar(pch);
                                break;
                            }
                        default:
                            {
                                /* print the unknown format character */
                                UNITY_OUTPUT_CHAR('%');
                                UnityPrintChar(pch);
                                break;
                            }
                    }
                }
            }
#ifdef UNITY_OUTPUT_COLOR
            /* print ANSI escape code */
            else if ((*pch == 27) && (*(pch + 1) == '['))
            {
                pch += UnityPrintAnsiEscapeString(pch);
                continue;
            }
#endif
            else if (*pch == '\n')
            {
                UNITY_PRINT_EOL();
            }
            else
            {
                UnityPrintChar(pch);
            }

            pch++;
        }
    }
}

void UnityPrintF(const UNITY_LINE_TYPE line, const char* format, ...)
{
    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrint("INFO");
    if(format != NULL)
    {
        UnityPrint(": ");
        va_list va;
        va_start(va, format);
        UnityPrintFVA(format, va);
        va_end(va);
    }
    UNITY_PRINT_EOL();
}
#endif /* ! UNITY_INCLUDE_PRINT_FORMATTED */


/*-----------------------------------------------
 * Control Functions
 *-----------------------------------------------*/

/*-----------------------------------------------*/
void UnityFail(const char* msg, const UNITY_LINE_TYPE line)
{
    RETURN_IF_FAIL_OR_IGNORE;

    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrint(UnityStrFail);
    if (msg != NULL)
    {
        UNITY_OUTPUT_CHAR(':');

#ifdef UNITY_PRINT_TEST_CONTEXT
        UNITY_PRINT_TEST_CONTEXT();
#endif
#ifndef UNITY_EXCLUDE_DETAILS
        if (Unity.CurrentDetail1)
        {
            UnityPrint(UnityStrDetail1Name);
            UnityPrint(Unity.CurrentDetail1);
            if (Unity.CurrentDetail2)
            {
                UnityPrint(UnityStrDetail2Name);
                UnityPrint(Unity.CurrentDetail2);
            }
            UnityPrint(UnityStrSpacer);
        }
#endif
        if (msg[0] != ' ')
        {
            UNITY_OUTPUT_CHAR(' ');
        }
        UnityPrint(msg);
    }

    UNITY_FAIL_AND_BAIL;
}

/*-----------------------------------------------*/
void UnityIgnore(const char* msg, const UNITY_LINE_TYPE line)
{
    RETURN_IF_FAIL_OR_IGNORE;

    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrint(UnityStrIgnore);
    if (msg != NULL)
    {
        UNITY_OUTPUT_CHAR(':');
        UNITY_OUTPUT_CHAR(' ');
        UnityPrint(msg);
    }
    UNITY_IGNORE_AND_BAIL;
}

/*-----------------------------------------------*/
void UnityMessage(const char* msg, const UNITY_LINE_TYPE line)
{
    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrint("INFO");
    if (msg != NULL)
    {
      UNITY_OUTPUT_CHAR(':');
      UNITY_OUTPUT_CHAR(' ');
      UnityPrint(msg);
    }
    UNITY_PRINT_EOL();
}

/*-----------------------------------------------*/
/* If we have not defined our own test runner, then include our default test runner to make life easier */
#ifndef UNITY_SKIP_DEFAULT_RUNNER
void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum)
{
    Unity.CurrentTestName = FuncName;
    Unity.CurrentTestLineNumber = (UNITY_LINE_TYPE)FuncLineNum;
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    if (TEST_PROTECT())
    {
        setUp();
        Func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
    }
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}
#endif

/*-----------------------------------------------*/
void UnitySetTestFile(const char* filename)
{
	Unity.TestFile = filename;
}

/*-----------------------------------------------*/
void UnityBegin(const char* filename)
{
    Unity.TestFile = filename;
    Unity.CurrentTestName = NULL;
    Unity.CurrentTestLineNumber = 0;
    Unity.NumberOfTests = 0;
    Unity.TestFailures = 0;
    Unity.TestIgnores = 0;
    Unity.CurrentTestFailed = 0;
    Unity.CurrentTestIgnored = 0;

    UNITY_CLR_DETAILS();
    UNITY_OUTPUT_START();
}

/*-----------------------------------------------*/
int UnityEnd(void)
{
    UNITY_PRINT_EOL();
    UnityPrint(UnityStrBreaker);
    UNITY_PRINT_EOL();
    UnityPrintNumber((UNITY_INT)(Unity.NumberOfTests));
    UnityPrint(UnityStrResultsTests);
    UnityPrintNumber((UNITY_INT)(Unity.TestFailures));
    UnityPrint(UnityStrResultsFailures);
    UnityPrintNumber((UNITY_INT)(Unity.TestIgnores));
    UnityPrint(UnityStrResultsIgnored);
    UNITY_PRINT_EOL();
    if (Unity.TestFailures == 0U)
    {
        UnityPrint(UnityStrOk);
    }
    else
    {
        UnityPrint(UnityStrFail);
#ifdef UNITY_DIFFERENTIATE_FINAL_FAIL
        UNITY_OUTPUT_CHAR('E'); UNITY_OUTPUT_CHAR('D');
#endif
    }
    UNITY_PRINT_EOL();
    UNITY_FLUSH_CALL();
    UNITY_OUTPUT_COMPLETE();
    return (int)(Unity.TestFailures);
}

/*-----------------------------------------------
 * Command Line Argument Support
 *-----------------------------------------------*/
#ifdef UNITY_USE_COMMAND_LINE_ARGS

char* UnityOptionIncludeNamed = NULL;
char* UnityOptionExcludeNamed = NULL;
int UnityVerbosity            = 1;

/*-----------------------------------------------*/
int UnityParseOptions(int argc, char** argv)
{
    int i;
    UnityOptionIncludeNamed = NULL;
    UnityOptionExcludeNamed = NULL;

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
                case 'l': /* list tests */
                    return -1;
                case 'n': /* include tests with name including this string */
                case 'f': /* an alias for -n */
                    if (argv[i][2] == '=')
                    {
                        UnityOptionIncludeNamed = &argv[i][3];
                    }
                    else if (++i < argc)
                    {
                        UnityOptionIncludeNamed = argv[i];
                    }
                    else
                    {
                        UnityPrint("ERROR: No Test String to Include Matches For");
                        UNITY_PRINT_EOL();
                        return 1;
                    }
                    break;
                case 'q': /* quiet */
                    UnityVerbosity = 0;
                    break;
                case 'v': /* verbose */
                    UnityVerbosity = 2;
                    break;
                case 'x': /* exclude tests with name including this string */
                    if (argv[i][2] == '=')
                    {
                        UnityOptionExcludeNamed = &argv[i][3];
                    }
                    else if (++i < argc)
                    {
                        UnityOptionExcludeNamed = argv[i];
                    }
                    else
                    {
                        UnityPrint("ERROR: No Test String to Exclude Matches For");
                        UNITY_PRINT_EOL();
                        return 1;
                    }
                    break;
                default:
                    UnityPrint("ERROR: Unknown Option ");
                    UNITY_OUTPUT_CHAR(argv[i][1]);
                    UNITY_PRINT_EOL();
                    return 1;
            }
        }
    }

    return 0;
}

/*-----------------------------------------------*/
int IsStringInBiggerString(const char* longstring, const char* shortstring)
{
    const char* lptr = longstring;
    const char* sptr = shortstring;
    const char* lnext = lptr;

    if (*sptr == '*')
    {
        return 1;
    }

    while (*lptr)
    {
        lnext = lptr + 1;

        /* If they current bytes match, go on to the next bytes */
        while (*lptr && *sptr && (*lptr == *sptr))
        {
            lptr++;
            sptr++;

            /* We're done if we match the entire string or up to a wildcard */
            if (*sptr == '*')
                return 1;
            if (*sptr == ',')
                return 1;
            if (*sptr == '"')
                return 1;
            if (*sptr == '\'')
                return 1;
            if (*sptr == ':')
                return 2;
            if (*sptr == 0)
                return 1;
        }

        /* Otherwise we start in the long pointer 1 character further and try again */
        lptr = lnext;
        sptr = shortstring;
    }

    return 0;
}

/*-----------------------------------------------*/
int UnityStringArgumentMatches(const char* str)
{
    int retval;
    const char* ptr1;
    const char* ptr2;
    const char* ptrf;

    /* Go through the options and get the substrings for matching one at a time */
    ptr1 = str;
    while (ptr1[0] != 0)
    {
        if ((ptr1[0] == '"') || (ptr1[0] == '\''))
        {
            ptr1++;
        }

        /* look for the start of the next partial */
        ptr2 = ptr1;
        ptrf = 0;
        do
        {
            ptr2++;
            if ((ptr2[0] == ':') && (ptr2[1] != 0) && (ptr2[0] != '\'') && (ptr2[0] != '"') && (ptr2[0] != ','))
            {
                ptrf = &ptr2[1];
            }
        } while ((ptr2[0] != 0) && (ptr2[0] != '\'') && (ptr2[0] != '"') && (ptr2[0] != ','));

        while ((ptr2[0] != 0) && ((ptr2[0] == ':') || (ptr2[0] == '\'') || (ptr2[0] == '"') || (ptr2[0] == ',')))
        {
            ptr2++;
        }

        /* done if complete filename match */
        retval = IsStringInBiggerString(Unity.TestFile, ptr1);
        if (retval == 1)
        {
            return retval;
        }

        /* done if testname match after filename partial match */
        if ((retval == 2) && (ptrf != 0))
        {
            if (IsStringInBiggerString(Unity.CurrentTestName, ptrf))
            {
                return 1;
            }
        }

        /* done if complete testname match */
        if (IsStringInBiggerString(Unity.CurrentTestName, ptr1) == 1)
        {
            return 1;
        }

        ptr1 = ptr2;
    }

    /* we couldn't find a match for any substrings */
    return 0;
}

/*-----------------------------------------------*/
int UnityTestMatches(void)
{
    /* Check if this test name matches the included test pattern */
    int retval;
    if (UnityOptionIncludeNamed)
    {
        retval = UnityStringArgumentMatches(UnityOptionIncludeNamed);
    }
    else
    {
        retval = 1;
    }

    /* Check if this test name matches the excluded test pattern */
    if (UnityOptionExcludeNamed)
    {
        if (UnityStringArgumentMatches(UnityOptionExcludeNamed))
        {
            retval = 0;
        }
    }

    return retval;
}

#endif /* UNITY_USE_COMMAND_LINE_ARGS */
/*-----------------------------------------------*/