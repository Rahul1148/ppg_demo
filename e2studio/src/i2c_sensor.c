
//-----------------------------------------------------------------
///
///     \file i2c_sensor.c
///
///     \brief sensor driver file
///
///
///     \author       Rahul bh
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
///      e2studio Version: 
//-----------------------------------------------------------------



//==============================================================================
//          __             __   ___  __
//  | |\ | /  ` |    |  | |  \ |__  /__`
//  | | \| \__, |___ \__/ |__/ |___ .__/
//
//==============================================================================

#include "common_utils.h"
#include "i2c_sensor.h"
#include <string.h>
#include <stdlib.h>


//==============================================================================
//   __   ___  ___         ___  __
//  |  \ |__  |__  | |\ | |__  /__`
//  |__/ |___ |    | | \| |___ .__/
//
//==============================================================================



//==============================================================================
//   __        __   __                          __   __
//  / _` |    /  \ |__)  /\  |       \  /  /\  |__) /__`
//  \__> |___ \__/ |__) /~~\ |___     \/  /~~\ |  \ .__/
//
//==============================================================================

uint8_t write_ptr_data_1[6];

uint32_t ppg_buffer1[3200];
uint32_t ppg_buffer2[3200];

//==============================================================================
//  ___      __   ___  __   ___  ___  __
//   |  \ / |__) |__  |  \ |__  |__  /__`
//   |   |  |    |___ |__/ |___ |    .__/
//
//==============================================================================

//==============================================================================
//   __  ___      ___    __                __   __
//  /__`  |   /\   |  | /  `    \  /  /\  |__) /__`
//  .__/  |  /~~\  |  | \__,     \/  /~~\ |  \ .__/
//
//==============================================================================





//==============================================================================
//   __        __          __      ___            __  ___    __        __
//  |__) |  | |__) |    | /  `    |__  |  | |\ | /  `  |  | /  \ |\ | /__`
//  |    \__/ |__) |___ | \__,    |    \__/ | \| \__,  |  | \__/ | \| .__/
//
//==============================================================================
/* Reading I2C call back event through i2c_Master callback */
static volatile i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

static fsp_err_t get_device_id(uint8_t *dev_id);
static fsp_err_t validate_i2c_event(void);



