/*=============================================================================
 *
 *	hal_sys.inc
 *
 *	MIPS assembler header file
 *
 * Purpose:	Indirection Table definitions.
 *
 * Description:	
 *		
 *
 *============================================================================*/
#ifndef __LIBROM_CONFIG_INC__
#define __LIBROM_CONFIG_INC__


#ifndef CONFIG_LIBROM_NOT_INLINED

    /* Header */
#define emv_hd_magic			0x000
#define emv_hd_version_major	0x004
#define emv_hd_version_minor	0x008
#define emv_hd_count			0x00c

#define emv_init					0x010
#define emv_shutdown			0x014
#define emv_get_status			0x018
#define emv_set_config				0x01c
#define emv_power_up				0x020
#define emv_power_down			0x024
#define emv_transmit				0x028
#define emv_attach					0x02c
#define emv_detach					0x030
#define emv_cancel					0x034
#define emv_get_last_error			0x038

#define emv_get_slot_info			0x03c
#define emv_set_slot_info			0x040
#define emv_rfu_1					0x044
#define emv_rfu_2					0x048
#define emv_rfu_3					0x04c
#define emv_rfu_4					0x050
#define emv_rfu_5					0x054
#define emv_rfu_6					0x058

    /* Trailer */
#define emv_tr_magic			0x05c
#define emv_tr_ckecksum			0x060



/* EMV Vector table address */
#define EMV_SYS_TABLE_BASE_LMA          0x8103f800
#define EMV_SYS_TABLE_BASE_VMA          0x8001f300

	.macro	emv_get_address reg,off
	la	\reg,EMV_SYS_TABLE_BASE_VMA
	lw	\reg,\off(\reg)
	.endm

#else

	.macro	emv_get_address reg,addr
    .extern \addr
    la     \reg,\addr
	.endm

#endif /* CONFIG_LIBROM_NOT_INLINED */



#ifndef CONFIG_LIBROM_NOT_INLINED

    /* Header */
#define hal_hd_magic			0x0
#define hal_hd_version_major	0x4
#define hal_hd_version_minor	0x8
#define hal_hd_count			0xc

    /* Vectors */
#define hal_sys_get_version				0x10
#define hal_sys_get_serial_number		0x14
#define hal_sys_end_of_life				0x18
#define hal_sys_init					0x1c

    /* ADC interface */
#define hal_adc_init					0x20
#define hal_adc_shutdown				0x24
#define hal_adc_set_config				0x28
#define hal_adc_get_status				0x2c
#define hal_adc_ioctl					0x30
#define hal_adc_read					0x34
#define hal_adc_attach					0x38
#define hal_adc_detach					0x3c
#define hal_adc_rfu_1					0x40

    /* APM Interface */
#define hal_apm_set_cpu_mode_ultra_low_power	0x44
#define hal_apm_set_cpu_mode_normal				0x48
#define hal_apm_set_cpu_mode_idle				0x4c
#define hal_apm_get_cpu_mode					0x50
#define hal_apm_reset_device					0x54
#define hal_apm_set_device_mode					0x58
#define hal_apm_get_device_mode					0x5c
#define hal_apm_set_clock_frequency				0x60
#define hal_apm_get_clock_frequency				0x64
#define hal_apm_ioctl							0x68
#define hal_apm_init							0x6c
#define hal_apm_shutdown						0x70
#define hal_apm_attach							0x74
#define hal_apm_detach							0x78

    /* Crypto Interface */
#define hal_crypto_init					0x7c
#define hal_crypto_shutdown				0x80
#define hal_crypto_set_key				0x84
#define hal_crypto_decrypt				0x88
#define hal_crypto_encrypt				0x8c
#define hal_crypto_rfu_1				0x90
#define hal_crypto_rfu_2				0x94

    /* Display Interface */
