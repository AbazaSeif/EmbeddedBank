/*============================================================================
 *
 *      hal_sys.h
 *
 *      
 *
 *==========================================================================*/
/*============================================================================
 * 
 * Copyright (c) 2002-2006 Innova Card.
 * All Rights Reserved.
 *
 * This software is the confidential and proprietary information of
 * Innova Card ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with Innova Card.
 *
 * Innova Card makes no representations or warranties about the suitability of 
 * the software, either express or implied, including but not limited to 
 * the implied warranties of merchantability, fitness for a particular purpose, 
 * or non-infrigement. Innova Card shall not be liable for any damages suffered 
 * by licensee as the result of using, modifying or distributing this software 
 * or its derivatives.
 * 
 *==========================================================================*/
/*============================================================================
 * 
 * Author(s):     Arnaud Corria 
 * Contributors:  Arnaud Ferir
 * Date:          
 * Purpose:       
 * Description:   
 * 
 *==========================================================================*/
#ifndef HAL_USIP_SYS_H
#define HAL_USIP_SYS_H
   
#define SYSTAB_ENTRY(x) ((int)x)
#define SYSTAB_MAGIC    0xDEADBEEF   
#define SYSTAB_COUNT    ( sizeof(sys_table_vectors) / sizeof(int) )
 
typedef struct {
    unsigned int magic;
    unsigned int version_major;
    unsigned int version_minor;
    unsigned int handlers_count;
} sys_table_header_t;

typedef struct {
    unsigned int magic;
    unsigned int ckecksum;
} sys_table_trailer_t;

extern sys_table_header_t const sys_table_hal_header;   
extern sys_table_trailer_t const sys_table_hal_trailer;   
extern int const sys_table_hal_vectors[]; 

extern sys_table_header_t const sys_table_libemv_header;
extern sys_table_trailer_t const sys_table_libemv_trailer;
extern int const sys_table_libemv_vectors[]; 

