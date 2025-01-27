
#include "proto/structs.pb.h"
#include <stdint.h>

int set_interface_attribs(int fd, int speed);
void set_mincount(int fd, int mcount);
int connect_to_tty();
void write_to_tty(int fd, unsigned char *buffer, int buffer_len);
void set_signal(int fd, int8_t angle, int8_t pulses, Signal signal);
Signal signal_new(SignalShape signalShape, uint8_t amplitude, uint8_t offset,
                  uint8_t duty, uint16_t period, uint16_t phase);
void clear_signal(int fd);
void play_signal(int fd, int play);
void ping(int fd);
void set_direction(int fd, int8_t angle, int16_t speed);
void add_signal(int fd, int8_t angle, int8_t pulses, Signal signal);

void PrintSignal(Signal sig);