#define hal_display_init				0x98
#define hal_display_shutdown			0x9c
#define hal_display_get_status			0xa0
#define hal_display_set_config			0xa4
#define hal_display_write				0xa8
#define hal_display_read				0xac
#define hal_display_ioctl				0xb0
#define hal_display_attach				0xb4
#define hal_display_detach				0xb8
#define hal_display_rfu_1				0xbc
#define hal_display_rfu_2				0xc0

    /* DMA Interface */
#define hal_dma_init					0xc4
#define hal_dma_shutdown				0xc8
#define hal_dma_set_config				0xcc
#define hal_dma_get_status				0xd0
#define hal_dma_ioctl					0xd4
#define hal_dma_attach					0xd8
#define hal_dma_detach					0xdc
#define hal_dma_rfu_1					0xe0
#define hal_dma_rfu_2 					0xe4

    /* Flash Interface */
#define hal_flash_get_info				0xe8
#define hal_flash_get_status			0xec
#define hal_flash_erase					0xf0
#define hal_flash_write					0xf4
#define hal_flash_read					0xf8
#define hal_flash_lock					0xfc
#define hal_flash_sign128				0x100
#define hal_flash_sign16				0x104
#define hal_flash_otp_write				0x108
#define hal_flash_otp_read				0x10c
#define hal_flash_suspend				0x110
#define hal_flash_resume				0x114
#define hal_flash_erase_sectors			0x118
#define hal_flash_attach				0x11c
#define hal_flash_detach				0x120
#define hal_flash_rfu_1					0x124
#define hal_flash_rfu_2					0x128
#define hal_flash_rfu_3					0x12c
#define hal_flash_otp_erase				0x130

    /* GPIO Interface */
#define hal_gpio_init					0x134
#define hal_gpio_shutdown				0x138
#define hal_gpio_set_config				0x13c
#define hal_gpio_ioctl					0x140
#define hal_gpio_attach					0x144
#define hal_gpio_detach					0x148
#define hal_gpio_read					0x14c
#define hal_gpio_write					0x150
#define hal_gpio_rfu_1					0x154
#define hal_gpio_rfu_2 					0x158

    /* I2C Interface */
#define hal_i2c_init					0x15c
#define hal_i2c_shutdown				0x160
#define hal_i2c_set_config				0x164
#define hal_i2c_ioctl					0x168
#define hal_i2c_attach					0x16c
#define hal_i2c_detach					0x170
#define hal_i2c_get_status				0x174
#define hal_i2c_start_write				0x178
#define hal_i2c_write					0x17c
#define hal_i2c_start_read				0x180
#define hal_i2c_read					0x184
#define hal_i2c_stop_read				0x188
#define hal_i2c_rfu_1					0x18c
#define hal_i2c_rfu_2					0x190

    /* Interrupt Controller */
#define hal_interrupt_mask				0x194
#define hal_interrupt_unmask			0x198
#define hal_interrupt_attach			0x19c
#define hal_interrupt_detach			0x1a0
#define hal_interrupt_get_isr			0x1a4
#define hal_interrupt_set_config		0x1a8
#define hal_interrupt_decode			0x1ac
#define hal_interrupt_rfu_1				0x1b0

    /* Keyboard Interface */
#define hal_keyboard_init				0x1b4
#define hal_keyboard_shutdown			0x1b8
#define hal_keyboard_get_status			0x1bc
#define hal_keyboard_set_config			0x1c0
#define hal_keyboard_read				0x1c4
#define hal_keyboard_write				0x1c8
#define hal_keyboard_attach				0x1cc
#define hal_keyboard_detach				0x1d0
#define hal_keyboard_ioctl				0x1d4
#define hal_keyboard_rfu_1				0x1d8
#define hal_keyboard_rfu_2				0x1dc
#define hal_keyboard_rfu_3				0x1e0
#define hal_keyboard_rfu_4				0x1e4

    /* External Memory Controller */
