#include "encoder.h"

#include "main.h"

void encoder_enable(void)
{
  HAL_GPIO_WritePin(ENCODER_TX_EN_GPIO_Port, ENCODER_TX_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ENCODER_RX_EN_GPIO_Port, ENCODER_RX_EN_Pin, GPIO_PIN_SET);
}

void encoder_disable(void)
{
  HAL_GPIO_WritePin(ENCODER_TX_EN_GPIO_Port, ENCODER_TX_EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ENCODER_RX_EN_GPIO_Port, ENCODER_RX_EN_Pin, GPIO_PIN_RESET);
}

encoder_state_t encoder_read(void)
{
  uint8_t k1 = (uint8_t)HAL_GPIO_ReadPin(ENCODER_K1_GPIO_Port, ENCODER_K1_Pin);
  uint8_t k2 = (uint8_t)HAL_GPIO_ReadPin(ENCODER_K2_GPIO_Port, ENCODER_K2_Pin);

  uint8_t encoder_state = (k1 << 1 | k2) & 0b11;

  switch (encoder_state)
  {
  case 0:
    return ENCODER_LOCKED;
  case 1:
    return ENCODER_TRANSIT;
  case 2:
    return ENCODER_OVEREXTENDED;
  case 3:
    return ENCODER_UNLOCKED;
  }

  return ENCODER_ERROR;
}

encoder_state_t encoder_poll(void)
{
  encoder_enable();
  HAL_Delay(10);
  encoder_state_t res = encoder_read();
  encoder_disable();

  return res;
}


void encoder_to_string(encoder_state_t val, char * str)
{
  switch(val){
    case ENCODER_LOCKED:
      sprintf(str, "locked");
    break;

    case ENCODER_TRANSIT:
      sprintf(str, "transit");
    break;

    case ENCODER_OVEREXTENDED:
      sprintf(str, "overextended");
    break;

    case ENCODER_UNLOCKED:
      sprintf(str, "unlocked");
    break;

    case ENCODER_ERROR:
      sprintf(str, "error");
    break;
  }
}
