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




#ifndef PERFORMDOCKING_H_
#define PERFORMDOCKING_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda.h>
#include <curand.h>
#include <cuda_runtime_api.h>
#include <cassert>

#include "profile.hpp"

//#include <math.h>
#include "processgrid.h"
#include "miscellaneous.h"
#include "processligand.h"
#include "getparameters.h"
#include "calcenergy.h"
#include "processresult.h"
#include "simulation_state.hpp"
#include "GpuData.h"


#define ELAPSEDSECS(stop,start) ((float) stop-start)/((float) CLOCKS_PER_SEC)

#if 0
// Experimental TSRI gradient-based minimizer kernel argument
// Setup here (temporarily?) the gradient-based minimizer and associated parameters.
// This should be ultimately configurable by the user as program exec. flags.

typedef struct {
	unsigned int max_num_of_iters;
	/*
	unsigned int max_num_of_consec_fails;
	float alpha;
	float conformation_min_perturbation [ACTUAL_GENOTYPE_LENGTH];
	*/
} Gradientparameters;
#endif

// Clears all GPU memory held in place by caching grids on the GPU.
void clear_gpu();
// Allocates space for GPU constants and copies what can be copied.
void setup_gpu_for_docking(GpuData& cData, 
                           GpuTempData& tData);
// Frees GPU memory allocated in setup_gpu_for_docking.
void finish_gpu_from_docking(GpuData& cData, 
                             GpuTempData& tData);
int docking_with_gpu(const Gridinfo* 		mygrid,
         	     /*const*/ float* 		cpu_floatgrids,
		           Dockpars*		mypars,
		     const Liganddata* 	 	myligand_init,
		     const Liganddata* 		myxrayligand,
                        Profile&                profile,
		     const int* 		argc,
		     char**			argv,
			SimulationState&	sim_state,
			GpuData& cData,
			GpuTempData& tData);

double check_progress(int* evals_of_runs,
		      int generation_cnt,
		      int max_num_of_evals,
		      int max_num_of_gens,
		      int num_of_runs,
		      unsigned long &total_evals);

#endif /* PERFORMDOCKING_H_ */
