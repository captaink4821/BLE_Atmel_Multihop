/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_H_INCLUDED
#define ATMEL_START_H_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
		extern "C" {
#endif

#include <hal_usart_async.h>

#include <hal_usart_sync.h>
#include <hal_usart_async.h>
#include <hal_timer.h>
#include <hpl_tc2_v200_base.h>
#include <hal_ext_irq.h>

	extern struct usart_async_descriptor BLE_FC_UART;

	extern struct usart_sync_descriptor CONSOLE_UART;
	extern struct usart_async_descriptor BLE_UART;
	extern struct timer_descriptor TIMER_0;

	void BLE_FC_UART_PORT_init(void);
	void BLE_FC_UART_CLOCK_init(void);
	void BLE_FC_UART_init(void);
	void BLE_FC_UART_example(void);

	void CONSOLE_UART_PORT_init(void);
	void CONSOLE_UART_CLOCK_init(void);
	void CONSOLE_UART_init(void);
	void CONSOLE_UART_example(void);

	void BLE_UART_PORT_init(void);
	void BLE_UART_CLOCK_init(void);
	void BLE_UART_init(void);
	void BLE_UART_example(void);

#define CONF_DMAC_MAX_USED_DESC ( /*SERCOM0*/ 0 + /*SERCOM3*/ 0 + \
	        /*SERCOM4*/ 0 + /*TC0*/ 0 + /*EIC*/ 0 + /*GCLK*/ 0 + /*MCLK*/ 0 + \
	        /*OSCCTRL*/ 0 + /*OSC32KCTRL*/ 0 )

#define CONF_DMAC_MAX_USED_CH ( /*SERCOM0*/ 0 + /*SERCOM3*/ 0 + /*SERCOM4*/ 0 +	\
	        /*TC0*/ 0 + /*EIC*/ 0 + /*GCLK*/ 0 + /*MCLK*/ 0 + /*OSCCTRL*/ 0 + \
	        /*OSC32KCTRL*/ 0 )

	/**
	 * \brief Perform system initialization, initialize pins and clocks for
	 * peripherals
	 */
	void system_init(void);

#ifdef __cplusplus
		}
#endif
#endif // ATMEL_START_H_INCLUDED
