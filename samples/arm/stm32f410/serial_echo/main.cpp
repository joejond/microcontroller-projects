#include "stm32f4xx_hal.h"

#include <SerialHAL.h>
#include <TimerHAL.h>

using namespace digitalcave;

extern UART_HandleTypeDef huart6;

extern "C" {
	void dc_main();
}

void dc_main(){
	//We flash the light briefly, then go into the infinite loop.
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	SerialHAL serial(&huart6, 64);
	
	uint32_t lastSend = timer_millis();

	while (1){
		if ((timer_millis() - lastSend) > 500){
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
			char buffer[32];
			snprintf(buffer, sizeof(buffer), "Time: %d\n", (uint16_t) timer_millis());
			serial.write(buffer);
			lastSend = timer_millis();

			uint8_t b = 0;
			while (serial.read(&b)){
				serial.write(b);
			}
		}
	}
}
