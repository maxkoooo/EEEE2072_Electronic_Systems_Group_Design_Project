#pragma once

#include <main.h>
#include <inttypes.h>


typedef struct{
    COMP_HandleTypeDef *hcomp;
    TIM_HandleTypeDef *htim;
    float timer_frequency;

    volatile uint8_t state;
    volatile uint32_t T1;
    volatile uint32_t T2;
    volatile uint32_t ticks;
    volatile uint16_t TIM1_OVC;
    volatile float freq;

    uint8_t current_comp_val;
}Comparator;

void comparatorInit(Comparator *this, COMP_HandleTypeDef *hcomp, TIM_HandleTypeDef *htim, float timer_frequency);
void comparatorStart(Comparator *this);
void comparatorStop(Comparator *this);
void comparatorHandleClockCallback(Comparator *this);
void comparatorCaptureCallback(Comparator *this);
float getFrequency(Comparator *this);