/*******************************************************************************
 * Function name  : ppg_data_capture
 *
 * Description    : function to manage read data from data rego in the max
 * Parameters     : void
 * Returns        : error return from renesas
 * FSP_SUCCESS                       successful event receiving returns FSP_SUCCESS
 * FSP_ERR_TRANSFER_ABORTED          Either on timeout elapsed or received callback event is I2C_MASTER_EVENT_ABORTED
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/


fsp_err_t ppg_data_capture(void)
{
    fsp_err_t err = FSP_SUCCESS;
    bool new_data_valid = false;
    uint8_t read_pointer = 0;
    uint8_t write_pointer;
    uint8_t one_sample = 0;
//    uint32_t temp1 = 0, temp2 = 0, temp1_0 = 0, temp1_1 = 0, temp1_2 = 0, temp1_3 = 0, temp2_0 = 0, temp2_1 = 0, temp2_2 = 0, temp2_3 = 0;
//    int iterator = 0;

for(int k=0;k<10;k++)
{

    err = WRITE_REGISTER1(0X04, 0x00);

            while(!new_data_valid)
            {
                write_pointer = GET_WRITE_REGISTER(0x04);
                if(write_pointer == 0x1F)
                {
                   new_data_valid = true;
                }

            }

            if(new_data_valid)
            {
                for(uint8_t j = 0;j<32;j++)
                 {
                    label:
                     err = WRITE_REGISTER1(0x06, (uint8_t)one_sample);
                     err = READ_FIFO_DATA_REG();
                     ppg_buffer1[one_sample] = (uint32_t) write_ptr_data_1[0] << 16 | (uint32_t) write_ptr_data_1[1] << 8| (uint32_t) write_ptr_data_1[2] << 0;
                     ppg_buffer2[one_sample] = (uint32_t) write_ptr_data_1[3] << 16| (uint32_t) write_ptr_data_1[4] << 8| (uint32_t) write_ptr_data_1[5] << 0;
                     read_pointer = GET_READ_REGISTER(0X06);
                     if((ppg_buffer1[one_sample] < 9050) || (ppg_buffer2[one_sample] < 9050))
                     goto label;
                     SEGGER_RTT_printf (0, "%d\r\n", (ppg_buffer1[one_sample] & 0x7ffff));
                     SEGGER_RTT_printf (0, "%d\r\n", (ppg_buffer2[one_sample] & 0x7ffff));

                     one_sample++;
//                    label:
//                    err = WRITE_REGISTER1(0x06, (uint8_t)one_sample);
//                    err = WRITE_DATA_REGISTER();
//                    ppg_buffer1[one_sample] = (uint32_t) write_ptr_data_1[0] << 16 | (uint32_t) write_ptr_data_1[1] << 8| (uint32_t) write_ptr_data_1[2] << 0;
//                    ppg_buffer2[one_sample] = (uint32_t) write_ptr_data_1[3] << 16| (uint32_t) write_ptr_data_1[4] << 8| (uint32_t) write_ptr_data_1[5] << 0;
//                    read_pointer = GET_READ_REGISTER(0X06);
//                    if((ppg_buffer1[one_sample] < 9050) || (ppg_buffer2[one_sample] < 9050))
//                        goto label;
//                    if(one_sample<2)
//                        goto label1;
//                    temp1 = (ppg_buffer1[one_sample-1] + ppg_buffer1[one_sample])/2;
//                    temp2 = (ppg_buffer2[one_sample-1] + ppg_buffer2[one_sample])/2;
//
//                    if(k == 10 && j == 31)    {
//                     temp1_0 = temp1;
//                     temp2_0 = temp2;
//                    for(iterator=0;;iterator++) {
//                        temp1_0 = temp1_0/10;
//                        temp2_0 = temp2_0/10;
//                        temp1_3 = temp1_2; temp1_2 = temp1_1; temp1_1 = temp1_0;
//                        temp2_3 = temp2_2; temp2_2 = temp2_1; temp2_1 = temp2_0;
//                        if(temp1_0 == 0 && temp2_0 == 0)
//                            break;
//                    }
//                    k = 8;
//                    SEGGER_RTT_printf (0, "temp1_3= %d\r\n", temp1_3);
//                    SEGGER_RTT_printf (0, "temp2_3= %d\r\n", temp2_3);
//                    SEGGER_RTT_printf (0, "Digits= %d\r\n", iterator+1);
//                    for(iterator;iterator>1;iterator--) {
//                        temp1_3 = temp1_3*10;
//                        temp2_3 = temp2_3*10;
//                    }
//                    SEGGER_RTT_printf (0, "Subtractor1: %d :: Subtractor2: %d\r\n", temp1_3, temp1_2);
//                    }
//                    //ppg_buffer1[one_sample] = ppg_buffer1[one_sample] - temp1_3;
//                    //ppg_buffer2[one_sample] = ppg_buffer2[one_sample] - temp2_3;
//                    SEGGER_RTT_printf (0, "%d\r\n", (ppg_buffer1[one_sample] - temp1_3));
//                    SEGGER_RTT_printf (0, "%d\r\n", (ppg_buffer2[one_sample] - temp2_3));
//                    //SEGGER_RTT_printf (0, "%d\r\n", (ppg_buffer1[one_sample] & 0x7ffff));
//                    //SEGGER_RTT_printf (0, "%d\r\n", (ppg_buffer2[one_sample] & 0x7ffff));
//                    label1:
//                    one_sample++;

                 }
            }
}

    return err;
}


/*******************************************************************************
 * Function name  : set_up
 *
 * Description    : function to manage a configuration of fifo of max86150;
 * Parameters     : void
 * Returns        : error return from renesas
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/

fsp_err_t set_up(void)
{
    fsp_err_t err = FSP_SUCCESS;

    err = WRITE_REGISTER1(0X0D,0X01);                                          //SYSTEM_CONTROL =0X0D,RESET_VALUE = 0X01;
    if(err == FSP_SUCCESS)
    {
        err = WRITE_REGISTER1(0X08,0X7F);                                      //fifo_configuration =0x08
        if(err == FSP_SUCCESS)
        {
            err = bit_mask(0x08,0x1f,0x04);                                    //fifo_configuration sample_avarage
            if(err == FSP_SUCCESS)
            {
                err = WRITE_REGISTER1(0X09,0X21);                              // mode configuration: 0x09,0x21
                if(err == FSP_SUCCESS)
                {
                    err = WRITE_REGISTER1(0X0A,0X00);                          //SPO2 CONFIGURATION:  0X0A ,0X09->0X00
                    if(err == FSP_SUCCESS)
                    {
                        err = WRITE_REGISTER1(0X0E,0XD6);                      // PPG_CONFIGURSTION 1 :0X0E,0XD6
                        if(err == FSP_SUCCESS)
                        {
                            err = WRITE_REGISTER1(0X0F,0X01);                  //PPG_CONFIGURSTION 2 : 0X0F,0X01
                            if(err == FSP_SUCCESS)
                            {
                                err = WRITE_REGISTER1(0X14,0X00);              //LED_RANGE :0X14,0X00
                                if(err == FSP_SUCCESS)
                                {
                                    err = WRITE_REGISTER1(0X0D,0X4);           //start FIFO:0X0D,0X4
                                    if(err == FSP_SUCCESS)
                                    {
                                        err = WRITE_REGISTER1(0X11,0XFF);           //SET APLITUDE REDLED:0X11,0XFF
                                        if(err == FSP_SUCCESS)
                                        {
                                            err = WRITE_REGISTER1(0X12,0XFF);           //SET APLITUDE IRLED:0X12,0XFF
                                        }
                                    }
                                }
                            }
                        }
                    }

                }


            }
        }
    }

    return err;
}

/*******************************************************************************
 * Function name  : WRITE_REGISTER1
 *
 * Description    : setting value into the register in max86150 through this WRITE_REGISTER1 function
 * Parameters     : reg_add(max_reg) ,reg_value(what value inside the register)
 * Returns        : error return from renesas
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/


fsp_err_t WRITE_REGISTER1(uint8_t reg_add,uint8_t reg_value)
{
    uint8_t write_reg[MEASURE_PAYLOAD_SIZE] = {reg_add,reg_value};
    fsp_err_t err = FSP_SUCCESS;


    err = R_IIC_MASTER_Write (&g_i2c_master_ctrl, write_reg, TWO_BYTE, false);
    if (FSP_SUCCESS == err)
     {
         err = validate_i2c_event();
         /* handle error */
         if(FSP_ERR_TRANSFER_ABORTED == err)
         {
             APP_ERR_PRINT("** POWER_CTL reg I2C write failed!!! ** \r\n");
         }
     }
     /* handle error */
     else
     {
         /* Write API returns itself is not successful */
         APP_ERR_PRINT("** R_IIC_MASTER_Write API failed ** \r\n");
     }
        return err;

}


