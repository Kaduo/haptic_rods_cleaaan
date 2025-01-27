#include <raylib.h>
#include "pb_encode.h"
#include "pb_decode.h"
#include "proto/structs.pb.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>


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

    RodGroup rodGroup = RodGroup_init_zero;
    printf("\n\n %d \n\n", rod.color.a);

    InitWindow(800, 200, "Hello world!");
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawRod(myRod);
        EndDrawing();
    }
}