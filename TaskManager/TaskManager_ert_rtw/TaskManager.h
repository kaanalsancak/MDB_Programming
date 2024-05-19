/*
 * File: TaskManager.h
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

#ifndef RTW_HEADER_TaskManager_h_
#define RTW_HEADER_TaskManager_h_
#ifndef TaskManager_COMMON_INCLUDES_
#define TaskManager_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "IQmathLib.h"
#include "MW_c2000DAC.h"
#endif                                 /* TaskManager_COMMON_INCLUDES_ */

#include <stddef.h>
#include "TaskManager_types.h"
#include <string.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

extern void config_ePWMSyncSource(void);
extern void config_ePWM_GPIO (void);
extern void config_ePWM_TBSync (void);
extern void config_ePWM_XBAR(void);

/* Block signals (default storage) */
typedef struct {
  real_T cnt;                          /* '<S7>/Chart' */
  real_T cnt_b;                        /* '<S1>/Chart' */
} B_TaskManager_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int32_T DigitalOutput_FRAC_LEN;      /* '<S3>/Digital Output' */
  int32_T DigitalOutput_FRAC_LEN_j;    /* '<S2>/Digital Output' */
  uint16_T is_active_c1_TaskManager;   /* '<S7>/Chart' */
  uint16_T is_c1_TaskManager;          /* '<S7>/Chart' */
  uint16_T is_active_c3_TaskManager;   /* '<S1>/Chart' */
  uint16_T is_c3_TaskManager;          /* '<S1>/Chart' */
} DW_TaskManager_T;

/* Parameters (default storage) */
struct P_TaskManager_T_ {
  real_T Subsystem_stp;                /* Mask Parameter: Subsystem_stp
                                        * Referenced by: '<S7>/Constant3'
                                        */
  real_T Subsystem_trsh;               /* Mask Parameter: Subsystem_trsh
                                        * Referenced by: '<S7>/Constant2'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: 1
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Constant_Value_p;             /* Expression: 0.5
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Gain_Gain;                    /* Expression: 100
                                        * Referenced by: '<S6>/Gain'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S6>/Constant1'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S6>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_TaskManager_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint32_T TID[3];
    } TaskCounters;
  } Timing;
};

typedef enum {
  MODEL_APPLICATION_NOT_RUNNING = 0x00U,
  MODEL_APPLICATION_READY_TO_START = 0x01U,
  MODEL_APPLICATION_WAIT_FOR_SCHEDULER_TO_START = 0x02U,
  MODEL_APPLICATION_RUNNING = 0x04U,
  MODEL_APPLICATION_RUNNING_ERROR = 0x08U
} RunModelStates_T;

/* Block parameters (default storage) */
extern P_TaskManager_T TaskManager_P;

/* Block signals (default storage) */
extern B_TaskManager_T TaskManager_B;

/* Block states (default storage) */
extern DW_TaskManager_T TaskManager_DW;

/* External function called from main */
extern void TaskManager_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void TaskManager_initialize(void);
extern void TaskManager_step0(void);
extern void TaskManager_step1(void);
extern void TaskManager_step2(void);
extern void TaskManager_terminate(void);

/* Real-time Model object */
extern RT_MODEL_TaskManager_T *const TaskManager_M;
extern volatile boolean_T stopRequested;
extern volatile RunModelStates_T runModel;

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
 * '<Root>' : 'TaskManager'
 * '<S1>'   : 'TaskManager/Dac'
 * '<S2>'   : 'TaskManager/Heart Beat'
 * '<S3>'   : 'TaskManager/High Freq'
 * '<S4>'   : 'TaskManager/Task Manager'
 * '<S5>'   : 'TaskManager/Dac/Chart'
 * '<S6>'   : 'TaskManager/Dac/SinGenerator'
 * '<S7>'   : 'TaskManager/Dac/SinGenerator/Subsystem'
 * '<S8>'   : 'TaskManager/Dac/SinGenerator/Subsystem/Chart'
 * '<S9>'   : 'TaskManager/Task Manager/Core Task Manager'
 * '<S10>'  : 'TaskManager/Task Manager/Task Blocks'
 * '<S11>'  : 'TaskManager/Task Manager/Core Task Manager/Variant Subsystem'
 * '<S12>'  : 'TaskManager/Task Manager/Core Task Manager/Variant Subsystem/HSBON'
 * '<S13>'  : 'TaskManager/Task Manager/Core Task Manager/Variant Subsystem/HSBON/Task Manager'
 * '<S14>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem'
 * '<S15>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem/HSBON'
 * '<S16>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem/HSBON/HeartBeatSubsystem'
 * '<S17>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem/HSBON/Task1Subsystem'
 * '<S18>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem/HSBON/ms1Subsystem'
 * '<S19>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem/HSBON/HeartBeatSubsystem/FcnCallGenPart'
 * '<S20>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem/HSBON/Task1Subsystem/FcnCallGenPart'
 * '<S21>'  : 'TaskManager/Task Manager/Task Blocks/Variant Subsystem/HSBON/ms1Subsystem/FcnCallGenPart'
 */
#endif                                 /* RTW_HEADER_TaskManager_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
