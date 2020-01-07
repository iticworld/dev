/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 5.
 */

#include <stdarg.h>
#include <string.h>

#include "novemberizing/string.hh"

namespace novemberizing
{
    static const uint32 __format_flag_minus = 0x00000001u << 0u;
    static const uint32 __format_flag_plus = 0x00000001u << 1u;
    static const uint32 __format_flag_space = 0x00000001u << 2u;
    static const uint32 __format_flag_sharp = 0x00000001u << 3u;
    static const uint32 __format_flag_zero = 0x00000001u << 4u;
    static const uint32 __format_flag_unknown = 0;

    static const int32 __format_width_asterisk = -1;
    static const int32 __format_width_unknown = 0;

    static const int32 __format_precision_asterisk = -1;
    static const int32 __format_precision_unknown = 0;

    static const uint32 __format_length_int8 = 1;
    static const uint32 __format_length_int16 = 2;
    static const uint32 __format_length_int32 = 3;
    static const uint32 __format_length_int64 = 4;
    static const uint32 __format_length_uint8 = 5;
    static const uint32 __format_length_uint16 = 6;
    static const uint32 __format_length_uint32 = 7;
    static const uint32 __format_length_uint64 = 8;
    static const uint32 __format_length_float32 = 9;
    static const uint32 __format_length_float64 = 10;
    static const uint32 __format_length_pointer = 11;
    static const uint32 __format_length_string = 12;
    static const uint32 __format_length_percent = 13;
    static const uint32 __format_length_unknown = 0;

    static void __format(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint64 limit, va_list ap);

    template <typename T> static T __format_parameter_get(va_list ap){ return va_arg(ap, T); }

    template <> signed char __format_parameter_get<signed char>(va_list ap){ return (signed char) va_arg(ap, int); }
    template <> short int __format_parameter_get<short int>(va_list ap){ return (short int) va_arg(ap, int); }
    template <> unsigned char __format_parameter_get<unsigned char>(va_list ap){ return (unsigned char) va_arg(ap, int); }
    template <> unsigned short int __format_parameter_get<unsigned short int>(va_list ap){ return (unsigned short int) va_arg(ap, int); }
    template <> float __format_parameter_get<float>(va_list ap){ return (float) va_arg(ap, double); }

    static void __format_adjust_capacity(char ** data, uint64 size, uint64 * capacity, uint64 n);
    static void __format_concatenate_until(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint64 * offset, uint64 limit, char c);

