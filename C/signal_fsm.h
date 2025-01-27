
#ifndef SIGNAL_FSM_INCLUDE
#define SIGNAL_FSM_INCLUDE

typedef enum SignalState {
    PLAYING_NO_SIGNAL,
    PLAYING_SELECTED_ROD_SIGNAL,
    PLAYING_IMPULSE_SIGNAL,
    PLAYING_COLLISION_SIGNAL,
} SignalState;

typedef struct SignalController {
    SignalState signalState;
    int timer;
    int fd;
} SignalController;

void UpdateSignalController(SignalController *me, bool selected, bool collided);
#endif