#pragma once

#include <stdbool.h>

#include "structure.h"

void check_sdl_execution_by_code(const int code);
void* check_sdl_execution_by_pointer(void* pointer);
void* check_memory_allocation(void* pointer);
bool compare_position(const Position a, const Position b);
void print_snake(const Snake* snake);
