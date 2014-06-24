#include <platform/mt_typedefs.h>
#include <platform/mt_reg_base.h>
#include <platform/mt_i2c.h>     
#include <platform/bq24156.h>
#include <printf.h>

int g_bq24156_log_en=0;

/**********************************************************
  *
  *   [I2C Slave Setting] 
  *
  *********************************************************/
#define bq24156_SLAVE_ADDR_WRITE 0xD4 /* p.2, 7-bit 0x6A*/
#define bq24156_SLAVE_ADDR_READ 0xD5

/**********************************************************
  *
  *   [Global Variable] 
  *
  *********************************************************/
#define bq24156_REG_NUM 7  /* p.28~30, memory location: 00~06 */
kal_uint8 bq24156_reg[bq24156_REG_NUM] = {0};

/**********************************************************
  *
  *   [I2C Function For Read/Write bq24156] 
  *
  *********************************************************/
U32 bq24156_i2c_read (U8 chip, U8 *cmdBuffer, int cmdBufferLen, U8 *dataBuffer, int dataBufferLen)
{
    U32 ret_code = I2C_OK;

    ret_code = mt_i2c_write(I2C4, chip, cmdBuffer, cmdBufferLen,1);    // set register command
    if (ret_code != I2C_OK)
        return ret_code;

    ret_code = mt_i2c_read(I2C4, chip, dataBuffer, dataBufferLen,1);

    //printf("[bq24156_i2c_read] Done\n");

    return ret_code;
}

U32 bq24156_i2c_write (U8 chip, U8 *cmdBuffer, int cmdBufferLen, U8 *dataBuffer, int dataBufferLen)
{
    U32 ret_code = I2C_OK;
    U8 write_data[I2C_FIFO_SIZE];
    int transfer_len = cmdBufferLen + dataBufferLen;
    int i=0, cmdIndex=0, dataIndex=0;

    if(I2C_FIFO_SIZE < (cmdBufferLen + dataBufferLen))
    {
        printf("[bq24156_i2c_write] exceed I2C FIFO length!! \n");
        return 0;
    }

    //write_data[0] = cmd;
    //write_data[1] = writeData;

    while(cmdIndex < cmdBufferLen)
    {
        write_data[i] = cmdBuffer[cmdIndex];
        cmdIndex++;
        i++;
    }

    while(dataIndex < dataBufferLen)
    {
        write_data[i] = dataBuffer[dataIndex];
        dataIndex++;
        i++;
    }

    /* dump write_data for check */
    for( i=0 ; i < transfer_len ; i++ )
    {
        //printf("[bq24156_i2c_write] write_data[%d]=%x\n", i, write_data[i]);
    }

    ret_code = mt_i2c_write(I2C4, chip, write_data, transfer_len,1);

    //printf("[bq24156_i2c_write] Done\n");

    return ret_code;
}

/**********************************************************
  *
  *   [Read / Write Function] 
  *
  *********************************************************/
kal_uint32 bq24156_read_interface (kal_uint8 RegNum, kal_uint8 *val, kal_uint8 MASK, kal_uint8 SHIFT)
{
    U8 chip_slave_address = bq24156_SLAVE_ADDR_WRITE;
    U8 cmd = 0x0;
    int cmd_len = 1;
    U8 data = 0xFF;
    int data_len = 1;
    U32 result_tmp;

    printf("--------------------------------------------------\n");

    cmd = RegNum;
    result_tmp = bq24156_i2c_read(chip_slave_address, &cmd, cmd_len, &data, data_len);

    printf("[bq24156_read_interface] Reg[%x]=0x%x\n", RegNum, data);
    
    data &= (MASK << SHIFT);
    *val = (data >> SHIFT);
    
    printf("[bq24156_read_interface] val=0x%x\n", *val);

    if(g_bq24156_log_en>1)        
        printf("%d\n", result_tmp);

    return 1;
}

kal_uint32 bq24156_config_interface (kal_uint8 RegNum, kal_uint8 val, kal_uint8 MASK, kal_uint8 SHIFT)
{
    U8 chip_slave_address = bq24156_SLAVE_ADDR_WRITE;
    U8 cmd = 0x0;
    int cmd_len = 1;
    U8 data = 0xFF;
    int data_len = 1;
    U32 result_tmp;

    printf("--------------------------------------------------\n");

    cmd = RegNum;
    result_tmp = bq24156_i2c_read(chip_slave_address, &cmd, cmd_len, &data, data_len);
    printf("[bq24156_config_interface] Reg[%x]=0x%x\n", RegNum, data);

    data &= ~(MASK << SHIFT);
    data |= (val << SHIFT);

    result_tmp = bq24156_i2c_write(chip_slave_address, &cmd, cmd_len, &data, data_len);
    printf("[bq24156_config_interface] write Reg[%x]=0x%x\n", RegNum, data);

    // Check
    result_tmp = bq24156_i2c_read(chip_slave_address, &cmd, cmd_len, &data, data_len);
    printf("[bq24156_config_interface] Check Reg[%x]=0x%x\n", RegNum, data);

    if(g_bq24156_log_en>1)        
        printf("%d\n", result_tmp);
    
    return 1;
}

