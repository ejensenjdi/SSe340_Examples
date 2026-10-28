/*
 * our_HAL.h
 *
 *  Created on: Sep 25, 2026
 *      Author: Elijah
 */

#ifndef INC_OUR_HAL_H_
#define INC_OUR_HAL_H_

extern SPI_HandleTypeDef hspi1;

int myBlink(uint32_t *i)
{
	  	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		  HAL_Delay(100);
		  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		  HAL_Delay(100);


		  *i=*i+1; //dereference pointer
		  // to change value instead of address

return 0;
}

int myFunction( int *myvar)
{
return 0;
}


int write_to_display(uint8_t *pixel_data, int N)
{

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin,GPIO_PIN_RESET);

	HAL_Delay(1);

	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin,GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1,0x2A,1,10); //send 2A to the SPI bus

	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin,GPIO_PIN_SET);
	HAL_Delay(1);

	//send Column data here
	uint8_t col_data[4] = {0,0,0,159};

	HAL_SPI_Transmit(&hspi1,col_data,4,10);


	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin,GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1,0x2B,1,10);//send 2B to the SPI bus

	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin,GPIO_PIN_SET);

	//send Row data here
	uint8_t row_data[4] = {0,0,0,127};

	HAL_SPI_Transmit(&hspi1,row_data,4,10);

	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin,GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1,0x2C,1,10);//send 2C to the SPI bus

	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin,GPIO_PIN_SET);


	//write to RAM  (SPI bus)
	HAL_SPI_Transmit(&hspi1,pixel_data,N,10);


	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin,GPIO_PIN_SET);


	return 0;
}




#endif /* INC_OUR_HAL_H_ */
