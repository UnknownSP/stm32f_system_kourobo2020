#ifndef __APP_H
#define __APP_H

/*NO Device mode*/
#define _NO_DEVICE 0

int appTask(void);
int appInit(void);

#define DD_NUM_OF_MD 6
#define DD_NUM_OF_AB 1

#define DD_NUM_OF_LD 0
#define DD_NUM_OF_SS 1
#define DD_USE_ENCODER1 1
#define DD_USE_ENCODER2 1
#define DD_NUM_OF_SV 0

#define USE_RASPI_CONTROL 1
#define DD_USE_RC 1

#include "DD_RC.h"
#include "DD_LD.h"
#include "DD_MD.h"
#include "DD_SV.h"
#include "DD_SS.h"

#define I2C_ODMETRY 0

#define R_F_KUDO_MD 0
#define R_B_KUDO_MD 1
#define L_B_KUDO_MD 2
#define L_F_KUDO_MD 3

#define ARM_SPIN_MD 4
#define GET_SKMT_MD 5

#define CENTRAL_THRESHOLD 4

#define AB_UPMECHA_ON (1<<3) //0b00001000
#define AB_CENTER_ON (1<<2) //0b00000100
#define AB_LEFT_ON (1<<4)  //0b00010000
#define AB_RIGHT_ON (1<<5)    //0b00100000

#define AB_UPMECHA_OFF (0b11110111)
#define AB_CENTER_OFF  (0b11111011)
#define AB_LEFT_OFF    (0b11101111)
#define AB_RIGHT_OFF   (0b11011111)

#define MD_GAIN ( DD_MD_MAX_DUTY / DD_RC_ANALOG_MAX )

#define _SW_LED_OFF_GPIOxID GPIOBID
#define _SW_LED_OFF_GPIOPIN GPIO_PIN_14
#define LED_OFF_SW() ((!MW_GPIORead(_SW_LED_OFF_GPIOxID,_SW_LED_OFF_GPIOPIN)))

#define _SW_FIRST_UP_LIMIT_GPIOxID GPIOBID
#define _SW_FIRST_UP_LIMIT_GPIOPIN GPIO_PIN_12
#define _IS_PRESSED_FIRST_UP_LIMITSW() ((!MW_GPIORead(_SW_FIRST_UP_LIMIT_GPIOxID,_SW_FIRST_UP_LIMIT_GPIOPIN)))

#define _SW_FIRST_UNDER_LIMIT_GPIOxID GPIOBID
#define _SW_FIRST_UNDER_LIMIT_GPIOPIN GPIO_PIN_2
#define _IS_PRESSED_FIRST_UNDER_LIMITSW() ((!MW_GPIORead(_SW_FIRST_UNDER_LIMIT_GPIOxID,_SW_FIRST_UNDER_LIMIT_GPIOPIN)))

#define _SW_ZENEBA_LIMIT_GPIOxID GPIOBID
#define _SW_ZENEBA_LIMIT_GPIOPIN GPIO_PIN_1
#define _IS_PRESSED_ZENEBA_LIMITSW() ((!MW_GPIORead(_SW_ZENEBA_LIMIT_GPIOxID,_SW_ZENEBA_LIMIT_GPIOPIN)))

#define _SW_ARM_UNDER_LIMIT_GPIOxID GPIOBID
#define _SW_ARM_UNDER_LIMIT_GPIOPIN GPIO_PIN_4
#define _IS_PRESSED_ARM_UNDER_LIMITSW() ((!MW_GPIORead(_SW_ARM_UNDER_LIMIT_GPIOxID,_SW_ARM_UNDER_LIMIT_GPIOPIN)))

#define _SW_ARM_UP_LIMIT_GPIOxID GPIOCID
#define _SW_ARM_UP_LIMIT_GPIOPIN GPIO_PIN_4
#define _IS_PRESSED_ARM_UP_LIMITSW() ((!MW_GPIORead(_SW_ARM_UP_LIMIT_GPIOxID,_SW_ARM_UP_LIMIT_GPIOPIN)))

#define _SW_PANEL_START_GPIOxID GPIOAID
#define _SW_PANEL_START_GPIOPIN GPIO_PIN_11
#define PANEL_START_SW() ((!MW_GPIORead(_SW_PANEL_START_GPIOxID,_SW_PANEL_START_GPIOPIN)))

#define _SW_PANEL_RIGHT_GPIOxID GPIOCID
#define _SW_PANEL_RIGHT_GPIOPIN GPIO_PIN_5
#define PANEL_RIGHT_SW() ((!MW_GPIORead(_SW_PANEL_RIGHT_GPIOxID,_SW_PANEL_RIGHT_GPIOPIN)))

#define _SW_PANEL_LEFT_GPIOxID GPIOAID
#define _SW_PANEL_LEFT_GPIOPIN GPIO_PIN_12
#define PANEL_LEFT_SW() ((!MW_GPIORead(_SW_PANEL_LEFT_GPIOxID,_SW_PANEL_LEFT_GPIOPIN)))

#define _SW_PANEL_RECET_GPIOxID GPIOCID
#define _SW_PANEL_RECET_GPIOPIN GPIO_PIN_8
#define PANEL_RECET_SW() ((!MW_GPIORead(_SW_PANEL_RECET_GPIOxID,_SW_PANEL_RECET_GPIOPIN)))

#define _SW_PANEL_ZONE_GPIOxID GPIOCID
#define _SW_PANEL_ZONE_GPIOPIN GPIO_PIN_0
#define PANEL_ZONE_SW() ((!MW_GPIORead(_SW_PANEL_ZONE_GPIOxID,_SW_PANEL_ZONE_GPIOPIN)))


