/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9.1 */

#ifndef PB_PROTO_STRUCTS_PB_H_INCLUDED
#define PB_PROTO_STRUCTS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _SignalShape {
    SignalShape_NO_SIGNAL = 0,
    SignalShape_STEADY = 1,
    SignalShape_SINE = 2,
    SignalShape_TRIANGLE = 3,
    SignalShape_FRONT_TEETH = 4,
    SignalShape_BACK_TEETH = 5
} SignalShape;

typedef enum _HapticProtocol {
    HapticProtocol_UNDEFINED = 0,
    HapticProtocol_PING = 1,
    HapticProtocol_SET_DIR = 130,
    HapticProtocol_ADD_SIGNAL = 131,
    HapticProtocol_PLAY = 132,
    HapticProtocol_CLEAR = 133
} HapticProtocol;

/* Struct definitions */
typedef struct _Signal {
    bool has_signalShape;
    SignalShape signalShape;
    bool has_period;
    uint32_t period; /* 2 bytes */
    bool has_amplitude;
    uint32_t amplitude; /* 1 byte */
    bool has_duty;
    uint32_t duty; /* 1 byte */
    bool has_offset;
    uint32_t offset; /* 1 byte */
    bool has_phase;
    uint32_t phase; /* 2 bytes */
} Signal;

typedef struct __Rectangle {
    bool has_width;
    float width;
    bool has_height;
    float height;
    bool has_x;
    float x;
    bool has_y;
    float y;
} _Rectangle;

typedef struct __Color {
    bool has_r;
    uint32_t r;
    bool has_g;
    uint32_t g;
    bool has_b;
    uint32_t b;
    bool has_a;
    uint32_t a;
} _Color;

typedef struct _Rod {
    bool has_signal;
    Signal signal;
    bool has_color;
    _Color color;
    bool has_rect;
    _Rectangle rect;
    bool has_numericLength;
    uint32_t numericLength;
} Rod;

typedef struct _RodGroup {
    pb_size_t rods_count;
    Rod rods[100];
} RodGroup;


#ifdef __cplusplus
extern "C" {
#endif

/* Helper constants for enums */
#define _SignalShape_MIN SignalShape_NO_SIGNAL
#define _SignalShape_MAX SignalShape_BACK_TEETH
#define _SignalShape_ARRAYSIZE ((SignalShape)(SignalShape_BACK_TEETH+1))

#define _HapticProtocol_MIN HapticProtocol_UNDEFINED
#define _HapticProtocol_MAX HapticProtocol_CLEAR
#define _HapticProtocol_ARRAYSIZE ((HapticProtocol)(HapticProtocol_CLEAR+1))

#define Signal_signalShape_ENUMTYPE SignalShape






/* Initializer values for message structs */
#define Signal_init_default                      {false, _SignalShape_MIN, false, 0, false, 0, false, 0, false, 0, false, 0}
#define _Rectangle_init_default                  {false, 0, false, 0, false, 0, false, 0}
#define _Color_init_default                      {false, 0, false, 0, false, 0, false, 0}
#define Rod_init_default                         {false, Signal_init_default, false, _Color_init_default, false, _Rectangle_init_default, false, 0}
#define RodGroup_init_default                    {0, {Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default, Rod_init_default}}
#define Signal_init_zero                         {false, _SignalShape_MIN, false, 0, false, 0, false, 0, false, 0, false, 0}
#define _Rectangle_init_zero                     {false, 0, false, 0, false, 0, false, 0}
#define _Color_init_zero                         {false, 0, false, 0, false, 0, false, 0}
#define Rod_init_zero                            {false, Signal_init_zero, false, _Color_init_zero, false, _Rectangle_init_zero, false, 0}
#define RodGroup_init_zero                       {0, {Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero, Rod_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define Signal_signalShape_tag                   1
#define Signal_period_tag                        2
#define Signal_amplitude_tag                     3
#define Signal_duty_tag                          4
#define Signal_offset_tag                        5
#define Signal_phase_tag                         6
#define _Rectangle_width_tag                     1
#define _Rectangle_height_tag                    2
#define _Rectangle_x_tag                         3
#define _Rectangle_y_tag                         4
#define _Color_r_tag                             1
#define _Color_g_tag                             2
#define _Color_b_tag                             3
#define _Color_a_tag                             4
#define Rod_signal_tag                           1
#define Rod_color_tag                            2
#define Rod_rect_tag                             3
#define Rod_numericLength_tag                    4
#define RodGroup_rods_tag                        1

/* Struct field encoding specification for nanopb */
#define Signal_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, UENUM,    signalShape,       1) \
X(a, STATIC,   OPTIONAL, UINT32,   period,            2) \
X(a, STATIC,   OPTIONAL, UINT32,   amplitude,         3) \
X(a, STATIC,   OPTIONAL, UINT32,   duty,              4) \
X(a, STATIC,   OPTIONAL, UINT32,   offset,            5) \
X(a, STATIC,   OPTIONAL, UINT32,   phase,             6)
#define Signal_CALLBACK NULL
#define Signal_DEFAULT NULL

#define _Rectangle_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, FLOAT,    width,             1) \
X(a, STATIC,   OPTIONAL, FLOAT,    height,            2) \
X(a, STATIC,   OPTIONAL, FLOAT,    x,                 3) \
X(a, STATIC,   OPTIONAL, FLOAT,    y,                 4)
#define _Rectangle_CALLBACK NULL
#define _Rectangle_DEFAULT NULL

#define _Color_FIELDLIST(X, a_) \
X(a_, STATIC,   OPTIONAL, UINT32,   r,                 1) \
X(a_, STATIC,   OPTIONAL, UINT32,   g,                 2) \
X(a_, STATIC,   OPTIONAL, UINT32,   b,                 3) \
X(a_, STATIC,   OPTIONAL, UINT32,   a,                 4)
#define _Color_CALLBACK NULL
#define _Color_DEFAULT NULL

#define Rod_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  signal,            1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  color,             2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  rect,              3) \
X(a, STATIC,   OPTIONAL, UINT32,   numericLength,     4)
#define Rod_CALLBACK NULL
#define Rod_DEFAULT NULL
#define Rod_signal_MSGTYPE Signal
#define Rod_color_MSGTYPE _Color
#define Rod_rect_MSGTYPE _Rectangle

#define RodGroup_FIELDLIST(X, a) \
X(a, STATIC,   REPEATED, MESSAGE,  rods,              1)
#define RodGroup_CALLBACK NULL
#define RodGroup_DEFAULT NULL
#define RodGroup_rods_MSGTYPE Rod

extern const pb_msgdesc_t Signal_msg;
extern const pb_msgdesc_t _Rectangle_msg;
extern const pb_msgdesc_t _Color_msg;
extern const pb_msgdesc_t Rod_msg;
extern const pb_msgdesc_t RodGroup_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Signal_fields &Signal_msg
#define _Rectangle_fields &_Rectangle_msg
#define _Color_fields &_Color_msg
#define Rod_fields &Rod_msg
#define RodGroup_fields &RodGroup_msg

/* Maximum encoded size of messages (where known) */
#define PROTO_STRUCTS_PB_H_MAX_SIZE              RodGroup_size
#define RodGroup_size                            9000
#define Rod_size                                 88
#define Signal_size                              32
#define _Color_size                              24
#define _Rectangle_size                          20

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
