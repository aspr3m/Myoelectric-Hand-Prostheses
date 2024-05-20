/**
  ******************************************************************************
  * @file    cnnmodel_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon May 13 21:15:35 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef CNNMODEL_DATA_PARAMS_H
#define CNNMODEL_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_CNNMODEL_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_cnnmodel_data_weights_params[1]))
*/

#define AI_CNNMODEL_DATA_CONFIG               (NULL)


#define AI_CNNMODEL_DATA_ACTIVATIONS_SIZES \
  { 5632, }
#define AI_CNNMODEL_DATA_ACTIVATIONS_SIZE     (5632)
#define AI_CNNMODEL_DATA_ACTIVATIONS_COUNT    (1)
#define AI_CNNMODEL_DATA_ACTIVATION_1_SIZE    (5632)



#define AI_CNNMODEL_DATA_WEIGHTS_SIZES \
  { 370200, }
#define AI_CNNMODEL_DATA_WEIGHTS_SIZE         (370200)
#define AI_CNNMODEL_DATA_WEIGHTS_COUNT        (1)
#define AI_CNNMODEL_DATA_WEIGHT_1_SIZE        (370200)



#define AI_CNNMODEL_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_cnnmodel_activations_table[1])

extern ai_handle g_cnnmodel_activations_table[1 + 2];



#define AI_CNNMODEL_DATA_WEIGHTS_TABLE_GET() \
  (&g_cnnmodel_weights_table[1])

extern ai_handle g_cnnmodel_weights_table[1 + 2];


#endif    /* CNNMODEL_DATA_PARAMS_H */
