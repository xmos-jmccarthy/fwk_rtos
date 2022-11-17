// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#pragma once

#include "mic_array.h"

C_API_START

MA_C_API void rtos_init(void);

MA_C_API void rtos_pdm_rx_task(void);

MA_C_API void rtos_decimator_task(chanend_t c_audio_frames);


C_API_END