/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "atmel_start.h"
#include <utils.h>
#include <hal_init.h>
#include <hpl_irq.h>
#include <hri_gclk2_v111.h>
#include <hri_mclk_v101.h>
#include <peripheral_gclk_config.h>

#if CONF_DMAC_MAX_USED_DESC > 0
#endif

/*! The buffer size for USART */
#define BLE_FC_UART_BUFFER_SIZE 16
/*! The buffer size for USART */
#define BLE_UART_BUFFER_SIZE 16

extern struct _irq_descriptor *_irq_table[PERIPH_COUNT_IRQn];
extern void Default_Handler(void);

struct usart_async_descriptor BLE_FC_UART;
struct usart_async_descriptor BLE_UART;
struct timer_descriptor TIMER_0;

static uint8_t BLE_FC_UART_buffer[BLE_FC_UART_BUFFER_SIZE];
static uint8_t BLE_UART_buffer[BLE_UART_BUFFER_SIZE];
static struct timer_task TIMER_0_task1, TIMER_0_task2;

struct usart_sync_descriptor CONSOLE_UART;

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void BLE_FC_UART_CLOCK_init()
{
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM0_GCLK_ID_CORE,
			CONF_GCLK_SERCOM0_CORE_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM0_GCLK_ID_SLOW,
			CONF_GCLK_SERCOM0_SLOW_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));

	hri_mclk_set_APBCMASK_SERCOM0_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void BLE_FC_UART_PORT_init()
{
	gpio_set_pin_function(PA04, PINMUX_PA04D_SERCOM0_PAD0);

	gpio_set_pin_function(PA05, PINMUX_PA05D_SERCOM0_PAD1);

	gpio_set_pin_function(PA06, PINMUX_PA06D_SERCOM0_PAD2);

	gpio_set_pin_function(PA07, PINMUX_PA07D_SERCOM0_PAD3);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void BLE_FC_UART_init(void)
{
	BLE_FC_UART_CLOCK_init();
	usart_async_init(&BLE_FC_UART,
			SERCOM0,
			BLE_FC_UART_buffer,
			BLE_FC_UART_BUFFER_SIZE);
	BLE_FC_UART_PORT_init();
}

void CONSOLE_UART_PORT_init(void)
{
	gpio_set_pin_function(PA22, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_function(PA23, PINMUX_PA23C_SERCOM3_PAD1);
}

void CONSOLE_UART_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM3_GCLK_ID_CORE,
			CONF_GCLK_SERCOM3_CORE_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM3_GCLK_ID_SLOW,
			CONF_GCLK_SERCOM3_SLOW_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));

	hri_mclk_set_APBCMASK_SERCOM3_bit(MCLK);
}

void CONSOLE_UART_init(void)
{
	CONSOLE_UART_CLOCK_init();
	usart_sync_init(&CONSOLE_UART, SERCOM3);
	CONSOLE_UART_PORT_init();
}

/**
 * Example of using CONSOLE_UART to write "Hello World" using the IO abstraction.
 */
void CONSOLE_UART_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&CONSOLE_UART, &io);
	usart_sync_enable(&CONSOLE_UART);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void BLE_UART_CLOCK_init()
{
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM4_GCLK_ID_CORE,
			CONF_GCLK_SERCOM4_CORE_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM4_GCLK_ID_SLOW,
			CONF_GCLK_SERCOM4_SLOW_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));

	hri_mclk_set_APBCMASK_SERCOM4_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void BLE_UART_PORT_init()
{
	gpio_set_pin_function(PB08, PINMUX_PB08D_SERCOM4_PAD0);

	gpio_set_pin_function(PB09, PINMUX_PB09D_SERCOM4_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void BLE_UART_init(void)
{
	BLE_UART_CLOCK_init();
	usart_async_init(&BLE_UART, SERCOM4, BLE_UART_buffer, BLE_UART_BUFFER_SIZE);
	BLE_UART_PORT_init();
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	hri_mclk_set_APBCMASK_TC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC0_GCLK_ID, CONF_GCLK_TC0_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));

	timer_init(&TIMER_0, TC0, _tc_get_timer());
}

