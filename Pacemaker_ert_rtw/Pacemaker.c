/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Pacemaker.c
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

#include "Pacemaker.h"
#include "Pacemaker_types.h"
#include "rtwtypes.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"
#include <stddef.h>
#include "MW_I2C.h"

/* Named constants for Chart: '<Root>/PACING MODES' */
#define Pacemaker_IN_AAI               ((uint8_T)1U)
#define Pacemaker_IN_AAIR              ((uint8_T)2U)
#define Pacemaker_IN_AAI_CHARGE        ((uint8_T)1U)
#define Pacemaker_IN_AAI_PACING        ((uint8_T)2U)
#define Pacemaker_IN_AAI_REFRACTORY    ((uint8_T)3U)
#define Pacemaker_IN_AOO               ((uint8_T)3U)
#define Pacemaker_IN_AOOR              ((uint8_T)4U)
#define Pacemaker_IN_AOO_CHARGE        ((uint8_T)1U)
#define Pacemaker_IN_AOO_PACING        ((uint8_T)2U)
#define Pacemaker_IN_INIT              ((uint8_T)5U)
#define Pacemaker_IN_MODE_SELECT       ((uint8_T)6U)
#define Pacemaker_IN_NO_ACTIVE_CHILD   ((uint8_T)0U)
#define Pacemaker_IN_SENSE             ((uint8_T)4U)
#define Pacemaker_IN_VOO               ((uint8_T)7U)
#define Pacemaker_IN_VOOR              ((uint8_T)8U)
#define Pacemaker_IN_VOO_Charge        ((uint8_T)1U)
#define Pacemaker_IN_VOO_Pace          ((uint8_T)2U)
#define Pacemaker_IN_VVI               ((uint8_T)9U)
#define Pacemaker_IN_VVIR              ((uint8_T)10U)
#define Pacemaker_IN_VVI_CHARGE        ((uint8_T)1U)
#define Pacemaker_IN_VVI_PACING        ((uint8_T)2U)
#define Pacemaker_IN_VVI_REFACTORY     ((uint8_T)3U)

/* Block signals (default storage) */
B_Pacemaker_T Pacemaker_B;

/* Block states (default storage) */
DW_Pacemaker_T Pacemaker_DW;

/* Real-time model */
static RT_MODEL_Pacemaker_T Pacemaker_M_;
RT_MODEL_Pacemaker_T *const Pacemaker_M = &Pacemaker_M_;

/* Forward declaration for local functions */
static void Pacemaker_AAI(const boolean_T *D0);
static void Pacemaker_AAIR(const boolean_T *D0);
static void Pacemaker_MODE_SELECT(void);
static void Pacemaker_VVI(const boolean_T *D1);
static void Pacemaker_VVIR(const boolean_T *D1);
static void Pacemaker_SystemCore_setup(freedomk64f_fxos8700_Pacemake_T *obj);
static void Pacemaker_SystemCore_setup_j(dsp_simulink_MovingAverage_Pa_T *obj);

/* Function for Chart: '<Root>/PACING MODES' */
static void Pacemaker_AAI(const boolean_T *D0)
{
  /* Constant: '<S1>/Constant1' */
  if (Pacemaker_P.Constant1_Value != 3.0) {
    Pacemaker_DW.is_AAI = Pacemaker_IN_NO_ACTIVE_CHILD;
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
  } else {
    switch (Pacemaker_DW.is_AAI) {
     case Pacemaker_IN_AAI_CHARGE:
      Pacemaker_B.FRONTEND_CTRL = true;
      Pacemaker_B.ATR_PACE_CTRL = false;
      Pacemaker_B.PACE_CHARGE_CTRL = true;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;
      Pacemaker_B.ATR_GND_CTRL = true;
      Pacemaker_DW.is_AAI = Pacemaker_IN_AAI_REFRACTORY;
      Pacemaker_DW.temporalCounter_i1 = 0U;
      break;

     case Pacemaker_IN_AAI_PACING:
      Pacemaker_B.PACE_CHARGE_CTRL = false;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.ATR_PACE_CTRL = true;
      Pacemaker_B.ATR_GND_CTRL = false;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;

      /* Constant: '<S1>/Constant4' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant4_Value)) {
        Pacemaker_DW.is_AAI = Pacemaker_IN_AAI_CHARGE;
        Pacemaker_B.FRONTEND_CTRL = true;
        Pacemaker_B.ATR_PACE_CTRL = false;

        /* Constant: '<S1>/Desired Voltage' */
        Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
        Pacemaker_B.PACE_CHARGE_CTRL = true;
        Pacemaker_B.ATR_GND_CTRL = true;
      }
      break;

     case Pacemaker_IN_AAI_REFRACTORY:
      /* Constant: '<S1>/Constant7' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant7_Value)) {
        Pacemaker_DW.is_AAI = Pacemaker_IN_SENSE;
        Pacemaker_DW.temporalCounter_i1 = 0U;
      }
      break;

     case Pacemaker_IN_SENSE:
      /* Constant: '<S1>/Constant11' incorporates:
       *  Constant: '<S1>/Constant4'
       *  Constant: '<S1>/Constant7'
       */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil((60000.0 /
            Pacemaker_P.Constant11_Value - Pacemaker_P.Constant4_Value) -
           Pacemaker_P.Constant7_Value)) {
        Pacemaker_DW.is_AAI = Pacemaker_IN_AAI_PACING;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.PACE_CHARGE_CTRL = false;
        Pacemaker_B.PACE_GND_CTRL = true;
        Pacemaker_B.ATR_PACE_CTRL = true;
        Pacemaker_B.ATR_GND_CTRL = false;
        Pacemaker_B.Z_ATR_CTRL = false;
        Pacemaker_B.Z_VENT_CTRL = false;
      } else if (*D0) {
        Pacemaker_DW.is_AAI = Pacemaker_IN_AAI_REFRACTORY;
        Pacemaker_DW.temporalCounter_i1 = 0U;
      }

      /* End of Constant: '<S1>/Constant11' */
      break;
    }
  }

  /* End of Constant: '<S1>/Constant1' */
}

