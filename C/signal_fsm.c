#include "app.h"
#include "signals.h"
#include "signal_fsm.h"

const int IMPULSE_DURATION = 60; // TODO : this is in frames, should be in seconds

const Signal IMPULSE_SIGNAL = (Signal){
    .signalShape = SignalShape_STEADY,
    .offset = 255,
    .amplitude = 255,
    0,
    0,
    0,
};

SignalController NewSignalController() {
    SignalController signalController = {.timer = 0, .fd = ConnectToTTY(), .signalState = PLAYING_NO_SIGNAL};
    SetDirection(signalController.fd, 78, 0); // Necessary for signals to play.
    return signalController;
}


void UpdateSignalController(SignalController *me, bool selected, bool collided, Rod *selectedRod) {
    SignalState oldSignalState = me->signalState;
    if (!selected) {
        me->signalState = PLAYING_NO_SIGNAL;
        me->timer += 1;
    } else {
        switch (me->signalState) {
            case PLAYING_NO_SIGNAL:
                if (selected){
                    me->signalState = PLAYING_SELECTED_ROD_SIGNAL;
                }
                break;
            case PLAYING_SELECTED_ROD_SIGNAL:
                if (collided) {
                    me->signalState = PLAYING_IMPULSE_SIGNAL;
                }
                break;
            case PLAYING_IMPULSE_SIGNAL:
                if (!collided) {
                    me->signalState = PLAYING_SELECTED_ROD_SIGNAL;
                } else if (me->timer > IMPULSE_DURATION) {
                    me->signalState = PLAYING_COLLISION_SIGNAL;
                }
                break;
            case PLAYING_COLLISION_SIGNAL:
                if (!collided) {
                    me->signalState = PLAYING_SELECTED_ROD_SIGNAL;
                }
                break;
        }
    }
    if (me->signalState != oldSignalState) {
        me->timer = 0;
        switch (me->signalState) {
            case PLAYING_NO_SIGNAL:
                printf("NO SIGNAL\n");
                ClearSignal(me->fd);
                break;
            case PLAYING_IMPULSE_SIGNAL:
                printf("IMPULSE SIGNAL\n");
                SetSignal(me->fd, -1, -1, IMPULSE_SIGNAL);
                PrintSignal(IMPULSE_SIGNAL);
                break;
            case PLAYING_COLLISION_SIGNAL:
                printf("COLLISION signal!\n");
                ClearSignal(me->fd); //TODO : CHECK if correct
                break;
            case PLAYING_SELECTED_ROD_SIGNAL:
                printf("SELECTED ROD SIGNAL!!!\n");
                SetSignal(me->fd, -1, -1, selectedRod->signal);
                PrintSignal(selectedRod->signal);
                break;
        }
        SetDirection(me->fd, 78, 0);
    } else {
        me->timer += 1;
    }
}