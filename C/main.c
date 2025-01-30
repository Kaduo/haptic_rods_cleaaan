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

const int TABLET_WIDTH = 1000;
const int TABLET_HEIGHT = 600;


void main() {

    char * buffer = 0;
    long length;
    FILE * f = fopen ("dummy.rg", "rb");

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

    RodGroup rodGroup = RodGroup_init_zero;

    if (buffer) {
        pb_istream_t stream =  pb_istream_from_buffer(buffer, length);
        bool status = pb_decode(&stream, RodGroup_fields, &rodGroup);
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            exit(EXIT_FAILURE);
        }
    }

    App app = {0};
    app.rodGroup = rodGroup;
    app.inputProvider.inputHistory = NULL;
    app.collided = false;
    app.selected = false;

    app.signalController = NewSignalController();
    InitWindow(TABLET_WIDTH, TABLET_HEIGHT, "Hello world!");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        UpdateApp(&app);
        DrawRodGroup(&app.rodGroup);
        EndDrawing();
    }
}