/*******************************************************************************
 * Function name  : READ_REGISTER1
 *
 * Description    : read a value inside register in max86150 through READ_REGISTER1 function
 * Parameters     : read_reg
 * Returns        : READ_DATA(return value from reg)
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/

/* write _register function*/
uint8_t READ_REGISTER1(uint8_t*read_reg)
{
    fsp_err_t err = FSP_SUCCESS;
    static uint8_t READ_DATA = RESET_VALUE;

    /* Write  Data register   */
        err = R_IIC_MASTER_Write (&g_i2c_master_ctrl,read_reg, 0x01, true);
        /* handle error */
        if (FSP_SUCCESS != err)
        {
            APP_ERR_PRINT("** R_IIC_MASTER_Write API failed ** \r\n");
        }
        else
        {
            err = validate_i2c_event ();
            /* Performs read operation only when write event is successful, failure part is handled at next stage*/
            if (FSP_SUCCESS == err)
            {
                err = R_IIC_MASTER_Read (&g_i2c_master_ctrl,&READ_DATA, 0X01, false);
                /* handle error */
                if (FSP_SUCCESS != err)
                {
                    APP_ERR_PRINT("** R_IIC_MASTER_Read API failed ** \r\n");
                }
                else
                {
                    err = validate_i2c_event ();

                    if (FSP_SUCCESS != err)
                    {
                        APP_ERR_PRINT("** Data register, I2C read failed ** \r\n");

                    }

                }

            }
            else
            {
                APP_ERR_PRINT("** ppg Data register, I2C write failed ** \r\n");

            }
        }


    return READ_DATA;


}

