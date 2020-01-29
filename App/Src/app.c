#include "app.h"
#include "DD_Gene.h"
#include "DD_RCDefinition.h"
#include "SystemTaskManager.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MW_GPIO.h"
#include "MW_IWDG.h"
#include "message.h"
#include "MW_flash.h"
#include "constManager.h"
#include "trapezoid_ctrl.h"

static char *testmode_name[] = {
  "MANUAL_SUSPENSION",
  "AUTO_FIRSTMECHA_UP",
  "AUTO_FIRSTMECHA_DOWN",
  "AUTO_SHEETS",
  "AUTO_SHEETS_1ZONE_RETURN",
  "AUTO_TOWEL_ALL",
  "AUTO_TOWEL_ALL_CLIP",
  "AUTO_TOWEL_3",
  "AUTO_TOWEL_2",
  "AUTO_TOWEL_1",
  "AUTO_SHEETS_TOWEL",
  "AUTO_TEST",
  "NO_OPERATION",
  "STOP_EVERYTHING",
};
/********/
/*suspensionSystem*/
static
int manual_omni_suspension(void);
static int duty_check(void);
/*ABSystem*/
static 
int ABSystem(void);
static
int LEDSystem(void);
/*メモ
 *g_ab_h...ABのハンドラ
 *g_md_h...MDのハンドラ
 *
 *g_rc_data...RCのデータ
 */

int appInit(void){

	ad_init();

	/*GPIO の設定などでMW,GPIOではHALを叩く*/
	return EXIT_SUCCESS;
}

/*application tasks*/
int appTask(void){
	int ret=0;
	int i;
	int32_t encoder_count = 0;
	static int32_t recent_system_count = 0;

	static unsigned int target_count = 0;
	static bool circle_flag = false, cross_flag = false;
	static int target_duty,duty;

	if(!__RC_ISPRESSED_CIRCLE(g_rc_data)) circle_flag = true;
	if(!__RC_ISPRESSED_CROSS(g_rc_data)) cross_flag = true;

	if(__RC_ISPRESSED_CIRCLE(g_rc_data) && circle_flag){ 
		target_count++;
		circle_flag = false;
	}
	if(__RC_ISPRESSED_CROSS(g_rc_data) && cross_flag){
		target_count--;
		cross_flag = false;
	}

	target_duty = (int)((double)target_count*(200.0/3.0));

	//manual_omni_suspension();
	//duty_check();

	if( g_SY_system_counter % _MESSAGE_INTERVAL_MS < _INTERVAL_MS ){
		encoder_count = DD_encoder1Get_int32();
		MW_printf("encoder_count:[%d]  time:[%d]  target:[%d]\n",encoder_count,g_SY_system_counter-recent_system_count,target_duty);
		if(abs(encoder_count) > target_duty){
			if(abs( abs(encoder_count) - target_duty) > 30){
				duty -= 50;
			}else{
				duty--;
			}
		}else if(abs(encoder_count) < target_duty){
			if(abs( abs(encoder_count) - target_duty) > 30){
				duty += 50;
			}else{
				duty++;
			}
		}
		for(i=0; i<4; i++){
			g_md_h[i].mode = D_MMOD_FORWARD;
			g_md_h[i].duty = duty;
			if(g_md_h[i].duty >= 9900){
				g_md_h[i].duty = 9900;
			}
		}
		DD_encoder1reset();
		encoder_count = 0;
		recent_system_count = g_SY_system_counter;
	}

	//if( g_SY_system_counter % _MESSAGE_INTERVAL_MS < _INTERVAL_MS ){
	//	MW_printf("encoder_count:[%d]  time:[%d]\n",encoder_count,g_SY_system_counter-recent_system_count);
	//}

	return EXIT_SUCCESS;
}

static
int manual_omni_suspension(void){
	const int cal_array[4][3] = {
		{ 1, -1, 1},
		{-1, -1, 1},
		{-1,  1, 1},
		{ 1,  1, 1},
	};
	int temp_array[4];
	int cal_duty[4];
	int in_array[3];
	int i=0,j=0;

	in_array[0] = DD_RCGetLX(g_rc_data);
	in_array[1] = -DD_RCGetLY(g_rc_data);
	in_array[2] = DD_RCGetRX(g_rc_data);

	for(i=0; i<4; i++){
		temp_array[i] = 0;
		for(j=0; j<3; j++){
			temp_array[i] += in_array[j]*cal_array[i][j];
		}
		cal_duty[i] = temp_array[i] * 50;
		g_md_h[i].duty = abs(cal_duty[i]);
		if(cal_duty[i] < 0){
			g_md_h[i].mode = D_MMOD_BACKWARD;
		}else if(cal_duty[i] > 0){
			g_md_h[i].mode = D_MMOD_FORWARD;
		}else{
			g_md_h[i].mode = D_MMOD_BRAKE;
		}
	}

	return EXIT_SUCCESS;
}

static int duty_check(void){
	static unsigned int count = 0;
	static bool circle_flag = false, cross_flag = false;
	int i;

	if(!__RC_ISPRESSED_CIRCLE(g_rc_data)) circle_flag = true;
	if(!__RC_ISPRESSED_CROSS(g_rc_data)) cross_flag = true;

	if(__RC_ISPRESSED_CIRCLE(g_rc_data) && circle_flag){ 
		count++;
		circle_flag = false;
	}
	if(__RC_ISPRESSED_CROSS(g_rc_data) && cross_flag){
		count--;
		cross_flag = false;
	}
	for(i=0; i<4; i++){
		g_md_h[i].mode = D_MMOD_FORWARD;
		g_md_h[i].duty = count * 200;
		if(g_md_h[i].duty >= 9900){
			g_md_h[i].duty = 9900;
		}
	}

	return 0;
}