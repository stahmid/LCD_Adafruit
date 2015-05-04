#include "touchlib.h"

int16_t comp (const void * elem1, const void * elem2) {
	int16_t f = *((int16_t*)elem1);
	int16_t s = *((int16_t*)elem2);
	if (f > s) return  1;
	if (f < s) return -1;
	return 0;
}

uint16_t findmedian(uint16_t* x){
	// pass odd number of elements
	uint16_t len = sizeof(x)/sizeof(*x);
	qsort (x, len, sizeof(*x), comp);

	return x[(--len)>>1];
}

uint16_t ts_readX(void){
	uint16_t ad_res;
	uint8_t i;

	_ym_OUTPUT(); _ym_DIGITAL(); _ym_LOW();
	delay_ms(1);

	_yp_INPUT(); _yp_ANALOG(); _ym_INPUT(); _ym_DIGITAL();
	_xp_OUTPUT(); _xp_DIGITAL(); _xp_HIGH();
	_xm_OUTPUT(); _xm_DIGITAL(); _xm_LOW();
	delay_ms(1);

	ad_res = 0;
	for (i=0; i<8; i++)
		ad_res += analogRead_touch(_yp_ADC_CH);

	ad_res >>= 3;
	_ym_OUTPUT(); _ym_DIGITAL(); _ym_LOW(); delay_ms(1);

	return ad_res;
}

uint16_t ts_readY(void){
	_xp_INPUT(); _xp_ANALOG(); _xm_INPUT(); _xm_DIGITAL();
	_xp_PD(); _xm_PD();
	_yp_noPD(); _ym_noPD();
	_yp_OUTPUT(); _yp_DIGITAL(); _yp_HIGH();
	_ym_OUTPUT(); _ym_DIGITAL(); _ym_LOW();
	delay_ms(1);
	return ( 1023 - analogRead_touch(_xp_ADC_CH) );
}

void ts_getPoint(touchpoint_t* tp){
#define n_samples 8

	/* Returns a point struct with components x, y and z
	 * n_samples tells the function how many times to read from ADC
	 *    to take median from
	 */
	uint16_t adc_result[n_samples];
	char i = 0;

	_yp_INPUT(); _yp_ANALOG(); _ym_INPUT(); //_ym_ANALOG();
	_yp_PD(); _ym_PD();
	_xp_noPD(); _xm_noPD();
	_xp_OUTPUT(); _xp_DIGITAL(); _xp_HIGH();
	_xm_OUTPUT(); _xm_LOW();
	delay_ms(1);

	for (i = 0; i < n_samples; i++) {
		adc_result[i] = analogRead_touch(_yp_ADC_CH) >> 3;
	}

	// filter the data
	tp->tp_x = 128 - findmedian((uint16_t*)adc_result);

	_xp_INPUT(); _xp_ANALOG(); _xm_INPUT(); _xm_DIGITAL();
	_xp_PD(); _xm_PD();
	_yp_noPD(); _ym_noPD();
	_yp_OUTPUT(); _yp_DIGITAL(); _yp_HIGH();
	_ym_OUTPUT(); _ym_DIGITAL(); _ym_LOW();
	delay_ms(1);

	for (i = 0; i < n_samples; i++) {
		adc_result[i] = analogRead_touch(_xp_ADC_CH) >> 3;
	}

	tp->tp_y = 128 - findmedian((uint16_t*)adc_result);

	tp->tp_z = ( ((128 - tp->tp_x) > pressureThreshold)
			& ( (128 - tp->tp_y) > pressureThreshold) );
//	tp->tp_z = 0;
}

uint16_t analogRead_touch(uint8_t ch){

	// clear channel setting
	ADC10CTL1 &= 0x0FFF;
	ADC10CTL1 |= (ch << 12);

	ADC10CTL0 |= (ADC10SC | ENC);	// enable and start sampling

	while (ADC10CTL1 & ADC10BUSY);	// wait for eoc
	ADC10CTL0 &= ~ENC;				// disable adc to allow changing properties

	return ADC10MEM;
}

