/*
 * @filename	adc_cfg.c
 * @author		SPARKBMS TEAM
 * @date		Apr 14, 2023
 * @ingroup		FOLDER NAME
 * @prefix		adc_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "adc_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

ADC_HandleTypeDef	adc_cfg = {
		.Instance = ADC1,
		.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
		.Init.ContinuousConvMode = DISABLE,
		.Init.DMAContinuousRequests = ENABLE,
		.Init.DataAlign = ADC_DATAALIGN_RIGHT,
		.Init.DiscontinuousConvMode = DISABLE,
		.Init.EOCSelection = ADC_EOC_SEQ_CONV,
		.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T2_TRGO,
		.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING,
		.Init.NbrOfConversion = ADC_NO_OF_CONVERSION,
		.Init.Resolution = ADC_RESOLUTION_12B,
		.Init.ScanConvMode = ENABLE,
		.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN
};

ADC_ChannelConfTypeDef	adc_channel_cfg[] = {
		{
				.Channel = ADC_CHANNEL_2,
				.Rank = ADC_REGULAR_RANK_1,
				.SamplingTime = ADC_SAMPLETIME_640CYCLES_5,
				.SingleDiff = ADC_SINGLE_ENDED
		},
		{
				.Channel = ADC_CHANNEL_3,
				.Rank = ADC_REGULAR_RANK_2,
				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
				.SingleDiff = ADC_SINGLE_ENDED
		},
		{
				.Channel = ADC_CHANNEL_5,
				.Rank = ADC_REGULAR_RANK_3,
				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
				.SingleDiff = ADC_SINGLE_ENDED
		},
//		{
//				.Channel = ADC_CHANNEL_6,
//				.Rank = ADC_REGULAR_RANK_4,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_7,
//				.Rank = ADC_REGULAR_RANK_5,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_8,
//				.Rank = ADC_REGULAR_RANK_6,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_9,
//				.Rank = ADC_REGULAR_RANK_7,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_10,
//				.Rank = ADC_REGULAR_RANK_8,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_11,
//				.Rank = ADC_REGULAR_RANK_9,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_12,
//				.Rank = ADC_REGULAR_RANK_10,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_13,
//				.Rank = ADC_REGULAR_RANK_11,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_1,
//				.Rank = ADC_REGULAR_RANK_12,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_14,
//				.Rank = ADC_REGULAR_RANK_13,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_15,
//				.Rank = ADC_REGULAR_RANK_14,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
//		{
//				.Channel = ADC_CHANNEL_16,
//				.Rank = ADC_REGULAR_RANK_15,
//				.SamplingTime = ADC_SAMPLETIME_2CYCLES_5,
//				.SingleDiff = ADC_SINGLE_ENDED
//		},
};

uint8_t adc_channel_cfg_length = sizeof(adc_channel_cfg)/sizeof(adc_channel_cfg[0]);
