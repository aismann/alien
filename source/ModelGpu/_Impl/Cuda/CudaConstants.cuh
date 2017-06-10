#pragma once

#define NUM_THREADS_PER_BLOCK 64
#define NUM_BLOCKS 64
#define NUM_CLUSTERS 500/*160000/64*/

#define LAYERS 2
#define CELL_MAX_BONDS 6
#define CELL_MAX_DISTANCE 1.3
#define MAX_COLLIDING_CLUSTERS 3

#define DEG_TO_RAD 3.1415926535897932384626433832795/180.0
#define RAD_TO_DEG 180.0/3.1415926535897932384626433832795

#define FP_PRECISION 0.00001

