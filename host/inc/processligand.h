/*

OCLADock, an OpenCL implementation of AutoDock 4.2 running a Lamarckian Genetic Algorithm
Copyright (C) 2017 TU Darmstadt, Embedded Systems and Applications Group, Germany. All rights reserved.

AutoDock is a Trade Mark of the Scripps Research Institute.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/


#ifndef PROCESSLIGAND_H_
#define PROCESSLIGAND_H_

#include "defines.h"
#include "processgrid.h"
#include "miscellaneous.h"

#define ATYPE_NUM 22

typedef struct
//Struct which contains ligand information. The fields contain the following information:
//num_of_atoms: 	Number of ligand atoms.
//num_of_atypes:	Number of different atom types in the ligand.
//num_of_rotbonds: 	Number of rotatable bonds in the ligand.
//atom_types: 		Each row (first index) contain an atom type (as two characters),
//			the row index is equal to the atom type code.
//atom_idxyzq: 		Each row describes one atom of the ligand.
//			The columns (second index) contain the atom type code, x, y and z coordinate
//                      (in Angstroms) and electrical charge  of the atom.
// 			The row index is equal to the index of the current atom.
//rotbonds: 		Each row corresponds to one rotatable bond of the ligand.
//			The rotatable bond is described with the indexes of the
//			two atoms which are connected to each other by the bond.
//			The row index is equal to the index of the rotatable bond.
//atom_rotbonds: 	The array contains the rotatable bonds - atoms assignment.
//			If the element atom_rotbonds[atom index][rotatable bond index] is equal to 1,
//			it means,that the atom must be rotated if the bond rotates.
//			A 0 means the opposite.
//atom_rigid_structures: The array contains the ridig structure ID of the atoms.
//			 If the atom_rigid_structures[atom1 index] = atom_rigid_structures[atom2 index],
//			 it means, that the atoms are in the same rigid molecule fragment.
//			 Rigid structures are seperated by branches in the pdbqt file.
//bonds: 		If the element bonds[atom index][atom index] is equal to 1,
//			a bond exists between the atoms.
//intraE_contributors: 	If the element [atom index][atom index] is equal to 1,
//			the energy contribution of the two atoms must be included in
//			intramolecular energy calculation,
//			which requires that there is at least one rotatable bond between the atoms and
//			their interaction type is not 1-2, 1-3 or 1-4
//VWpars_x: 		The matrices contain the A, B, C and D Van der Waals parameters for the ligand atom types.
//			The VWpars_A [atom type code of atom 1][atom type code of atom 2] element is equal
//			to the A parameter for these types, the VWpars_B contains the B parameters in the
//			same manner etc.
//volume, solpar: 	these fields are similar to VWpars_x-s,
//			they contain the atoms' volume and solvation parameter.
//num_of_rotations_required:
//num_of_intraE_contributors:
//rotbonds_moving_vectors, rotbonds_unit_vectors: the vectors required for rotation around the
//						  corresponding rotatable bond (the first index is
//						  the index of the rotatable bond). When rotating
//						  a point around the bond with ID i, first it must be moved
//						  according to rotbonds_moving_vectors [i], then must be rotated
//						  around the line which crosses the origo and is parallel to
//						  rotbonds_unit_vectors [i], then it must be moved back with
//						  -1*rotbonds_moving_vectors [i].
//						  WARNING: after calling calc_conform for a Liganddata structure,
//						  the orientation of the molecule will be changed, and these
//						  vecotrs will be unvalid, so they must be calculated again if
//						  it is necessary.
{
	int 	num_of_atoms;
	int 	num_of_atypes;
	int 	num_of_rotbonds;
	char 	atom_types [MAX_NUM_OF_ATYPES][3];	//in the case of arrays, the first index is called row index,
	double 	atom_idxyzq [MAX_NUM_OF_ATOMS][5];	//the second is called column index
	int 	rotbonds [MAX_NUM_OF_ROTBONDS][2];
	char 	atom_rotbonds [MAX_NUM_OF_ATOMS][MAX_NUM_OF_ROTBONDS];
	int 	atom_rigid_structures [MAX_NUM_OF_ATOMS];
	char 	bonds [MAX_NUM_OF_ATOMS][MAX_NUM_OF_ATOMS];
	char 	intraE_contributors [MAX_NUM_OF_ATOMS][MAX_NUM_OF_ATOMS];

	// -------------------------------------------
	// Smoothed pairwise potentials
	// -------------------------------------------
	// Sizes are hardcoded, ATYPE_NUM=22 float elements as in
	// https://git.esa.informatik.tu-darmstadt.de/docking/ocladock/blob/master/host/src/processligand.cpp#L456
	// See "User Guide AutoDock 4.2" (page 34)
	double  reqm [ATYPE_NUM];
	double  reqm_hbond [ATYPE_NUM];

	unsigned int  atom1_types_reqm [ATYPE_NUM];
	unsigned int  atom2_types_reqm [ATYPE_NUM];
	// -------------------------------------------

	double 	VWpars_A [MAX_NUM_OF_ATYPES][MAX_NUM_OF_ATYPES];
	double	VWpars_B [MAX_NUM_OF_ATYPES][MAX_NUM_OF_ATYPES];
	double 	VWpars_C [MAX_NUM_OF_ATYPES][MAX_NUM_OF_ATYPES];
	double 	VWpars_D [MAX_NUM_OF_ATYPES][MAX_NUM_OF_ATYPES];
	double 	volume [MAX_NUM_OF_ATYPES];
	double 	solpar [MAX_NUM_OF_ATYPES];
	int 	num_of_rotations_required;
	int 	num_of_intraE_contributors;
	int 	num_of_rotcyc;
	double 	rotbonds_moving_vectors [MAX_NUM_OF_ROTBONDS][3];
	double 	rotbonds_unit_vectors [MAX_NUM_OF_ROTBONDS][3];
} Liganddata;

int init_liganddata(const char*, Liganddata*, Gridinfo*);

int set_liganddata_typeid(Liganddata*, int, const char*);

void get_intraE_contributors(Liganddata*);

int get_bonds(Liganddata*);

int get_VWpars(Liganddata*, const double, const double);

void get_moving_and_unit_vectors(Liganddata*);

int get_liganddata(const char*, Liganddata*, const double, const double);

int gen_new_pdbfile(const char*, const char*, const Liganddata*);

void get_movvec_to_origo(const Liganddata*, double []);

void move_ligand(Liganddata*, const double []);

void scale_ligand(Liganddata*, const double);

double calc_rmsd(const Liganddata*, const Liganddata*, const int);

double calc_ddd_Mehler_Solmajer(double);

int is_H_bond(const char*, const char*);

void print_ref_lig_energies_f(Liganddata,
			      Gridinfo,
			      const float*,
			      const float,
			      const float,
			      const float);

//////////////////////////////////
//float functions

void calc_distdep_tables_f(float   	r_6_table [],
			   float 	r_10_table [],
			   float 	r_12_table [],
			   float 	r_epsr_table [],
			   float 	desolv_table [],
			   const float  scaled_AD4_coeff_elec,
		           const float  AD4_coeff_desolv);

void calc_q_tables_f(const Liganddata* myligand,
		     float qasp,
		     float q1q2 [][256],
		     float qasp_mul_absq []);

void change_conform_f(Liganddata* myligand,
		      const float genotype_f [],
		      float* 	  cpu_ref_ori_angles,
		      int 	  debug);

float calc_interE_f(const Gridinfo* 	mygrid,
		    const Liganddata* 	myligand,
	            const float* 	fgrids,
		    float 		outofgrid_tolerance,
                    int 		debug);

void calc_interE_peratom_f(const Gridinfo* 	mygrid,
			   const Liganddata* 	myligand,
			   const float* 	fgrids,
                           float 		outofgrid_tolerance,
			   float* 		elecE,
	                   float 		peratom_vdw [MAX_NUM_OF_ATOMS],
			   float 		peratom_elec [MAX_NUM_OF_ATOMS],
			   int 			debug);

float calc_intraE_f(const Liganddata* 	myligand,
		    float 		dcutoff,
		    char 		ignore_desolv,
		    const float 	scaled_AD4_coeff_elec,
		    const float 	AD4_coeff_desolv,
		    const float 	qasp,
		    int 		debug);

#endif /* PROCESSLIGAND_H_ */
