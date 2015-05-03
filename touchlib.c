#include "touchlib.h"

uint16_t ts_readX(void){
	_yp_INPUT(); _yp_ANALOG(); _ym_INPUT(); //_ym_ANALOG();
	_yp_PD(); _ym_PD();
	_xp_noPD(); _xm_noPD();
	_xp_OUTPUT(); _xp_DIGITAL(); _xp_HIGH();
	_xm_OUTPUT(); _xm_LOW();
	delay_ms(1);
	return ( 1023 - analogRead_touch(_yp_ADC_CH) );
}

uint16_t ts_readY(void){
	_xp_INPUT(); _xp_ANALOG(); _xm_INPUT(); //_xm_ANALOG();
	_xp_PD(); _xm_PD();
	_yp_noPD(); _ym_noPD();
	_yp_OUTPUT(); _yp_DIGITAL(); _yp_HIGH();
	_ym_OUTPUT(); _ym_LOW();
	delay_ms(1);
	return ( 1023 - analogRead_touch(_xp_ADC_CH) );
}

uint16_t compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

uint16_t findMedian(uint16_t* array, uint16_t len){
	int k;
	//    qsort(array,len,sizeof(int),compare);
	if (((len/2)*2)==len){ // even number of elements
		k = len/2;
		return (*(array+k) + *(array+k+1))/2;
	}
	else{ // odd number of elements
		k = (len-1)/2;
		return *(array+k);
	}
}


void ts_getPoint(touchpoint_t* tp){
#define n_samples 5

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

//	for (i = 0; i < n_samples; i++) {
//		adc_result[i] = analogRead_touch(_yp_ADC_CH);
//	}

	tp->tp_x = 1023 - analogRead_touch(_yp_ADC_CH);
	// filter the data
	//    tp->tp_x = 1023 - findMedian((uint16_t*)adc_result,n_samples);

	_xp_INPUT(); _xp_ANALOG(); _xm_INPUT(); //_xm_ANALOG();
	_xp_PD(); _xm_PD();
	_yp_noPD(); _ym_noPD();
	_yp_OUTPUT(); _yp_DIGITAL(); _yp_HIGH();
	_ym_OUTPUT(); _ym_LOW();
	delay_ms(1);

//	for (i = 0; i < n_samples; i++)
//		adc_result[i] = analogRead_touch(_xp_ADC_CH);

	tp->tp_y = 1023 - analogRead_touch(_xp_ADC_CH);

	//    tp->tp_y = 1023 - findMedian((int*)adc_result,n_samples);

	tp->tp_z = ( ((1023 - tp->tp_x) > pressureThreshold)
			& ( (1023 - tp->tp_y) > pressureThreshold) );
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