/* Function for Chart: '<Root>/PACING MODES' */
static void Pacemaker_AAIR(const boolean_T *D0)
{
  real_T tmp;

  /* Constant: '<S1>/Constant1' */
  if (Pacemaker_P.Constant1_Value != 7.0) {
    Pacemaker_DW.is_AAIR = Pacemaker_IN_NO_ACTIVE_CHILD;
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
  } else {
    switch (Pacemaker_DW.is_AAIR) {
     case Pacemaker_IN_AAI_CHARGE:
      Pacemaker_B.FRONTEND_CTRL = true;
      Pacemaker_B.ATR_PACE_CTRL = false;
      Pacemaker_B.PACE_CHARGE_CTRL = true;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;
      Pacemaker_B.ATR_GND_CTRL = true;
      if (*D0) {
        Pacemaker_DW.is_AAIR = Pacemaker_IN_AAI_REFRACTORY;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = false;
      } else {
        /* UnitDelay: '<Root>/Unit Delay' incorporates:
         *  Constant: '<S1>/Constant4'
         */
        tmp = 60000.0 / Pacemaker_DW.UnitDelay_DSTATE -
          Pacemaker_P.Constant4_Value;
        if ((Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(tmp)) ||
            (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(tmp -
              Pacemaker_P.Constant7_Value))) {
          Pacemaker_DW.is_AAIR = Pacemaker_IN_AAI_PACING;
          Pacemaker_DW.temporalCounter_i1 = 0U;
          Pacemaker_B.FRONTEND_CTRL = false;
          Pacemaker_B.PACE_CHARGE_CTRL = false;
          Pacemaker_B.ATR_PACE_CTRL = true;
          Pacemaker_B.ATR_GND_CTRL = false;
        }
      }
      break;

     case Pacemaker_IN_AAI_PACING:
      Pacemaker_B.FRONTEND_CTRL = false;
      Pacemaker_B.PACE_CHARGE_CTRL = false;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.ATR_PACE_CTRL = true;
      Pacemaker_B.ATR_GND_CTRL = false;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;

      /* Constant: '<S1>/Constant4' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant4_Value)) {
        Pacemaker_DW.is_AAIR = Pacemaker_IN_AAI_CHARGE;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = true;
        Pacemaker_B.ATR_PACE_CTRL = false;

        /* Constant: '<S1>/Desired Voltage' */
        Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
        Pacemaker_B.PACE_CHARGE_CTRL = true;
        Pacemaker_B.ATR_GND_CTRL = true;
      }
      break;

     case Pacemaker_IN_AAI_REFRACTORY:
      Pacemaker_B.FRONTEND_CTRL = false;

      /* Constant: '<S1>/Constant7' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant7_Value)) {
        Pacemaker_DW.is_AAIR = Pacemaker_IN_AAI_CHARGE;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = true;
        Pacemaker_B.ATR_PACE_CTRL = false;

        /* Constant: '<S1>/Desired Voltage' */
        Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
        Pacemaker_B.PACE_CHARGE_CTRL = true;
        Pacemaker_B.PACE_GND_CTRL = true;
        Pacemaker_B.Z_ATR_CTRL = false;
        Pacemaker_B.Z_VENT_CTRL = false;
        Pacemaker_B.ATR_GND_CTRL = true;
      }

      /* End of Constant: '<S1>/Constant7' */
      break;
    }
  }

  /* End of Constant: '<S1>/Constant1' */
}

/* Function for Chart: '<Root>/PACING MODES' */
static void Pacemaker_MODE_SELECT(void)
{
  /* Constant: '<S1>/Constant1' */
  if (Pacemaker_P.Constant1_Value == 1.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_AOO;
    Pacemaker_DW.is_AOO = Pacemaker_IN_AOO_CHARGE;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.ATR_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;
    Pacemaker_B.ATR_GND_CTRL = true;
  } else if (Pacemaker_P.Constant1_Value == 3.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_AAI;
    Pacemaker_DW.is_AAI = Pacemaker_IN_AAI_CHARGE;
    Pacemaker_B.FRONTEND_CTRL = true;
    Pacemaker_B.ATR_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.Z_ATR_CTRL = false;
    Pacemaker_B.Z_VENT_CTRL = false;
    Pacemaker_B.ATR_GND_CTRL = true;
  } else if (Pacemaker_P.Constant1_Value == 2.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_VOO;
    Pacemaker_DW.is_VOO = Pacemaker_IN_VOO_Charge;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.ATR_PACE_CTRL = false;
    Pacemaker_B.VENT_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.Z_ATR_CTRL = false;
    Pacemaker_B.Z_VENT_CTRL = false;
    Pacemaker_B.ATR_GND_CTRL = false;
    Pacemaker_B.VENT_GND_CTRL = true;
  } else if (Pacemaker_P.Constant1_Value == 4.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_VVI;
    Pacemaker_DW.is_VVI = Pacemaker_IN_VVI_CHARGE;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.FRONTEND_CTRL = true;
    Pacemaker_B.VENT_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;

    /* Constant: '<S1>/Constant5' */
    Pacemaker_B.VENT_CMP_REF_PWM = Pacemaker_P.Constant5_Value;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.Z_ATR_CTRL = false;
    Pacemaker_B.Z_VENT_CTRL = false;
    Pacemaker_B.VENT_GND_CTRL = true;
  } else if (Pacemaker_P.Constant1_Value == 5.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_AOOR;
    Pacemaker_DW.is_AOOR = Pacemaker_IN_AOO_CHARGE;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.ATR_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;
    Pacemaker_B.ATR_GND_CTRL = true;
  } else if (Pacemaker_P.Constant1_Value == 6.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_VOOR;
    Pacemaker_DW.is_VOOR = Pacemaker_IN_VOO_Charge;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.ATR_PACE_CTRL = false;
    Pacemaker_B.VENT_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.Z_ATR_CTRL = false;
    Pacemaker_B.Z_VENT_CTRL = false;
    Pacemaker_B.ATR_GND_CTRL = false;
    Pacemaker_B.VENT_GND_CTRL = true;
  } else if (Pacemaker_P.Constant1_Value == 8.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_VVIR;
    Pacemaker_DW.is_VVIR = Pacemaker_IN_VVI_CHARGE;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.FRONTEND_CTRL = true;
    Pacemaker_B.VENT_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;

    /* Constant: '<S1>/Constant5' */
    Pacemaker_B.VENT_CMP_REF_PWM = Pacemaker_P.Constant5_Value;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.Z_ATR_CTRL = false;
    Pacemaker_B.Z_VENT_CTRL = false;
    Pacemaker_B.VENT_GND_CTRL = true;
  } else if (Pacemaker_P.Constant1_Value == 7.0) {
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_AAIR;
    Pacemaker_DW.is_AAIR = Pacemaker_IN_AAI_CHARGE;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.FRONTEND_CTRL = true;
    Pacemaker_B.ATR_PACE_CTRL = false;

    /* Constant: '<S1>/Desired Voltage' */
    Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
    Pacemaker_B.PACE_CHARGE_CTRL = true;
    Pacemaker_B.PACE_GND_CTRL = true;
    Pacemaker_B.Z_ATR_CTRL = false;
    Pacemaker_B.Z_VENT_CTRL = false;
    Pacemaker_B.ATR_GND_CTRL = true;
  }

  /* End of Constant: '<S1>/Constant1' */
}