/****以下追加分*****************/

#define ARM_SPIN_MAX_DUTY 1500

#define MOVE_STOP_RANGE 5
#define SPIN_STOP_RANGE 100 // 1.0
#define ACCELARATING_COEFF 20

#define DUTY_MAX_VALUE 4000
#define DUTY_MIN_VALUE 1000
#define DUTY_MAX_DISTANCE 1000
#define DUTY_MIN_DISTANCE 10
#define STRAIGHT_DUTY_GET(x) ((int)((((double)(DUTY_MAX_VALUE-DUTY_MIN_VALUE)/(double)(-DUTY_MAX_DISTANCE))*((double)(DUTY_MAX_DISTANCE-x)))+DUTY_MAX_VALUE))

#define XY_TO_INPUT_MAX_VALUE 100

#define INPUT_MAX_DUTY_COMPARE_COEFF 70

#define SPIN_INPUT_MAX_VALUE 100
#define SPIN_INPUT_MIN_VALUE 15
#define SPIN_INPUT_MAX_DEGREE 9000 // 90.0
#define SPIN_INPUT_MIN_DEGREE 100  // 1.0
#define SPIN_DUTY_GET(x) ((int)((((double)(SPIN_INPUT_MAX_VALUE-SPIN_INPUT_MIN_VALUE)/(double)(-SPIN_INPUT_MAX_DEGREE))*((double)(SPIN_INPUT_MAX_DEGREE-x)))+SPIN_INPUT_MAX_VALUE))

#define ARM_MAX_VALUE 1500
#define ARM_MIN_VALUE 1000
#define ARM_MAX_DEGREE 1000
#define ARM_MIN_DEGREE 20
#define ARM_DUTY_GET(x) ((int)((((double)(ARM_MAX_VALUE-ARM_MIN_VALUE)/(double)(-ARM_MAX_DEGREE))*((double)(ARM_MAX_DEGREE-x)))+ARM_MAX_VALUE))

#define ARM_STOP_RANGE 100

typedef enum{
  PLUS_ACCELERATING = 0,
  CONSTANT_SPEED = 1,
  MINUS_ACCELERATING = 2,
  ARRIVED_TARGET = 3,
  OVER_SHOOT = 4,
}MovingSituation_t;

typedef enum{
  MOVING_ARM = 0,
  SET_TARGET = 1,
  RESET_ARM_FUNC = 2,
}Arm_MovingSituation_t;

typedef enum{
  FALL_MECHA = 0,
  NEAR_ROBOT = 1,
  UNE_150 = 2,
  UNE_200 = 3,
  UNE_250 = 4,
  NEAR_UNE = 5,
}Arm_MovingTarget_t;

#define FALL_MECHA_ENC (-3072)
#define NEAR_ROBOT_ENC (-1024)
#define UNE_150_ENC (-1500)
#define UNE_200_ENC (-2000)
#define UNE_250_ENC (-2500)
#define NEAR_UNE_ENC (-1200)

typedef enum{
  MANUAL_SUSPENSION = 0,
  AUTO_FIRSTMECHA_UP= 1,
  AUTO_FIRSTMECHA_DOWN= 2,
  AUTO_SHEETS = 3,
  AUTO_SHEETS_1ZONE_RETURN = 4,
  AUTO_TOWEL_ALL= 5,
  AUTO_TOWEL_ALL_CLIP= 6,
  AUTO_TOWEL_3= 7,
  AUTO_TOWEL_2= 8,
  AUTO_TOWEL_1= 9,
  AUTO_SHEETS_TOWEL = 10,
  //AUTO_FIRSTMECHA_MOVE= 9,
  AUTO_TEST = 11,
  NO_OPERATION = 12,
  STOP_EVERYTHING = 13,
}TestMode_t;

typedef enum{
  BLUE_ZONE = 0,
  RED_ZONE = 1,
}GameZone_t;

typedef enum{
  PLUS_X = 0,
  MINUS_X = 1,
  PLUS_Y = 2,
  MINUS_Y = 3,
}MovingDestination_t;

typedef enum{
  TURN_NOW = 0,
  TURN_END = 1,
}TurnSituation_t;

typedef enum{
  NOW_POSITION_RIGHT = 0,
  NOW_POSITION_LEFT = 1,
  NOW_POSITION_CENTER = 2,
  NOW_POSITION_STOP = 3,
}NowPosition_t;

typedef enum{
  STEERING_NOW = 0,
  STEERING_STOP = 1,
}SteeringSituation_t;

typedef enum{
  FIRST_UP_MECHA_UP = 0,
  FIRST_UP_MECHA_DOWN = 1,
  FIRST_UP_MECHA_STOP = 2,
}FirstUpMecha_t;

typedef enum{
  ZENEBA_SPIN_NOW = 0,
  ZENEBA_SPIN_END = 1,
  ZENEBA_RECET = 2,
}ZenebaMecha_t;

typedef enum{
  GET_LAUNDRY = 0,
  GET_CLIP = 1,
  SET_RELEASE_POSI = 2,
  SET_CLIP_POSI = 3,
  SET_UP_POSI = 4,
}ArmMechaTarget_t;

typedef enum{
  ARM_SPIN_NOW = 0,
  ARM_SPIN_END = 1,
  ARM_RECET = 2,
}ArmMecha_t;

typedef enum{
  GETTING_NOW = 0,
  GETTING_ZENEBA_NOW = 1,
  GETTING_END = 2,
  GETTING_RECET = 3,
}GetObject_t;


#endif