typedef struct
{
    /* Header */
    int hd_magic;
    int hd_version_major;
    int hd_version_minor;
    int hd_count;
    
    /* Vectors */
    int hal_sys_get_version;
    int hal_sys_get_serial_number;
    int hal_sys_end_of_life;
    int hal_sys_init;
    
    /* ADC interface */
    int hal_adc_init; 
    int hal_adc_shutdown;
    int hal_adc_set_config;
    int hal_adc_get_status;
    int hal_adc_ioctl;
    int hal_adc_read;
    int hal_adc_attach;
    int hal_adc_detach;
    int hal_adc_rfu_1;
    
    /* APM Interface */
    int hal_apm_set_cpu_mode_ultra_low_power; 
    int hal_apm_set_cpu_mode_normal;
    int hal_apm_set_cpu_mode_idle;
    int hal_apm_get_cpu_mode;
    int hal_apm_reset_device;
    int hal_apm_set_device_mode;
    int hal_apm_get_device_mode;
    int hal_apm_set_clock_frequency;
    int hal_apm_get_clock_frequency;
    int hal_apm_ioctl;
    int hal_apm_init;
    int hal_apm_shutdown;
    int hal_apm_attach;
    int hal_apm_detach;
    
    /* Crypto Interface */
    int hal_crypto_init;
    int hal_crypto_shutdown;
    int hal_crypto_set_key;
    int hal_crypto_decrypt;
    int hal_crypto_encrypt;
    int hal_crypto_rfu_1;
    int hal_crypto_rfu_2; 
    
    /* Display Interface */
    int hal_display_init;
    int hal_display_shutdown;
    int hal_display_get_status;
    int hal_display_set_config;
    int hal_display_write;
    int hal_display_read;
    int hal_display_ioctl;
    int hal_display_attach;
    int hal_display_detach;
    int hal_display_rfu_1;
    int hal_display_rfu_2; 
    
    /* DMA Interface */
    int hal_dma_init;
    int hal_dma_shutdown;
    int hal_dma_set_config;
    int hal_dma_get_status;
    int hal_dma_ioctl;
    int hal_dma_attach;
    int hal_dma_detach;
    int hal_dma_rfu_1;
    int hal_dma_rfu_2; 
    
    /* Flash Interface */
    int hal_flash_get_info;
    int hal_flash_get_status;
    int hal_flash_erase;
    int hal_flash_write;
    int hal_flash_read;
    int hal_flash_lock;
    int hal_flash_sign128;
    int hal_flash_sign16;
    int hal_flash_otp_write;
    int hal_flash_otp_read;
    int hal_flash_suspend;
    int hal_flash_resume;
    int hal_flash_erase_sectors;
    int hal_flash_attach;
    int hal_flash_detach;
    int hal_flash_rfu_1;
    int hal_flash_rfu_2;
    int hal_flash_rfu_3;
    int hal_flash_otp_erase; 
    
    /* GPIO Interface */
    int hal_gpio_init;
    int hal_gpio_shutdown;
    int hal_gpio_set_config;
    int hal_gpio_ioctl;
    int hal_gpio_attach;
    int hal_gpio_detach;
    int hal_gpio_read;
    int hal_gpio_write;
    int hal_gpio_rfu_1;
    int hal_gpio_rfu_2; 
    
    /* I2C Interface */
    int hal_i2c_init;
    int hal_i2c_shutdown;
    int hal_i2c_set_config;
    int hal_i2c_ioctl;
    int hal_i2c_attach;
    int hal_i2c_detach;
    int hal_i2c_get_status;
    int hal_i2c_start_write;
    int hal_i2c_write;
    int hal_i2c_start_read;
    int hal_i2c_read;
    int hal_i2c_stop_read;
    int hal_i2c_rfu_1;
    int hal_i2c_rfu_2;
    
    /* Interrupt Controller */
    int hal_interrupt_mask;
    int hal_interrupt_unmask;
    int hal_interrupt_attach;
    int hal_interrupt_detach;
    int hal_interrupt_get_isr;
    int hal_interrupt_set_config;
    int hal_interrupt_decode;
    int hal_interrupt_rfu_1;
    
    /* Keyboard Interface */
    int hal_keyboard_init;
    int hal_keyboard_shutdown;
    int hal_keyboard_get_status;
    int hal_keyboard_set_config;
    int hal_keyboard_read;
    int hal_keyboard_write;
    int hal_keyboard_attach;
    int hal_keyboard_detach;
    int hal_keyboard_ioctl;
    int hal_keyboard_rfu_1;
    int hal_keyboard_rfu_2;
    int hal_keyboard_rfu_3;
    int hal_keyboard_rfu_4;
    
    /* External Memory Controller */
    int hal_memc_set_key;
    int hal_memc_init;
    int hal_memc_shutdown;
    int hal_memc_get_status;
    int hal_memc_set_config;
    int hal_memc_ioctl;
    int hal_memc_attach;
    int hal_memc_detach;
    int hal_memc_rfu_1;
    int hal_memc_rfu_2; 

    /* MSR system calls */
    int hal_msr_init;
    int hal_msr_shutdown;
    int hal_msr_read;
    int hal_msr_get_status;
    int hal_msr_attach;
    int hal_msr_detach;
    int hal_msr_rfu_1;
    int hal_msr_rfu_2;
    int hal_msr_rfu_3;
    int hal_msr_rfu_4; 
    
    /* Parallel Interface */
    int hal_parallel_init;
    int hal_parallel_shutdown;
    int hal_parallel_set_config;
    int hal_parallel_ioctl;
    int hal_parallel_attach;
    int hal_parallel_detach;
    int hal_parallel_get_status;
    int hal_parallel_read;
    int hal_parallel_write;
    int hal_parallel_rfu_1;
    int hal_parallel_rfu_2; 
    
    /* Thermal Printer Interface */
    int hal_printer_init;
    int hal_printer_shutdown;
    int hal_printer_get_status;
    int hal_printer_set_config;
    int hal_printer_ioctl;
    int hal_printer_head_write;
    int hal_printer_motor_write;
    int hal_printer_motor_step;
    int hal_printer_motor_get_position;
    int hal_printer_motor_set_position;
    int hal_printer_attach;
    int hal_printer_detach;
    int hal_printer_rfu_1;
    int hal_printer_rfu_2; 
    
    /* PS2 interface */
    int hal_ps2_init;
    int hal_ps2_shutdown;
    int hal_ps2_set_config;
    int hal_ps2_attach;
    int hal_ps2_detach;
    int hal_ps2_get_status;
    int hal_ps2_read;
    int hal_ps2_write;
    int hal_ps2_rfu_1;
    int hal_ps2_rfu_2; 
    
    /* PWM Interface */
    int hal_pwm_init;
    int hal_pwm_shutdown;
    int hal_pwm_set_config;
    int hal_pwm_run;
    int hal_pwm_stop;
    int hal_pwm_get_status;
    int hal_pwm_attach;
    int hal_pwm_detach;
    int hal_pwm_rfu_1;
    int hal_pwm_rfu_2; 
    
    /* RNG Interface */
    int hal_rng_init;
    int hal_rng_shutdown;
    int hal_rng_get_status;
    int hal_rng_read;
    int hal_rng_read128;
    int hal_rng_attach;
    int hal_rng_detach;
    int hal_rng_rfu_1;
    int hal_rng_rfu_2;
    
    /* RTC Interface */
    int hal_rtc_init;
    int hal_rtc_get_time;
    int hal_rtc_set_time;
    int hal_rtc_set_alarm;
    int hal_rtc_get_status;
    int hal_rtc_ioctl;
    int hal_rtc_attach;
    int hal_rtc_detach;
    int hal_rtc_rfu_1;
    int hal_rtc_rfu_2;    
    
    /* Smart Card Slot Interface */
    int hal_scs_init;
    int hal_scs_shutdown;
    int hal_scs_get_status;
    int hal_scs_set_config;
    int hal_scs_power_up;
    int hal_scs_power_down;
    int hal_scs_t0_in;
    int hal_scs_t0_out;
    int hal_scs_t1_block;
    int hal_scs_pps_exchange; 
    int hal_scs_ioctl;                   
    int hal_scs_attach;
    int hal_scs_detach;
    int hal_scs_get_slot_info;
    int hal_scs_set_slot_info;
    int hal_scs_get_last_error;
    int hal_scs_cancel;
    int hal_scs_rfu_1;
    int hal_scs_rfu_2;
    int hal_scs_rfu_3;
    int hal_scs_rfu_4;
    
    /* Sensors */
    int hal_sensor_set_config;
    int hal_sensor_ioctl;
    int hal_sensor_get_status;
    int hal_sensor_rfu_1;
    int hal_sensor_rfu_2;
    
    /* Security Storage Memory */
    int hal_storage_read;
    int hal_storage_write;
    int hal_storage_rfu_1;
    int hal_storage_rfu_2;
    
    /* SPI Interface */
    int hal_spi_init;
    int hal_spi_shutdown;
    int hal_spi_set_config;
    int hal_spi_ioctl;
    int hal_spi_attach;
    int hal_spi_detach;
    int hal_spi_get_status;
    int hal_spi_write;
    int hal_spi_read;
    int hal_spi_rfu_1;
    int hal_spi_rfu_2;
    int hal_spi_rfu_3;
    int hal_spi_rfu_4;
    
    /* Timer Interface */
    int hal_timer_init;
    int hal_timer_shutdown;
    int hal_timer_run;
    int hal_timer_stop;
    int hal_timer_set_config;
    int hal_timer_get_status;
    int hal_timer_read;
    int hal_timer_ioctl; 
    int hal_timer_attach;
    int hal_timer_detach;
    int hal_timer_rfu_1;
    int hal_timer_rfu_2;
    
    /* UART Interface */
    int hal_uart_init; 
    int hal_uart_shutdown;
    int hal_uart_set_config;
    int hal_uart_get_status;
    int hal_uart_write;
    int hal_uart_read;
    int hal_uart_attach;
    int hal_uart_detach;
    int hal_uart_ioctl;
    int hal_uart_rfu_1;
    int hal_uart_rfu_2;
    int hal_uart_rfu_3;
    int hal_uart_rfu_4;
    
    /* USB Interface */
    int hal_usb_ioctl;
    int hal_usb_otg_init;
    int hal_usb_otg_shutdown;
    int hal_usb_otg_set_status;
    int hal_usb_otg_get_status;
    int hal_usb_device_init;
    int hal_usb_device_shutdown;
    int hal_usb_device_recv_data;
    int hal_usb_device_send_data; 
    int hal_usb_device_cancel_transfer;
    int hal_usb_device_attach;
    int hal_usb_device_detach;
    int hal_usb_device_init_endpoint; 
    int hal_usb_device_deinit_endpoint;
    int hal_usb_device_stall_endpoint;
    int hal_usb_device_unstall_endpoint; 
    int hal_usb_device_assert_resume; 
    int hal_usb_device_get_transfer_status;
    int hal_usb_device_get_status; 
    int hal_usb_device_set_status; 
    int hal_usb_rfu_1;
    int hal_usb_host_init;
    int hal_usb_host_bus_control;
    int hal_usb_host_cancel_transfer;  
    int hal_usb_host_close_pipe;
    int hal_usb_host_close_all_pipes;
    int hal_usb_host_attach;
    int hal_usb_host_detach;
    int hal_usb_host_open_pipe;
    int hal_usb_host_send_setup;
    int hal_usb_host_get_transfer_status;
    int hal_usb_host_shutdown;
    int hal_usb_host_recv_data;
    int hal_usb_host_send_data;
    int hal_usb_host_driver_info_register;
    int hal_usb_hostdev_find_pipe_handle;
    int hal_usb_hostdev_get_buffer;
    int hal_usb_hostdev_get_descriptor;
    int hal_usb_hostdev_select_config;
    int hal_usb_hostdev_select_interface;
    int hal_usb_host_ch9_get_status;
    int hal_usb_host_ch9_clear_feature;
    int hal_usb_host_ch9_set_feature;
    int hal_usb_host_ch9_set_address;
    int hal_usb_host_ch9_get_descriptor;
    int hal_usb_host_ch9_set_descriptor;
    int hal_usb_host_ch9_get_configuration;
    int hal_usb_host_ch9_set_configuration;
    int hal_usb_host_ch9_get_interface;
    int hal_usb_host_ch9_set_interface;
    int hal_usb_host_ch9_synch_frame;
    int hal_usb_host_register_ch9_callback;
    int hal_usb_hostdev_cntrl_request;
    int hal_usb_rfu_2;
    int hal_usb_rfu_3;
    int hal_usb_rfu_4;
    int hal_usb_rfu_5;

    int hal_tlb_write;
    int hal_tlb_write2;
    int hal_cache_enable;
    int hal_cache_disable;
    
    /* Watchdog Timer Interface */
    int hal_watchdog_init;
    int hal_watchdog_shutdown;
    int hal_watchdog_set_config;
    int hal_watchdog_rearm;
    int hal_watchdog_disarm;
    int hal_watchdog_read;
    int hal_watchdog_get_status;
    int hal_watchdog_attach;
    int hal_watchdog_detach;
    int hal_watchdog_rfu_1;
    int hal_watchdog_rfu_2;
    
    int tr_magic;
    int tr_ckecksum;
          
} hal_sys_table_entry_t;
 