/**********************************************************
  *
  *   [Extern Function] 
  *
  *********************************************************/
//CON0----------------------------------------------------

void bq24156_set_tmr_rst(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON0), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON0_TMR_RST_MASK),
                                    (kal_uint8)(CON0_TMR_RST_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

kal_uint32 bq24156_get_slrst_status(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON0), 
                                    (&val),
                                    (kal_uint8)(CON0_SLRST_MASK),
                                    (kal_uint8)(CON0_SLRST_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
    
    return val;
}

void bq24156_set_en_stat(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON0), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON0_EN_STAT_MASK),
                                    (kal_uint8)(CON0_EN_STAT_SHIFT)
                                    );
    if(g_bq24156_log_en>1)
    {
        printf("%d\n", ret);
    }
}

kal_uint32 bq24156_get_chip_status(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON0), 
                                    (&val),
                                    (kal_uint8)(CON0_STAT_MASK),
                                    (kal_uint8)(CON0_STAT_SHIFT)
                                    );
    if(g_bq24156_log_en>1)
    {
        printf("%d\n", ret);
    }
    
    return val;
}

#if 0 /* NA for bq24156A, p.28 */
kal_uint32 bq24156_get_boost_status(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON0), 
                                    (&val),
                                    (kal_uint8)(CON0_BOOST_MASK),
                                    (kal_uint8)(CON0_BOOST_SHIFT)
                                    );
    if(g_bq24156_log_en>1)
    {
        printf("%d\n", ret);
    }
    
    return val;
}
#endif

kal_uint32 bq24156_get_fault_status(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON0), 
                                    (&val),
                                    (kal_uint8)(CON0_FAULT_MASK),
                                    (kal_uint8)(CON0_FAULT_SHIFT)
                                    );
    if(g_bq24156_log_en>1)
    {
        printf("%d\n", ret);
    }
    
    return val;
}

//CON1----------------------------------------------------

void bq24156_set_input_charging_current(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON1), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON1_LIN_LIMIT_MASK),
                                    (kal_uint8)(CON1_LIN_LIMIT_SHIFT)
                                    );
    if(g_bq24156_log_en>1)
    {
        printf("%d\n", ret);
    }
}

void bq24156_set_v_low(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON1), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON1_LOW_V_MASK),
                                    (kal_uint8)(CON1_LOW_V_SHIFT)
                                    );
    if(g_bq24156_log_en>1)
    {
        printf("%d\n", ret);
    }
}

void bq24156_set_te(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON1), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON1_TE_MASK),
                                    (kal_uint8)(CON1_TE_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

void bq24156_set_ce(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON1), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON1_CE_MASK),
                                    (kal_uint8)(CON1_CE_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

void bq24156_set_hz_mode(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON1), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON1_HZ_MODE_MASK),
                                    (kal_uint8)(CON1_HZ_MODE_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

#if 0 /* NA for bq24156A, p.28 */
void bq24156_set_opa_mode(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON1), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON1_OPA_MODE_MASK),
                                    (kal_uint8)(CON1_OPA_MODE_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}
#endif

//CON2----------------------------------------------------

void bq24156_set_oreg(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON2), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON2_OREG_MASK),
                                    (kal_uint8)(CON2_OREG_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

#if 0 /* NA for bq24156A, p.28 */
void bq24156_set_otg_pl(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON2), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON2_OTG_PL_MASK),
                                    (kal_uint8)(CON2_OTG_PL_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

void bq24156_set_otg_en(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON2), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON2_OTG_EN_MASK),
                                    (kal_uint8)(CON2_OTG_EN_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}
#endif

//CON3----------------------------------------------------

kal_uint32 bq24156_get_vender_code(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON3), 
                                    (&val),
                                    (kal_uint8)(CON3_VENDER_CODE_MASK),
                                    (kal_uint8)(CON3_VENDER_CODE_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
    
    return val;
}

