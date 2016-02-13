#include "main.h"
#include "ir_decode.h"

/** @defgroup IR_DECODE_Private_Variables
  * @{
  */

static void IR_DataSampling(uint32_t lowPulseLength, uint32_t wholePulseLength);
static uint8_t IR_DecodeHeader(uint32_t lowPulseLength, uint32_t wholePulseLength);
static uint8_t IR_DecodeBit(uint32_t lowPulseLength , uint32_t wholePulseLength);

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  static uint32_t ICValue1;
  static uint32_t ICValue2;

  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
  {
    /* Get the Input Capture value */
    ICValue2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
    IR_DataSampling(ICValue1, ICValue2);
  }
  else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
  {
    ICValue1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) - ICValue2;
  }
}

/**
  * @brief  Identify the IR data.
  * @param  lowPulseLength: low pulse duration.
  * @param  wholePulseLength: whole pulse duration.
  * @retval None
  */
static void IR_DataSampling(uint32_t lowPulseLength, uint32_t wholePulseLength)
{
  uint8_t  tmpBit = 0;

  if ((IRTmpPacket.status == IR_STATUS_HEADER))
  {
    /* Convert raw pulse timing to data value */
    tmpBit = IR_DecodeHeader(lowPulseLength, wholePulseLength);

    /* If the Header timing is correct */
    if ( tmpBit!= IR_HEADER_ERROR)
    {
      /* Wrong header time */
      IR_ResetPacket();
    }
  }
  else
  /* If the pulse timing is correct */
  if ((IRTmpPacket.status == IR_STATUS_RX))
  {
    /* Convert raw pulse timing to data value */
    tmpBit = IR_DecodeBit(lowPulseLength, wholePulseLength);
    if (tmpBit != IR_BIT_ERROR) /* If the pulse timing is correct */
    {
      if (tmpBit == 1)
      {
      	/* This operation fills in the incoming bit to the correct position in 32 bit word*/
      	IRTmpPacket.data |= (1 << IRTmpPacket.count);
      }
      //else if (tmpBit == 0)
      //{
      //}
      /* Increment the bit count  */
      IRTmpPacket.count++;
    }
    else
    {
      /* Reception Status for the inverted message */
      IRTmpPacket.status = IR_STATUS_HEADER;
    }

    /* If all bits identified */
    if (IRTmpPacket.count == IR_BITS_COUNT)
    {
     /* Frame received*/
      IRFrameReceived = YES;
#if defined SAMSUNG_SIRC
      ConvertSamsung();
#elif defined LIVARNOLUX_SIRC
      //ConvertLivarnolux();
#elif defined SONY_SIRC
      ConvertSony();
#endif
      IRTmpPacket.count = 0;
      IRTmpPacket.data = 0;
      IRTmpPacket.status = IR_STATUS_HEADER;
    }
  }
}


/**
  * @brief  Check the header pulse if it has correct pulse time.
  * @param  lowPulseLength: low pulse header duration.
  * @param  wholePulseLength: whole pulse header duration.
  * @retval IR_HEADER_OK or IR_HEADER_ERROR
  */
static uint8_t IR_DecodeHeader(uint32_t lowPulseLength, uint32_t wholePulseLength)
{
  /* First check if low pulse time is according to the specs */
  if ((lowPulseLength >= IRHeaderLowMin) && (lowPulseLength <= IRHeaderLowMax))
  {
    /* Check if the high pulse is OK */
    if ((wholePulseLength >= IRHeaderWholeMin) && (wholePulseLength <= IRHeaderWholeMax))
    {
      return IR_HEADER_OK; /* Valid Header */
    }
  }
  return IR_HEADER_ERROR;  /* Wrong Header */
}

/**
  * @brief  Convert raw time to data value.
  * @param  lowPulseLength: low pulse bit duration.
  * @param  wholePulseLength: whole pulse bit duration.
  * @retval BitValue( data0 or data1) or IR_BIT_ERROR
  */
