#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

typedef enum {
    MPEG2_OK = 0,
    MPEG2_ERROR_BITSTREAM,
    MPEG2_ERROR_SYNTAX,
    MPEG2_ERROR_UNSUPPORTED,
    MPEG2_ERROR_MEMORY
} MPEG2Error;

const char* mpeg2_error_string(MPEG2Error error);

#endif 