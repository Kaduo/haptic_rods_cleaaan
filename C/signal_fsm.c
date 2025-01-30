#include "app.h"
#include "signals.h"
#include "signal_fsm.h"

const int IMPULSE_DURATION = 60;

const Signal IMPULSE_SIGNAL = (Signal){
    SignalShape_STEADY,
    255,
    255,
    0,
    0,
    0,
};

SignalController NewSignalController() {
    SignalController signalController = {.timer = 0, .fd = ConnectToTTY(), .signalState = PLAYING_NO_SIGNAL};
    SetDirection(signalController.fd, 0, 1000); // Necessary for signals to play.
    return signalController;
}


void UpdateSignalController(SignalController *me, bool selected, bool collided, Rod *selectedRod) {
    SignalState oldSignalState = me->signalState;
    if (!selected) {
        me->signalState = PLAYING_NO_SIGNAL;
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
                printf("NO SIGNAL");
                ClearSignal(me->fd);
                break;
            case PLAYING_IMPULSE_SIGNAL:
                printf("HSLKDJF");
                SetSignal(me->fd, 0, 0, IMPULSE_SIGNAL);
                break;
            case PLAYING_COLLISION_SIGNAL:
                printf("HUH!\n");
                ClearSignal(me->fd); //TODO : CHECK if correct
                break;
            case PLAYING_SELECTED_ROD_SIGNAL:
                printf("HIHI\n");
                SetSignal(me->fd, 0, 0, selectedRod->signal); // TODO : FIX angle?
                break;
        }
    } else {
        me->timer += 1;
    }
}



// typedef bool (*SignalStateUpdateFun)(SignalController*, SignalState);
// typedef void (*SignalStateEnterFun)(SignalController*, SignalState);
// // typedef void (*SignalStateExitFun)(SignalController*, SignalState);



// typedef struct SignalState {
//     SignalStateLabel label;
//     int timer;
//     SignalStateUpdateFun update;
//     SignalStateEnterFun enter;
//     // SignalStateExitFun exit;
// } SignalState;

// typedef struct SignalController {
//     SignalState signalState;
//     int fd;
// } SignalController;


// // void UpdateSignalControllerState(SignalController *signalController, bool selected, bool collided) {
// //     if (!selected)
// // }

// bool UpdateSignalState(SignalController *parent, SignalState me) {
//     me.timer += 1;
//     return me.update(parent, me);
// }

//  EnterSignalState(SignalController *parent, SignalState me) {
//     me.timer += 0;
//     me.enter(parent, me);
// }

// SignalState UpdateNoSignalState(SignalState me, bool selected, bool collided) {
//     if (selected) {
//         me = SignalState
//     }
//     return me;
// }

// bool UpdateSelectedRodSignalState(SignalState me, bool selected, bool collided) {
//     switch (event) {
//         case RodReleased:
//             state->timer = 0;
//             state->label = NoSignal;
//             break;
//         case RodCollided:
//             state->timer = 0;
//             state->label = ImpulseSignal;
//             break;
//         default:
//             state->timer +=1;
//             break;
//     }
// }

// const int IMPULSE_DURATION = 100;

// void UpdateImpulseSignalState(SignalState *state, SignalEvent event) {
//     switch (event) {
//         case RodReleased:
//             state->timer = 0;
//             state->label = NoSignal;
//             break;
//         case RodStoppedColliding:
//             state->timer = 0;
//             state->label = SelectedRodSignal;
//             break;
//         case Nothing:
//             state->timer +=1;
//             if (state->timer > IMPULSE_DURATION) {
//                 state->label=CollisionSignal;
//                 state->timer = 0;
//             }
//             break;
//         default:
//             state->timer +=1;
//             break;
//     }
// }


// // void UpdateSignalState(SignalState *state, SignalEvent transition) {
// // }

// // typedef void (*UpdateSignalState)(SignalState*, SignalEvent);

// // typedef struct SignalStateInterface {
// //     (void )
// // } SignalStateInterface;

// // typedef struct SignalState {
// //     SignalStateInterface inner;
// // } SignalState;

// // SignalState UpdateNoSignalState(SignalState *signalState, SignalEvent signalEvent) {
// //     switch (signalEvent) {
// //         case Nothing:
// //             signalState->timer += 1;
// //             break;
// //         case RodSelected:
// //             *signalState = SelectedRodPlayingState
// //     }
// // }