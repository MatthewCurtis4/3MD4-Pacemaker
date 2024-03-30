/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Pacemaker.h
 *
 * Code generated for Simulink model 'Pacemaker'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Mar 30 16:22:45 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Pacemaker_h_
#define RTW_HEADER_Pacemaker_h_
#ifndef Pacemaker_COMMON_INCLUDES_
#define Pacemaker_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "MW_digitalIO.h"
#include "MW_I2C.h"
#include "MW_PWM.h"
#endif                                 /* Pacemaker_COMMON_INCLUDES_ */

#include "Pacemaker_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T csumrev[499];
  real_T PACING_REF_PWM;               /* '<Root>/PACING MODES' */
  real_T VENT_CMP_REF_PWM;             /* '<Root>/PACING MODES' */
  real_T rtb_MovingAverage_m;
  real_T modValueRev;
  real_T z;
  boolean_T PACE_CHARGE_CTRL;          /* '<Root>/PACING MODES' */
  boolean_T Z_ATR_CTRL;                /* '<Root>/PACING MODES' */
  boolean_T Z_VENT_CTRL;               /* '<Root>/PACING MODES' */
  boolean_T ATR_PACE_CTRL;             /* '<Root>/PACING MODES' */
  boolean_T VENT_PACE_CTRL;            /* '<Root>/PACING MODES' */
  boolean_T PACE_GND_CTRL;             /* '<Root>/PACING MODES' */
  boolean_T ATR_GND_CTRL;              /* '<Root>/PACING MODES' */
  boolean_T VENT_GND_CTRL;             /* '<Root>/PACING MODES' */
  boolean_T FRONTEND_CTRL;             /* '<Root>/PACING MODES' */
} B_Pacemaker_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  dsp_simulink_MovingAverage_Pa_T obj; /* '<S5>/Moving Average' */
  freedomk64f_fxos8700_Pacemake_T obj_m;/* '<S5>/FXOS8700 6-Axes Sensor' */
  freedomk64f_DigitalRead_Pacem_T obj_my;/* '<S5>/D1' */
  freedomk64f_DigitalRead_Pacem_T obj_d;/* '<S5>/D0' */
  freedomk64f_DigitalWrite_Pace_T obj_k;/* '<S2>/Digital Write9' */
  freedomk64f_DigitalWrite_Pace_T obj_c;/* '<S2>/Digital Write8' */
  freedomk64f_DigitalWrite_Pace_T obj_m1;/* '<S2>/Digital Write7' */
  freedomk64f_DigitalWrite_Pace_T obj_o;/* '<S2>/Digital Write6' */
  freedomk64f_DigitalWrite_Pace_T obj_l;/* '<S2>/Digital Write5' */
  freedomk64f_DigitalWrite_Pace_T obj_h;/* '<S2>/Digital Write3' */
  freedomk64f_DigitalWrite_Pace_T obj_h5;/* '<S2>/Digital Write11' */
  freedomk64f_DigitalWrite_Pace_T obj_p;/* '<S2>/Digital Write10' */
  freedomk64f_DigitalWrite_Pace_T obj_l5;/* '<S2>/Digital Write' */
  freedomk64f_PWMOutput_Pacemak_T obj_j;/* '<S2>/PWM Output2' */
  freedomk64f_PWMOutput_Pacemak_T obj_a;/* '<S2>/PWM Output1' */
  freedomk64f_PWMOutput_Pacemak_T obj_e;/* '<S2>/PWM Output' */
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  uint32_T temporalCounter_i1;         /* '<Root>/PACING MODES' */
  uint8_T is_c1_Pacemaker;             /* '<Root>/PACING MODES' */
  uint8_T is_AOO;                      /* '<Root>/PACING MODES' */
  uint8_T is_VOO;                      /* '<Root>/PACING MODES' */
  uint8_T is_AAI;                      /* '<Root>/PACING MODES' */
  uint8_T is_VVI;                      /* '<Root>/PACING MODES' */
  uint8_T is_AOOR;                     /* '<Root>/PACING MODES' */
  uint8_T is_VOOR;                     /* '<Root>/PACING MODES' */
  uint8_T is_AAIR;                     /* '<Root>/PACING MODES' */
  uint8_T is_VVIR;                     /* '<Root>/PACING MODES' */
  uint8_T is_active_c1_Pacemaker;      /* '<Root>/PACING MODES' */
  boolean_T IC_FirstOutputTime;        /* '<Root>/IC' */
} DW_Pacemaker_T;

