
#include "proto/structs.pb.h"
#include <stdint.h>

int SetInterfaceAttributes(int fd, int speed);
void SetMincount(int fd, int mcount);
int ConnectToTTY();
void write_to_tty(int fd, unsigned char *buffer, int buffer_len);
void SetSignal(int fd, int8_t angle, int8_t pulses, Signal signal);
Signal signal_new(SignalShape signalShape, uint8_t amplitude, uint8_t offset,
                  uint8_t duty, uint16_t period, uint16_t phase);
void StopSignal(int fd);
void PlayCurrentSignal(int fd, int play);
void Ping(int fd);
void SetDirection(int fd, int8_t angle, int16_t speed);
void AddSignal(int fd, int8_t angle, int8_t pulses, Signal signal);

void PrintSignal(Signal sig);