typedef struct
{
    /* Header */
    int hd_magic;
    int hd_version_major;
    int hd_version_minor;
    int hd_count;
    
    int emv_init;
    int emv_shutdown;  
    int emv_get_status;
    int emv_set_config;
    int emv_power_up;
    int emv_power_down;
    int emv_transmit;
    int emv_attach;
    int emv_detach;
    int emv_cancel;
    int emv_get_last_error;

    int emv_get_slot_info;
    int emv_set_slot_info;
    int emv_rfu_1;
    int emv_rfu_2;
    int emv_rfu_3;
    int emv_rfu_4;
    int emv_rfu_5;
    int emv_rfu_6;
    
    int tr_magic;
    int tr_ckecksum;
    
}   emv_sys_table_entry_t;

typedef struct 
{
    int hal_uart_isr0;
    int hal_uart_isr1;
    int hal_spi_isr;
    int hal_dma_isr;
    int hal_keyboard_isr;
    int hal_display_isr;
    int hal_timer_isr;
    int hal_memc_isr;
    int hal_printer_isr;
    int hal_rtc_isr;
    int hal_scs_isr0;
    int hal_scs_isr1;
    int hal_scs_isr2;
    int hal_gpio_isr;
    int hal_nmi_isr;
    int hal_i2c_isr;
    int hal_core_timer_isr;
    int hal_bus_error_isr;
    int hal_apm_isr;
    int hal_usb_isr;
    int hal_ps2_h_isr;
    int hal_parallel_isr;
    int hal_uart_isr2;
    int hal_uart_isr3;
    int hal_msr_isr;
    int hal_flash_isr;
    int hal_rng_isr;
    int hal_ext_intr_isr;
    int hal_adc_isr;    
          
}   hal_sys_isr_entry_t;

