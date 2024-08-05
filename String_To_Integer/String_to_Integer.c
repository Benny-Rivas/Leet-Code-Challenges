#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

int myAtoi(char* s) 
{
    if (s == NULL)
    {
        return 1; // Null input string
    }

    int s_length = strlen(s);

    if (s_length > 200)
    {
        return 2;   //  Length of s doesn't fit constraints.
    }

    for (int i = 0; i < s_length; i++)
    {
        if ((s[i] != 0) && (s[i] < 32) || (s[i] > 32) && (s[i] < 43) || (s[i] == 44) || (s[i] == 47) || (s[i] > 57) && (s[i] < 65) || (s[i] > 90) && (s[i] < 97) || (s[i] > 122))
        {
            return 3;   // Contents of s do not fit the constraints. Contains characters other than (0-9), ' ', '+', '-', '.'
        }
    }

    bool first_digit = false;
    bool sign_negative = false;
    bool sign_found = false;
    char int_list[200];
    int char_counter = 0;


    for (int i = 0; i < s_length; i++)
    {
            if ((first_digit) && (s[i] > 47) && (s[i] < 58))
            {
                int_list[char_counter] = s[i];
                char_counter++;
            }
            else if (first_digit)
            {
                break;
            }

        if (!first_digit)
        {
            if ((s[i] == 32) && (!sign_found))
            {
                continue; // Skip leading spaces 
            }

            else if ((s[i] == 32) && (sign_found))
            {
                return 0; // Skip leading spaces 
            }

            else if ((s[i] == 45) && (!sign_negative) && (!sign_found))
            {
                sign_negative = true;
                sign_found = true;
            }

            else if ((s[i] == 43) && (!sign_negative) && (!sign_found))
            {
                sign_found = true;
            }

            else if (isdigit(s[i]))
            {
                first_digit = true;
                int_list[char_counter] = s[i];
                char_counter++;
            }

            else if ((s[i] > 64) && (s[i] < 91) || (!first_digit) && (s[i] > 96) && (s[i] < 123) || (!first_digit) && (s[i] == 46) || (s[i] == 46))
            {
                return 0; // Non numeric character before first_digit is found.
            }

            else if (((s[i] == 45) || (s[i] == 43)) && (sign_found))
            {
                return 0; // Multiple signs found before first numerical character 
            }
        }
    }

    int_list[char_counter] = '\0';

    //Convert int_list to signed 32 bit number.

    long result = 0;

    for (int i = 0; i < char_counter; i++) 
    {
        result = result * 10 + (int_list[i] - '0');

        if (sign_negative && -result < INT_MIN) 
        {
            return INT_MIN;
        }

        if (!sign_negative && result > INT_MAX) 
        {
            return INT_MAX;
        }
    }

    if (sign_negative) {
        result = -result;
    }

    return (int)result; 
}

int main() 
{
    char str[] = "   +4545d45456";
    int result = myAtoi(str);
    printf("%d\n", result);
    getchar();

    return 0;
}