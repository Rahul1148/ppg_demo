//-----------------------------------------------------------------
///
///     \file i2c_sensor.h
///
///     \brief sensor driver file
///
///
///     \author       Rahul
///
///     Location:     India
///
///     Project Name: PPG_DEMO
///
///     \date Created 20OCT2024
///
///      Tools:  e2StudioIDE
///      Device:   RENESASA FPB-RA4E1(R7FA4E10D2CFM)
///      Operating System: windows 10
///      e2studio Version: 4.30.0.v20231201-0110
///      Eclipse CDT Version: 11.4.0.202309142347
///      IDF Eclipse Plugin Version: 3.0.0.202406051940
///      IDF Version:   5.3
//-----------------------------------------------------------------

#ifndef I2C_SENSOR_H_
#define I2C_SENSOR_H_

//==============================================================================
//          __             __   ___  __
//  | |\ | /  ` |    |  | |  \ |__  /__`
//  | | \| \__, |___ \__/ |__/ |___ .__/
//
//==============================================================================


//==============================================================================
//   __   ___  ___         ___  __
//  |  \ |__  |__  | |\ | |__  /__`
//  |__/ |___ |    | | \| |___ .__/
//
//==============================================================================


#define ONE_BYTE                0x01
#define TWO_BYTE                0x02

#define MEASURE_PAYLOAD_SIZE    0x03        //measurement enable data length
#define ENABLE_BIT              0x08

#define DEVICE_ID_REG           0xFF
#define DEVICE_SIGNATURE        0x1E

/* configure the  fifo_register */
#define A_FULL_ENABLE_REG       0X02
#define A_FULL_ENABLE_DATA      0x80

#define Reset_part_reg          0x0D
#define Reset_part_data         0X01

#define FIFO_ENABLE_reg         0X0D
#define FIFO_ENABLE_data        0X04

#define FIFO_ROLLS_ON_FULL_reg  0x08
#define FIFO_ROLLS_ON_FULL_data 0x10  //1F TO 10,0F.7f

/* Enable the pgg and ecg mode registers*/
#define PPG_SLOT_reg                0x09
#define PPG_SLOT_data               0x01     // 01 for led1 only

#define ECG_SLOT_reg                0x0A
#define ECG_SLOT_data               0x00

/* Configuration of the Acquisition Settings for the Best PPG Performance */

#define PPG_LED1_reg                0x11
#define PPG_LED2_reg                0x12

#define PPG_LED1_data               0xFF
#define PPG_LED2_data               0xFF

#define PPG_ADC_RGE_reg             0X0E
#define PPG_ADC_RGE_data            0x51   // CHANGED D6 --> 0XDB ,11 ,51

#define LED_START_INTG_DELAY_reg    0x0F
#define LED_START_INTG_DELAY_data   0x05      // CHANGED 00 to 03 ,05

/* Configuration the Acquisition Settings for the Best ECG Performance */
#define ECG_ADC_OSR_reg             0x3C
#define ECG_ADC_OSR_data            0x03

#define PGA_ECG_Gain_reg            0x3E
#define PGA_ECG_Gain_data           0x0D

/* Configuration of the AFE Settings for the Best ECG Performance*/
#define AFE_ONE_reg                 0XFF
#define AFE_ONE_data                0X54

#define AFE_TWO_reg                 0XFF
#define AFE_TWO_data                0X4D

#define AFE_THREE_reg               0XCE
#define AFE_THREE_data              0X0A

#define AFE_FOUR_reg                0XCF
#define AFE_FOUR_data               0X18

#define AFE_FIVE_reg                0XFF
#define AFE_FIVE_data               0X00

#define SENSOR_DATA_SIZE            0x06

#define fifo_read_pointer           0x06
#define fifo_write_pointer          0x04

//==============================================================================
//   __        __   __                          __   __
//  / _` |    /  \ |__)  /\  |       \  /  /\  |__) /__`
//  \__> |___ \__/ |__) /~~\ |___     \/  /~~\ |  \ .__/
//
//==============================================================================

//==============================================================================
//  ___      __   ___  __   ___  ___  __
//   |  \ / |__) |__  |  \ |__  |__  /__`
//   |   |  |    |___ |__/ |___ |    .__/
//
//==============================================================================

//==============================================================================
//   __        __          __      ___            __  ___    __        __
//  |__) |  | |__) |    | /  `    |__  |  | |\ | /  `  |  | /  \ |\ | /__`
//  |    \__/ |__) |___ | \__,    |    \__/ | \| \__,  |  | \__/ | \| .__/
//
//==============================================================================

fsp_err_t init_sensor(void);
void deinit_sensor(void);
fsp_err_t bit_mask(uint8_t reg,uint8_t mask_bit,uint8_t thing);
fsp_err_t WRITE_REGISTER1(uint8_t reg_add,uint8_t reg_value);
uint8_t READ_REGISTER1(uint8_t*read_reg);
fsp_err_t soft_rest(void);
fsp_err_t set_up(void);
fsp_err_t enableDATAREADY(void);
fsp_err_t ppg_data_capture(void);
uint8_t GET_READ_REGISTER(uint8_t reg);
uint8_t GET_WRITE_REGISTER(uint8_t reg);
fsp_err_t READ_FIFO_DATA_REG(void);



#endif /* I2C_SENSOR_H_ */