/* Function for Chart: '<Root>/PACING MODES' */
static void Pacemaker_VVI(const boolean_T *D1)
{
  boolean_T out;

  /* Constant: '<S1>/Constant1' */
  if (Pacemaker_P.Constant1_Value != 4.0) {
    Pacemaker_DW.is_VVI = Pacemaker_IN_NO_ACTIVE_CHILD;
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
  } else {
    switch (Pacemaker_DW.is_VVI) {
     case Pacemaker_IN_VVI_CHARGE:
      Pacemaker_B.FRONTEND_CTRL = true;
      Pacemaker_B.VENT_PACE_CTRL = false;
      Pacemaker_B.PACE_CHARGE_CTRL = true;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;
      Pacemaker_B.VENT_GND_CTRL = true;
      if (*D1) {
        /* Constant: '<S1>/Constant11' incorporates:
         *  Constant: '<S1>/Constant6'
         */
        out = (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
                Pacemaker_P.Constant11_Value - Pacemaker_P.Constant6_Value));
      } else {
        out = false;
      }

      if (out) {
        Pacemaker_DW.is_VVI = Pacemaker_IN_VVI_REFACTORY;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = false;
      } else {
        if (!*D1) {
          /* Constant: '<S1>/Constant11' incorporates:
           *  Constant: '<S1>/Constant4'
           */
          out = (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
                  Pacemaker_P.Constant11_Value - Pacemaker_P.Constant4_Value));
        } else {
          out = false;
        }

        if (out) {
          Pacemaker_DW.is_VVI = Pacemaker_IN_VVI_PACING;
          Pacemaker_DW.temporalCounter_i1 = 0U;
          Pacemaker_B.PACE_CHARGE_CTRL = false;
          Pacemaker_B.VENT_GND_CTRL = false;
          Pacemaker_B.VENT_PACE_CTRL = true;
        }
      }
      break;

     case Pacemaker_IN_VVI_PACING:
      Pacemaker_B.PACE_CHARGE_CTRL = false;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;
      Pacemaker_B.VENT_GND_CTRL = false;
      Pacemaker_B.VENT_PACE_CTRL = true;

      /* Constant: '<S1>/Constant4' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant4_Value)) {
        Pacemaker_DW.is_VVI = Pacemaker_IN_VVI_CHARGE;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = true;
        Pacemaker_B.VENT_PACE_CTRL = false;

        /* Constant: '<S1>/Desired Voltage' */
        Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
        Pacemaker_B.PACE_CHARGE_CTRL = true;

        /* Constant: '<S1>/Constant5' */
        Pacemaker_B.VENT_CMP_REF_PWM = Pacemaker_P.Constant5_Value;
        Pacemaker_B.VENT_GND_CTRL = true;
      }
      break;

     case Pacemaker_IN_VVI_REFACTORY:
      Pacemaker_B.FRONTEND_CTRL = false;

      /* Constant: '<S1>/Constant6' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant6_Value)) {
        Pacemaker_DW.is_VVI = Pacemaker_IN_VVI_CHARGE;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = true;
        Pacemaker_B.VENT_PACE_CTRL = false;

        /* Constant: '<S1>/Desired Voltage' */
        Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
        Pacemaker_B.PACE_CHARGE_CTRL = true;

        /* Constant: '<S1>/Constant5' */
        Pacemaker_B.VENT_CMP_REF_PWM = Pacemaker_P.Constant5_Value;
        Pacemaker_B.PACE_GND_CTRL = true;
        Pacemaker_B.Z_ATR_CTRL = false;
        Pacemaker_B.Z_VENT_CTRL = false;
        Pacemaker_B.VENT_GND_CTRL = true;
      }
      break;
    }
  }

  /* End of Constant: '<S1>/Constant1' */
}

/* Function for Chart: '<Root>/PACING MODES' */
static void Pacemaker_VVIR(const boolean_T *D1)
{
  boolean_T out;

  /* Constant: '<S1>/Constant1' */
  if (Pacemaker_P.Constant1_Value != 8.0) {
    Pacemaker_DW.is_VVIR = Pacemaker_IN_NO_ACTIVE_CHILD;
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
  } else {
    switch (Pacemaker_DW.is_VVIR) {
     case Pacemaker_IN_VVI_CHARGE:
      Pacemaker_B.FRONTEND_CTRL = true;
      Pacemaker_B.VENT_PACE_CTRL = false;
      Pacemaker_B.PACE_CHARGE_CTRL = true;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;
      Pacemaker_B.VENT_GND_CTRL = true;
      if (*D1) {
        /* UnitDelay: '<Root>/Unit Delay' incorporates:
         *  Constant: '<S1>/Constant6'
         */
        out = (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
                Pacemaker_DW.UnitDelay_DSTATE - Pacemaker_P.Constant6_Value));
      } else {
        out = false;
      }

      if (out) {
        Pacemaker_DW.is_VVIR = Pacemaker_IN_VVI_REFACTORY;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = false;
      } else {
        if (!*D1) {
          /* UnitDelay: '<Root>/Unit Delay' incorporates:
           *  Constant: '<S1>/Constant4'
           */
          out = (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
                  Pacemaker_DW.UnitDelay_DSTATE - Pacemaker_P.Constant4_Value));
        } else {
          out = false;
        }

        if (out) {
          Pacemaker_DW.is_VVIR = Pacemaker_IN_VVI_PACING;
          Pacemaker_DW.temporalCounter_i1 = 0U;
          Pacemaker_B.PACE_CHARGE_CTRL = false;
          Pacemaker_B.VENT_GND_CTRL = false;
          Pacemaker_B.VENT_PACE_CTRL = true;
        }
      }
      break;

     case Pacemaker_IN_VVI_PACING:
      Pacemaker_B.PACE_CHARGE_CTRL = false;
      Pacemaker_B.PACE_GND_CTRL = true;
      Pacemaker_B.Z_ATR_CTRL = false;
      Pacemaker_B.Z_VENT_CTRL = false;
      Pacemaker_B.VENT_GND_CTRL = false;
      Pacemaker_B.VENT_PACE_CTRL = true;

      /* Constant: '<S1>/Constant4' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant4_Value)) {
        Pacemaker_DW.is_VVIR = Pacemaker_IN_VVI_CHARGE;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = true;
        Pacemaker_B.VENT_PACE_CTRL = false;

        /* Constant: '<S1>/Desired Voltage' */
        Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
        Pacemaker_B.PACE_CHARGE_CTRL = true;

        /* Constant: '<S1>/Constant5' */
        Pacemaker_B.VENT_CMP_REF_PWM = Pacemaker_P.Constant5_Value;
        Pacemaker_B.VENT_GND_CTRL = true;
      }
      break;

     case Pacemaker_IN_VVI_REFACTORY:
      Pacemaker_B.FRONTEND_CTRL = false;

      /* Constant: '<S1>/Constant6' */
      if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
          (Pacemaker_P.Constant6_Value)) {
        Pacemaker_DW.is_VVIR = Pacemaker_IN_VVI_CHARGE;
        Pacemaker_DW.temporalCounter_i1 = 0U;
        Pacemaker_B.FRONTEND_CTRL = true;
        Pacemaker_B.VENT_PACE_CTRL = false;

        /* Constant: '<S1>/Desired Voltage' */
        Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
        Pacemaker_B.PACE_CHARGE_CTRL = true;

        /* Constant: '<S1>/Constant5' */
        Pacemaker_B.VENT_CMP_REF_PWM = Pacemaker_P.Constant5_Value;
        Pacemaker_B.PACE_GND_CTRL = true;
        Pacemaker_B.Z_ATR_CTRL = false;
        Pacemaker_B.Z_VENT_CTRL = false;
        Pacemaker_B.VENT_GND_CTRL = true;
      }
      break;
    }
  }

  /* End of Constant: '<S1>/Constant1' */
}

static void Pacemaker_SystemCore_setup(freedomk64f_fxos8700_Pacemake_T *obj)
{
  MW_I2C_Mode_Type ModeType;
  uint32_T i2cname;
  uint8_T b_SwappedDataBytes[2];
  uint8_T b_RegisterValue;
  uint8_T status;
  obj->isInitialized = 1;
  ModeType = MW_I2C_MASTER;
  i2cname = 0;
  obj->i2cobj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, ModeType);
  obj->i2cobj.BusSpeed = 100000U;
  MW_I2C_SetBusSpeed(obj->i2cobj.MW_I2C_HANDLE, obj->i2cobj.BusSpeed);
  b_SwappedDataBytes[0] = 43U;
  b_SwappedDataBytes[1] = 64U;
  MW_I2C_MasterWrite(obj->i2cobj.MW_I2C_HANDLE, 29U, &b_SwappedDataBytes[0], 2U,
                     false, false);
  OSA_TimeDelay(500U);
  status = 42U;
  status = MW_I2C_MasterWrite(obj->i2cobj.MW_I2C_HANDLE, 29U, &status, 1U, true,
    false);
  if (status == 0) {
    MW_I2C_MasterRead(obj->i2cobj.MW_I2C_HANDLE, 29U, &status, 1U, false, true);
    memcpy((void *)&b_RegisterValue, (void *)&status, (size_t)1 * sizeof(uint8_T));
  } else {
    b_RegisterValue = 0U;
  }

  b_SwappedDataBytes[0] = 42U;
  b_SwappedDataBytes[1] = (uint8_T)(b_RegisterValue & 254);
  MW_I2C_MasterWrite(obj->i2cobj.MW_I2C_HANDLE, 29U, &b_SwappedDataBytes[0], 2U,
                     false, false);
  b_SwappedDataBytes[0] = 14U;
  b_SwappedDataBytes[1] = 1U;
  MW_I2C_MasterWrite(obj->i2cobj.MW_I2C_HANDLE, 29U, &b_SwappedDataBytes[0], 2U,
                     false, false);
  b_SwappedDataBytes[0] = 91U;
  b_SwappedDataBytes[1] = 0U;
  MW_I2C_MasterWrite(obj->i2cobj.MW_I2C_HANDLE, 29U, &b_SwappedDataBytes[0], 2U,
                     false, false);
  b_SwappedDataBytes[0] = 42U;
  b_SwappedDataBytes[1] = 33U;
  MW_I2C_MasterWrite(obj->i2cobj.MW_I2C_HANDLE, 29U, &b_SwappedDataBytes[0], 2U,
                     false, false);
  obj->isSetupComplete = true;
}