/* 0x00: bq24156A, p.29 */
kal_uint32 bq24156_get_pn(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON3), 
                                    (&val),
                                    (kal_uint8)(CON3_PIN_MASK),
                                    (kal_uint8)(CON3_PIN_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
    
    return val;
}

kal_uint32 bq24156_get_revision(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON3), 
                                    (&val),
                                    (kal_uint8)(CON3_REVISION_MASK),
                                    (kal_uint8)(CON3_REVISION_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
    
    return val;
}

//CON4----------------------------------------------------

void bq24156_set_reset(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON4), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON4_RESET_MASK),
                                    (kal_uint8)(CON4_RESET_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);    
}

void bq24156_set_icharge(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON4), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON4_I_CHR_MASK),
                                    (kal_uint8)(CON4_I_CHR_SHIFT)
                                    );

    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }
}

kal_uint32 bq24156_get_icharge(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON4), 
                                    (&val),
                                    (kal_uint8)(CON4_I_CHR_MASK),
                                    (kal_uint8)(CON4_I_CHR_SHIFT)
                                    );
                                    
    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }
                                    
    return val;
}

void bq24156_set_iterm(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON4), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON4_I_TERM_MASK),
                                    (kal_uint8)(CON4_I_TERM_SHIFT)
                                    );
    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }
}

//CON5----------------------------------------------------

void bq24156_set_low_chg(kal_uint32 val)
{
    kal_uint32 ret=0;

    ret=bq24156_config_interface(     (kal_uint8)(bq24156_CON5), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON5_LOW_CHG_MASK),
                                    (kal_uint8)(CON5_LOW_CHG_SHIFT)
                                    );
                                    
    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }
                                    
    return val;
}

kal_uint32 bq24156_get_low_chg(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON5), 
                                    (&val),
                                    (kal_uint8)(CON5_LOW_CHG_MASK),
                                    (kal_uint8)(CON5_LOW_CHG_SHIFT)
                                    );
                                    
    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }
                                    
    return val;
}

kal_uint32 bq24156_get_dpm_status(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON5), 
                                    (&val),
                                    (kal_uint8)(CON5_DPM_STATUS_MASK),
                                    (kal_uint8)(CON5_DPM_STATUS_SHIFT)
                                    );
                                    
    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }
                                    
    return val;
}

kal_uint32 bq24156_get_cd_status(void)
{
    kal_uint32 ret=0;
    kal_uint8 val=0;

    ret=bq24156_read_interface(     (kal_uint8)(bq24156_CON5), 
                                    (&val),
                                    (kal_uint8)(CON5_CD_STATUS_MASK),
                                    (kal_uint8)(CON5_CD_STATUS_SHIFT)
                                    );
                                    
    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }
                                    
    return val;
}

void bq24156_set_vsreg(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON5), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON5_VSREG_MASK),
                                    (kal_uint8)(CON5_VSREG_SHIFT)
                                    );
                                    
    if(g_bq24156_log_en > 1)
    {
        printf("%d\n", ret);
    }    
}

//CON6----------------------------------------------------

void bq24156_set_i_safe(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON6), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON6_ISAFE_MASK),
                                    (kal_uint8)(CON6_ISAFE_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

void bq24156_set_v_safe(kal_uint32 val)
{
    kal_uint32 ret=0;    

    ret=bq24156_config_interface(   (kal_uint8)(bq24156_CON6), 
                                    (kal_uint8)(val),
                                    (kal_uint8)(CON6_VSAFE_MASK),
                                    (kal_uint8)(CON6_VSAFE_SHIFT)
                                    );
    if(g_bq24156_log_en>1)        
        printf("%d\n", ret);
}

/**********************************************************
  *
  *   [Internal Function] 
  *
  *********************************************************/
void bq24156_dump_register(void)
{
    U8 chip_slave_address = bq24156_SLAVE_ADDR_WRITE;
    U8 cmd = 0x0;
    int cmd_len = 1;
    U8 data = 0xFF;
    int data_len = 1;
    int i=0;
    for (i=0;i<bq24156_REG_NUM;i++)
    {
        cmd = i;
        bq24156_i2c_read(chip_slave_address, &cmd, cmd_len, &data, data_len);
        bq24156_reg[i] = data;
        printf("[bq24156_dump_register] Reg[0x%X]=0x%X\n", i, bq24156_reg[i]);
    }
}

void bq24156_hw_init(void)
{    
    /* do nothing, just for hook point reservation */
}