    static uint32 __format_check_flag(const char * fmt, uint64 * offset, uint64 limit);
    static int32 __format_check_width(const char * fmt, uint64 * offset, uint64 limit);
    static int32 __format_check_precision(const char * fmt, uint64 * offset, uint64 limit);
    static uint32 __format_check_length(const char * fmt, uint64 * offset, uint64 limit);

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, va_list ap);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int8 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int16 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int32 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int64 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float32 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float64 v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const void * v);
    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const char * v);

    static void __format_concatenate_character(char ** data, uint64 * size, uint64 * capacity, char c);
    static void __format_concatenate_character(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int8 v);
    static void __format_concatenate_character(char ** data, uint64 * size, uint64 * capacity, char c, uint64 n);

    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint64 * offset, uint64 limit);
    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * s, uint64 len);
    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * s);
    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const char * v);
    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const char * v, uint64 len);

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int8 v);
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int16 v);
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int32 v);
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int64 v);
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v);
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v);
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v);
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v);

    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v);
    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v);
    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v);
    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v);

    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v);
    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v);
    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v);
    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v);

    static void __format_concatenate_use_sprintf(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float32 v);
    static void __format_concatenate_use_sprintf(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float64 v);

    static void __format_concatenate_pointer(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const void * v);



    string string::format(const char * fmt, ...)
    {
        string out;
        va_list ap;
        va_start(ap, fmt);
        __format(&out.__data, &out.__size, &out.__capacity, fmt, string::length(fmt), ap);
        va_end(ap);
        return out;
    }

    static void __format(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint64 limit, va_list ap)
    {
        uint64 offset = 0;
        while(offset <= limit)
        {
            __format_concatenate_until(data, size, capacity, fmt, &offset, limit, '%');
            if(offset < limit)
            {
                /** implement this */
                uint64 position = offset + 1;
                uint32 flag = __format_check_flag(fmt, &position, limit);
                int32 width = __format_check_width(fmt, &position, limit);
                int32 precision = __format_check_precision(fmt, &position, limit);
                uint32 length = __format_check_length(fmt, &position, limit);
                if(length != __format_length_unknown)
                {
                    if(length == __format_length_percent)
                    {
                        __format_concatenate_character(data, size, capacity, '%');
                        offset = position + 2;
                        (*data)[*size] = 0;
                    }
                    else
                    {
                        char specifier = fmt[position];
                        if(width == __format_width_asterisk)
                        {
                            width = __format_parameter_get<uint32>(ap);
                        }
                        if(precision == __format_precision_asterisk)
                        {
                            precision = __format_parameter_get<uint32>(ap);
                        }
                        char * _fmt = string::create(&fmt[offset], position + 1 - offset);
                        __format_concatenate_parameter(data, size, capacity, _fmt, flag, width, precision, length, specifier, ap);
                        ::free(_fmt);
                        offset = position + 1;
                        (*data)[*size] = 0;
                    }
                    continue;
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, fmt, &offset, limit);
                }
            }
            (*data)[*size] = 0;
            break;
        }
    }

    static void __format_concatenate_until(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint64 * offset, uint64 limit, char c)
    {
        __format_adjust_capacity(data, *size, capacity, limit - *offset);
        for(;*offset < limit; *offset += 1, *size += 1)
        {
            if(fmt[*offset] != c)
            {
                (*data)[*size] = fmt[*offset];
                continue;
            }
            break;
        }
    }

    static void __format_adjust_capacity(char ** data, uint64 size, uint64 * capacity, uint64 n)
    {
        if(*capacity - size < n)
        {
            *capacity = capacity::get(size + n, string::page);
            *data = core::memory::allocate<char>(*data, *capacity);
        }
    }

    static uint32 __format_check_flag(const char * fmt, uint64 * offset, uint64 limit)
    {
        uint32 flags = __format_flag_unknown;
        uint64 position = *offset;
        while(position < limit)
        {
            if(fmt[position] == '+')
            {
                flags |= __format_flag_plus;
            }
            else if(fmt[position] == '-')
            {
                flags |= __format_flag_minus;
            }
            else if(fmt[position] == ' ')
            {
                flags |= __format_flag_space;
            }
            else if(fmt[position] == '#')
            {
                flags |= __format_flag_sharp;
            }
            else if(fmt[position] == '0')
            {
                flags |= __format_flag_zero;
            }
            else
            {
                *offset = position;
                return flags;
            }
            position += 1;
        }
        *offset = position;
        return flags;
    }

    static int32 __format_check_width(const char * fmt, uint64 * offset, uint64 limit)
    {
        uint64 position = *offset;
        if(position < limit)
        {
            if(fmt[position] == '*')
            {
                *offset += 1;
                return __format_width_asterisk;
            }
            if(48 <= fmt[position] && fmt[position] <= 57)
            {
                uint32 n = 0;
                for(;48 <= fmt[position] && fmt[position] <= 57 && position < limit; position++, n = n * 10)
                {
                    n += fmt[position] - 48;
                }
                *offset = position;
                return n;
            }
            return __format_width_unknown;
        }
    }

    static int32 __format_check_precision(const char * fmt, uint64 * offset, uint64 limit)
    {
        uint64 position = *offset;
        if(position < limit)
        {
            if(fmt[position] == '.')
            {
                position++;
                if(position < limit)
                {
                    if(fmt[position] == '*')
                    {
                        *offset += 2;
                        return __format_precision_asterisk;
                    }
                    if(48 <= fmt[position] && fmt[position] <= 57)
                    {
                        uint32 n = 0;
                        for(;48 <= fmt[position] && fmt[position] <= 57 && position < limit; position++, n = n * 10)
                        {
                            n += fmt[position]- 48;
                        }
                        *offset = position;
                        return n;
                    }
                }
            }
        }
        return __format_precision_unknown;
    }

    static uint32 __format_check_length(const char * _format, uint64 * offset, uint64 limit)
    {
        uint64 position = *offset;
        if(position >= limit){ return __format_length_unknown; }
        if(_format[position] == 'h')
        {
            if(position + 1 < limit)
            {
                if(_format[position + 1] == 'h' && position + 2 < limit)
                {
                    switch(_format[position + 2])
                    {
                        case 'd': *offset = position + 2; return __format_length_int8;
                        case 'i': *offset = position + 2; return __format_length_int8;
                        case 'u': *offset = position + 2; return __format_length_uint8;
                        case 'o': *offset = position + 2; return __format_length_uint8;
                        case 'x': *offset = position + 2; return __format_length_uint8;
                        case 'X': *offset = position + 2; return __format_length_uint8;
                        case 'f': *offset = position + 2; return __format_length_float32;
                        case 'F': *offset = position + 2; return __format_length_float32;
                        case 'e': *offset = position + 2; return __format_length_float32;
                        case 'E': *offset = position + 2; return __format_length_float32;
                        case 'g': *offset = position + 2; return __format_length_float32;
                        case 'G': *offset = position + 2; return __format_length_float32;
                        case 'a': *offset = position + 2; return __format_length_float32;
                        case 'A': *offset = position + 2; return __format_length_float32;
                        case 'c': *offset = position + 2; return __format_length_int8;
                        case 's': *offset = position + 2; return __format_length_string;
                        case 'p': *offset = position + 2; return __format_length_pointer;
                        case 'n': *offset = position + 2; return __format_length_pointer;
                        default:                          return __format_length_unknown;
                    }
                }
                else
                {
                    switch(_format[position + 1])
                    {
                        case 'd': *offset = position + 1; return __format_length_int16;
                        case 'i': *offset = position + 1; return __format_length_int16;
                        case 'u': *offset = position + 1; return __format_length_uint16;
                        case 'o': *offset = position + 1; return __format_length_uint16;
                        case 'x': *offset = position + 1; return __format_length_uint16;
                        case 'X': *offset = position + 1; return __format_length_uint16;
                        case 'f': *offset = position + 1; return __format_length_float32;
                        case 'F': *offset = position + 1; return __format_length_float32;
                        case 'e': *offset = position + 1; return __format_length_float32;
                        case 'E': *offset = position + 1; return __format_length_float32;
                        case 'g': *offset = position + 1; return __format_length_float32;
                        case 'G': *offset = position + 1; return __format_length_float32;
                        case 'a': *offset = position + 1; return __format_length_float32;
                        case 'A': *offset = position + 1; return __format_length_float32;
                        case 'c': *offset = position + 1; return __format_length_int8;
                        case 's': *offset = position + 1; return __format_length_string;
                        case 'p': *offset = position + 1; return __format_length_pointer;
                        case 'n': *offset = position + 1; return __format_length_pointer;
                        default:                          return __format_length_unknown;
                    }
                }
            }
            return __format_length_unknown;
        }
        if(_format[position] == 'l')
        {
            if(position + 1 < limit)
            {
                if(_format[position + 1] == 'l' && position + 2 < limit)
                {
                    switch(_format[position + 2])
                    {
                        case 'd': *offset = position + 2; return __format_length_int64;
                        case 'i': *offset = position + 2; return __format_length_int64;
                        case 'u': *offset = position + 2; return __format_length_uint64;
                        case 'o': *offset = position + 2; return __format_length_uint64;
                        case 'x': *offset = position + 2; return __format_length_uint64;
                        case 'X': *offset = position + 2; return __format_length_uint64;
                        case 'f': *offset = position + 2; return __format_length_float64;
                        case 'F': *offset = position + 2; return __format_length_float64;
                        case 'e': *offset = position + 2; return __format_length_float64;
                        case 'E': *offset = position + 2; return __format_length_float64;
                        case 'g': *offset = position + 2; return __format_length_float64;
                        case 'G': *offset = position + 2; return __format_length_float64;
                        case 'a': *offset = position + 2; return __format_length_float64;
                        case 'A': *offset = position + 2; return __format_length_float64;
                        case 'c': *offset = position + 2; return __format_length_int8;
                        case 's': *offset = position + 2; return __format_length_string;
                        case 'p': *offset = position + 2; return __format_length_pointer;
                        case 'n': *offset = position + 2; return __format_length_pointer;
                        default:                          return __format_length_unknown;
                    }
                }
                else
                {
                    switch(_format[position + 1])
                    {
                        case 'd': *offset = position + 1; return __format_length_int64;
                        case 'i': *offset = position + 1; return __format_length_int64;
                        case 'u': *offset = position + 1; return __format_length_uint64;
                        case 'o': *offset = position + 1; return __format_length_uint64;
                        case 'x': *offset = position + 1; return __format_length_uint64;
                        case 'X': *offset = position + 1; return __format_length_uint64;
                        case 'f': *offset = position + 1; return __format_length_float64;
                        case 'F': *offset = position + 1; return __format_length_float64;
                        case 'e': *offset = position + 1; return __format_length_float64;
                        case 'E': *offset = position + 1; return __format_length_float64;
                        case 'g': *offset = position + 1; return __format_length_float64;
                        case 'G': *offset = position + 1; return __format_length_float64;
                        case 'a': *offset = position + 1; return __format_length_float64;
                        case 'A': *offset = position + 1; return __format_length_float64;
                        case 'c': *offset = position + 1; return __format_length_int8;
                        case 's': *offset = position + 1; return __format_length_string;
                        case 'p': *offset = position + 1; return __format_length_pointer;
                        case 'n': *offset = position + 1; return __format_length_pointer;
                        default:                          return __format_length_unknown;
                    }
                }
            }
            return __format_length_unknown;
        }
        if(_format[position] == 'j')
        {
            switch(_format[position + 1])
            {
                case 'd': *offset = position + 1; return __format_length_int64;
                case 'i': *offset = position + 1; return __format_length_int64;
                case 'u': *offset = position + 1; return __format_length_uint64;
                case 'o': *offset = position + 1; return __format_length_uint64;
                case 'x': *offset = position + 1; return __format_length_uint64;
                case 'X': *offset = position + 1; return __format_length_uint64;
                case 'f': *offset = position + 1; return __format_length_float64;
                case 'F': *offset = position + 1; return __format_length_float64;
                case 'e': *offset = position + 1; return __format_length_float64;
                case 'E': *offset = position + 1; return __format_length_float64;
                case 'g': *offset = position + 1; return __format_length_float64;
                case 'G': *offset = position + 1; return __format_length_float64;
                case 'a': *offset = position + 1; return __format_length_float64;
                case 'A': *offset = position + 1; return __format_length_float64;
                case 'c': *offset = position + 1; return __format_length_int8;
                case 's': *offset = position + 1; return __format_length_string;
                case 'p': *offset = position + 1; return __format_length_pointer;
                case 'n': *offset = position + 1; return __format_length_pointer;
                default:                          return __format_length_unknown;
            }
        }
        if(_format[position] == 'z')
        {
            switch(_format[position + 1])
            {
                case 'd': *offset = position + 1; return __format_length_int64;
                case 'i': *offset = position + 1; return __format_length_int64;
                case 'u': *offset = position + 1; return __format_length_uint64;
                case 'o': *offset = position + 1; return __format_length_uint64;
                case 'x': *offset = position + 1; return __format_length_uint64;
                case 'X': *offset = position + 1; return __format_length_uint64;
                case 'f': *offset = position + 1; return __format_length_float64;
                case 'F': *offset = position + 1; return __format_length_float64;
                case 'e': *offset = position + 1; return __format_length_float64;
                case 'E': *offset = position + 1; return __format_length_float64;
                case 'g': *offset = position + 1; return __format_length_float64;
                case 'G': *offset = position + 1; return __format_length_float64;
                case 'a': *offset = position + 1; return __format_length_float64;
                case 'A': *offset = position + 1; return __format_length_float64;
                case 'c': *offset = position + 1; return __format_length_int8;
                case 's': *offset = position + 1; return __format_length_string;
                case 'p': *offset = position + 1; return __format_length_pointer;
                case 'n': *offset = position + 1; return __format_length_pointer;
                default:                          return __format_length_unknown;
            }
        }
        if(_format[position] == 't')
        {
            switch(_format[position + 1])
            {
                case 'd': *offset = position + 1; return __format_length_int64;
                case 'i': *offset = position + 1; return __format_length_int64;
                case 'u': *offset = position + 1; return __format_length_uint64;
                case 'o': *offset = position + 1; return __format_length_uint64;
                case 'x': *offset = position + 1; return __format_length_uint64;
                case 'X': *offset = position + 1; return __format_length_uint64;
                case 'f': *offset = position + 1; return __format_length_float64;
                case 'F': *offset = position + 1; return __format_length_float64;
                case 'e': *offset = position + 1; return __format_length_float64;
                case 'E': *offset = position + 1; return __format_length_float64;
                case 'g': *offset = position + 1; return __format_length_float64;
                case 'G': *offset = position + 1; return __format_length_float64;
                case 'a': *offset = position + 1; return __format_length_float64;
                case 'A': *offset = position + 1; return __format_length_float64;
                case 'c': *offset = position + 1; return __format_length_int8;
                case 's': *offset = position + 1; return __format_length_string;
                case 'p': *offset = position + 1; return __format_length_pointer;
                case 'n': *offset = position + 1; return __format_length_pointer;
                default:                          return __format_length_unknown;
            }
        }
        if(_format[position] == 'L')
        {
            switch(_format[position + 1])
            {
                case 'd': *offset = position + 1; return __format_length_int64;
                case 'i': *offset = position + 1; return __format_length_int64;
                case 'u': *offset = position + 1; return __format_length_uint64;
                case 'o': *offset = position + 1; return __format_length_uint64;
                case 'x': *offset = position + 1; return __format_length_uint64;
                case 'X': *offset = position + 1; return __format_length_uint64;
                case 'f': *offset = position + 1; return __format_length_float64;
                case 'F': *offset = position + 1; return __format_length_float64;
                case 'e': *offset = position + 1; return __format_length_float64;
                case 'E': *offset = position + 1; return __format_length_float64;
                case 'g': *offset = position + 1; return __format_length_float64;
                case 'G': *offset = position + 1; return __format_length_float64;
                case 'a': *offset = position + 1; return __format_length_float64;
                case 'A': *offset = position + 1; return __format_length_float64;
                case 'c': *offset = position + 1; return __format_length_int8;
                case 's': *offset = position + 1; return __format_length_string;
                case 'p': *offset = position + 1; return __format_length_pointer;
                case 'n': *offset = position + 1; return __format_length_pointer;
                default:                          return __format_length_unknown;
            }
        }
        switch(_format[position])
        {
            case 'd': *offset = position; return __format_length_int32;
            case 'i': *offset = position; return __format_length_int32;
            case 'u': *offset = position; return __format_length_uint32;
            case 'o': *offset = position; return __format_length_uint32;
            case 'x': *offset = position; return __format_length_uint32;
            case 'X': *offset = position; return __format_length_uint32;
            case 'f': *offset = position; return __format_length_float32;
            case 'F': *offset = position; return __format_length_float32;
            case 'e': *offset = position; return __format_length_float32;
            case 'E': *offset = position; return __format_length_float32;
            case 'g': *offset = position; return __format_length_float32;
            case 'G': *offset = position; return __format_length_float32;
            case 'a': *offset = position; return __format_length_float32;
            case 'A': *offset = position; return __format_length_float32;
            case 'c': *offset = position; return __format_length_int8;
            case 's': *offset = position; return __format_length_string;
            case 'p': *offset = position; return __format_length_pointer;
            case 'n': *offset = position; return __format_length_pointer;
            case '%': *offset = position; return __format_length_percent;
            default:                      return __format_length_unknown;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, va_list ap)
    {
        switch(length)
        {
            case __format_length_int8:      __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<int8>(ap));         return;
            case __format_length_int16:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<int16>(ap));        return;
            case __format_length_int32:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<int32>(ap));        return;
            case __format_length_int64:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<int64>(ap));        return;
            case __format_length_uint8:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<uint8>(ap));        return;
            case __format_length_uint16:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<uint16>(ap));       return;
            case __format_length_uint32:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<uint32>(ap));       return;
            case __format_length_uint64:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<uint64>(ap));       return;
            case __format_length_float32:   __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<float32>(ap));      return;
            case __format_length_float64:   __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<float64>(ap));      return;
            case __format_length_pointer:   __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<const void *>(ap)); return;
            case __format_length_string:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, __format_parameter_get<const char *>(ap)); return;
            default:                                                                                                                                                                        return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int8 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'c': __format_concatenate_character(data, size, capacity, fmt, flag, width, precision, length, specifier, v);          return;
            default:                                                                                                                    return;
        }

    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int16 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                    return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int32 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                    return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int64 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                    return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v)
    {
        switch(specifier)
        {
            case 'u': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);     return;
            case 'o': __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);       return;
            case 'x': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'X': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                        return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v)
    {
        switch(specifier)
        {
            case 'u': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);     return;
            case 'o': __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);       return;
            case 'x': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'X': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                        return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v)
    {
        switch(specifier)
        {
            case 'u': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);     return;
            case 'o': __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);       return;
            case 'x': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'X': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                        return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v)
    {
        switch(specifier)
        {
            case 'u': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);     return;
            case 'o': __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, v);       return;
            case 'x': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'X': __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                        return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float32 v)
    {
        switch(specifier)
        {
            case 'f': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'F': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'e': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'E': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'g': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'G': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'a': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'A': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            default:                                                                                                                return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float64 v)
    {
        switch(specifier)
        {
            case 'f': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'F': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'e': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'E': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'g': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'G': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'a': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            case 'A': __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, v);    return;
            default:                                                                                                                return;
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const void * v)
    {
        if(specifier == 'p')
        {
            __format_concatenate_pointer(data, size, capacity, fmt, flag, width, precision, length, specifier, v);
        }
    }

    static void __format_concatenate_parameter(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const char * v)
    {
        if(specifier == 's')
        {
            __format_concatenate_string(data, size, capacity, fmt, flag, width, precision, length, specifier, v);
        }
    }

    static void __format_concatenate_character(char ** data, uint64 * size, uint64 * capacity, char c)
    {
        __format_adjust_capacity(data, *size, capacity, 1);
        (*data)[*size] = c;
        *size += 1;
    }

    static void __format_concatenate_character(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int8 v)
    {
        (void)(fmt);
        (void)(precision);
        (void)(length);
        (void)(specifier);
        if(width > 1)
        {
            if(flag == __format_flag_minus)
            {
                __format_concatenate_character(data, size, capacity, ' ', (uint64) width - 1);
                __format_concatenate_character(data, size, capacity, (char) v);
            }
            else
            {
                __format_concatenate_character(data, size, capacity, (char) v);
                __format_concatenate_character(data, size, capacity, ' ', (uint64) width - 1);
            }
        }
        else
        {
            __format_concatenate_character(data, size, capacity, (char) v);
        }
    }

    static void __format_concatenate_character(char ** data, uint64 * size, uint64 * capacity, char c, uint64 n)
    {
        __format_adjust_capacity(data, *size, capacity, n);
        memset(&(*data)[*size], c, n);
        *size += n;
    }

    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint64 * offset, uint64 limit)
    {
        __format_adjust_capacity(data, *size, capacity, limit - *offset);
        for(;*offset < limit; *offset += 1, *size += 1)
        {
            (*data)[*size] = fmt[*offset];
        }
    }

    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * s, uint64 len)
    {
        if(s != nullptr && len > 0)
        {
            __format_adjust_capacity(data, *size, capacity, len);
            ::memcpy(&(*data)[*size], s, len);
            *size += len;
        }
    }

    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * s)
    {
        __format_concatenate_string(data, size, capacity, s, s != nullptr ? ::strlen(s) : 0);
    }

    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const char * v)
    {
        __format_concatenate_string(data, size, capacity, fmt, flag, width, precision, length, specifier, v, v!=nullptr ? ::strlen(v) : 0);
    }

    static void __format_concatenate_string(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const char * v, uint64 len)
    {
        if(v != nullptr && len > 0)
        {
            (void)(fmt);
            (void)(flag);
            (void)(width);
            (void)(length);
            (void)(precision);
            (void)(specifier);
            __format_adjust_capacity(data, *size, capacity, len);
            ::memcpy(&(*data)[*size], v, len);
            *size += len;
        }
    }

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int8 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (int64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int16 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (int64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int32 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (int64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, int64 v)
    {
        (void)(precision);
        char sign = 0;
        if(v >= 0)
        {
            if(flag & __format_flag_plus)
            {
                sign = '+';
            }
            else if(flag & __format_flag_space)
            {
                sign = ' ';
            }

        }
        else
        {
            sign = '-';
            v = v * (int8)(-1);
        }
        const uint64 max = 1024;
        uint64 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                int64 remain = v % 10;
                str[--index] = (char) (remain + 48);
                v = v / (int8) 10;
            }
        }
        else
        {
            str[--index] = '0';
        }
        int64 len = max - index - 1 + (sign ? 1 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_character(data, size, capacity, '0', width - 1 - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, '0', width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
            }
            else if(flag & __format_flag_minus)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', width - 1 - (max - index - 1));
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', width - (max - index - 1));
                }
            }
            else
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, ' ', width - 1 - (max - index - 1));
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
            }
        }
        else
        {
            if(sign)
            {
                __format_concatenate_character(data, size, capacity, sign);
            }
            __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
        }

    }
    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v)
    {
        (void)(fmt);
        (void)(precision);
        char sign = 0;
        if(flag & __format_flag_plus)
        {
            sign = '+';
        }
        else if(flag & __format_flag_space)
        {
            sign = ' ';
        }
        const int32 max = 1024;
        int32 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                uint64 remain = v % 10;
                str[--index] = (char) (remain + 48);
                v = v / (int8) 10;
            }
        }
        else
        {
            str[--index] = '0';
        }
        int32 len = max - index - 1 + (sign ? 1 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_character(data, size, capacity, '0', (uint64) width - 1 - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, '0', (uint64) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
            }
            else if(flag & __format_flag_minus)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - 1 - (max - index - 1));
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index - 1));
                }
            }
            else
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - 1 - (max - index - 1));
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
                }
            }
        }
        else
        {
            if(sign)
            {
                __format_concatenate_character(data, size, capacity, sign);
            }
            __format_concatenate_string(data, size, capacity, &str[index], (uint64) (max - index - 1));
        }
    }

    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v)
    {
        __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v)
    {
        __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v)
    {
        __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_octal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v)
    {
        (void)(fmt);
        const int32 max = 1024;
        int32 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                uint64 remain = v & 0x07u;
                str[--index] = (char) (remain + 48);
                v = (v >> 3u);
            }
        }
        else
        {
            str[--index] = '0';
        }
        int32 len = max - index - 1 + ((flag & __format_flag_sharp) ? 1 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                __format_concatenate_character(data, size, capacity, '0', (uint64) width - (max - index - 1));
                __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
            }
            else if(flag & __format_flag_minus)
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_character(data, size, capacity, '0');
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index));
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index - 1));
                }
            }
            else
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index));
                    __format_concatenate_character(data, size, capacity, '0');
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                }
            }
        }

    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint8 v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint16 v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint32 v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (uint64) v);
    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, uint64 v)
    {
        (void)(fmt);
        const int32 max = 1024;
        int32 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                uint64 remain = v & 0x0Fu;
                if(remain >= 10)
                {
                    if(specifier=='X')
                    {
                        str[--index] = (char) (remain + 55);
                    }
                    else
                    {
                        str[--index] = (char) (remain + 87);
                    }
                }
                else
                {
                    str[--index] = (char) (remain + 48);
                }
                v = (v >> 4u);
            }
        }
        else
        {
            str[--index] = '0';
        }
        int32 len = max - index - 1 + ((flag & __format_flag_sharp) ? 2 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_string(data, size, capacity, "0x");
                    __format_concatenate_character(data, size, capacity, '0', (uint64) width - (max - index) - 1);
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, '0', (uint64) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                }
            }
            else if(flag & __format_flag_minus)
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_string(data, size, capacity, "0x");
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index) - 1);
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index - 1));
                }
            }
            else
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index) - 1);
                    __format_concatenate_string(data, size, capacity, "0x");
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', (uint64) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
                }
            }
        }
        else
        {
            __format_concatenate_string(data, size, capacity, &str[index], (uint64) max - index - 1);
        }
    }

    static void __format_concatenate_use_sprintf(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float32 v)
    {
        __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, (float64) v);
    }

    static void __format_concatenate_use_sprintf(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, float64 v)
    {
        (void)(flag);
        (void)(width);
        (void)(precision);
        (void)(length);
        (void)(specifier);
        const uint64 max = 1024;
        char str[1024];
        snprintf(str, max, fmt, v);
        __format_concatenate_string(data, size, capacity, str);
    }

    static void __format_concatenate_pointer(char ** data, uint64 * size, uint64 * capacity, const char * fmt, uint32 flag, int32 width, int32 precision, uint32 length, char specifier, const void * v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag | __format_flag_sharp, width, precision, length, specifier, (uint64) v);
    }
}