#define hal_memc_set_key				0x1e8
#define hal_memc_init					0x1ec
#define hal_memc_shutdown				0x1f0
#define hal_memc_get_status				0x1f4
#define hal_memc_set_config				0x1f8
#define hal_memc_ioctl					0x1fc
#define hal_memc_attach					0x200
#define hal_memc_detach					0x204
#define hal_memc_rfu_1					0x208
#define hal_memc_rfu_2 					0x20c

    /* MSR system calls */
#define hal_msr_init					0x210
#define hal_msr_shutdown				0x214
#define hal_msr_read					0x218
#define hal_msr_get_status				0x21c
#define hal_msr_attach					0x220
#define hal_msr_detach					0x224
#define hal_msr_rfu_1					0x228
#define hal_msr_rfu_2					0x22c
#define hal_msr_rfu_3					0x230
#define hal_msr_rfu_4 					0x234

    /* Parallel Interface */
#define hal_parallel_init				0x238
#define hal_parallel_shutdown			0x23c
#define hal_parallel_set_config			0x240
#define hal_parallel_ioctl				0x244
#define hal_parallel_attach				0x248
#define hal_parallel_detach				0x24c
#define hal_parallel_get_status			0x250
#define hal_parallel_read				0x254
#define hal_parallel_write				0x258
#define hal_parallel_rfu_1				0x25c
#define hal_parallel_rfu_2 				0x260

    /* Thermal Printer Interface */
#define hal_printer_init				0x264
#define hal_printer_shutdown			0x268
#define hal_printer_get_status			0x26c
#define hal_printer_set_config			0x270
#define hal_printer_ioctl				0x274
#define hal_printer_head_write			0x278
#define hal_printer_motor_write			0x27c
#define hal_printer_motor_step			0x280
#define hal_printer_motor_get_position	0x284
#define hal_printer_motor_set_position	0x288
#define hal_printer_attach				0x28c
#define hal_printer_detach				0x290
#define hal_printer_rfu_1				0x294
#define hal_printer_rfu_2 				0x298

    /* PS2 interface */
#define hal_ps2_init					0x29c
#define hal_ps2_shutdown				0x2a0
#define hal_ps2_set_config				0x2a4
#define hal_ps2_attach					0x2a8
#define hal_ps2_detach					0x2ac
#define hal_ps2_get_status				0x2b0
#define hal_ps2_read					0x2b4
#define hal_ps2_write					0x2b8
#define hal_ps2_rfu_1					0x2bc
#define hal_ps2_rfu_2 					0x2c0

    /* PWM Interface */
#define hal_pwm_init					0x2c4
#define hal_pwm_shutdown				0x2c8
#define hal_pwm_set_config				0x2cc
#define hal_pwm_run						0x2d0
#define hal_pwm_stop					0x2d4
#define hal_pwm_get_status				0x2d8
#define hal_pwm_attach					0x2dc
#define hal_pwm_detach					0x2e0
#define hal_pwm_rfu_1					0x2e4
#define hal_pwm_rfu_2 					0x2e8

    /* RNG Interface */
#define hal_rng_init					0x2ec
#define hal_rng_shutdown				0x2f0
#define hal_rng_get_status				0x2f4
#define hal_rng_read					0x2f8
#define hal_rng_read128					0x3fc
#define hal_rng_attach					0x300
#define hal_rng_detach					0x304
#define hal_rng_rfu_1					0x308
#define hal_rng_rfu_2					0x30c

    /* RTC Interface */
#define hal_rtc_init					0x310
#define hal_rtc_get_time				0x314
#define hal_rtc_set_time				0x318
#define hal_rtc_set_alarm				0x31c
#define hal_rtc_get_status				0x320
#define hal_rtc_ioctl					0x324
#define hal_rtc_attach					0x328
#define hal_rtc_detach					0x32c
#define hal_rtc_rfu_1					0x330
#define hal_rtc_rfu_2    				0x334

    /* Smart Card Slot Interface */
