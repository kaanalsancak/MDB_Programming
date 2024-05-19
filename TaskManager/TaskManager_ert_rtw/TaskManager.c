/*
 * File: TaskManager.c
 *
 * Code generated for Simulink model 'TaskManager'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sun May 19 08:18:15 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TaskManager.h"
#include "rtwtypes.h"
#include <math.h>
#include "TaskManager_private.h"
#include <string.h>
#define TaskManager_IN_IDLE            (1U)
#define TaskManager_IN_NO_ACTIVE_CHILD (0U)
#define TaskManager_IN_RESET           (2U)

/* Block signals (default storage) */
B_TaskManager_T TaskManager_B;

/* Block states (default storage) */
DW_TaskManager_T TaskManager_DW;

/* Real-time model */
static RT_MODEL_TaskManager_T TaskManager_M_;
RT_MODEL_TaskManager_T *const TaskManager_M = &TaskManager_M_;
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void TaskManager_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(TaskManager_M, 1));
  eventFlags[2] = ((boolean_T)rtmStepTask(TaskManager_M, 2));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (TaskManager_M->Timing.TaskCounters.TID[1])++;
  if ((TaskManager_M->Timing.TaskCounters.TID[1]) > 99) {/* Sample time: [0.001s, 0.0s] */
    TaskManager_M->Timing.TaskCounters.TID[1] = 0;
  }

  (TaskManager_M->Timing.TaskCounters.TID[2])++;
  if ((TaskManager_M->Timing.TaskCounters.TID[2]) > 199999) {/* Sample time: [2.0s, 0.0s] */
    TaskManager_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/* Model step function for TID0 */
void TaskManager_step0(void)           /* Sample time: [1.0E-5s, 0.0s] */
{
  {                                    /* Sample time: [1.0E-5s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* S-Function (fcgen): '<S20>/FcnCallGen' incorporates:
   *  SubSystem: '<Root>/High Freq'
   */
  /* S-Function (c280xgpio_do): '<S3>/Digital Output' incorporates:
   *  Constant: '<S3>/Constant'
   */
  {
    GpioDataRegs.GPATOGGLE.bit.GPIO6 = (uint16_T)(TaskManager_P.Constant_Value_a
      != 0);
  }

  /* End of Outputs for S-Function (fcgen): '<S20>/FcnCallGen' */
}

/* Model step function for TID1 */
void TaskManager_step1(void)           /* Sample time: [0.001s, 0.0s] */
{
  real_T rtb_Gain;

  /* S-Function (fcgen): '<S21>/FcnCallGen' incorporates:
   *  SubSystem: '<Root>/Dac'
   */
  /* Chart: '<S1>/Chart' */
  if (TaskManager_DW.is_active_c3_TaskManager == 0U) {
    TaskManager_DW.is_active_c3_TaskManager = 1U;
    TaskManager_DW.is_c3_TaskManager = TaskManager_IN_RESET;
    TaskManager_B.cnt_b = 0.0;
  } else if (TaskManager_DW.is_c3_TaskManager == 1U) {
    if (TaskManager_B.cnt_b == 100.0) {
      TaskManager_DW.is_c3_TaskManager = TaskManager_IN_RESET;
      TaskManager_B.cnt_b = 0.0;
    } else {
      TaskManager_B.cnt_b++;
    }

    /* case IN_RESET: */
  } else if (TaskManager_B.cnt_b == 0.0) {
    TaskManager_DW.is_c3_TaskManager = TaskManager_IN_IDLE;
    TaskManager_B.cnt_b++;
  } else {
    TaskManager_B.cnt_b = 0.0;
  }

  /* End of Chart: '<S1>/Chart' */

  /* MATLABSystem: '<S1>/DAC' */
  MW_C2000DACSat(0U, TaskManager_B.cnt_b);

  /* MATLABSystem: '<S1>/DAC2' */
  MW_C2000DACSat(2U, TaskManager_B.cnt_b);

  /* Chart: '<S7>/Chart' incorporates:
   *  Constant: '<S7>/Constant2'
   *  Constant: '<S7>/Constant3'
   */
  if (TaskManager_DW.is_active_c1_TaskManager == 0U) {
    TaskManager_DW.is_active_c1_TaskManager = 1U;
    TaskManager_DW.is_c1_TaskManager = TaskManager_IN_RESET;
    TaskManager_B.cnt = 0.0;
  } else if (TaskManager_DW.is_c1_TaskManager == 1U) {
    if (TaskManager_B.cnt >= TaskManager_P.Subsystem_trsh) {
      TaskManager_DW.is_c1_TaskManager = TaskManager_IN_RESET;
      TaskManager_B.cnt = 0.0;
    } else {
      TaskManager_B.cnt += TaskManager_P.Subsystem_stp;
    }

    /* case IN_RESET: */
  } else if (TaskManager_B.cnt == 0.0) {
    TaskManager_DW.is_c1_TaskManager = TaskManager_IN_IDLE;
    TaskManager_B.cnt += TaskManager_P.Subsystem_stp;
  } else {
    TaskManager_B.cnt = 0.0;
  }

  /* End of Chart: '<S7>/Chart' */

  /* Gain: '<S6>/Gain' incorporates:
   *  Constant: '<S6>/Constant'
   *  Constant: '<S6>/Constant1'
   *  Gain: '<S6>/Gain1'
   *  Product: '<S6>/Divide'
   *  Sum: '<S6>/Add'
   *  Trigonometry: '<S6>/Sin'
   */
  rtb_Gain = ((real32_T)sin((real32_T)(TaskManager_P.Constant1_Value *
    TaskManager_B.cnt)) * TaskManager_P.Gain1_Gain +
              TaskManager_P.Constant_Value_p) * TaskManager_P.Gain_Gain;

  /* S-Function (c2802xpwm): '<S1>/ePWM' */

  /*-- Update CMPA value for ePWM1 --*/
  {
    EPwm1Regs.CMPA.bit.CMPA = (uint16_T)((uint32_T)EPwm1Regs.TBPRD *
      TaskManager_B.cnt_b * 0.01);
  }

  /*-- Update CMPB value for ePWM1 --*/
  {
    EPwm1Regs.CMPB.bit.CMPB = (uint16_T)((uint32_T)EPwm1Regs.TBPRD * rtb_Gain *
      0.01);
  }

  /* End of Outputs for S-Function (fcgen): '<S21>/FcnCallGen' */
}

/* Model step function for TID2 */
void TaskManager_step2(void)           /* Sample time: [2.0s, 0.0s] */
{
  /* S-Function (fcgen): '<S19>/FcnCallGen' incorporates:
   *  SubSystem: '<Root>/Heart Beat'
   */
  /* S-Function (c280xgpio_do): '<S2>/Digital Output' incorporates:
   *  Constant: '<S2>/Constant'
   */
  {
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = (uint16_T)(TaskManager_P.Constant_Value
      != 0);
  }

  /* End of Outputs for S-Function (fcgen): '<S19>/FcnCallGen' */
}

/* Model initialize function */
void TaskManager_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)TaskManager_M, 0,
                sizeof(RT_MODEL_TaskManager_T));

  /* block I/O */
  (void) memset(((void *) &TaskManager_B), 0,
                sizeof(B_TaskManager_T));

  /* states (dwork) */
  (void) memset((void *)&TaskManager_DW, 0,
                sizeof(DW_TaskManager_T));

  /* SystemInitialize for S-Function (fcgen): '<S21>/FcnCallGen' incorporates:
   *  SubSystem: '<Root>/Dac'
   */
  /* Start for S-Function (c2802xpwm): '<S1>/ePWM' */

  /*** Initialize ePWM1 modules ***/
  {
    /*  // Time Base Control Register
       EPwm1Regs.TBCTL.bit.CTRMODE              = 2U;          // Counter Mode
       EPwm1Regs.TBCTL.bit.SYNCOSEL             = 3U;          // Sync Output Select
       EPwm1Regs.TBCTL2.bit.SYNCOSELX           = 0U;          // Sync Output Select - additional options

       EPwm1Regs.TBCTL.bit.PRDLD                = 0U;          // Shadow select

       EPwm1Regs.TBCTL2.bit.PRDLDSYNC           = 0U;          // Shadow select

       EPwm1Regs.TBCTL.bit.PHSEN                = 0U;          // Phase Load Enable
       EPwm1Regs.TBCTL.bit.PHSDIR               = 0U;          // Phase Direction Bit
       EPwm1Regs.TBCTL.bit.HSPCLKDIV            = 0U;          // High Speed TBCLK Pre-scaler
       EPwm1Regs.TBCTL.bit.CLKDIV               = 0U;          // Time Base Clock Pre-scaler
     */
    EPwm1Regs.TBCTL.all = (EPwm1Regs.TBCTL.all & ~0x3FFFU) | 0x32U;
    EPwm1Regs.TBCTL2.all = (EPwm1Regs.TBCTL2.all & ~0xF000U) | 0x0U;

    /*-- Setup Time-Base (TB) Submodule --*/
    EPwm1Regs.TBPRD = 10000U;          // Time Base Period Register

    /* // Time-Base Phase Register
       EPwm1Regs.TBPHS.bit.TBPHS               = 0U;          // Phase offset register
     */
    EPwm1Regs.TBPHS.all = (EPwm1Regs.TBPHS.all & ~0xFFFF0000U) | 0x0U;

    // Time Base Counter Register
    EPwm1Regs.TBCTR = 0x0000U;         /* Clear counter*/

    /*-- Setup Counter_Compare (CC) Submodule --*/
    /*	// Counter Compare Control Register

       EPwm1Regs.CMPCTL.bit.LOADASYNC           = 0U;          // Active Compare A Load SYNC Option
       EPwm1Regs.CMPCTL.bit.LOADBSYNC           = 0U;          // Active Compare B Load SYNC Option
       EPwm1Regs.CMPCTL.bit.LOADAMODE           = 0U;          // Active Compare A Load
       EPwm1Regs.CMPCTL.bit.LOADBMODE           = 0U;          // Active Compare B Load
       EPwm1Regs.CMPCTL.bit.SHDWAMODE           = 0U;          // Compare A Register Block Operating Mode
       EPwm1Regs.CMPCTL.bit.SHDWBMODE           = 0U;          // Compare B Register Block Operating Mode
     */
    EPwm1Regs.CMPCTL.all = (EPwm1Regs.CMPCTL.all & ~0x3C5FU) | 0x0U;

    /* EPwm1Regs.CMPCTL2.bit.SHDWCMODE           = 0U;          // Compare C Register Block Operating Mode
       EPwm1Regs.CMPCTL2.bit.SHDWDMODE           = 0U;          // Compare D Register Block Operating Mode
       EPwm1Regs.CMPCTL2.bit.LOADCSYNC           = 0U;          // Active Compare C Load SYNC Option
       EPwm1Regs.CMPCTL2.bit.LOADDSYNC           = 0U;          // Active Compare D Load SYNC Option
       EPwm1Regs.CMPCTL2.bit.LOADCMODE           = 0U;          // Active Compare C Load
       EPwm1Regs.CMPCTL2.bit.LOADDMODE           = 0U;          // Active Compare D Load
     */
    EPwm1Regs.CMPCTL2.all = (EPwm1Regs.CMPCTL2.all & ~0x3C5FU) | 0x0U;
    EPwm1Regs.CMPA.bit.CMPA = 5000U;   // Counter Compare A Register
    EPwm1Regs.CMPB.bit.CMPB = 5000U;   // Counter Compare B Register
    EPwm1Regs.CMPC = 32000U;           // Counter Compare C Register
    EPwm1Regs.CMPD = 32000U;           // Counter Compare D Register

    /*-- Setup Action-Qualifier (AQ) Submodule --*/
    EPwm1Regs.AQCTLA.all = 150U;
                               // Action Qualifier Control Register For Output A
    EPwm1Regs.AQCTLB.all = 2310U;
                               // Action Qualifier Control Register For Output B

    /*	// Action Qualifier Software Force Register
       EPwm1Regs.AQSFRC.bit.RLDCSF              = 0U;          // Reload from Shadow Options
     */
    EPwm1Regs.AQSFRC.all = (EPwm1Regs.AQSFRC.all & ~0xC0U) | 0x0U;

    /*	// Action Qualifier Continuous S/W Force Register
       EPwm1Regs.AQCSFRC.bit.CSFA               = 0U;          // Continuous Software Force on output A
       EPwm1Regs.AQCSFRC.bit.CSFB               = 0U;          // Continuous Software Force on output B
     */
    EPwm1Regs.AQCSFRC.all = (EPwm1Regs.AQCSFRC.all & ~0xFU) | 0x0U;

    /*-- Setup Dead-Band Generator (DB) Submodule --*/
    /*	// Dead-Band Generator Control Register
       EPwm1Regs.DBCTL.bit.OUT_MODE             = 0U;          // Dead Band Output Mode Control
       EPwm1Regs.DBCTL.bit.IN_MODE              = 0U;          // Dead Band Input Select Mode Control
       EPwm1Regs.DBCTL.bit.POLSEL               = 0;          // Polarity Select Control
       EPwm1Regs.DBCTL.bit.HALFCYCLE            = 0U;          // Half Cycle Clocking Enable
       EPwm1Regs.DBCTL.bit.SHDWDBREDMODE        = 0U;          // DBRED shadow mode
       EPwm1Regs.DBCTL.bit.SHDWDBFEDMODE        = 0U;          // DBFED shadow mode
       EPwm1Regs.DBCTL.bit.LOADREDMODE          = 4U;        // DBRED load
       EPwm1Regs.DBCTL.bit.LOADFEDMODE          = 4U;        // DBFED load
     */
    EPwm1Regs.DBCTL.all = (EPwm1Regs.DBCTL.all & ~0x8FFFU) | 0x0U;
    EPwm1Regs.DBRED.bit.DBRED = (uint16_T)(0);
                         // Dead-Band Generator Rising Edge Delay Count Register
    EPwm1Regs.DBFED.bit.DBFED = (uint16_T)(0);
                        // Dead-Band Generator Falling Edge Delay Count Register

    /*-- Setup Event-Trigger (ET) Submodule --*/
    /*	// Event Trigger Selection and Pre-Scale Register
       EPwm1Regs.ETSEL.bit.SOCAEN               = 0U;          // Start of Conversion A Enable
       EPwm1Regs.ETSEL.bit.SOCASELCMP           = 0U;
       EPwm1Regs.ETSEL.bit.SOCASEL              = 1U;          // Start of Conversion A Select
       EPwm1Regs.ETPS.bit.SOCPSSEL              = 1U;          // EPWM1SOC Period Select
       EPwm1Regs.ETSOCPS.bit.SOCAPRD2           = 1U;
       EPwm1Regs.ETSEL.bit.SOCBEN               = 0U;          // Start of Conversion B Enable
       EPwm1Regs.ETSEL.bit.SOCBSELCMP           = 0U;
       EPwm1Regs.ETSEL.bit.SOCBSEL              = 1U;          // Start of Conversion A Select
       EPwm1Regs.ETPS.bit.SOCPSSEL              = 1;          // EPWM1SOCB Period Select
       EPwm1Regs.ETSOCPS.bit.SOCBPRD2           = 1U;
       EPwm1Regs.ETSEL.bit.INTEN                = 0U;          // EPWM1INTn Enable
       EPwm1Regs.ETSEL.bit.INTSELCMP            = 0U;
       EPwm1Regs.ETSEL.bit.INTSEL               = 1U;          // Start of Conversion A Select
       EPwm1Regs.ETPS.bit.INTPSSEL              = 1U;          // EPWM1INTn Period Select
       EPwm1Regs.ETINTPS.bit.INTPRD2            = 1U;
     */
    EPwm1Regs.ETSEL.all = (EPwm1Regs.ETSEL.all & ~0xFF7FU) | 0x1101U;
    EPwm1Regs.ETPS.all = (EPwm1Regs.ETPS.all & ~0x30U) | 0x30U;
    EPwm1Regs.ETSOCPS.all = (EPwm1Regs.ETSOCPS.all & ~0xF0FU) | 0x101U;
    EPwm1Regs.ETINTPS.all = (EPwm1Regs.ETINTPS.all & ~0xFU) | 0x1U;

    /*-- Setup PWM-Chopper (PC) Submodule --*/
    /*	// PWM Chopper Control Register
       EPwm1Regs.PCCTL.bit.CHPEN                = 0U;          // PWM chopping enable
       EPwm1Regs.PCCTL.bit.CHPFREQ              = 0U;          // Chopping clock frequency
       EPwm1Regs.PCCTL.bit.OSHTWTH              = 0U;          // One-shot pulse width
       EPwm1Regs.PCCTL.bit.CHPDUTY              = 0U;          // Chopping clock Duty cycle
     */
    EPwm1Regs.PCCTL.all = (EPwm1Regs.PCCTL.all & ~0x7FFU) | 0x0U;

    /*-- Set up Trip-Zone (TZ) Submodule --*/
    EALLOW;
    EPwm1Regs.TZSEL.all = 0U;          // Trip Zone Select Register

    /*	// Trip Zone Control Register
       EPwm1Regs.TZCTL.bit.TZA                  = 3U;          // TZ1 to TZ6 Trip Action On EPWM1A
       EPwm1Regs.TZCTL.bit.TZB                  = 3U;          // TZ1 to TZ6 Trip Action On EPWM1B
       EPwm1Regs.TZCTL.bit.DCAEVT1              = 3U;          // EPWM1A action on DCAEVT1
       EPwm1Regs.TZCTL.bit.DCAEVT2              = 3U;          // EPWM1A action on DCAEVT2
       EPwm1Regs.TZCTL.bit.DCBEVT1              = 3U;          // EPWM1B action on DCBEVT1
       EPwm1Regs.TZCTL.bit.DCBEVT2              = 3U;          // EPWM1B action on DCBEVT2
     */
    EPwm1Regs.TZCTL.all = (EPwm1Regs.TZCTL.all & ~0xFFFU) | 0xFFFU;

    /*	// Trip Zone Enable Interrupt Register
       EPwm1Regs.TZEINT.bit.OST                 = 0U;          // Trip Zones One Shot Int Enable
       EPwm1Regs.TZEINT.bit.CBC                 = 0U;          // Trip Zones Cycle By Cycle Int Enable
       EPwm1Regs.TZEINT.bit.DCAEVT1             = 0U;          // Digital Compare A Event 1 Int Enable
       EPwm1Regs.TZEINT.bit.DCAEVT2             = 0U;          // Digital Compare A Event 2 Int Enable
       EPwm1Regs.TZEINT.bit.DCBEVT1             = 0U;          // Digital Compare B Event 1 Int Enable
       EPwm1Regs.TZEINT.bit.DCBEVT2             = 0U;          // Digital Compare B Event 2 Int Enable
     */
    EPwm1Regs.TZEINT.all = (EPwm1Regs.TZEINT.all & ~0x7EU) | 0x0U;

    /*	// Digital Compare A Control Register
       EPwm1Regs.DCACTL.bit.EVT1SYNCE           = 0U;          // DCAEVT1 SYNC Enable
       EPwm1Regs.DCACTL.bit.EVT1SOCE            = 1U;          // DCAEVT1 SOC Enable
       EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL      = 0U;          // DCAEVT1 Force Sync Signal
       EPwm1Regs.DCACTL.bit.EVT1SRCSEL          = 0U;          // DCAEVT1 Source Signal
       EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL      = 0U;          // DCAEVT2 Force Sync Signal
       EPwm1Regs.DCACTL.bit.EVT2SRCSEL          = 0U;          // DCAEVT2 Source Signal
     */
    EPwm1Regs.DCACTL.all = (EPwm1Regs.DCACTL.all & ~0x30FU) | 0x4U;

    /*	// Digital Compare B Control Register
       EPwm1Regs.DCBCTL.bit.EVT1SYNCE           = 0U;          // DCBEVT1 SYNC Enable
       EPwm1Regs.DCBCTL.bit.EVT1SOCE            = 0U;          // DCBEVT1 SOC Enable
       EPwm1Regs.DCBCTL.bit.EVT1FRCSYNCSEL      = 0U;          // DCBEVT1 Force Sync Signal
       EPwm1Regs.DCBCTL.bit.EVT1SRCSEL          = 0U;          // DCBEVT1 Source Signal
       EPwm1Regs.DCBCTL.bit.EVT2FRCSYNCSEL      = 0U;          // DCBEVT2 Force Sync Signal
       EPwm1Regs.DCBCTL.bit.EVT2SRCSEL          = 0U;          // DCBEVT2 Source Signal
     */
    EPwm1Regs.DCBCTL.all = (EPwm1Regs.DCBCTL.all & ~0x30FU) | 0x0U;

    /*	// Digital Compare Trip Select Register
       EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL      = 0U;          // Digital Compare A High COMP Input Select

       EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL      = 0U;          // Digital Compare A Low COMP Input Select
       EPwm1Regs.DCTRIPSEL.bit.DCBHCOMPSEL      = 0U;          // Digital Compare B High COMP Input Select
       EPwm1Regs.DCTRIPSEL.bit.DCBLCOMPSEL      = 0U;          // Digital Compare B Low COMP Input Select
     */
    EPwm1Regs.DCTRIPSEL.all = (EPwm1Regs.DCTRIPSEL.all & ~ 0xFFFFU) | 0x0U;

    /*	// Trip Zone Digital Comparator Select Register
       EPwm1Regs.TZDCSEL.bit.DCAEVT1            = 0U;          // Digital Compare Output A Event 1
       EPwm1Regs.TZDCSEL.bit.DCAEVT2            = 0U;          // Digital Compare Output A Event 2
       EPwm1Regs.TZDCSEL.bit.DCBEVT1            = 0U;          // Digital Compare Output B Event 1
       EPwm1Regs.TZDCSEL.bit.DCBEVT2            = 0U;          // Digital Compare Output B Event 2
     */
    EPwm1Regs.TZDCSEL.all = (EPwm1Regs.TZDCSEL.all & ~0xFFFU) | 0x0U;

    /*	// Digital Compare Filter Control Register
       EPwm1Regs.DCFCTL.bit.BLANKE              = 0U;          // Blanking Enable/Disable
       EPwm1Regs.DCFCTL.bit.PULSESEL            = 1U;          // Pulse Select for Blanking & Capture Alignment
       EPwm1Regs.DCFCTL.bit.BLANKINV            = 0U;          // Blanking Window Inversion
       EPwm1Regs.DCFCTL.bit.SRCSEL              = 0U;          // Filter Block Signal Source Select
     */
    EPwm1Regs.DCFCTL.all = (EPwm1Regs.DCFCTL.all & ~0x3FU) | 0x10U;
    EPwm1Regs.DCFOFFSET = 0U;          // Digital Compare Filter Offset Register
    EPwm1Regs.DCFWINDOW = 0U;          // Digital Compare Filter Window Register

    /*	// Digital Compare Capture Control Register
       EPwm1Regs.DCCAPCTL.bit.CAPE              = 0U;          // Counter Capture Enable
     */
    EPwm1Regs.DCCAPCTL.all = (EPwm1Regs.DCCAPCTL.all & ~0x1U) | 0x0U;

    /*	// HRPWM Configuration Register
       EPwm1Regs.HRCNFG.bit.SWAPAB              = 0U;          // Swap EPWMA and EPWMB Outputs Bit
       EPwm1Regs.HRCNFG.bit.SELOUTB             = 0U;          // EPWMB Output Selection Bit
     */
    EPwm1Regs.HRCNFG.all = (EPwm1Regs.HRCNFG.all & ~0xA0U) | 0x0U;

    /* Update the Link Registers with the link value for all the Compare values and TBPRD */
    /* No error is thrown if the ePWM register exists in the model or not */
    EPwm1Regs.EPWMXLINK.bit.TBPRDLINK = 0U;
    EPwm1Regs.EPWMXLINK.bit.CMPALINK = 0U;
    EPwm1Regs.EPWMXLINK.bit.CMPBLINK = 0U;
    EPwm1Regs.EPWMXLINK.bit.CMPCLINK = 0U;
    EPwm1Regs.EPWMXLINK.bit.CMPDLINK = 0U;

    /* SYNCPER - Peripheral synchronization output event
       EPwm1Regs.HRPCTL.bit.PWMSYNCSEL            = 0U;          // EPWMSYNCPER selection
       EPwm1Regs.HRPCTL.bit.PWMSYNCSELX           = 0U;          //  EPWMSYNCPER selection
     */
    EPwm1Regs.HRPCTL.all = (EPwm1Regs.HRPCTL.all & ~0x72U) | 0x0U;
    EDIS;
  }

  /* SystemInitialize for Chart: '<S1>/Chart' */
  TaskManager_DW.is_active_c3_TaskManager = 0U;
  TaskManager_DW.is_c3_TaskManager = TaskManager_IN_NO_ACTIVE_CHILD;
  TaskManager_B.cnt_b = 0.0;

  /* Start for MATLABSystem: '<S1>/DAC' */
  MW_ConfigureDACA();

  /* Start for MATLABSystem: '<S1>/DAC2' */
  MW_ConfigureDACC();

  /* SystemInitialize for Chart: '<S7>/Chart' */
  TaskManager_DW.is_active_c1_TaskManager = 0U;
  TaskManager_DW.is_c1_TaskManager = TaskManager_IN_NO_ACTIVE_CHILD;
  TaskManager_B.cnt = 0.0;

  /* End of SystemInitialize for S-Function (fcgen): '<S21>/FcnCallGen' */

  /* SystemInitialize for S-Function (fcgen): '<S19>/FcnCallGen' incorporates:
   *  SubSystem: '<Root>/Heart Beat'
   */
  /* Start for S-Function (c280xgpio_do): '<S2>/Digital Output' */
  EALLOW;
  GpioCtrlRegs.GPAMUX2.all &= 0x3FFFFFFFU;
  GpioCtrlRegs.GPADIR.all |= 0x80000000U;
  EDIS;

  /* End of SystemInitialize for S-Function (fcgen): '<S19>/FcnCallGen' */

  /* SystemInitialize for S-Function (fcgen): '<S20>/FcnCallGen' incorporates:
   *  SubSystem: '<Root>/High Freq'
   */
  /* Start for S-Function (c280xgpio_do): '<S3>/Digital Output' */
  EALLOW;
  GpioCtrlRegs.GPAMUX1.all &= 0xFFFFCFFFU;
  GpioCtrlRegs.GPADIR.all |= 0x40U;
  EDIS;

  /* End of SystemInitialize for S-Function (fcgen): '<S20>/FcnCallGen' */
}

/* Model terminate function */
void TaskManager_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
