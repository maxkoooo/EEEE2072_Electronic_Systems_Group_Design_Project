#include "comparator.h"
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <FFT.h>
#include <inttypes.h>

void comparatorInit(Comparator *this, COMP_HandleTypeDef *hcomp, TIM_HandleTypeDef *htim, float timer_frequency){
    this->hcomp = hcomp;
	this->htim = htim;
	this->timer_frequency = timer_frequency;

	this->state = 0;
	this->T1 = 0;
	this->T2 = 0;
	this->ticks = 0;
	this->TIM1_OVC = 0;
	this->freq = 0;
}

void comparatorStart(Comparator *this){
	HAL_COMP_Start(this->hcomp);
	HAL_TIM_Base_Start_IT(this->htim);
	HAL_TIM_IC_Start_IT(this->htim, TIM_CHANNEL_1);
	this->current_comp_val = HAL_COMP_GetOutputLevel(this->hcomp);
}

void comparatorStop(Comparator *this){
    HAL_COMP_Stop(this->hcomp);
    HAL_TIM_Base_Stop_IT(this->htim);
    // add tim ic stop
}

void comparatorCaptureCallback(Comparator *this) {
	if(this->state == 0){
		this->T1 = TIM1->CCR1;
	    this->TIM1_OVC = 0;
	    this->state = 1;
	}
	else if(this->state == 1){
		this->T2 = TIM1->CCR1;
	    this->ticks = (this->T2 + (this->TIM1_OVC * 65536)) - this->T1;
	    this->freq = (float)(this->timer_frequency/this->ticks);
	    this->state = 0;
	}
}

void comparatorPeriodElapsedCallback(Comparator *this){
	(this->TIM1_OVC)++;
}

float getFrequency(Comparator *this){
    return this->freq;
}