#define hal_scs_init					0x338
#define hal_scs_shutdown				0x33c
#define hal_scs_get_status				0x340
#define hal_scs_set_config				0x344
#define hal_scs_power_up				0x348
#define hal_scs_power_down				0x34c
#define hal_scs_t0_in					0x350
#define hal_scs_t0_out					0x354
#define hal_scs_t1_block				0x358
#define hal_scs_pps_exchange 			0x35c
#define hal_scs_ioctl                   0x360
#define hal_scs_attach					0x364
#define hal_scs_detach					0x368
#define hal_scs_get_slot_info			0x36c
#define hal_scs_set_slot_info			0x370
#define hal_scs_get_last_error			0x374
#define hal_scs_cancel					0x378
#define hal_scs_rfu_1					0x37c
#define hal_scs_rfu_2					0x380
#define hal_scs_rfu_3					0x384
#define hal_scs_rfu_4					0x388

    /* Sensors */
#define hal_sensor_set_config			0x38c
#define hal_sensor_ioctl				0x390
#define hal_sensor_get_status			0x394
#define hal_sensor_rfu_1				0x398
#define hal_sensor_rfu_2				0x39c

    /* Security Storage Memory */
#define hal_storage_read				0x3a0
#define hal_storage_write				0x3a4
#define hal_storage_rfu_1				0x3a8
#define hal_storage_rfu_2				0x3ac

    /* SPI Interface */
#define hal_spi_init					0x3b0
#define hal_spi_shutdown				0x3b4
#define hal_spi_set_config				0x3b8
#define hal_spi_ioctl					0x3bc
#define hal_spi_attach					0x3c0
#define hal_spi_detach					0x3c4
#define hal_spi_get_status				0x3c8
#define hal_spi_write					0x3cc
#define hal_spi_read					0x3d0
#define hal_spi_rfu_1					0x3d4
#define hal_spi_rfu_2					0x3d8
#define hal_spi_rfu_3					0x3dc
#define hal_spi_rfu_4					0x3e0

    /* Timer Interface */
#define hal_timer_init					0x3e4
#define hal_timer_shutdown				0x3e8
#define hal_timer_run					0x3ec
#define hal_timer_stop					0x3f0
#define hal_timer_set_config			0x3f4
#define hal_timer_get_status			0x3f8
#define hal_timer_read					0x3fc
#define hal_timer_ioctl 				0x400
#define hal_timer_attach				0x404
#define hal_timer_detach				0x408
#define hal_timer_rfu_1					0x40c
#define hal_timer_rfu_2					0x410

    /* UART Interface */
#define hal_uart_init 					0x414
#define hal_uart_shutdown				0x418
#define hal_uart_set_config				0x41c
#define hal_uart_get_status				0x420
#define hal_uart_write					0x424
#define hal_uart_read					0x428
#define hal_uart_attach					0x42c
#define hal_uart_detach					0x430
#define hal_uart_ioctl					0x434
#define hal_uart_rfu_1					0x438
#define hal_uart_rfu_2					0x43c
#define hal_uart_rfu_3					0x440
#define hal_uart_rfu_4					0x444

    /* USB Interface */
