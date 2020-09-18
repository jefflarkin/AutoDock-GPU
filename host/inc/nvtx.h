/*

AutoDock-GPU, an OpenCL implementation of AutoDock 4.2 running a Lamarckian Genetic Algorithm
Copyright (C) 2017 TU Darmstadt, Embedded Systems and Applications Group, Germany. All rights reserved.
For some of the code, Copyright (C) 2019 Computational Structural Biology Center, the Scripps Research Institute.

AutoDock is a Trade Mark of the Scripps Research Institute.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/




#ifndef NVTX_H
#define NVTX_H
/* Wraps NVTX API for simplicity and ease of turning on/off. */

#ifdef USE_NVTX
#include <nvtx3/nvToolsExt.h>
#define NVTX_PUSH(msg) { nvtxRangePushA(msg); }
const static unsigned int nvtxColors[] = { 0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00, 0xFFFF00FF, 0xFF00FFFF};
const static int nvtxColorCnt = 6;
static int nvtxCurrentColor;
#pragma omp threadprivate(nvtxCurrentColor)
#define NVTX_PUSH_RGBA(msg,colornum) { \
  nvtxEventAttributes_t eventAttrib = {0};\
    eventAttrib.version = NVTX_VERSION;\
    eventAttrib.size = NVTX_EVENT_ATTRIB_STRUCT_SIZE;\
    eventAttrib.colorType = NVTX_COLOR_ARGB;\
    eventAttrib.color = nvtxColors[colornum%nvtxColorCnt];\
    eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII;\
    eventAttrib.message.ascii = msg;\
    nvtxRangePushEx(&eventAttrib);\
}
#define NVTX_POP() { nvtxRangePop(); }
#else
#define NVTX_PUSH(msg) { };
#define NVTX_POP() { };
#endif

#endif