/* Parameters (default storage) */
struct P_Pacemaker_T_ {
  real_T D0_SampleTime;                /* Expression: SampleTime
                                        * Referenced by: '<S5>/D0'
                                        */
  real_T D1_SampleTime;                /* Expression: SampleTime
                                        * Referenced by: '<S5>/D1'
                                        */
  real_T FXOS87006AxesSensor_SampleTime;/* Expression: -1
                                         * Referenced by: '<S5>/FXOS8700 6-Axes Sensor'
                                         */
  real_T Converttoms2_Gain;            /* Expression: 9.81
                                        * Referenced by: '<S5>/Convert to m//s^2'
                                        */
  real_T gravitationalacceleration_Value;/* Expression: 9.81
                                          * Referenced by: '<S5>/ gravitational  acceleration'
                                          */
  real_T Constant11_Value;             /* Expression: 60
                                        * Referenced by: '<S1>/Constant11'
                                        */
  real_T Constant2_Value;              /* Expression: 120
                                        * Referenced by: '<S1>/Constant2'
                                        */
  real_T Constant9_Value;              /* Expression: 1
                                        * Referenced by: '<S1>/Constant9'
                                        */
  real_T Constant3_Value;              /* Expression: 1
                                        * Referenced by: '<S1>/Constant3'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 60
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  real_T IC_Value;                     /* Expression: 60
                                        * Referenced by: '<Root>/IC'
                                        */
  real_T Constant_Value;               /* Expression: 30
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Constant8_Value;              /* Expression: 300
                                        * Referenced by: '<S1>/Constant8'
                                        */
  real_T DesiredVoltage_Value;         /* Expression: 5
                                        * Referenced by: '<S1>/Desired Voltage'
                                        */
  real_T Constant4_Value;              /* Expression: 1
                                        * Referenced by: '<S1>/Constant4'
                                        */
  real_T Constant6_Value;              /* Expression: 300
                                        * Referenced by: '<S1>/Constant6'
                                        */
  real_T Constant7_Value;              /* Expression: 250
                                        * Referenced by: '<S1>/Constant7'
                                        */
  real_T Constant1_Value;              /* Expression: 5
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Constant5_Value;              /* Expression: 90
                                        * Referenced by: '<S1>/Constant5'
                                        */
  real_T ConvertvoltagetoPWMduty2_Gain;/* Expression: 20
                                        * Referenced by: '<S2>/Convert voltage  to PWM duty2'
                                        */
  real_T ConvertvoltagetoPWMduty1_Gain;/* Expression: 20
                                        * Referenced by: '<S2>/Convert voltage  to PWM duty1'
                                        */
  real_T Constant10_Value;             /* Expression: 5
                                        * Referenced by: '<S1>/Constant10'
                                        */
  real_T ConvertvoltagetoPWMduty_Gain; /* Expression: 20
                                        * Referenced by: '<S2>/Convert voltage  to PWM duty'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Pacemaker_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_Pacemaker_T Pacemaker_P;

/* Block signals (default storage) */
extern B_Pacemaker_T Pacemaker_B;

/* Block states (default storage) */
extern DW_Pacemaker_T Pacemaker_DW;

/* Model entry point functions */
extern void Pacemaker_initialize(void);
extern void Pacemaker_step(void);
extern void Pacemaker_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Pacemaker_T *const Pacemaker_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Pacemaker'
 * '<S1>'   : 'Pacemaker/Input System'
 * '<S2>'   : 'Pacemaker/Output System'
 * '<S3>'   : 'Pacemaker/PACING MODES'
 * '<S4>'   : 'Pacemaker/Rate Adaptive Pacing'
 * '<S5>'   : 'Pacemaker/Input System/Hardware Pins Subsystem Inputs'
 * '<S6>'   : 'Pacemaker/Rate Adaptive Pacing/Rate Modulation'
 * '<S7>'   : 'Pacemaker/Rate Adaptive Pacing/Time Response'
 * '<S8>'   : 'Pacemaker/Rate Adaptive Pacing/Rate Modulation/Activity Response'
 */
#endif                                 /* RTW_HEADER_Pacemaker_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
