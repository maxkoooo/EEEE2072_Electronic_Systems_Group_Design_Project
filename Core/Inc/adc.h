#pragma once

#include <main.h>
#include <stdio.h>
#include <stdint.h>
#include <FFT.h>


typedef struct{
    ADC_HandleTypeDef *hadc;

    struct ADC_param ADC_val;
    struct FFT_res FFT_val;
    int flag;
}ADC;

void ADCInit(ADC *this, ADC_HandleTypeDef *hadc, const uint64_t adc_buf_len,
                uint32_t adc_buf[], uint32_t clock_speed, uint32_t prescaler,
                uint32_t bit, float sampling_time);
void ADCStart(ADC *this);
void ADCStop(ADC *this);
void ADCHandleCallback(ADC *this);
float ADCGetVoltage(ADC *this);
float ADCCalculateFrequency(ADC *this, int restart);