#ifndef CONFIG_LIBROM_NOT_INLINED

#include <stddef.h> /* for offsetof() definition */

/* EMV Vector table address */
#define EMV_SYS_TABLE_BASE_LMA          0x8103f800
#define EMV_SYS_TABLE_BASE_VMA          0x8001f300

/* HAL Vector table address */
#define HAL_SYS_TABLE_BASE_LMA          0x8103f864 
#define HAL_SYS_TABLE_BASE_VMA          0x8001f364

/* ISR Vector table address */
#define HAL_ISR_TABLE_BASE              0xa001f910


/* HAL Vector table offsets */

#define __hal_get_syscall_num(_x_)     offsetof(hal_sys_table_entry_t, _x_)

#define hal_sys_get_entry(_x_)                                             \
    (HAL_SYS_TABLE_BASE_VMA + __hal_get_syscall_num(_x_))

#define hal_sys_get_magic()                                                \
        ((unsigned int)hal_sys_get_entry(hd_magic))

#define hal_sys_get_version_maj()                                          \
        ((unsigned int)hal_sys_get_entry(hd_version_major))

#define hal_sys_get_version_min()                                          \
        ((unsigned int)hal_sys_get_entry(hd_version_minor))

#define hal_sys_get_count()                                                \
        ((unsigned int)hal_sys_get_entry(hd_count))