/*******************************************************************************
 * Function name  : soft_rest
 *
 * Description    : system reset in the max86150
 * Parameters     : void
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/


fsp_err_t soft_rest(void)
{
    fsp_err_t err = FSP_SUCCESS;

   err = bit_mask(0x0D,0xFE,0x01);


//    uint8_t soft_reset_regdata = READ_REGISTER1(&soft_rst_reg);
//    soft_reset_regdata = soft_reset_regdata & thing;
//    uint8_t soft_rstreg[MEASURE_PAYLOAD_SIZE] = {soft_rst_reg,soft_reset_regdata};
//    err = WRITE_REGISTER1(soft_rstreg);

    return err;
}
/*******************************************************************************
 * Function name  : bit_mask
 *
 * Description    : first read the reg and reset currect bit value
 * Parameters     : reg,mask_bit,thing
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/



fsp_err_t bit_mask(uint8_t reg,uint8_t mask_bit,uint8_t thing)       //reg,mask_reg,thing
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t data_read_reg = READ_REGISTER1(&reg);
    data_read_reg = data_read_reg & mask_bit;
    err = WRITE_REGISTER1(reg,data_read_reg|thing);

    return err;
}

/*******************************************************************************
 * Function name  : enableDATAREADY
 *
 * Description    : this function interrup the data enable
 * Parameters     : void
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/

fsp_err_t enableDATAREADY(void)
{
    fsp_err_t err     = FSP_SUCCESS;
    err = bit_mask(0X02,0xBF,0X40);                                           // enable interrup enable 0x02
    return err;
}

/*******************************************************************************
 * Function name  : GET_READ_REGISTER
 *
 * Description    : read the reg
 * Parameters     : void
 * Returns        : reg value
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/


uint8_t GET_READ_REGISTER(uint8_t reg)
{
    return READ_REGISTER1(&reg);
}
/*******************************************************************************
 * Function name  : GET_WRITE_REGISTER
 *
 * Description    : write the reg
 * Parameters     : void
 * Returns        : reg value
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/
uint8_t GET_WRITE_REGISTER(uint8_t reg)
{
    return READ_REGISTER1(&reg);
}

/*******************************************************************************
 * Function name  : init_sensor
 *
 * Description    : init sensor and capture data calling in this function
 * Parameters     : void
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/

fsp_err_t init_sensor(void)
{
    uint8_t device_id = RESET_VALUE;
    fsp_err_t err     = FSP_SUCCESS;
    err = R_IIC_MASTER_Open(&g_i2c_master_ctrl, &g_i2c_master_cfg);

    /* handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Open API failed ** \r\n");
        return err;
    }

    /* Get device ID as a start of communication */
    err = get_device_id (&device_id);

//    uint8_t FLUSH[MEASURE_PAYLOAD_SIZE] = {0X0D, 0X04};
    if (err == FSP_SUCCESS)
    {
        err = soft_rest();
        if(err == FSP_SUCCESS)
        {
            err = set_up();
            if(err == FSP_SUCCESS)
            {
                err = enableDATAREADY();
                if(err == FSP_SUCCESS)
                {
                    if(err == FSP_SUCCESS)
                    {
                        err = ppg_data_capture();
                        err = WRITE_REGISTER1(0X0D,0X01);
                        err = WRITE_REGISTER1(0X0D,0X06);

                    }
                }
            }

        }

    }
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT("** Get device id failed ** \r\n");
        return err;
    }
    return err;
}

