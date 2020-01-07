/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 5.
 */

#include <cstdarg>
#include <cstring>
#include <cstdio>

#include "string.hh"

namespace novemberizing
{
    static const type::uint32 __format_flag_minus = 0x00000001u << 0u;
    static const type::uint32 __format_flag_plus = 0x00000001u << 1u;
    static const type::uint32 __format_flag_space = 0x00000001u << 2u;
    static const type::uint32 __format_flag_sharp = 0x00000001u << 3u;
    static const type::uint32 __format_flag_zero = 0x00000001u << 4u;
    static const type::uint32 __format_flag_unknown = 0;

    static const type::int32 __format_width_asterisk = -1;
    static const type::int32 __format_width_unknown = 0;

    static const type::int32 __format_precision_asterisk = -1;
    static const type::int32 __format_precision_unknown = 0;

    static const type::uint32 __format_length_int8 = 1;
    static const type::uint32 __format_length_int16 = 2;
    static const type::uint32 __format_length_int32 = 3;
    static const type::uint32 __format_length_int64 = 4;
    static const type::uint32 __format_length_uint8 = 5;
    static const type::uint32 __format_length_uint16 = 6;
    static const type::uint32 __format_length_uint32 = 7;
    static const type::uint32 __format_length_uint64 = 8;
    static const type::uint32 __format_length_float32 = 9;
    static const type::uint32 __format_length_float64 = 10;
    static const type::uint32 __format_length_pointer = 11;
    static const type::uint32 __format_length_string = 12;
    static const type::uint32 __format_length_percent = 13;
    static const type::uint32 __format_length_unknown = 0;

    static void __format(char ** data, type::size * size, type::size * capacity, const char * fmt, type::size limit, va_list ap);

    static void __format_adjust_capacity(char ** data, type::size size, type::size * capacity, type::size n);
    static void __format_concatenate_until(char ** data, type::size * size, type::size * capacity, const char * fmt, type::size * offset, type::size limit, char c);

