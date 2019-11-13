#ifdef __cplusplus
 extern "C" {
#endif


#include "keybd.h"
#include "main.h"
#include "stm32l0xx.h"
#include "stm32l0xx_hal.h"


/* HELPER FUNCTIONS --------------------------------------------------------*/

/* ---- (1) TRANSMIT AN I2C CHARACTER ---- */

 void I2C_Transmit(char* output){
     HAL_I2C_Master_Transmit(&hi2c1, 0x50<<1, (uint8_t*)(output), 1, HAL_MAX_DELAY);
 }



 /* ---- (2) DEBOUNCE A PARTICULAR ROW ---- */
 void btnDebounce(int** state_array, int row, int col, int press_state){

	// CHECK IF SHIFT IS ACTIVATED
	int shift_status = (!state_array[4][0] || !state_array[4][11]);
	int caps_flag = !state_array[0][5];

	if (shift_status || caps_flag){
		HAL_GPIO_WritePin(LED_DEBUG_GPIO_Port, LED_DEBUG_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(LED_DEBUG_GPIO_Port, LED_DEBUG_Pin, GPIO_PIN_RESET);
	}

	switch (row)
	{

		// ROW 0
		case 0:
			switch (col)
			{
				// ESC KEY --> Send KEYCODE E0
				case 0:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE0);}
					state_array[row][col] = press_state;
					break;
				// [? /] KEY --> Send char
				case 14:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("?");
						else
							I2C_Transmit("/");
					}
					state_array[row][col] = press_state;
					break;
				// DEL KEY --> Send KEYCODE E1
				case 15:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE1);}
					state_array[row][col] = press_state;
					break;
				default:
					break;
			}
			break;

		// ROW 1
		case 1:
			switch (col)
			{

				// [~ `] KEY --> Send char
				case 0:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("~");
						else
							I2C_Transmit("`");
					}
					state_array[row][col] = press_state;
					break;

				// [! 1] KEY --> Send char
				case 1:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("!");
						else
							I2C_Transmit("1");
					}
					state_array[row][col] = press_state;
					break;

				// [@ 2] KEY --> Send char
				case 2:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("@");
						else
							I2C_Transmit("2");
					}
					state_array[row][col] = press_state;
					break;

				// [# 3] KEY --> Send char
				case 3:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("#");
						else
							I2C_Transmit("3");
					}
					state_array[row][col] = press_state;
					break;

				// [$ 4] KEY --> Send char
				case 4:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("$");
						else
							I2C_Transmit("4");
					}
					state_array[row][col] = press_state;
					break;

				// [% 5] KEY --> Send char
				case 5:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("%");
						else
							I2C_Transmit("5");
					}
					state_array[row][col] = press_state;
					break;

				// [^ 6] KEY --> Send char
				case 6:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("^");
						else
							I2C_Transmit("6");
					}
					state_array[row][col] = press_state;
					break;

			    // [& 7] KEY --> Send char
				case 7:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("&");
						else
							I2C_Transmit("7");
					}
					state_array[row][col] = press_state;
					break;

				// [* 8] KEY --> Send char
				case 8:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("*");
						else
							I2C_Transmit("8");
					}
					state_array[row][col] = press_state;
					break;

				// [( 9] KEY --> Send char
				case 9:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("(");
						else
							I2C_Transmit("9");
					}
					state_array[row][col] = press_state;
					break;

				// [) 0] KEY --> Send char
				case 10:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit(")");
						else
							I2C_Transmit("0");
					}
					state_array[row][col] = press_state;
					break;

				// [_ -] KEY --> Send char
				case 11:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("_");
						else
							I2C_Transmit("-");
					}
					state_array[row][col] = press_state;
					break;

				// [+ =] KEY --> Send char
				case 12:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("+");
						else
							I2C_Transmit("-");
					}
					state_array[row][col] = press_state;
					break;

				// BACKSPACE KEY --> SEND KEYCODE E2
				case 13:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE2);}
					state_array[row][col] = press_state;
					break;
				default:
					break;
			}
			break;

		// ROW 2
		case 2:
			switch (col)
			{

				// TAB KEY --> SEND KEYCODE E3
				case 0:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE3);}
					state_array[row][col] = press_state;
					break;

				// Q KEY --> Send char
				case 1:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("Q");
						else
							I2C_Transmit("q");
					}
					state_array[row][col] = press_state;
					break;

				// W Key --> Send char
				case 2:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("W");
						else
							I2C_Transmit("w");
					}
					state_array[row][col] = press_state;
					break;

				// E Key --> Send char
				case 3:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("E");
						else
							I2C_Transmit("e");
					}
					state_array[row][col] = press_state;
					break;

				// R Key --> Send char
				case 4:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("R");
						else
							I2C_Transmit("r");
					}
					state_array[row][col] = press_state;
					break;

				// T Key --> Send char
				case 5:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("T");
						else
							I2C_Transmit("t");
					}
					state_array[row][col] = press_state;
					break;

				// Y Key --> Send char
				case 6:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("Y");
						else
							I2C_Transmit("y");
					}
					state_array[row][col] = press_state;
					break;

				// U Key --> Send char
				case 7:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("U");
						else
							I2C_Transmit("u");
					}
					state_array[row][col] = press_state;
					break;

				// I Key --> Send char
				case 8:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("I");
						else
							I2C_Transmit("i");
					}
					state_array[row][col] = press_state;
					break;

				// O Key --> Send char
				case 9:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("O");
						else
							I2C_Transmit("o");
					}
					state_array[row][col] = press_state;
					break;

				// P Key --> Send char
				case 10:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("P");
						else
							I2C_Transmit("p");
					}
					state_array[row][col] = press_state;
					break;

				// [[ {] Key --> Send char
				case 11:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("{");
						else
							I2C_Transmit("[");
					}
					state_array[row][col] = press_state;
					break;

				// [} ]] Key --> Send char
				case 12:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("}");
						else
							I2C_Transmit("]");
					}
					state_array[row][col] = press_state;
					break;

				// [\ |] Key --> Send char
				case 14:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("|");
						else
							I2C_Transmit("|");
					}
					state_array[row][col] = press_state;
					break;
				default:
					break;
			}
			break;


		// ROW 3
		case 3:
			switch (col)
			{

				// CAPS LOCK KEY --> TOGGLE CAPS LOCK
				case 0:
					if(press_state & !state_array[row][col]){state_array[0][5] ^= 1;}
					state_array[row][col] = press_state;
					break;

				// A Key --> Send char
				case 1:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("A");
						else
							I2C_Transmit("a");
					}
					state_array[row][col] = press_state;
					break;

				// S Key --> Send char
				case 2:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("S");
						else
							I2C_Transmit("s");
					}
					state_array[row][col] = press_state;
					break;

				// D Key --> Send char
				case 3:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("D");
						else
							I2C_Transmit("d");
					}
					state_array[row][col] = press_state;
					break;

				// F Key --> Send char
				case 4:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("F");
						else
							I2C_Transmit("f");
					}
					state_array[row][col] = press_state;
					break;

				// G Key --> Send char
				case 5:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("G");
						else
							I2C_Transmit("g");
					}
					state_array[row][col] = press_state;
					break;

				// H Key --> Send char
				case 6:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("H");
						else
							I2C_Transmit("h");
					}
					state_array[row][col] = press_state;
					break;

				// J key --> Send char
				case 7:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("J");
						else
							I2C_Transmit("j");
					}
					state_array[row][col] = press_state;
					break;

				// K key --> Send char
				case 8:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("K");
						else
							I2C_Transmit("k");
					}
					state_array[row][col] = press_state;
					break;

				// L key --> Send char
				case 9:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("L");
						else
							I2C_Transmit("l");
					}
					state_array[row][col] = press_state;
					break;

				// [: ;] Key --> Send char
				case 10:
					if(press_state & !state_array[row][col]){
						if (caps_flag)
							I2C_Transmit(":");
						else
							I2C_Transmit(";");
					}
					state_array[row][col] = press_state;
					break;

				// [" '] Key --> Send char
				case 11:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("\"");
						else
							I2C_Transmit("'");
					}
					state_array[row][col] = press_state;
					break;

				// ENTER Key --> Send KEYCODE E4
				case 13:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE4);}
					state_array[row][col] = press_state;
					break;
				default:
					break;
			}
			break;

		// ROW 4
		case 4:
			switch (col)
			{

				// SHIFT Key --> No change
				case 0:
					if(press_state & !state_array[row][col]){}
					state_array[row][col] = press_state;
					break;

				// Z Key --> Send char
				case 1:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("Z");
						else
							I2C_Transmit("z");
					}
					state_array[row][col] = press_state;
					break;

				// X Key --> Send Char
				case 2:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("X");
						else
							I2C_Transmit("x");
					}
					state_array[row][col] = press_state;
					break;

				// C Key --> Send Char
				case 3:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("C");
						else
							I2C_Transmit("c");
					}
					state_array[row][col] = press_state;
					break;

				// V Key --> Send Char
				case 4:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("V");
						else
							I2C_Transmit("v");
					}
					state_array[row][col] = press_state;
					break;

				// B Key --> Send Char
				case 5:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("B");
						else
							I2C_Transmit("b");
					}
					state_array[row][col] = press_state;
					break;

				// N Key --> Send Char
				case 6:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("N");
						else
							I2C_Transmit("n");
					}
					state_array[row][col] = press_state;
					break;

				// M Key --> Send Char
				case 7:
					if(press_state & !state_array[row][col]){
						if (shift_status || caps_flag)
							I2C_Transmit("M");
						else
							I2C_Transmit("n");
					}
					state_array[row][col] = press_state;
					break;

				// [< ,] Key --> Send Char
				case 8:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("<");
						else
							I2C_Transmit(",");
					}
					state_array[row][col] = press_state;
					break;

				// [> .] Key --> Send Char
				case 9:
					if(press_state & !state_array[row][col]){
						if (shift_status)
							I2C_Transmit("<");
						else
							I2C_Transmit(",");
					}
					state_array[row][col] = press_state;
					break;

				// UP KEY --> SEND KEYCODE E5
				case 10:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE5);}
					state_array[row][col] = press_state;
					break;

				// RIGHT SHIFT KEY
				case 11:
					if(press_state & !state_array[row][col]){}
					state_array[row][col] = press_state;
					break;
				default:
					break;
			}
			break;


		// ROW 5
		case 5:
			switch (col)
			{

				// SPACE KEYS
				case 4:
					if(press_state & !state_array[row][col]){I2C_Transmit(" ");}
					state_array[row][col] = press_state;
					break;
				case 6:
					if(press_state & !state_array[row][col]){I2C_Transmit(" ");}
					state_array[row][col] = press_state;
					break;
				case 8:
					if(press_state & !state_array[row][col]){I2C_Transmit(" ");}
					state_array[row][col] = press_state;
					break;

				// LEFT KEY --> SEND KEYCODE E6
				case 11:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE6);}
					state_array[row][col] = press_state;
					break;

				// DOWN KEY --> SEND KEYCODE E7
				case 12:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE7);}
					state_array[row][col] = press_state;
					break;

				// RIGHT KEY --> SEND KEYCODE E8
				case 13:
					if(press_state & !state_array[row][col]){I2C_Transmit(0xE8);}
					state_array[row][col] = press_state;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

 }


 /* ---- (3) SET COLUMNS AND READ ROWS ---- */
 void matrixDebounce(int** state_array){

	 // ITERATE THROUGH ALL COLUMNS
	 for(int col = 0; col < 16; col++){

		// INITIALIZE ALL COLUMNS TO SET MODE
		HAL_GPIO_WritePin(GPIO_COL_0_GPIO_Port, GPIO_COL_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_1_GPIO_Port, GPIO_COL_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_2_GPIO_Port, GPIO_COL_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_3_GPIO_Port, GPIO_COL_3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_4_GPIO_Port, GPIO_COL_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_5_GPIO_Port, GPIO_COL_5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_6_GPIO_Port, GPIO_COL_6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_7_GPIO_Port, GPIO_COL_7_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_8_GPIO_Port, GPIO_COL_8_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_9_GPIO_Port, GPIO_COL_9_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_10_GPIO_Port, GPIO_COL_10_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_11_GPIO_Port, GPIO_COL_11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_12_GPIO_Port, GPIO_COL_12_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_13_GPIO_Port, GPIO_COL_13_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_14_GPIO_Port, GPIO_COL_14_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIO_COL_15_GPIO_Port, GPIO_COL_15_Pin, GPIO_PIN_SET);

		// RESET THE DESIRED COL PIN
		switch (col)
		{
				case 0:
					HAL_GPIO_WritePin(GPIO_COL_0_GPIO_Port, GPIO_COL_0_Pin, GPIO_PIN_RESET);
					break;
				case 1:
					HAL_GPIO_WritePin(GPIO_COL_1_GPIO_Port, GPIO_COL_1_Pin, GPIO_PIN_RESET);
					break;
				case 2:
					HAL_GPIO_WritePin(GPIO_COL_2_GPIO_Port, GPIO_COL_2_Pin, GPIO_PIN_RESET);
					break;
				case 3:
					HAL_GPIO_WritePin(GPIO_COL_3_GPIO_Port, GPIO_COL_3_Pin, GPIO_PIN_RESET);
					break;
				case 4:
					HAL_GPIO_WritePin(GPIO_COL_4_GPIO_Port, GPIO_COL_4_Pin, GPIO_PIN_RESET);
					break;
				case 5:
					HAL_GPIO_WritePin(GPIO_COL_5_GPIO_Port, GPIO_COL_5_Pin, GPIO_PIN_RESET);
					break;
				case 6:
					HAL_GPIO_WritePin(GPIO_COL_6_GPIO_Port, GPIO_COL_6_Pin, GPIO_PIN_RESET);
					break;
				case 7:
					HAL_GPIO_WritePin(GPIO_COL_7_GPIO_Port, GPIO_COL_7_Pin, GPIO_PIN_RESET);
					break;
				case 8:
					HAL_GPIO_WritePin(GPIO_COL_8_GPIO_Port, GPIO_COL_8_Pin, GPIO_PIN_RESET);
					break;
				case 9:
					HAL_GPIO_WritePin(GPIO_COL_9_GPIO_Port, GPIO_COL_9_Pin, GPIO_PIN_RESET);
					break;
				case 10:
					HAL_GPIO_WritePin(GPIO_COL_10_GPIO_Port, GPIO_COL_10_Pin, GPIO_PIN_RESET);
					break;
				case 11:
					HAL_GPIO_WritePin(GPIO_COL_11_GPIO_Port, GPIO_COL_11_Pin, GPIO_PIN_RESET);
					break;
				case 12:
					HAL_GPIO_WritePin(GPIO_COL_12_GPIO_Port, GPIO_COL_12_Pin, GPIO_PIN_RESET);
					break;
				case 13:
					HAL_GPIO_WritePin(GPIO_COL_13_GPIO_Port, GPIO_COL_13_Pin, GPIO_PIN_RESET);
					break;
				case 14:
					HAL_GPIO_WritePin(GPIO_COL_14_GPIO_Port, GPIO_COL_14_Pin, GPIO_PIN_RESET);
					break;
				case 15:
					HAL_GPIO_WritePin(GPIO_COL_15_GPIO_Port, GPIO_COL_15_Pin, GPIO_PIN_RESET);
					break;
				default:
					break;

		}

		// PERFORM DEBOUNCING ON ALL ROWS
		btnDebounce(state_array, 0, col, HAL_GPIO_ReadPin(GPIO_ROW_0_GPIO_Port, GPIO_ROW_0_Pin));
		btnDebounce(state_array, 1, col, HAL_GPIO_ReadPin(GPIO_ROW_1_GPIO_Port, GPIO_ROW_1_Pin));
		btnDebounce(state_array, 2, col, HAL_GPIO_ReadPin(GPIO_ROW_2_GPIO_Port, GPIO_ROW_2_Pin));
		btnDebounce(state_array, 3, col, HAL_GPIO_ReadPin(GPIO_ROW_3_GPIO_Port, GPIO_ROW_3_Pin));
		btnDebounce(state_array, 4, col, HAL_GPIO_ReadPin(GPIO_ROW_4_GPIO_Port, GPIO_ROW_4_Pin));
		btnDebounce(state_array, 5, col, HAL_GPIO_ReadPin(GPIO_ROW_5_GPIO_Port, GPIO_ROW_5_Pin));

	 }

 }



/* ---- (4) INITIALIZE STATE ARRAY ---- */
 void state_array_init(int** array, int rows, int cols)
 {
   int i, j;
   for (i = 0; i < rows; i++)
   {
	 for (j = 0; j < cols; j++)
	 {
		 array[i][j] = 1;
	 }
   }
 }