#define hal_sys_get_checksum()                                             \
        ((unsigned int)hal_sys_get_entry(tr_checksum))


/* EMV Vector table offsets */

#define __emv_get_syscall_num(_x_)     offsetof(emv_sys_table_entry_t, _x_)

#define emv_sys_get_entry(_x_)                                             \
    (EMV_SYS_TABLE_BASE_VMA + __emv_get_syscall_num(_x_))

#define emv_sys_get_magic()                                                \
        ((unsigned int)emv_sys_get_entry(hd_magic))

#define emv_sys_get_version_maj()                                          \
        ((unsigned int)emv_sys_get_entry(hd_version_major))

#define emv_sys_get_version_min()                                          \
        ((unsigned int)emv_sys_get_entry(hd_version_minor))

#define emv_sys_get_count()                                                \
        ((unsigned int)emv_sys_get_entry(hd_count))

#define emv_sys_get_checksum()                                             \
        ((unsigned int)emv_sys_get_entry(tr_checksum))
      


            
#define __hal_defunc0(_x_, _void_)                                   \
    typedef int (* _x_##_t)(void);                                         \
    static inline __attribute__((always_inline)) int _x_( void )           \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) hal_sys_get_entry(_x_));                     \
        return _x_##_();                                                   \
    }

#define __hal_defunc1(_x_, _t0_, _a0_)                               \
    typedef int (* _x_##_t)(_t0_ _a0_);                                    \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_ )      \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) hal_sys_get_entry(_x_));                     \
        return _x_##_(_a0_);                                               \
    }

#define __hal_defunc2(_x_, _t0_, _a0_ , _t1_, _a1_)                  \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_);                         \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) hal_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_);                                         \
    }
                