static void Pacemaker_SystemCore_setup_j(dsp_simulink_MovingAverage_Pa_T *obj)
{
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->NumChannels = 1;
  obj->FrameLength = 1;
  obj->_pobj0.isInitialized = 0;
  obj->_pobj0.isInitialized = 0;
  obj->pStatistic = &obj->_pobj0;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/* Model step function */
void Pacemaker_step(void)
{
  g_dsp_internal_SlidingWindowA_T *obj;
  real_T rtb_Converttoms2_idx_0;
  real_T rtb_Converttoms2_idx_1;
  real_T rtb_Converttoms2_idx_2;
  int32_T i;
  int16_T b_RegisterValue[3];
  uint8_T output_raw[6];
  uint8_T b_x[2];
  uint8_T y[2];
  uint8_T status;
  boolean_T D0;
  boolean_T D1;

  /* MATLABSystem: '<S5>/FXOS8700 6-Axes Sensor' */
  if (Pacemaker_DW.obj_m.SampleTime !=
      Pacemaker_P.FXOS87006AxesSensor_SampleTime) {
    Pacemaker_DW.obj_m.SampleTime = Pacemaker_P.FXOS87006AxesSensor_SampleTime;
  }

  status = 1U;
  status = MW_I2C_MasterWrite(Pacemaker_DW.obj_m.i2cobj.MW_I2C_HANDLE, 29U,
    &status, 1U, true, false);
  if (status == 0) {
    MW_I2C_MasterRead(Pacemaker_DW.obj_m.i2cobj.MW_I2C_HANDLE, 29U, &output_raw
                      [0], 6U, false, true);
    memcpy((void *)&b_RegisterValue[0], (void *)&output_raw[0], (size_t)3 *
           sizeof(int16_T));
    memcpy((void *)&y[0], (void *)&b_RegisterValue[0], (size_t)2 * sizeof
           (uint8_T));
    b_x[0] = y[1];
    b_x[1] = y[0];
    memcpy((void *)&b_RegisterValue[0], (void *)&b_x[0], (size_t)1 * sizeof
           (int16_T));
    memcpy((void *)&y[0], (void *)&b_RegisterValue[1], (size_t)2 * sizeof
           (uint8_T));
    b_x[0] = y[1];
    b_x[1] = y[0];
    memcpy((void *)&b_RegisterValue[1], (void *)&b_x[0], (size_t)1 * sizeof
           (int16_T));
    memcpy((void *)&y[0], (void *)&b_RegisterValue[2], (size_t)2 * sizeof
           (uint8_T));
    b_x[0] = y[1];
    b_x[1] = y[0];
    memcpy((void *)&b_RegisterValue[2], (void *)&b_x[0], (size_t)1 * sizeof
           (int16_T));
  } else {
    b_RegisterValue[0] = 0;
    b_RegisterValue[1] = 0;
    b_RegisterValue[2] = 0;
  }

  /* Gain: '<S5>/Convert to m//s^2' incorporates:
   *  MATLABSystem: '<S5>/FXOS8700 6-Axes Sensor'
   */
  rtb_Converttoms2_idx_0 = (real_T)(int16_T)(b_RegisterValue[0] >> 2) * 2.0 *
    0.244 / 1000.0 * Pacemaker_P.Converttoms2_Gain;
  rtb_Converttoms2_idx_1 = (real_T)(int16_T)(b_RegisterValue[1] >> 2) * 2.0 *
    0.244 / 1000.0 * Pacemaker_P.Converttoms2_Gain;
  rtb_Converttoms2_idx_2 = (real_T)(int16_T)(b_RegisterValue[2] >> 2) * 2.0 *
    0.244 / 1000.0 * Pacemaker_P.Converttoms2_Gain;

  /* Sum: '<S5>/Subtract' incorporates:
   *  Constant: '<S5>/ gravitational  acceleration'
   *  Math: '<S5>/Magnitude Squared'
   *  Math: '<S5>/Magnitude Squared1'
   *  Math: '<S5>/Magnitude Squared2'
   *  Sqrt: '<S5>/Sqrt'
   *  Sum: '<S5>/Add'
   *
   * About '<S5>/Magnitude Squared':
   *  Operator: magnitude^2
   *
   * About '<S5>/Magnitude Squared1':
   *  Operator: magnitude^2
   *
   * About '<S5>/Magnitude Squared2':
   *  Operator: magnitude^2
   */
  rtb_Converttoms2_idx_0 = sqrt((rtb_Converttoms2_idx_0 * rtb_Converttoms2_idx_0
    + rtb_Converttoms2_idx_1 * rtb_Converttoms2_idx_1) + rtb_Converttoms2_idx_2 *
    rtb_Converttoms2_idx_2) - Pacemaker_P.gravitationalacceleration_Value;

  /* MATLABSystem: '<S5>/Moving Average' */
  if (Pacemaker_DW.obj.TunablePropsChanged) {
    Pacemaker_DW.obj.TunablePropsChanged = false;
  }

  obj = Pacemaker_DW.obj.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->pCumSum = 0.0;
    for (i = 0; i < 499; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    obj->pCumSum = 0.0;
    for (i = 0; i < 499; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
  }

  rtb_Converttoms2_idx_1 = obj->pCumRevIndex;
  rtb_Converttoms2_idx_2 = obj->pCumSum;
  for (i = 0; i < 499; i++) {
    Pacemaker_B.csumrev[i] = obj->pCumSumRev[i];
  }

  Pacemaker_B.modValueRev = obj->pModValueRev;
  Pacemaker_B.z = 0.0;
  Pacemaker_B.rtb_MovingAverage_m = 0.0;
  rtb_Converttoms2_idx_2 += rtb_Converttoms2_idx_0;
  if (Pacemaker_B.modValueRev == 0.0) {
    Pacemaker_B.z = Pacemaker_B.csumrev[(int32_T)rtb_Converttoms2_idx_1 - 1] +
      rtb_Converttoms2_idx_2;
  }

  Pacemaker_B.csumrev[(int32_T)rtb_Converttoms2_idx_1 - 1] =
    rtb_Converttoms2_idx_0;
  if (rtb_Converttoms2_idx_1 != 499.0) {
    rtb_Converttoms2_idx_1++;
  } else {
    rtb_Converttoms2_idx_1 = 1.0;
    rtb_Converttoms2_idx_2 = 0.0;
    for (i = 497; i >= 0; i--) {
      Pacemaker_B.csumrev[i] += Pacemaker_B.csumrev[i + 1];
    }
  }

  if (Pacemaker_B.modValueRev == 0.0) {
    Pacemaker_B.rtb_MovingAverage_m = Pacemaker_B.z / 500.0;
  }

  obj->pCumSum = rtb_Converttoms2_idx_2;
  for (i = 0; i < 499; i++) {
    obj->pCumSumRev[i] = Pacemaker_B.csumrev[i];
  }

  obj->pCumRevIndex = rtb_Converttoms2_idx_1;
  if (Pacemaker_B.modValueRev > 0.0) {
    obj->pModValueRev = Pacemaker_B.modValueRev - 1.0;
  } else {
    obj->pModValueRev = 0.0;
  }

  /* Outputs for Atomic SubSystem: '<S4>/Rate Modulation' */
  /* MATLAB Function: '<S6>/Activity Response' incorporates:
   *  Constant: '<S1>/Constant11'
   *  Constant: '<S1>/Constant3'
   *  Constant: '<S1>/Constant9'
   *  MATLABSystem: '<S5>/Moving Average'
   */
  if (Pacemaker_B.rtb_MovingAverage_m > Pacemaker_P.Constant9_Value) {
    rtb_Converttoms2_idx_1 = (Pacemaker_B.rtb_MovingAverage_m -
      Pacemaker_P.Constant9_Value) * Pacemaker_P.Constant3_Value +
      Pacemaker_P.Constant11_Value;
  } else {
    rtb_Converttoms2_idx_1 = Pacemaker_P.Constant11_Value;
  }

  /* MinMax: '<S6>/Min' incorporates:
   *  Constant: '<S1>/Constant2'
   *  MATLAB Function: '<S6>/Activity Response'
   */
  if ((!(rtb_Converttoms2_idx_1 <= Pacemaker_P.Constant2_Value)) && (!rtIsNaN
       (Pacemaker_P.Constant2_Value))) {
    rtb_Converttoms2_idx_1 = Pacemaker_P.Constant2_Value;
  }

  /* End of MinMax: '<S6>/Min' */

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S1>/Constant11'
   */
  if ((!(rtb_Converttoms2_idx_1 >= Pacemaker_P.Constant11_Value)) && (!rtIsNaN
       (Pacemaker_P.Constant11_Value))) {
    rtb_Converttoms2_idx_1 = Pacemaker_P.Constant11_Value;
  }

  /* End of MinMax: '<S6>/Max' */
  /* End of Outputs for SubSystem: '<S4>/Rate Modulation' */

  /* InitialCondition: '<Root>/IC' */
  if (Pacemaker_DW.IC_FirstOutputTime) {
    Pacemaker_DW.IC_FirstOutputTime = false;

    /* MATLAB Function: '<S4>/Time Response' incorporates:
     *  InitialCondition: '<Root>/IC'
     */
    Pacemaker_DW.UnitDelay_DSTATE = Pacemaker_P.IC_Value;
  }

  /* End of InitialCondition: '<Root>/IC' */

  /* MATLAB Function: '<S4>/Time Response' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant11'
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S1>/Constant8'
   */
  if (rtb_Converttoms2_idx_1 > Pacemaker_DW.UnitDelay_DSTATE) {
    rtb_Converttoms2_idx_2 = (Pacemaker_P.Constant2_Value -
      Pacemaker_P.Constant11_Value) / (400.0 * Pacemaker_P.Constant_Value);
    rtb_Converttoms2_idx_0 = rtb_Converttoms2_idx_2 / 4.0;
  } else {
    rtb_Converttoms2_idx_2 = (Pacemaker_P.Constant2_Value -
      Pacemaker_P.Constant11_Value) / (400.0 * Pacemaker_P.Constant8_Value);
    rtb_Converttoms2_idx_0 = rtb_Converttoms2_idx_2 / 2.0;
  }

  rtb_Converttoms2_idx_1 -= Pacemaker_DW.UnitDelay_DSTATE;
  rtb_Converttoms2_idx_2 *= rtb_Converttoms2_idx_1 /
    (Pacemaker_P.Constant2_Value - Pacemaker_P.Constant11_Value);
  if (fabs(rtb_Converttoms2_idx_2) < rtb_Converttoms2_idx_0) {
    Pacemaker_B.modValueRev = fabs(rtb_Converttoms2_idx_1);
    if (Pacemaker_B.modValueRev > 0.01) {
      rtb_Converttoms2_idx_2 = rtb_Converttoms2_idx_0 * rtb_Converttoms2_idx_1 /
        Pacemaker_B.modValueRev;
    }
  }

  Pacemaker_DW.UnitDelay_DSTATE += rtb_Converttoms2_idx_2;

  /* MinMax: '<S4>/Min' incorporates:
   *  Constant: '<S1>/Constant2'
   */
  if ((Pacemaker_P.Constant2_Value <= Pacemaker_DW.UnitDelay_DSTATE) || rtIsNaN
      (Pacemaker_DW.UnitDelay_DSTATE)) {
    /* MATLAB Function: '<S4>/Time Response' */
    Pacemaker_DW.UnitDelay_DSTATE = Pacemaker_P.Constant2_Value;
  }

  /* End of MinMax: '<S4>/Min' */

  /* MinMax: '<S4>/Max' incorporates:
   *  Constant: '<S1>/Constant11'
   */
  if ((Pacemaker_P.Constant11_Value >= Pacemaker_DW.UnitDelay_DSTATE) || rtIsNaN
      (Pacemaker_DW.UnitDelay_DSTATE)) {
    /* MATLAB Function: '<S4>/Time Response' */
    Pacemaker_DW.UnitDelay_DSTATE = Pacemaker_P.Constant11_Value;
  }

  /* End of MinMax: '<S4>/Max' */

  /* MATLABSystem: '<S5>/D1' */
  if (Pacemaker_DW.obj_my.SampleTime != Pacemaker_P.D1_SampleTime) {
    Pacemaker_DW.obj_my.SampleTime = Pacemaker_P.D1_SampleTime;
  }

  /* MATLABSystem: '<S5>/D1' */
  D1 = MW_digitalIO_read(Pacemaker_DW.obj_my.MW_DIGITALIO_HANDLE);

  /* MATLABSystem: '<S5>/D0' */
  if (Pacemaker_DW.obj_d.SampleTime != Pacemaker_P.D0_SampleTime) {
    Pacemaker_DW.obj_d.SampleTime = Pacemaker_P.D0_SampleTime;
  }

  /* MATLABSystem: '<S5>/D0' */
  D0 = MW_digitalIO_read(Pacemaker_DW.obj_d.MW_DIGITALIO_HANDLE);

  /* Chart: '<Root>/PACING MODES' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant11'
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S1>/Desired Voltage'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  if (Pacemaker_DW.temporalCounter_i1 < MAX_uint32_T) {
    Pacemaker_DW.temporalCounter_i1++;
  }

  if (Pacemaker_DW.is_active_c1_Pacemaker == 0U) {
    Pacemaker_DW.is_active_c1_Pacemaker = 1U;
    Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_INIT;
    Pacemaker_DW.temporalCounter_i1 = 0U;
    Pacemaker_B.VENT_PACE_CTRL = false;
    Pacemaker_B.PACE_GND_CTRL = false;
    Pacemaker_B.ATR_GND_CTRL = false;
    Pacemaker_B.ATR_PACE_CTRL = false;
    Pacemaker_B.VENT_GND_CTRL = false;
  } else {
    switch (Pacemaker_DW.is_c1_Pacemaker) {
     case Pacemaker_IN_AAI:
      Pacemaker_AAI(&D0);
      break;

     case Pacemaker_IN_AAIR:
      Pacemaker_AAIR(&D0);
      break;

     case Pacemaker_IN_AOO:
      if (Pacemaker_P.Constant1_Value != 1.0) {
        Pacemaker_DW.is_AOO = Pacemaker_IN_NO_ACTIVE_CHILD;
        Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
      } else {
        switch (Pacemaker_DW.is_AOO) {
         case Pacemaker_IN_AOO_CHARGE:
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.ATR_PACE_CTRL = false;
          Pacemaker_B.PACE_CHARGE_CTRL = true;
          Pacemaker_B.ATR_GND_CTRL = true;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
               Pacemaker_P.Constant11_Value - Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_AOO = Pacemaker_IN_AOO_PACING;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.PACE_CHARGE_CTRL = false;
            Pacemaker_B.ATR_PACE_CTRL = true;
            Pacemaker_B.ATR_GND_CTRL = false;
            Pacemaker_B.Z_ATR_CTRL = false;
            Pacemaker_B.Z_VENT_CTRL = false;
          }
          break;

         case Pacemaker_IN_AOO_PACING:
          Pacemaker_B.PACE_CHARGE_CTRL = false;
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.ATR_PACE_CTRL = true;
          Pacemaker_B.ATR_GND_CTRL = false;
          Pacemaker_B.Z_ATR_CTRL = false;
          Pacemaker_B.Z_VENT_CTRL = false;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
              (Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_AOO = Pacemaker_IN_AOO_CHARGE;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.ATR_PACE_CTRL = false;
            Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
            Pacemaker_B.PACE_CHARGE_CTRL = true;
            Pacemaker_B.ATR_GND_CTRL = true;
          }
          break;
        }
      }
      break;

     case Pacemaker_IN_AOOR:
      if (Pacemaker_P.Constant1_Value != 5.0) {
        Pacemaker_DW.is_AOOR = Pacemaker_IN_NO_ACTIVE_CHILD;
        Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
      } else {
        switch (Pacemaker_DW.is_AOOR) {
         case Pacemaker_IN_AOO_CHARGE:
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.ATR_PACE_CTRL = false;
          Pacemaker_B.PACE_CHARGE_CTRL = true;
          Pacemaker_B.ATR_GND_CTRL = true;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
               Pacemaker_DW.UnitDelay_DSTATE - Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_AOOR = Pacemaker_IN_AOO_PACING;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.PACE_CHARGE_CTRL = false;
            Pacemaker_B.ATR_PACE_CTRL = true;
            Pacemaker_B.ATR_GND_CTRL = false;
            Pacemaker_B.Z_ATR_CTRL = false;
            Pacemaker_B.Z_VENT_CTRL = false;
          }
          break;

         case Pacemaker_IN_AOO_PACING:
          Pacemaker_B.PACE_CHARGE_CTRL = false;
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.ATR_PACE_CTRL = true;
          Pacemaker_B.ATR_GND_CTRL = false;
          Pacemaker_B.Z_ATR_CTRL = false;
          Pacemaker_B.Z_VENT_CTRL = false;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
              (Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_AOOR = Pacemaker_IN_AOO_CHARGE;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.ATR_PACE_CTRL = false;
            Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
            Pacemaker_B.PACE_CHARGE_CTRL = true;
            Pacemaker_B.ATR_GND_CTRL = true;
          }
          break;
        }
      }
      break;

     case Pacemaker_IN_INIT:
      Pacemaker_B.VENT_PACE_CTRL = false;
      Pacemaker_B.PACE_GND_CTRL = false;
      Pacemaker_B.ATR_GND_CTRL = false;
      Pacemaker_B.ATR_PACE_CTRL = false;
      Pacemaker_B.VENT_GND_CTRL = false;
      if (Pacemaker_DW.temporalCounter_i1 >= 100U) {
        Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
      }
      break;

     case Pacemaker_IN_MODE_SELECT:
      Pacemaker_MODE_SELECT();
      break;

     case Pacemaker_IN_VOO:
      if (Pacemaker_P.Constant1_Value != 2.0) {
        Pacemaker_DW.is_VOO = Pacemaker_IN_NO_ACTIVE_CHILD;
        Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
      } else {
        switch (Pacemaker_DW.is_VOO) {
         case Pacemaker_IN_VOO_Charge:
          Pacemaker_B.ATR_PACE_CTRL = false;
          Pacemaker_B.VENT_PACE_CTRL = false;
          Pacemaker_B.PACE_CHARGE_CTRL = true;
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.Z_ATR_CTRL = false;
          Pacemaker_B.Z_VENT_CTRL = false;
          Pacemaker_B.ATR_GND_CTRL = false;
          Pacemaker_B.VENT_GND_CTRL = true;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
               Pacemaker_P.Constant11_Value - Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_VOO = Pacemaker_IN_VOO_Pace;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.PACE_CHARGE_CTRL = false;
            Pacemaker_B.VENT_GND_CTRL = false;
            Pacemaker_B.VENT_PACE_CTRL = true;
          }
          break;

         case Pacemaker_IN_VOO_Pace:
          Pacemaker_B.PACE_CHARGE_CTRL = false;
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.ATR_PACE_CTRL = false;
          Pacemaker_B.ATR_GND_CTRL = false;
          Pacemaker_B.Z_ATR_CTRL = false;
          Pacemaker_B.Z_VENT_CTRL = false;
          Pacemaker_B.VENT_GND_CTRL = false;
          Pacemaker_B.VENT_PACE_CTRL = true;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
              (Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_VOO = Pacemaker_IN_VOO_Charge;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.VENT_PACE_CTRL = false;
            Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
            Pacemaker_B.PACE_CHARGE_CTRL = true;
            Pacemaker_B.VENT_GND_CTRL = true;
          }
          break;
        }
      }
      break;

     case Pacemaker_IN_VOOR:
      if (Pacemaker_P.Constant1_Value != 6.0) {
        Pacemaker_DW.is_VOOR = Pacemaker_IN_NO_ACTIVE_CHILD;
        Pacemaker_DW.is_c1_Pacemaker = Pacemaker_IN_MODE_SELECT;
      } else {
        switch (Pacemaker_DW.is_VOOR) {
         case Pacemaker_IN_VOO_Charge:
          Pacemaker_B.ATR_PACE_CTRL = false;
          Pacemaker_B.VENT_PACE_CTRL = false;
          Pacemaker_B.PACE_CHARGE_CTRL = true;
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.Z_ATR_CTRL = false;
          Pacemaker_B.Z_VENT_CTRL = false;
          Pacemaker_B.ATR_GND_CTRL = false;
          Pacemaker_B.VENT_GND_CTRL = true;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil(60000.0 /
               Pacemaker_DW.UnitDelay_DSTATE - Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_VOOR = Pacemaker_IN_VOO_Pace;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.PACE_CHARGE_CTRL = false;
            Pacemaker_B.VENT_GND_CTRL = false;
            Pacemaker_B.VENT_PACE_CTRL = true;
          }
          break;

         case Pacemaker_IN_VOO_Pace:
          Pacemaker_B.PACE_CHARGE_CTRL = false;
          Pacemaker_B.PACE_GND_CTRL = true;
          Pacemaker_B.ATR_PACE_CTRL = false;
          Pacemaker_B.ATR_GND_CTRL = false;
          Pacemaker_B.Z_ATR_CTRL = false;
          Pacemaker_B.Z_VENT_CTRL = false;
          Pacemaker_B.VENT_GND_CTRL = false;
          Pacemaker_B.VENT_PACE_CTRL = true;
          if (Pacemaker_DW.temporalCounter_i1 >= (uint32_T)ceil
              (Pacemaker_P.Constant4_Value)) {
            Pacemaker_DW.is_VOOR = Pacemaker_IN_VOO_Charge;
            Pacemaker_DW.temporalCounter_i1 = 0U;
            Pacemaker_B.VENT_PACE_CTRL = false;
            Pacemaker_B.PACING_REF_PWM = Pacemaker_P.DesiredVoltage_Value;
            Pacemaker_B.PACE_CHARGE_CTRL = true;
            Pacemaker_B.VENT_GND_CTRL = true;
          }
          break;
        }
      }
      break;

     case Pacemaker_IN_VVI:
      Pacemaker_VVI(&D1);
      break;

     case Pacemaker_IN_VVIR:
      Pacemaker_VVIR(&D1);
      break;
    }
  }

  /* End of Chart: '<Root>/PACING MODES' */

  /* MATLABSystem: '<S2>/Digital Write3' */
  MW_digitalIO_write(Pacemaker_DW.obj_h.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.PACE_CHARGE_CTRL);

  /* MATLABSystem: '<S2>/Digital Write' */
  MW_digitalIO_write(Pacemaker_DW.obj_l5.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.Z_ATR_CTRL);

  /* MATLABSystem: '<S2>/PWM Output2' incorporates:
   *  Gain: '<S2>/Convert voltage  to PWM duty2'
   */
  MW_PWM_SetDutyCycle(Pacemaker_DW.obj_j.MW_PWM_HANDLE,
                      Pacemaker_P.ConvertvoltagetoPWMduty2_Gain *
                      Pacemaker_B.PACING_REF_PWM);

  /* MATLABSystem: '<S2>/Digital Write5' */
  MW_digitalIO_write(Pacemaker_DW.obj_l.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.Z_VENT_CTRL);

  /* MATLABSystem: '<S2>/Digital Write6' */
  MW_digitalIO_write(Pacemaker_DW.obj_o.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.ATR_PACE_CTRL);

  /* MATLABSystem: '<S2>/Digital Write7' */
  MW_digitalIO_write(Pacemaker_DW.obj_m1.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.VENT_PACE_CTRL);

  /* MATLABSystem: '<S2>/Digital Write8' */
  MW_digitalIO_write(Pacemaker_DW.obj_c.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.PACE_GND_CTRL);

  /* MATLABSystem: '<S2>/Digital Write9' */
  MW_digitalIO_write(Pacemaker_DW.obj_k.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.ATR_GND_CTRL);

  /* MATLABSystem: '<S2>/Digital Write10' */
  MW_digitalIO_write(Pacemaker_DW.obj_p.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.VENT_GND_CTRL);

  /* MATLABSystem: '<S2>/Digital Write11' */
  MW_digitalIO_write(Pacemaker_DW.obj_h5.MW_DIGITALIO_HANDLE,
                     Pacemaker_B.FRONTEND_CTRL);

  /* MATLABSystem: '<S2>/PWM Output' incorporates:
   *  Gain: '<S2>/Convert voltage  to PWM duty1'
   */
  MW_PWM_SetDutyCycle(Pacemaker_DW.obj_e.MW_PWM_HANDLE,
                      Pacemaker_P.ConvertvoltagetoPWMduty1_Gain *
                      Pacemaker_B.VENT_CMP_REF_PWM);

  /* MATLABSystem: '<S2>/PWM Output1' incorporates:
   *  Constant: '<S1>/Constant10'
   *  Gain: '<S2>/Convert voltage  to PWM duty'
   */
  MW_PWM_SetDutyCycle(Pacemaker_DW.obj_a.MW_PWM_HANDLE,
                      Pacemaker_P.ConvertvoltagetoPWMduty_Gain *
                      Pacemaker_P.Constant10_Value);
}

/* Model initialize function */
void Pacemaker_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    freedomk64f_DigitalRead_Pacem_T *obj_0;
    freedomk64f_DigitalWrite_Pace_T *obj_1;
    freedomk64f_PWMOutput_Pacemak_T *obj_2;
    g_dsp_internal_SlidingWindowA_T *obj;
    int32_T i;

    /* Start for InitialCondition: '<Root>/IC' */
    Pacemaker_DW.IC_FirstOutputTime = true;

    /* InitializeConditions for MATLAB Function: '<S4>/Time Response' incorporates:
     *  UnitDelay: '<Root>/Unit Delay'
     */
    Pacemaker_DW.UnitDelay_DSTATE = Pacemaker_P.UnitDelay_InitialCondition;

    /* Start for MATLABSystem: '<S5>/FXOS8700 6-Axes Sensor' */
    Pacemaker_DW.obj_m.isInitialized = 0;
    Pacemaker_DW.obj_m.i2cobj.isInitialized = 0;
    Pacemaker_DW.obj_m.i2cobj.matlabCodegenIsDeleted = false;
    Pacemaker_DW.obj_m.matlabCodegenIsDeleted = false;
    Pacemaker_DW.obj_m.SampleTime = Pacemaker_P.FXOS87006AxesSensor_SampleTime;
    Pacemaker_SystemCore_setup(&Pacemaker_DW.obj_m);

    /* Start for MATLABSystem: '<S5>/Moving Average' */
    Pacemaker_DW.obj.isInitialized = 0;
    Pacemaker_DW.obj.NumChannels = -1;
    Pacemaker_DW.obj.FrameLength = -1;
    Pacemaker_DW.obj.matlabCodegenIsDeleted = false;
    Pacemaker_SystemCore_setup_j(&Pacemaker_DW.obj);

    /* InitializeConditions for MATLABSystem: '<S5>/Moving Average' */
    obj = Pacemaker_DW.obj.pStatistic;
    if (obj->isInitialized == 1) {
      obj->pCumSum = 0.0;
      for (i = 0; i < 499; i++) {
        obj->pCumSumRev[i] = 0.0;
      }

      obj->pCumRevIndex = 1.0;
      obj->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<S5>/Moving Average' */

    /* Start for MATLABSystem: '<S5>/D1' */
    Pacemaker_DW.obj_my.matlabCodegenIsDeleted = false;
    Pacemaker_DW.obj_my.SampleTime = Pacemaker_P.D1_SampleTime;
    obj_0 = &Pacemaker_DW.obj_my;
    Pacemaker_DW.obj_my.isInitialized = 1;
    obj_0->MW_DIGITALIO_HANDLE = MW_digitalIO_open(1U, 0);
    Pacemaker_DW.obj_my.isSetupComplete = true;

    /* Start for MATLABSystem: '<S5>/D0' */
    Pacemaker_DW.obj_d.matlabCodegenIsDeleted = false;
    Pacemaker_DW.obj_d.SampleTime = Pacemaker_P.D0_SampleTime;
    obj_0 = &Pacemaker_DW.obj_d;
    Pacemaker_DW.obj_d.isInitialized = 1;
    obj_0->MW_DIGITALIO_HANDLE = MW_digitalIO_open(0U, 0);
    Pacemaker_DW.obj_d.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write3' */
    Pacemaker_DW.obj_h.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_h;
    Pacemaker_DW.obj_h.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(2U, 1);
    Pacemaker_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write' */
    Pacemaker_DW.obj_l5.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_l5;
    Pacemaker_DW.obj_l5.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(4U, 1);
    Pacemaker_DW.obj_l5.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/PWM Output2' */
    Pacemaker_DW.obj_j.matlabCodegenIsDeleted = false;
    obj_2 = &Pacemaker_DW.obj_j;
    Pacemaker_DW.obj_j.isInitialized = 1;
    obj_2->MW_PWM_HANDLE = MW_PWM_Open(5U, 2000.0, 0.0);
    MW_PWM_Start(Pacemaker_DW.obj_j.MW_PWM_HANDLE);
    Pacemaker_DW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write5' */
    Pacemaker_DW.obj_l.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_l;
    Pacemaker_DW.obj_l.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(7U, 1);
    Pacemaker_DW.obj_l.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write6' */
    Pacemaker_DW.obj_o.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_o;
    Pacemaker_DW.obj_o.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(8U, 1);
    Pacemaker_DW.obj_o.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write7' */
    Pacemaker_DW.obj_m1.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_m1;
    Pacemaker_DW.obj_m1.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(9U, 1);
    Pacemaker_DW.obj_m1.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write8' */
    Pacemaker_DW.obj_c.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_c;
    Pacemaker_DW.obj_c.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(10U, 1);
    Pacemaker_DW.obj_c.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write9' */
    Pacemaker_DW.obj_k.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_k;
    Pacemaker_DW.obj_k.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(11U, 1);
    Pacemaker_DW.obj_k.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write10' */
    Pacemaker_DW.obj_p.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_p;
    Pacemaker_DW.obj_p.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(12U, 1);
    Pacemaker_DW.obj_p.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Write11' */
    Pacemaker_DW.obj_h5.matlabCodegenIsDeleted = false;
    obj_1 = &Pacemaker_DW.obj_h5;
    Pacemaker_DW.obj_h5.isInitialized = 1;
    obj_1->MW_DIGITALIO_HANDLE = MW_digitalIO_open(13U, 1);
    Pacemaker_DW.obj_h5.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/PWM Output' */
    Pacemaker_DW.obj_e.matlabCodegenIsDeleted = false;
    obj_2 = &Pacemaker_DW.obj_e;
    Pacemaker_DW.obj_e.isInitialized = 1;
    obj_2->MW_PWM_HANDLE = MW_PWM_Open(3U, 2000.0, 0.0);
    MW_PWM_Start(Pacemaker_DW.obj_e.MW_PWM_HANDLE);
    Pacemaker_DW.obj_e.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/PWM Output1' */
    Pacemaker_DW.obj_a.matlabCodegenIsDeleted = false;
    obj_2 = &Pacemaker_DW.obj_a;
    Pacemaker_DW.obj_a.isInitialized = 1;
    obj_2->MW_PWM_HANDLE = MW_PWM_Open(6U, 2000.0, 0.0);
    MW_PWM_Start(Pacemaker_DW.obj_a.MW_PWM_HANDLE);
    Pacemaker_DW.obj_a.isSetupComplete = true;
  }
}

/* Model terminate function */
void Pacemaker_terminate(void)
{
  b_freedomk64f_I2CMasterWrite__T *obj;
  g_dsp_internal_SlidingWindowA_T *obj_0;

  /* Terminate for MATLABSystem: '<S5>/FXOS8700 6-Axes Sensor' */
  if (!Pacemaker_DW.obj_m.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_m.isInitialized == 1) &&
        Pacemaker_DW.obj_m.isSetupComplete) {
      MW_I2C_Close(Pacemaker_DW.obj_m.i2cobj.MW_I2C_HANDLE);
    }
  }

  obj = &Pacemaker_DW.obj_m.i2cobj;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
    }
  }

  /* End of Terminate for MATLABSystem: '<S5>/FXOS8700 6-Axes Sensor' */

  /* Terminate for MATLABSystem: '<S5>/Moving Average' */
  if (!Pacemaker_DW.obj.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj.isInitialized == 1) &&
        Pacemaker_DW.obj.isSetupComplete) {
      obj_0 = Pacemaker_DW.obj.pStatistic;
      if (obj_0->isInitialized == 1) {
        obj_0->isInitialized = 2;
      }

      Pacemaker_DW.obj.NumChannels = -1;
      Pacemaker_DW.obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S5>/Moving Average' */

  /* Terminate for MATLABSystem: '<S5>/D1' */
  if (!Pacemaker_DW.obj_my.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_my.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_my.isInitialized == 1) &&
        Pacemaker_DW.obj_my.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_my.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S5>/D1' */

  /* Terminate for MATLABSystem: '<S5>/D0' */
  if (!Pacemaker_DW.obj_d.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_d.isInitialized == 1) &&
        Pacemaker_DW.obj_d.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_d.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S5>/D0' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write3' */
  if (!Pacemaker_DW.obj_h.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_h.isInitialized == 1) &&
        Pacemaker_DW.obj_h.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_h.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write3' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write' */
  if (!Pacemaker_DW.obj_l5.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_l5.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_l5.isInitialized == 1) &&
        Pacemaker_DW.obj_l5.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_l5.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write' */

  /* Terminate for MATLABSystem: '<S2>/PWM Output2' */
  if (!Pacemaker_DW.obj_j.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_j.isInitialized == 1) &&
        Pacemaker_DW.obj_j.isSetupComplete) {
      MW_PWM_Stop(Pacemaker_DW.obj_j.MW_PWM_HANDLE);
      MW_PWM_Close(Pacemaker_DW.obj_j.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/PWM Output2' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write5' */
  if (!Pacemaker_DW.obj_l.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_l.isInitialized == 1) &&
        Pacemaker_DW.obj_l.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_l.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write5' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write6' */
  if (!Pacemaker_DW.obj_o.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_o.isInitialized == 1) &&
        Pacemaker_DW.obj_o.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_o.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write6' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write7' */
  if (!Pacemaker_DW.obj_m1.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_m1.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_m1.isInitialized == 1) &&
        Pacemaker_DW.obj_m1.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_m1.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write7' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write8' */
  if (!Pacemaker_DW.obj_c.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_c.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_c.isInitialized == 1) &&
        Pacemaker_DW.obj_c.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_c.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write8' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write9' */
  if (!Pacemaker_DW.obj_k.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_k.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_k.isInitialized == 1) &&
        Pacemaker_DW.obj_k.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_k.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write9' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write10' */
  if (!Pacemaker_DW.obj_p.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_p.isInitialized == 1) &&
        Pacemaker_DW.obj_p.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_p.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write10' */

  /* Terminate for MATLABSystem: '<S2>/Digital Write11' */
  if (!Pacemaker_DW.obj_h5.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_h5.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_h5.isInitialized == 1) &&
        Pacemaker_DW.obj_h5.isSetupComplete) {
      MW_digitalIO_close(Pacemaker_DW.obj_h5.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Write11' */

  /* Terminate for MATLABSystem: '<S2>/PWM Output' */
  if (!Pacemaker_DW.obj_e.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_e.isInitialized == 1) &&
        Pacemaker_DW.obj_e.isSetupComplete) {
      MW_PWM_Stop(Pacemaker_DW.obj_e.MW_PWM_HANDLE);
      MW_PWM_Close(Pacemaker_DW.obj_e.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/PWM Output' */

  /* Terminate for MATLABSystem: '<S2>/PWM Output1' */
  if (!Pacemaker_DW.obj_a.matlabCodegenIsDeleted) {
    Pacemaker_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((Pacemaker_DW.obj_a.isInitialized == 1) &&
        Pacemaker_DW.obj_a.isSetupComplete) {
      MW_PWM_Stop(Pacemaker_DW.obj_a.MW_PWM_HANDLE);
      MW_PWM_Close(Pacemaker_DW.obj_a.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/PWM Output1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