#define hal_usb_ioctl						0x448
#define hal_usb_otg_init					0x44c
#define hal_usb_otg_shutdown				0x450
#define hal_usb_otg_set_status				0x454
#define hal_usb_otg_get_status				0x458
#define hal_usb_device_init					0x45c
#define hal_usb_device_shutdown				0x460
#define hal_usb_device_recv_data			0x464
#define hal_usb_device_send_data 			0x468
#define hal_usb_device_cancel_transfer		0x46c
#define hal_usb_device_attach				0x470
#define hal_usb_device_detach				0x474
#define hal_usb_device_init_endpoint	 	0x478
#define hal_usb_device_deinit_endpoint		0x47c
#define hal_usb_device_stall_endpoint		0x480
#define hal_usb_device_unstall_endpoint		0x484
#define hal_usb_device_assert_resume		0x488
#define hal_usb_device_get_transfer_status	0x48c
#define hal_usb_device_get_status 			0x490
#define hal_usb_device_set_status 			0x494
#define hal_usb_rfu_1						0x498
#define hal_usb_host_init					0x49c
#define hal_usb_host_bus_control			0x4a0
#define hal_usb_host_cancel_transfer	  	0x4a4
#define hal_usb_host_close_pipe				0x4a8
#define hal_usb_host_close_all_pipes		0x4ac
#define hal_usb_host_attach					0x4b0
#define hal_usb_host_detach					0x4b4
#define hal_usb_host_open_pipe				0x4b8
#define hal_usb_host_send_setup				0x4bc
#define hal_usb_host_get_transfer_status	0x4c0
#define hal_usb_host_shutdown				0x4c4
#define hal_usb_host_recv_data				0x4c8
#define hal_usb_host_send_data				0x4cc
#define hal_usb_host_driver_info_register	0x4d0
#define hal_usb_hostdev_find_pipe_handle	0x4d4
#define hal_usb_hostdev_get_buffer			0x4d8
#define hal_usb_hostdev_get_descriptor		0x4dc
#define hal_usb_hostdev_select_config		0x4e0
#define hal_usb_hostdev_select_interface	0x4e4
#define hal_usb_host_ch9_get_status			0x4e8
#define hal_usb_host_ch9_clear_feature		0x4ec
#define hal_usb_host_ch9_set_feature		0x4f0
#define hal_usb_host_ch9_set_address		0x4f4
#define hal_usb_host_ch9_get_descriptor		0x4f8
#define hal_usb_host_ch9_set_descriptor		0x4fc
#define hal_usb_host_ch9_get_configuration	0x500
#define hal_usb_host_ch9_set_configuration	0x504
#define hal_usb_host_ch9_get_interface		0x508
#define hal_usb_host_ch9_set_interface		0x50c
#define hal_usb_host_ch9_synch_frame		0x510
#define hal_usb_host_register_ch9_callback	0x514
#define hal_usb_hostdev_cntrl_request		0x518
#define hal_usb_rfu_2						0x51c
#define hal_usb_rfu_3						0x520
#define hal_usb_rfu_4						0x524
#define hal_usb_rfu_5						0x528

#define hal_tlb_write					0x52c
#define hal_tlb_write2					0x530
#define hal_cache_enable				0x534
#define hal_cache_disable				0x538

    /* Watchdog Timer Interface */
#define hal_watchdog_init				0x53c
#define hal_watchdog_shutdown			0x540
#define hal_watchdog_set_config			0x544
#define hal_watchdog_rearm				0x548
#define hal_watchdog_disarm				0x54c
#define hal_watchdog_read				0x550
#define hal_watchdog_get_status			0x554
#define hal_watchdog_attach				0x558
#define hal_watchdog_detach				0x55c
#define hal_watchdog_rfu_1				0x560
#define hal_watchdog_rfu_2				0x564

#define hal_tr_magic					0x568
#define hal_tr_ckecksum					0x56c



/* HAL Vector table address */
#define HAL_SYS_TABLE_BASE_LMA          0x8103f864 
#define HAL_SYS_TABLE_BASE_VMA          0x8001f364

	.macro	hal_get_address reg,off
	la	\reg,HAL_SYS_TABLE_BASE_VMA
	lw	\reg,\off(\reg)
	.endm

#else

	.macro	hal_get_address reg,addr
    .extern \addr
    la     \reg,\addr
	.endm

#endif /* CONFIG_LIBROM_NOT_INLINED */

/* ISR Vector table address */
#define HAL_ISR_TABLE_BASE              0x8001f910

	.macro	hal_get_isr reg,off
	la	\reg,HAL_ISR_TABLE_BASE			/* handler table */
	add	\reg,\reg,\off					/* address of ISR ptr */
	lw	\reg,0(\reg)					/* ISR pointer */
	.endm




/*----------------------------------------------------------------------------*/
#endif /* __LIBROM_CONFIG_INC__ */