#define __hal_defunc3(_x_, _t0_, _a0_ , _t1_, _a1_, _t2_, _a2_)      \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_ , _t2_ _a2_);             \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_, _t2_ _a2_) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) hal_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_, _a2_);                                   \
    }

#define __hal_defunc4(_x_, _t0_, _a0_ , _t1_, _a1_, _t2_, _a2_, _t3_, _a3_)  \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_ , _t2_ _a2_, _t3_ _a3_);  \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_, _t2_ _a2_, _t3_ _a3_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) hal_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_, _a2_, _a3_);                             \
    }
    
#define __hal_defunc5(_x_, _t0_, _a0_ , _t1_, _a1_, _t2_, _a2_, _t3_, _a3_, _t4_, _a4_)  \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_ , _t2_ _a2_, _t3_ _a3_, _t4_ _a4_); \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_, _t2_ _a2_, _t3_ _a3_, _t4_ _a4_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) hal_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_, _a2_, _a3_, _a4_);                       \
    }
  
#define __hal_defunc7(_x_, _t0_, _a0_ , _t1_, _a1_, _t2_, _a2_, _t3_, _a3_, _t4_, _a4_, _t5_, _a5_, _t6_, _a6_)  \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_ , _t2_ _a2_, _t3_ _a3_, _t4_ _a4_, _t5_ _a5_, _t6_ _a6_); \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_, _t2_ _a2_, _t3_ _a3_, _t4_ _a4_, _t5_ _a5_, _t6_ _a6_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) hal_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_, _a2_, _a3_, _a4_, _a5_, _a6_);           \
    }
    
#define __hal_deisr(_x_, _void_)                                       \
    typedef int (* _x_##_t)(void);                                         \
    static inline __attribute__((always_inline)) int _x_( void )           \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*)(HAL_ISR_TABLE_BASE                           \
                          + offsetof(hal_sys_isr_entry_t, _x_)));          \
        return _x_##_();                                                   \
    }
     
#define __emv_defunc0(_x_, _void_)                                         \
    typedef int (* _x_##_t)(void);                                         \
    static inline __attribute__((always_inline)) int _x_( void )           \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) emv_sys_get_entry(_x_));                     \
        return _x_##_();                                                   \
    }

#define __emv_defunc1(_x_, _t0_, _a0_)                                     \
    typedef int (* _x_##_t)(_t0_ _a0_);                                    \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_ )      \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) emv_sys_get_entry(_x_));                     \
        return _x_##_(_a0_);                                               \
    }

#define __emv_defunc2(_x_, _t0_, _a0_ , _t1_, _a1_)                        \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_);                         \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) emv_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_);                                         \
    }
                
#define __emv_defunc3(_x_, _t0_, _a0_ , _t1_, _a1_, _t2_, _a2_)      \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_ , _t2_ _a2_);             \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_, _t2_ _a2_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) emv_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_, _a2_);                                   \
    }

#define __emv_defunc4(_x_, _t0_, _a0_ , _t1_, _a1_, _t2_, _a2_, _t3_, _a3_)  \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_ , _t2_ _a2_, _t3_ _a3_);  \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_, _t2_ _a2_, _t3_ _a3_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) emv_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_, _a2_, _a3_);                             \
    }
    