/*******************************************************************************
 * Function name  : READ_FIFO_DATA_REG
 *
 * Description    : reading fifo data from the max86150
 * Parameters     : void
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/


fsp_err_t READ_FIFO_DATA_REG(void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t reg = 0x07;

    /* Write  Data register   */
    err = R_IIC_MASTER_Write (&g_i2c_master_ctrl, &reg, ONE_BYTE, true);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Write API failed ** \r\n");
        return err;
    }
    else
    {
        err = validate_i2c_event ();
        /* Performs read operation only when write event is successful, failure part is handled at next stage*/
        if (FSP_SUCCESS == err)
        {
            err = R_IIC_MASTER_Read (&g_i2c_master_ctrl, write_ptr_data_1, 0b00000110, false);
            /* handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("** R_IIC_MASTER_Read API failed ** \r\n");
                return err;
            }
            else
            {
                err = validate_i2c_event ();

                if (FSP_SUCCESS != err)
                {
                    APP_ERR_PRINT("** Data register, I2C read failed ** \r\n");
                    return err;
                }

            }

        }
        else
        {
            APP_ERR_PRINT("** ppg Data register, I2C write failed ** \r\n");
            return err;
        }

    }

    return err;
}


/*******************************************************************************
 * Function name  : deinit_sensor
 *
 * Description    : closing i2c function
 * Parameters     : void
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/
void deinit_sensor(void)
{
    fsp_err_t err     = FSP_SUCCESS;

    /* close open modules */
    err =  R_IIC_MASTER_Close (&g_i2c_master_ctrl);

    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Close API failed ** \r\n");
    }
}


/*******************************************************************************
 * Function name  : get_device_id
 *
 * Description    : dev_id access using this function
 * Parameters     : dev_id
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/
static fsp_err_t get_device_id(uint8_t *dev_id)
{
    fsp_err_t err         = FSP_SUCCESS;
    uint8_t reg_address   = DEVICE_ID_REG;

    /* Parameter checking */
    if (NULL == dev_id)
    {
        err = FSP_ERR_INVALID_POINTER;
        APP_ERR_PRINT("** NULL Pointer check fail ** \r\n");
        return err;
    }



    /* Send register address to sensor */
    err = R_IIC_MASTER_Write(&g_i2c_master_ctrl, &reg_address, ONE_BYTE, true);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Write API failed ** \r\n");
    }
    else
    {
        err = validate_i2c_event();
        /* handle error */
        if(FSP_ERR_TRANSFER_ABORTED == err)
        {
            APP_ERR_PRINT("** Device ID reg, I2C write failed ** \r\n");
        }
        else
        {
            /* Read only when I2C write and its callback event is successful */
            err  = R_IIC_MASTER_Read(&g_i2c_master_ctrl, dev_id, ONE_BYTE, false);
            /* handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("** R_IIC_MASTER_Read API failed ** \r\n");
                //  Do nothing, the error is returned in the end
            }
            else
            {
                err = validate_i2c_event();
                /* handle error */
                if(FSP_ERR_TRANSFER_ABORTED == err)
                {
                    APP_ERR_PRINT("** Device ID read,  I2C read failed ** \r\n");
                }
            }
        }
    }
    /* On successful I2C transaction with PMOD-ACL return from here */
    return err;
}

/*******************************************************************************
 * Function name  : i2c_master_callback
 *
 * Description    : dev_id access using this function
 * Parameters     : p_args
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/
void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        i2c_event = p_args->event;
    }
}


/*******************************************************************************
 * Function name  : i2c_master_callback
 *
 * Description    : Validate i2c receive/transmit  based on required write read operation
 * Parameters     : void
 * Returns        : error
 *
 * Known Issues   :
 * Note           :
 * author         : Rahul
 * date           : 20OCT2024
 ******************************************************************************/
static fsp_err_t validate_i2c_event(void)
{
    uint16_t local_time_out = UINT16_MAX;

    /* resetting call back event capture variable */
    i2c_event = (i2c_master_event_t)RESET_VALUE;

    do
    {
        /* This is to avoid infinite loop */
        --local_time_out;

        if(RESET_VALUE == local_time_out)
        {
            return FSP_ERR_TRANSFER_ABORTED;
        }

    }while(i2c_event == RESET_VALUE);

    if(i2c_event != I2C_MASTER_EVENT_ABORTED)
    {
        i2c_event = (i2c_master_event_t)RESET_VALUE;  // Make sure this is always Reset before return
        return FSP_SUCCESS;
    }

    i2c_event = (i2c_master_event_t)RESET_VALUE; // Make sure this is always Reset before return
    return FSP_ERR_TRANSFER_ABORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_iic_master_ep)
 **********************************************************************************************************************/