void EXTERNAL_IRQ_0_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, EIC_GCLK_ID, CONF_GCLK_EIC_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
	hri_mclk_set_APBAMASK_EIC_bit(MCLK);

	ext_irq_init();

	// Set pin direction to input
	gpio_set_pin_direction(BLE_APP_SW, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BLE_APP_SW,
	        // <y> Pull configuration
	        // <id> pad_pull_config
	        // <GPIO_PULL_OFF"> Off
	        // <GPIO_PULL_UP"> Pull-up
	        // <GPIO_PULL_DOWN"> Pull-down
			GPIO_PULL_UP);

	gpio_set_pin_function(BLE_APP_SW, PINMUX_PA02A_EIC_EXTINT2);
}

void SERCOM0_Handler(void)
{
	if (_irq_table[ SERCOM0_IRQn + 0 ]) {
		_irq_table[ SERCOM0_IRQn + 0 ]->handler(
				_irq_table[ SERCOM0_IRQn + 0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void SERCOM3_Handler(void)
{
	if (_irq_table[ SERCOM0_IRQn + 3 ]) {
		_irq_table[ SERCOM0_IRQn + 3 ]->handler(
				_irq_table[ SERCOM0_IRQn + 3 ]->parameter);
	} else {
		Default_Handler();
	}
}
void SERCOM4_Handler(void)
{
	if (_irq_table[ SERCOM0_IRQn + 4 ]) {
		_irq_table[ SERCOM0_IRQn + 4 ]->handler(
				_irq_table[ SERCOM0_IRQn + 4 ]->parameter);
	} else {
		Default_Handler();
	}
}
void TC0_Handler(void)
{
	if (_irq_table[ TC0_IRQn + 0 ]) {
		_irq_table[ TC0_IRQn + 0 ]->handler(
				_irq_table[ TC0_IRQn + 0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void EIC_Handler(void)
{
	if (_irq_table[ EIC_IRQn + 0 ]) {
		_irq_table[ EIC_IRQn + 0 ]->handler(
				_irq_table[ EIC_IRQn + 0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void MCLK_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void OSCCTRL_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void OSC32KCTRL_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}

/**
 * Example of using BLE_FC_UART to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_BLE_FC_UART[12] = "Hello World!";

static void tx_cb_BLE_FC_UART(
		const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void BLE_FC_UART_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&BLE_FC_UART,
			USART_ASYNC_TXC_CB,
			tx_cb_BLE_FC_UART);
	/*usart_async_register_callback(&BLE_FC_UART, USART_ASYNC_RXC_CB, rx_cb);
	   usart_async_register_callback(&BLE_FC_UART, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&BLE_FC_UART, &io);
	usart_async_enable(&BLE_FC_UART);

	io_write(io, example_BLE_FC_UART, 12);
}

/**
 * Example of using BLE_UART to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_BLE_UART[12] = "Hello World!";

static void tx_cb_BLE_UART(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void BLE_UART_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&BLE_UART, USART_ASYNC_TXC_CB, tx_cb_BLE_UART);
	/*usart_async_register_callback(&BLE_UART, USART_ASYNC_RXC_CB, rx_cb);
	   usart_async_register_callback(&BLE_UART, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&BLE_UART, &io);
	usart_async_enable(&BLE_UART);

	io_write(io, example_BLE_UART, 12);
}

/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb = TIMER_0_task1_cb;
	TIMER_0_task1.mode = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb = TIMER_0_task2_cb;
	TIMER_0_task2.mode = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

static void button_on_PA02_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{
	ext_irq_register(PIN_PA02, button_on_PA02_pressed);
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA00

	// Set pin direction to output
	gpio_set_pin_direction(CE_PIN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(CE_PIN,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(CE_PIN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA01

	// Set pin direction to output
	gpio_set_pin_direction(WAKEUP_PIN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(WAKEUP_PIN,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(WAKEUP_PIN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA03

	// Set pin direction to output
	gpio_set_pin_direction(BTLC1000_CHIP_ENABLE_PIN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BTLC1000_CHIP_ENABLE_PIN,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(BTLC1000_CHIP_ENABLE_PIN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB07

	// Set pin direction to output
	gpio_set_pin_direction(BTLC1000_WAKEUP_PIN, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BTLC1000_WAKEUP_PIN,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(BTLC1000_WAKEUP_PIN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB10

	// Set pin direction to output
	gpio_set_pin_direction(BLE_APP_LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BLE_APP_LED,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(BLE_APP_LED, GPIO_PIN_FUNCTION_OFF);

	BLE_FC_UART_init();

	CONSOLE_UART_init();
	BLE_UART_init();
	TIMER_0_init();
	EXTERNAL_IRQ_0_init();
}
