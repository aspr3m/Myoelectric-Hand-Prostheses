/**
  ******************************************************************************
  * @file    cnnmodel.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon May 13 21:15:35 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "cnnmodel.h"
#include "cnnmodel_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_cnnmodel
 
#undef AI_CNNMODEL_MODEL_SIGNATURE
#define AI_CNNMODEL_MODEL_SIGNATURE     "0x7fb374fe18678338bf69b32ad1a6038d"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon May 13 21:15:35 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_CNNMODEL_N_BATCHES
#define AI_CNNMODEL_N_BATCHES         (1)

static ai_ptr g_cnnmodel_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_cnnmodel_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_gaussian_noise_input0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 72, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1280, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  nl_1_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1280, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1280, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  pool_6_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 640, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 768, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  nl_9_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 768, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_10_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 768, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  pool_14_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 384, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  gemm_16_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  nl_16_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  gemm_17_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  nl_18_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 6, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 960, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_2_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 40960, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_10_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_10_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  gemm_16_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 49152, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  gemm_16_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  gemm_17_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 768, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  gemm_17_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_gaussian_noise_input0_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 24), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &serving_default_gaussian_noise_input0_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_gaussian_noise_input0_output0, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 24, 1), AI_STRIDE_INIT(4, 4, 4, 12, 288),
  1, &serving_default_gaussian_noise_input0_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 1), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &conv2d_1_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  nl_1_nl_output, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 1), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &nl_1_nl_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_2_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 1), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &eltwise_2_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_2_output0, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 20), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &eltwise_2_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  pool_6_output, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 10), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &pool_6_output_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  pool_6_output0, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 1), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &pool_6_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_output, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 6, 1), AI_STRIDE_INIT(4, 4, 4, 512, 3072),
  1, &conv2d_9_output_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  nl_9_nl_output, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 6, 1), AI_STRIDE_INIT(4, 4, 4, 512, 3072),
  1, &nl_9_nl_output_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 6, 1), AI_STRIDE_INIT(4, 4, 4, 512, 3072),
  1, &eltwise_10_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_output0, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 6), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &eltwise_10_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  pool_14_output, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 3), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &pool_14_output_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  pool_14_output0, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1536, 1536),
  1, &pool_14_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  gemm_16_output, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &gemm_16_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  nl_16_nl_output, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &nl_16_nl_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  gemm_17_output, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 4, 4, 24, 24),
  1, &gemm_17_output_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  nl_18_output, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 4, 4, 24, 24),
  1, &nl_18_output_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 3, 5, 1, 64), AI_STRIDE_INIT(4, 4, 12, 768, 3840),
  1, &conv2d_1_weights_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_2_scale, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &eltwise_2_scale_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_2_bias, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &eltwise_2_bias_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_weights, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 64, 5, 1, 128), AI_STRIDE_INIT(4, 4, 256, 32768, 163840),
  1, &conv2d_9_weights_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_bias, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &conv2d_9_bias_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_scale, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &eltwise_10_scale_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_bias, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &eltwise_10_bias_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  gemm_16_weights, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 384, 128, 1, 1), AI_STRIDE_INIT(4, 4, 1536, 196608, 196608),
  1, &gemm_16_weights_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  gemm_16_bias, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &gemm_16_bias_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  gemm_17_weights, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 128, 6, 1, 1), AI_STRIDE_INIT(4, 4, 512, 3072, 3072),
  1, &gemm_17_weights_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  gemm_17_bias, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 4, 4, 24, 24),
  1, &gemm_17_bias_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_18_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_17_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_18_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_18_layer, 18,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm,
  &nl_18_chain,
  NULL, &nl_18_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_17_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_16_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_17_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_17_weights, &gemm_17_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  gemm_17_layer, 17,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &gemm_17_chain,
  NULL, &nl_18_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_16_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_16_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_16_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_16_nl_layer, 16,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_16_nl_chain,
  NULL, &gemm_17_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_16_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_14_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_16_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_16_weights, &gemm_16_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  gemm_16_layer, 16,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &gemm_16_chain,
  NULL, &nl_16_nl_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_14_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_10_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_14_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_14_layer, 14,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &pool_14_chain,
  NULL, &gemm_16_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(1, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_9_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_10_scale, &eltwise_10_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_10_layer, 11,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_10_chain,
  NULL, &pool_14_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_9_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_9_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_9_nl_layer, 9,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_9_nl_chain,
  NULL, &eltwise_10_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_6_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_9_weights, &conv2d_9_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_9_layer, 9,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_9_chain,
  NULL, &nl_9_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_2_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_6_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_6_layer, 6,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &pool_6_chain,
  NULL, &conv2d_9_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(1, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_1_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_2_scale, &eltwise_2_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_2_layer, 3,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_2_chain,
  NULL, &pool_6_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_1_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_1_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_1_nl_layer, 1,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_1_nl_chain,
  NULL, &eltwise_2_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_gaussian_noise_input0_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_1_chain,
  NULL, &nl_1_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 370200, 1, 1),
    370200, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 5632, 1, 1),
    5632, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNNMODEL_IN_NUM, &serving_default_gaussian_noise_input0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNNMODEL_OUT_NUM, &nl_18_output),
  &conv2d_1_layer, 0x189bd05b, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 370200, 1, 1),
      370200, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 5632, 1, 1),
      5632, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNNMODEL_IN_NUM, &serving_default_gaussian_noise_input0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_CNNMODEL_OUT_NUM, &nl_18_output),
  &conv2d_1_layer, 0x189bd05b, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool cnnmodel_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_cnnmodel_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_gaussian_noise_input0_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 5120);
    serving_default_gaussian_noise_input0_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 5120);
    conv2d_1_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    conv2d_1_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    nl_1_nl_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    nl_1_nl_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    eltwise_2_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    eltwise_2_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    pool_6_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    pool_6_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    conv2d_9_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 2560);
    conv2d_9_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 2560);
    nl_9_nl_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 2560);
    nl_9_nl_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 2560);
    eltwise_10_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 2560);
    eltwise_10_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 2560);
    pool_14_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    pool_14_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    gemm_16_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 1536);
    gemm_16_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 1536);
    nl_16_nl_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    nl_16_nl_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    gemm_17_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 512);
    gemm_17_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 512);
    nl_18_output_array.data = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    nl_18_output_array.data_start = AI_PTR(g_cnnmodel_activations_map[0] + 0);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool cnnmodel_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_cnnmodel_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 0);
    conv2d_1_weights_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 0);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 3840);
    conv2d_1_bias_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 3840);
    eltwise_2_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_2_scale_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 4096);
    eltwise_2_scale_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 4096);
    eltwise_2_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_2_bias_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 4352);
    eltwise_2_bias_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 4352);
    conv2d_9_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_weights_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 4608);
    conv2d_9_weights_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 4608);
    conv2d_9_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_bias_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 168448);
    conv2d_9_bias_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 168448);
    eltwise_10_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_10_scale_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 168960);
    eltwise_10_scale_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 168960);
    eltwise_10_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_10_bias_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 169472);
    eltwise_10_bias_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 169472);
    gemm_16_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_16_weights_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 169984);
    gemm_16_weights_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 169984);
    gemm_16_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_16_bias_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 366592);
    gemm_16_bias_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 366592);
    gemm_17_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_17_weights_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 367104);
    gemm_17_weights_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 367104);
    gemm_17_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_17_bias_array.data = AI_PTR(g_cnnmodel_weights_map[0] + 370176);
    gemm_17_bias_array.data_start = AI_PTR(g_cnnmodel_weights_map[0] + 370176);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_cnnmodel_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_CNNMODEL_MODEL_NAME,
      .model_signature   = AI_CNNMODEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 323616,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x189bd05b,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_cnnmodel_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_CNNMODEL_MODEL_NAME,
      .model_signature   = AI_CNNMODEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 323616,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x189bd05b,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_cnnmodel_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_cnnmodel_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_cnnmodel_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_cnnmodel_create(network, AI_CNNMODEL_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_cnnmodel_data_params_get(&params) != true) {
    err = ai_cnnmodel_get_error(*network);
    return err;
  }
#if defined(AI_CNNMODEL_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_CNNMODEL_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_cnnmodel_init(*network, &params) != true) {
    err = ai_cnnmodel_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_cnnmodel_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_cnnmodel_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_cnnmodel_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_cnnmodel_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= cnnmodel_configure_weights(net_ctx, params);
  ok &= cnnmodel_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_cnnmodel_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_cnnmodel_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_CNNMODEL_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

