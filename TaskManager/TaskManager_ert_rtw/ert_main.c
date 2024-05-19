/*
 * File: ert_main.c
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
#include "MW_target_hardware_resources.h"

volatile int IsrOverrun = 0;
boolean_T isRateRunning[3] = { 0, 0, 0 };

boolean_T need2runFlags[3] = { 0, 0, 0 };

uint16_T SOCB_RateTimerEventCounter[3] = {
  1,
  1,
  1,
};

uint16_T SOCB_RateTimerEventCounterTrigVal[3] = {
  1,
  100,
  32767,
};

void updateBaseRateTime(void);
void updateBaseRateTime(void)
{
}

void rt_OneStep(void)
{
  int_T i;
  for (i = 1; i < 3; i++) {
    if (--SOCB_RateTimerEventCounter[i] == 0) {
      SOCB_RateTimerEventCounter[i] = SOCB_RateTimerEventCounterTrigVal[i];
      if (need2runFlags[i]++) {
        IsrOverrun = 1;
        need2runFlags[i]--;            /* allow future iterations to succeed*/
      }
    }
  }

  /* Check base rate for overrun */
  if (isRateRunning[0]++) {
    IsrOverrun = 1;
    isRateRunning[0]--;                /* allow future iterations to succeed*/
    return;
  }

  /* Set model state to running when first base rate is triggered */
  if (MODEL_APPLICATION_WAIT_FOR_SCHEDULER_TO_START == runModel) {
    runModel = MODEL_APPLICATION_RUNNING;
  }

  enableTimer0Interrupt();
  TaskManager_step0();

  /* Get model outputs here */
  disableTimer0Interrupt();
  isRateRunning[0]--;
  for (i = 1; i < 3; i++) {
    if (isRateRunning[i]) {
      /* Yield to higher priority*/
      return;
    }

    if (need2runFlags[i]) {
      isRateRunning[i]++;
      enableTimer0Interrupt();

      /* Step the model for subrate "i" */
      switch (i)
      {
       case 1 :
        TaskManager_step1();

        /* Get model outputs here */
        break;

       case 2 :
        TaskManager_step2();

        /* Get model outputs here */
        break;

       default :
        break;
      }

      disableTimer0Interrupt();
      need2runFlags[i]--;
      isRateRunning[i]--;
    }
  }
}

volatile boolean_T stopRequested;
volatile RunModelStates_T runModel;
int main(void)
{
  float modelBaseRate = 1.0E-5;
  float systemClock = 200;

  /* Initialize variables */
  stopRequested = false;
  runModel = MODEL_APPLICATION_NOT_RUNNING;

  /* Do not start execution until all slave CPUs are
     in a ready state to receive boot command from master CPU */
  waitUntilAllSlaveCPUsReadyToBoot();
  c2000_flash_init();
  init_board();

#if defined(MW_EXEC_PROFILER_ON) || (defined(MW_EXTMODE_RUNNING) && !defined(XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME))

  hardwareTimer1Init();

#endif

  ;

  /* Once microcontroller's system clock is initialized,
     send start Boot command to all CPUs */
  sendStartBootCmdToSlaveCPU(2);

  /* Wait for Model Initialization of slave CPU 2 */
  sendStartModelInitCmdToSlaveCPU(2);
  waitForAckForStartModelInitCmdFromSlaveCPU(2);
  do {
  } while (0 == receiveEndModelInitCmdFromSlaveCPU(2));

  rtmSetErrorStatus(TaskManager_M, 0);
  TaskManager_initialize();
  globalInterruptDisable();
  if (rtmGetErrorStatus(TaskManager_M) == (NULL)) {
    runModel = MODEL_APPLICATION_READY_TO_START;
  } else {
    runModel = MODEL_APPLICATION_NOT_RUNNING;
  }

  config_ePWM_TBSync();
  globalInterruptEnable();
  while ((MODEL_APPLICATION_READY_TO_START == runModel) ||
         (MODEL_APPLICATION_WAIT_FOR_SCHEDULER_TO_START == runModel) ||
         (MODEL_APPLICATION_RUNNING == runModel)) {
    /*  Start scheduler */
    if (MODEL_APPLICATION_READY_TO_START == runModel) {
      if (checkSlaveCPUReadyToRunApplication(2)) {
        sendRunApplicationCmdToAllSlaveCPUs();

        /* Set application running status to scheduler configuring state */
        runModel = MODEL_APPLICATION_WAIT_FOR_SCHEDULER_TO_START;

        /* Start scheduler */
        configureTimer0(modelBaseRate, systemClock);

        /* Enable scheduler interrupt */
        enableTimer0Interrupt();
      }
    }

    stopRequested = !(rtmGetErrorStatus(TaskManager_M) == (NULL));
  }

  /* Terminate model */
  TaskManager_terminate();
  globalInterruptDisable();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
