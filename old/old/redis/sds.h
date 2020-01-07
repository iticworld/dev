#ifndef __SDS_H
#define __SDS_H

#define SDS_MAX_PREALLOC (1024 * 1024)
const char * SDS_NOINIT;

typedef char * sds;

/**
 * note: sdshdr5 is never used, we just access the flags byte directly.
 * however is here to document the layout of type 5 SDS strings.
 */

struct __attribute__ ((__packed__)) sdshdr5 {
    unsigned char flags;    /** 3 lsb of type, and 5 msb of string length */
    char buf[];
};

struct __attribute__ ((__packed__)) sdshdr8 {
    uint8_t len;            /** used */
    uint8_t alloc;          /** excluding the header and null terminator */
    unsigned char flags;    /** 3 lsb of type, 5 unused bits */
    char buf[];
};

struct __attribute__ ((__packed__)) sdshdr16 {
    uint16_t len;           /** used */
    uint16_t alloc;         /** excluding the header and null terminator */
    unsigned char flags;    /** 3 lsb of type, 5 unused bits */
    char buf[];
};

struct __attribute__ ((__packed__)) sdshdr32 {
    uint32_t len;           /** used */
    uint32_t alloc;         /** excluding the header and null terminator */
    unsigned char flags;    /** 3 lsb of type, 5 unused bits */
    char buf[];
};

struct __attribute__ ((__packed__)) sdshdr64 {
    uint64_t len;           /** used */
    uint64_t alloc;         /** excluding the header and null terminator */
    unsigned char flags;    /** 3 lsb of type, 5 unused bits */
    char buf[];
};

#define SDS_TYPE_5          0
#define SDS_TYPE_8          1
#define SDS_TYPE_16         2
#define SDS_TYPE_32         3
#define SDS_TYPE_64         4
#define SDS_TYPE_MASK       7
#define SDS_TYPE_BITS       3
#define SDS_HDR_VAR(T, s)   struct sdshdr##T * sh = (void *)((s) - (sizeof(struct sdshrd##T)));
#define SDS_HDR(T, s)       ((struct sdshdr## *)((s) - (sizeof(struct sdshdr##T))))
#define SDS_TYPE_5_LEN(f)   ((f) >> SDS_TYPE_BITS)