    static type::uint32 __format_check_flag(const char * fmt, type::size * offset, type::size limit);
    static type::int32 __format_check_width(const char * fmt, type::size * offset, type::size limit);
    static type::int32 __format_check_precision(const char * fmt, type::size * offset, type::size limit);
    static type::uint32 __format_check_length(const char * fmt, type::size * offset, type::size limit);

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, va_list ap);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int8 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int16 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int32 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int64 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float32 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float64 v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const void * v);
    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const char * v);

    static void __format_concatenate_character(char ** data, type::size * size, type::size * capacity, char c);
    static void __format_concatenate_character(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int8 v);
    static void __format_concatenate_character(char ** data, type::size * size, type::size * capacity, char c, type::size n);

    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * fmt, type::size * offset, type::size limit);
    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * s, type::size len);
    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * s);
    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const char * v);
    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const char * v, type::size len);

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int8 v);
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int16 v);
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int32 v);
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int64 v);
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v);
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v);
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v);
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v);

    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v);
    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v);
    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v);
    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v);

    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v);
    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v);
    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v);
    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v);

    static void __format_concatenate_use_sprintf(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float32 v);
    static void __format_concatenate_use_sprintf(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float64 v);

    static void __format_concatenate_pointer(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const void * v);

    static char * __format_string_create(const char * source, type::size length)
    {
        char * out = memory::allocate<char>(length + 1);    // NOLINT
        strncpy(out, source, length);
        out[length] = 0;
        return out;
    }


    string string::format(const char * fmt, ...)
    {
        string out;
        va_list ap;
        va_start(ap, fmt);
        __format(&out.__data, &out.__size, &out.__capacity, fmt, string::length(fmt), ap);
        va_end(ap);
        return out;
    }

    static void __format(char ** data, type::size * size, type::size * capacity, const char * fmt, type::size limit, va_list ap)
    {
        type::size offset = 0;
        while(offset <= limit)
        {
            __format_concatenate_until(data, size, capacity, fmt, &offset, limit, '%');
            if(offset < limit)
            {
                /** implement this */
                type::size position = offset + 1;
                type::uint32 flag = __format_check_flag(fmt, &position, limit);
                type::int32 width = __format_check_width(fmt, &position, limit);
                type::int32 precision = __format_check_precision(fmt, &position, limit);
                type::uint32 length = __format_check_length(fmt, &position, limit);
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
                            width = va_arg(ap, type::uint32);
                        }
                        if(precision == __format_precision_asterisk)
                        {
                            precision = va_arg(ap, type::uint32);
                        }
                        char * _fmt = __format_string_create(&fmt[offset], position + 1 - offset);
                        __format_concatenate_parameter(data, size, capacity, _fmt, flag, width, precision, length, specifier, ap);
                        memory::deallocate<char>(_fmt);
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

    static void __format_concatenate_until(char ** data, type::size * size, type::size * capacity, const char * fmt, type::size * offset, type::size limit, char c)
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

    static void __format_adjust_capacity(char ** data, type::size size, type::size * capacity, type::size n)
    {
        if(*capacity - size < n)
        {
            *capacity = ((size + n) / string::page + 1) * string::page;
            *data = memory::allocate<char>(*data, *capacity);
        }
    }

    static type::uint32 __format_check_flag(const char * fmt, type::size * offset, type::size limit)
    {
        type::uint32 flags = __format_flag_unknown;
        type::uint64 position = *offset;
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

    static type::int32 __format_check_width(const char * fmt, type::size * offset, type::size limit)
    {
        type::uint64 position = *offset;
        if(position < limit)
        {
            if(fmt[position] == '*')
            {
                *offset += 1;
                return __format_width_asterisk;
            }
            if(48 <= fmt[position] && fmt[position] <= 57)
            {
                type::uint32 n = 0;
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

    static type::int32 __format_check_precision(const char * fmt, type::size * offset, type::size limit)
    {
        type::uint64 position = *offset;
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
                        type::uint32 n = 0;
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

    static type::uint32 __format_check_length(const char * fmt, type::size * offset, type::size limit)
    {
        type::uint64 position = *offset;
        if(position >= limit){ return __format_length_unknown; }
        if(fmt[position] == 'h')
        {
            if(position + 1 < limit)
            {
                if(fmt[position + 1] == 'h' && position + 2 < limit)
                {
                    switch(fmt[position + 2])
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
                    switch(fmt[position + 1])
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
        if(fmt[position] == 'l')
        {
            if(position + 1 < limit)
            {
                if(fmt[position + 1] == 'l' && position + 2 < limit)
                {
                    switch(fmt[position + 2])
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
                    switch(fmt[position + 1])
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
        if(fmt[position] == 'j')
        {
            switch(fmt[position + 1])
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
        if(fmt[position] == 'z')
        {
            switch(fmt[position + 1])
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
        if(fmt[position] == 't')
        {
            switch(fmt[position + 1])
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
        if(fmt[position] == 'L')
        {
            switch(fmt[position + 1])
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
        switch(fmt[position])
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

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, va_list ap)
    {
        switch(length)
        {
            case __format_length_int8:      __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::int8) va_arg(ap, int));     return;
            case __format_length_int16:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::int16) va_arg(ap, int));    return;
            case __format_length_int32:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::int32) va_arg(ap, int));    return;
            case __format_length_int64:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, va_arg(ap, type::int64));          return;
            case __format_length_uint8:     __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint16) va_arg(ap, int));   return;
            case __format_length_uint16:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint32) va_arg(ap, int));   return;
            case __format_length_uint32:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, va_arg(ap, type::uint64));         return;
            case __format_length_uint64:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, va_arg(ap, type::uint64));         return;
            case __format_length_float32:   __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, va_arg(ap, double));               return;
            case __format_length_float64:   __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, va_arg(ap, long double));          return;
            case __format_length_pointer:   __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, va_arg(ap, const void *));         return;
            case __format_length_string:    __format_concatenate_parameter(data, size, capacity, fmt, flag, width, precision, length, specifier, va_arg(ap, const char *));         return;
            default:                                                                                                                                                                return;
        }
    }

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int8 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'c': __format_concatenate_character(data, size, capacity, fmt, flag, width, precision, length, specifier, v);          return;
            default:                                                                                                                    return;
        }

    }

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int16 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                    return;
        }
    }

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int32 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                    return;
        }
    }

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int64 v)
    {
        switch(specifier)
        {
            case 'd': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            case 'i': __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, v); return;
            default:                                                                                                                    return;
        }
    }

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v)
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

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v)
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

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v)
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

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v)
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

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float32 v)
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

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float64 v)
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

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const void * v)
    {
        if(specifier == 'p')
        {
            __format_concatenate_pointer(data, size, capacity, fmt, flag, width, precision, length, specifier, v);
        }
    }

    static void __format_concatenate_parameter(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const char * v)
    {
        if(specifier == 's')
        {
            __format_concatenate_string(data, size, capacity, fmt, flag, width, precision, length, specifier, v);
        }
    }

    static void __format_concatenate_character(char ** data, type::size * size, type::size * capacity, char c)
    {
        __format_adjust_capacity(data, *size, capacity, 1);
        (*data)[*size] = c;
        *size += 1;
    }

    static void __format_concatenate_character(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int8 v)
    {
        (void)(fmt);
        (void)(precision);
        (void)(length);
        (void)(specifier);
        if(width > 1)
        {
            if(flag == __format_flag_minus)
            {
                __format_concatenate_character(data, size, capacity, ' ', (type::size) width - 1);
                __format_concatenate_character(data, size, capacity, (char) v);
            }
            else
            {
                __format_concatenate_character(data, size, capacity, (char) v);
                __format_concatenate_character(data, size, capacity, ' ', (type::size) width - 1);
            }
        }
        else
        {
            __format_concatenate_character(data, size, capacity, (char) v);
        }
    }

    static void __format_concatenate_character(char ** data, type::size * size, type::size * capacity, char c, type::size n)
    {
        __format_adjust_capacity(data, *size, capacity, n);
        memset(&(*data)[*size], c, n);
        *size += n;
    }

    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * fmt, type::size * offset, type::size limit)
    {
        __format_adjust_capacity(data, *size, capacity, limit - *offset);
        for(;*offset < limit; *offset += 1, *size += 1)
        {
            (*data)[*size] = fmt[*offset];
        }
    }

    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * s, type::size len)
    {
        if(s != nullptr && len > 0)
        {
            __format_adjust_capacity(data, *size, capacity, len);
            ::memcpy(&(*data)[*size], s, len);
            *size += len;
        }
    }

    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * s)
    {
        __format_concatenate_string(data, size, capacity, s, s != nullptr ? ::strlen(s) : 0);
    }

    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const char * v)
    {
        __format_concatenate_string(data, size, capacity, fmt, flag, width, precision, length, specifier, v, v!=nullptr ? ::strlen(v) : 0);
    }

    static void __format_concatenate_string(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const char * v, type::size len)
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

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int8 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::int64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int16 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::int64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int32 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::int64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::int64 v)
    {
        (void)(fmt);
        (void)(precision);
        (void)(length);
        (void)(specifier);
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
            v = v * (type::int8)(-1);
        }
        const type::uint64 max = 1024;
        type::uint64 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                type::int64 remain = v % 10;
                str[--index] = (char) (remain + 48);
                v = v / (type::int8) 10;
            }
        }
        else
        {
            str[--index] = '0';
        }
        type::int64 len = max - index - 1 + (sign ? 1 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_character(data, size, capacity, '0', width - 1 - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, '0', width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
            }
            else if(flag & __format_flag_minus)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', width - 1 - (max - index - 1));
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', width - (max - index - 1));
                }
            }
            else
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, ' ', width - 1 - (max - index - 1));
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
            }
        }
        else
        {
            if(sign)
            {
                __format_concatenate_character(data, size, capacity, sign);
            }
            __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
        }

    }
    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v)
    {
        __format_concatenate_integer_to_decimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_decimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v)
    {
        (void)(fmt);
        (void)(precision);
        (void)(length);
        (void)(specifier);
        char sign = 0;
        if(flag & __format_flag_plus)
        {
            sign = '+';
        }
        else if(flag & __format_flag_space)
        {
            sign = ' ';
        }
        const type::int32 max = 1024;
        type::int32 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                type::uint64 remain = v % 10;
                str[--index] = (char) (remain + 48);
                v = v / (type::int8) 10;
            }
        }
        else
        {
            str[--index] = '0';
        }
        type::int32 len = max - index - 1 + (sign ? 1 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_character(data, size, capacity, '0', (type::size) width - 1 - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, '0', (type::size) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
            }
            else if(flag & __format_flag_minus)
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - 1 - (max - index - 1));
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index - 1));
                }
            }
            else
            {
                if(sign)
                {
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - 1 - (max - index - 1));
                    __format_concatenate_character(data, size, capacity, sign);
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
                }
            }
        }
        else
        {
            if(sign)
            {
                __format_concatenate_character(data, size, capacity, sign);
            }
            __format_concatenate_string(data, size, capacity, &str[index], (type::size) (max - index - 1));
        }
    }

    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v)
    {
        __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v)
    {
        __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v)
    {
        __format_concatenate_integer_to_octal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_octal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v)
    {
        (void)(fmt);
        (void)(precision);
        (void)(length);
        (void)(specifier);
        const type::int32 max = 1024;
        type::int32 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                type::uint64 remain = v & 0x07u;
                str[--index] = (char) (remain + 48);
                v = (v >> 3u);
            }
        }
        else
        {
            str[--index] = '0';
        }
        type::int32 len = max - index - 1 + ((flag & __format_flag_sharp) ? 1 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                __format_concatenate_character(data, size, capacity, '0', (type::size) width - (max - index - 1));
                __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
            }
            else if(flag & __format_flag_minus)
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_character(data, size, capacity, '0');
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index));
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index - 1));
                }
            }
            else
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index));
                    __format_concatenate_character(data, size, capacity, '0');
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                }
            }
        }

    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint8 v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint16 v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint32 v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::uint64) v);
    }

    static void __format_concatenate_integer_to_hexadecimal(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::uint64 v)
    {
        (void)(fmt);
        (void)(precision);
        (void)(length);
        const type::int32 max = 1024;
        type::int32 index = max;
        char str[max];
        str[--index] = 0;
        if(v > 0)
        {
            while(v > 0 && index != 0)
            {
                type::uint64 remain = v & 0x0Fu;
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
        type::int32 len = max - index - 1 + ((flag & __format_flag_sharp) ? 2 : 0);
        if(len < width)
        {
            if(flag & __format_flag_zero)
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_string(data, size, capacity, "0x");
                    __format_concatenate_character(data, size, capacity, '0', (type::size) width - (max - index) - 1);
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, '0', (type::size) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                }
            }
            else if(flag & __format_flag_minus)
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_string(data, size, capacity, "0x");
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index) - 1);
                }
                else
                {
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index - 1));
                }
            }
            else
            {
                if(flag & __format_flag_sharp)
                {
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index) - 1);
                    __format_concatenate_string(data, size, capacity, "0x");
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                }
                else
                {
                    __format_concatenate_character(data, size, capacity, ' ', (type::size) width - (max - index - 1));
                    __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
                }
            }
        }
        else
        {
            __format_concatenate_string(data, size, capacity, &str[index], (type::size) max - index - 1);
        }
    }

    static void __format_concatenate_use_sprintf(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float32 v)
    {
        __format_concatenate_use_sprintf(data, size, capacity, fmt, flag, width, precision, length, specifier, (type::float64) v);
    }

    static void __format_concatenate_use_sprintf(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, type::float64 v)
    {
        (void)(flag);
        (void)(width);
        (void)(precision);
        (void)(length);
        (void)(specifier);
        const type::uint64 max = 1024;
        char str[1024];
        snprintf(str, max, fmt, v);
        __format_concatenate_string(data, size, capacity, str);
    }

    static void __format_concatenate_pointer(char ** data, type::size * size, type::size * capacity, const char * fmt, type::uint32 flag, type::int32 width, type::int32 precision, type::uint32 length, char specifier, const void * v)
    {
        __format_concatenate_integer_to_hexadecimal(data, size, capacity, fmt, flag | __format_flag_sharp, width, precision, length, specifier, (type::uint64) v);
    }
}

