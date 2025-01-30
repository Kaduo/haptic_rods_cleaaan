#include <raylib.h>
#include "pb_encode.h"
#include "pb_decode.h"
#include "proto/structs.pb.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "signals.h"
#include "signal_fsm.h"

void main() {

    char * buffer = 0;
    long length;
    FILE * f = fopen ("myRod.spec", "rb");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, f);
        }
        fclose (f);
    }

    Rod myRod = Rod_init_zero;

    if (buffer) {
        pb_istream_t stream =  pb_istream_from_buffer(buffer, length);
        bool status = pb_decode(&stream, Rod_fields, &myRod);
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            exit(EXIT_FAILURE);
        }
    }
    Rod rod = Rod_init_zero;
    rod.rect.width = 50;
    rod.rect.height = 50;
    rod.color.r = 255;
    rod.color.a = 255;

    Rod rod2 = rod;
    rod2.rect.x = 100;
    rod2.signal.signalShape = SignalShape_SINE;
    rod2.signal.amplitude = 255;
    rod2.signal.period = 255;
    rod2.signal.offset = 255;


    RodGroup rodGroup = RodGroup_init_zero;
    printf("\n\n %d \n\n", rod.color.a);
    rodGroup.rods[0] = rod;
    rodGroup.rods[1] = rod2;
    rodGroup.rods_count = 2;

    App app = {0};
    app.rodGroup = rodGroup;
    app.inputProvider.inputHistory = NULL;
    app.collided = false;
    app.selected = false;

    app.signalController = NewSignalController();
    InitWindow(800, 200, "Hello world!");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        UpdateApp(&app);
        DrawRodGroup(&app.rodGroup);
        EndDrawing();
    }
}