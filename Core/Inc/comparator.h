#pragma once

#include <main.h>
#include <inttypes.h>


typedef struct{
    COMP_HandleTypeDef *hcomp;
    TIM_HandleTypeDef *htim;
    float timer_frequency;

    uint8_t current_comp_val;
    uint64_t ticks;
    uint64_t clock_ticks;
    uint32_t period;
}Comparator;

void comparatorInit(Comparator *this, COMP_HandleTypeDef *hcomp, TIM_HandleTypeDef *htim, float timer_frequency);
void comparatorStart(Comparator *this);
void comparatorStop(Comparator *this);
void comparatorHandleClockCallback(Comparator *this);
void comparatorCaptureCallback(Comparator *this);
float comparatorCalculateFrequency(Comparator *this);
