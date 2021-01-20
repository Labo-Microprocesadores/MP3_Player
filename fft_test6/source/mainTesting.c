
#include "arm_math.h"
#include "arm_const_structs.h"
#include "vumeterRefresh.h"

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "clock_config.h"

/***********************************/
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "core_cm4.h"
#include <stdbool.h>
#include <stdint.h>

#define __CORE_CLOCK__  100000000U
#define __FOREVER__     for(;;)
#define __ISR__         void __attribute__ ((interrupt))

static uint32_t __LDM_interruptDisableCount = 0;

void hw_Init (void)
{
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2)); /* set CP10, CP11 for Full Access to the FPU*/

    WDOG->UNLOCK  = WDOG_UNLOCK_WDOGUNLOCK(0xC520); /* Key 1 */
    WDOG->UNLOCK  = WDOG_UNLOCK_WDOGUNLOCK(0xD928); /* Key 2 */
    WDOG->STCTRLH = WDOG_STCTRLH_ALLOWUPDATE_MASK | WDOG_STCTRLH_CLKSRC_MASK | 0x0100U; /* Disable WDOG */

    PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* Release hold with ACKISO:  Only has an effect if recovering from VLLSx.*/

    SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) | SIM_CLKDIV1_OUTDIV2(0x01) | SIM_CLKDIV1_OUTDIV3(0x01) | SIM_CLKDIV1_OUTDIV4(0x03); /* Core-System = 100MHz, Bus = 50MHz, FlexBus = 50MHz, Flash = 25MHz */
    SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0x03); /* Set 32 kHz clock source (ERCLK32K) */
    SIM->SOPT2 = SIM_SOPT2_PLLFLLSEL_MASK; /* Set high frequency clock source (PLL) */
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK; /* All PORTs enabled */

    MCG->SC = MCG_SC_FCRDIV(0x02); /* Fast clock internal reference divider */
    MCG->C2 = MCG_C2_RANGE(0x02); /* High frequency range external reference selection */

    OSC->CR = OSC_CR_ERCLKEN_MASK; /* Set external reference clock (OSCERCLK) */

    MCG->C7 = MCG_C7_OSCSEL(0x00); /* Set FLL external reference clock (OSCCLK0) */
    MCG->C1 = MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x07); /* Set external reference as source, FLL external reference divider (PBE mode) */
    while((MCG->S & MCG_S_IREFST_MASK) != 0x00U); /* Check external reference validation */
    MCG->C5 = MCG_C5_PRDIV0(0x0F); /* Set PLL divider while PLL turned off */
    MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0x08); /* Set PLL multiplier and PLL select */
    while((MCG->S & MCG_S_LOCK0_MASK) == 0x00U); /* Wait until PLL is locked*/
    MCG->C1 &= ~MCG_C1_CLKS_MASK;
    while((MCG->S & MCG_S_CLKST_MASK) != 0x0CU); /* Wait until output of the PLL is selected */
}

/***************************************/
int main (void)
{
	hw_Init();
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; // activo clock gating

	PORTC->PCR[16] = 0x00;
	PORTC->PCR[16] |= PORT_PCR_MUX(1);
	PORTC->PCR[16] |= PORT_PCR_IRQC(0);
	GPIOC->PDDR |= 1 << 16;

	GPIOC->PDOR &= ~(1 << 16);

	PORTC->PCR[17] = 0x00;
	PORTC->PCR[17] |= PORT_PCR_MUX(1);
	PORTC->PCR[17] |= PORT_PCR_IRQC(0);
	GPIOC->PDDR |= 1 << 17;

	GPIOC->PDOR &= ~(1 << 17);

	vumeterRefresh_init();

	  float32_t baja[1024];
	  float32_t alta[1024];
	  float32_t otra[1024];
	  float32_t otra2[1024];
	  float32_t otra3[1024];
	  float32_t otra4[1024];
	  float32_t signal[1024];
	  int i;
	  for(i=0; i<1024; i++){
	         baja[i] = 30.0f*arm_sin_f32(2*3.1415926f*50*i/44100);
	         /*
	         alta[i] = 10.0f*arm_sin_f32(2*3.1415926f*10*i/44100);
	         otra[i] = 20.0f*arm_sin_f32(2*3.1415926f*100*i/44100);
	         otra2[i] = 30.0f*arm_sin_f32(2*3.1415926f*200*i/44100);
	         otra3[i] = 30.0f*arm_sin_f32(2*3.1415926f*300*i/44100);
	         */
	         otra4[i] = 30.0f*arm_sin_f32(2*3.1415926f*15000*i/44100);
	         signal[i] = baja[i]+otra4[i];
	     }

	GPIOC->PDOR |= (1 << 16);
	vumeterRefresh_fft(signal, 44100, 80, 20000);
	GPIOC->PDOR &= ~(1 << 16);

	GPIOC->PDOR |= (1 << 16);
	vumeterRefresh_fft(signal, 44100, 80, 20000);
	GPIOC->PDOR &= ~(1 << 16);

	GPIOC->PDOR |= (1 << 16);
	vumeterRefresh_fft(signal, 44100, 80, 20000);
	GPIOC->PDOR &= ~(1 << 16);
	return 0;
}