#define __emv_defunc5(_x_, _t0_, _a0_ , _t1_, _a1_, _t2_, _a2_, _t3_, _a3_, _t4_, _a4_)  \
    typedef int (* _x_##_t)(_t0_ _a0_, _t1_ _a1_ , _t2_ _a2_, _t3_ _a3_, _t4_ _a4_); \
    static inline __attribute__((always_inline)) int _x_( _t0_ _a0_, _t1_ _a1_, _t2_ _a2_, _t3_ _a3_, _t4_ _a4_ ) \
    {                                                                      \
        register _x_##_t _x_##_;                                           \
        _x_##_ = (*(_x_##_t*) emv_sys_get_entry(_x_));                     \
        return _x_##_(_a0_, _a1_, _a2_, _a3_, _a4_);                       \
    }
     
#endif
  
  
/** @defgroup HAL_SYSTEM HAL SYSTEM 
 *
 * @{ 
 */
 
/** 
 * This structure is used to retreive the version of a software component.
 * A version is coded in two parts : the major and the minor version.
 */ 
typedef struct {
    int major;
    int minor; 
} version_t;

/** 
 * This structure is used to retreive the version of the chip, the Secure 
 * Flash Loader ansd the HAL library 
 */
typedef struct {
    version_t usip; 
    version_t loader;
    version_t libhal;
} hal_sys_version_t;

#define HAL_SYS_MAGIC_END_OF_LIFE   0xDEADBEEF

#ifdef CONFIG_LIBROM_NOT_INLINED

/** 
 * The function initializes the memory allocator. 
 * It must be call prior to any call to the hal_sys_alloc() function.
 */   
int hal_sys_pool_init( void );

/** 
 * The function shutdowns the memory allocator. 
 */ 
int hal_sys_pool_shutdown( void );

/** 
 * The function is used to reconfigure the memory pool base and size. 
 */
int hal_sys_pool_config( int *base, unsigned int size );

/**
 * The function allocates a memory block of at least size bytes. 
 * The block may be larger than size bytes because of space required for 
 * alignment. 
 * 
 * @param[in] size      Bytes to allocate
 * 
 * @retval NULL     There is insufficient memory available.
 * @retval Other    A void pointer to the allocated space, 
 * 
 */
void *hal_sys_alloc( unsigned int size );


/**
 * The function deallocates a memory block previously allocated with 
 * the hal_sys_alloc() function.
 * 
 * @param[in] p         Previously allocated memory block to be freed.
 * 
 * @retval -ERR_NO      No error  
 * 
 */
int hal_sys_free( void *p );

/** 
 * The function updates the Chip Life Cycle to the End Of Life phase. 
 * In this phase, USIP is not longer useable, excepted for retrieving 
 * the Unique serial Number, the Life Cycle and the different versions 
 * (see #hal_sys_get_version()) through the Secure Flash Loader. 
 * A magic number is used as parameter to prevent a wrong manipulation.
 * 
 * @param[in] magic    The magic number.
 * 
 * @retval -ERR_NO      No error  
 * @retval -ERR_INVAL   Invalid parameter 
 * @retval Other        See \link Error_Codes Error Codes \endlink
 * 
 */
int hal_sys_end_of_life( unsigned int magic );

/** 
 * The function is used to retreive the component, the secure flash loader and 
 * the HAL library versions. 
 * A version is coded in two parts : the major version and the minor version. 
 * 
 * @param[out]   version    Pointer to an initialized structure.
 * 
 * @retval -ERR_NO      No error  
 * @retval -ERR_INVAL   Invalid parameter 
 * @retval Other        See \link Error_Codes Error Codes \endlink
 * 
 */
int hal_sys_get_version( hal_sys_version_t *version );

/** 
 * The function is used to retreive the Unique Serial Number of the component.
 * 
 * @param[out]  serial_number    Valid pointer to a 16-byte array .
 * 
 * @retval -ERR_NO      No error 
 * @retval -ERR_INVAL   Invalid parameter 
 * @retval Other        See \link Error_Codes Error Codes \endlink
 * 
 */
int hal_sys_get_serial_number( unsigned char *serial_number );

/** 
 * The function is provided for debug purpose to initialize the HAL internal 
 * state machine and to set the indirection table. 
 * 
 * @retval -ERR_NO      No error  
 * @retval Other        See \link Error_Codes Error Codes \endlink
 * 
 */
int hal_sys_init( void );

#else

__hal_defunc1(hal_sys_end_of_life, unsigned int, magic);
__hal_defunc1(hal_sys_get_version, hal_sys_version_t *, version);
__hal_defunc1(hal_sys_get_serial_number, unsigned char *, serial_number);
__hal_defunc0(hal_sys_init, void);

#endif
 
/**  @} */


 
/*--------------------------------------------------------------------------*/
#endif /* HAL_USIP_SYS_H */