static uint8_t IR_DecodeBit(uint32_t lowPulseLength , uint32_t wholePulseLength)
{
  uint8_t i = 0;

#ifdef SONY_SIRC

  if ((wholePulseLength >= IROnTimeMin) && (wholePulseLength <= IROnTimeMax))
  {
    for (i = 0; i < 2; i++) /* There are data0 to data1 */
    {
      /* Check if the length is in given range */
      if ((lowPulseLength >= IRValue00 + (IRValueStep * i) - IRValueMargin) && (lowPulseLength <= IRValue00 + (IRValueStep * i) + IRValueMargin))
        return i; /* Return bit value */
    }
  }
#else

  /* First check if low pulse time is according to the specs */
  if ((lowPulseLength >= IROnTimeMin) && (lowPulseLength <= IROnTimeMax))
  {
    for (i = 0; i < 2; i++) /* There are data0 to data1 */
    {
      /* Check if the length is in given range */
      if ((wholePulseLength >= IRValue00 + (IRValueStep * i) - IRValueMargin) && (wholePulseLength <= IRValue00 + (IRValueStep * i) + IRValueMargin))
        return i; /* Return bit value */
    }
  }

#endif

  return IR_BIT_ERROR; /* No correct pulse length was found */
}

/**
  * @brief  Put the packet to default state, ready to be filled in by incoming
  *         data.
  * @param  None
  * @retval None
  */
void IR_ResetPacket(void)
{
  IRTmpPacket.count = 0;
  IRTmpPacket.status = IR_STATUS_RX;
  IRTmpPacket.data = 0;
}

/**
  * @brief  Initialize the IR bit time range.
  * @param  None
  * @retval None
  */
void IR_Init(void)
{
  /* TIMER frequency input */
  /* Set TIMx instance */
  TIM_ICInitStructure.Instance = IR_TIM;
  TIM_ICInitStructure.Init.Period = 0xFFFF;
  TIM_ICInitStructure.Init.Prescaler = TIM_PRESCALER;
  TIM_ICInitStructure.Init.ClockDivision = 0;
  TIM_ICInitStructure.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIM_ICInitStructure.State = HAL_TIM_STATE_RESET;

  if(HAL_TIM_IC_Init(&TIM_ICInitStructure) != HAL_OK)
  {
    /* Initialization Error */
  }

  /*##-2- Configure the Input Capture channels ###############################*/
  /* Common configuration */
  sConfig.ICPrescaler = TIM_ICPSC_DIV1;
  sConfig.ICFilter = 0;

  /* Configure the Input Capture of channel 1 */
  sConfig.ICPolarity = TIM_ICPOLARITY_FALLING;
  sConfig.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if(HAL_TIM_IC_ConfigChannel(&TIM_ICInitStructure, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Initialization Error */
  }

  /* Configure the Input Capture of channel 2 */
  sConfig.ICPolarity = TIM_ICPOLARITY_RISING;
  sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if(HAL_TIM_IC_ConfigChannel(&TIM_ICInitStructure, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Initialization Error */
  }

  /*##-3- Configure the slave mode ###########################################*/
  /* Select the slave Mode: Reset Mode */
  /* Slave synchro config */
  Slave_Config.InputTrigger = TIM_TS_TI2FP2;
  Slave_Config.SlaveMode = TIM_SLAVEMODE_RESET;
  if(HAL_TIM_SlaveConfigSynchronization(&TIM_ICInitStructure,&Slave_Config) != HAL_OK)
  {
    /* Initialization Error */
  }

  /*##-4- Start the Input Capture in interrupt mode ##########################*/
  if(HAL_TIM_IC_Start_IT(&TIM_ICInitStructure, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Initialization Error */
  }

  /*##-5- Start the Input Capture in interrupt mode ##########################*/
  if(HAL_TIM_IC_Start_IT(&TIM_ICInitStructure, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Initialization Error */
  }
  /* IR bit definitions*/
  IROnTimeMin    = IR_ONTIME_MIN_US;
  IROnTimeMax    = IR_ONTIME_MAX_US;
  IRValueStep    = IR_VALUE_STEP_US;
  IRValueMargin  = IR_VALUE_MARGIN_US;
  IRValue00      = IR_VALUE_00_US;

  /* Header time definitions*/
  IRHeaderLowMin     = IR_HEADER_LOW_MIN_US;
  IRHeaderLowMax     = IR_HEADER_LOW_MAX_US;
  IRHeaderWholeMin   = IR_HEADER_WHOLE_MIN_US;
  IRHeaderWholeMax   = IR_HEADER_WHOLE_MAX_US;

  /* Default state */
  IR_ResetPacket();
  IRFrameReceived = NO;
}
