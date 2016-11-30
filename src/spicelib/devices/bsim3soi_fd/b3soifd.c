/**********
Copyright 1999 Regents of the University of California.  All rights reserved.
Author: Weidong Liu and Pin Su         Feb 1999
Author: 1998 Samuel Fung, Dennis Sinitsky and Stephen Tang
Modified by Wei Jin 99/9/27
Modified by Paolo Nenzi 2002
File: b3soifd.c          98/5/01
**********/

/*
 * Revision 2.1  99/9/27 Pin Su 
 * BSIMFD2.1 release
 */

#include "ngspice/ngspice.h"
#include "ngspice/devdefs.h"
#include "b3soifddef.h"
#include "ngspice/suffix.h"

IFparm B3SOIFDpTable[] = { /* parameters */
IOP( "l",   B3SOIFD_L,      IF_REAL   , "Length"),
IOP( "w",   B3SOIFD_W,      IF_REAL   , "Width"),
IOP( "m",   B3SOIFD_M,      IF_REAL   , "Parallel Multiplier"),
IOP( "ad",  B3SOIFD_AD,     IF_REAL   , "Drain area"),
IOP( "as",  B3SOIFD_AS,     IF_REAL   , "Source area"),
IOP( "pd",  B3SOIFD_PD,     IF_REAL   , "Drain perimeter"),
IOP( "ps",  B3SOIFD_PS,     IF_REAL   , "Source perimeter"),
IOP( "nrd", B3SOIFD_NRD,    IF_REAL   , "Number of squares in drain"),
IOP( "nrs", B3SOIFD_NRS,    IF_REAL   , "Number of squares in source"),
IOP( "off", B3SOIFD_OFF,    IF_FLAG   , "Device is initially off"),
IP( "ic",  B3SOIFD_IC,     IF_REALVEC , "Vector of DS,GS,BS initial voltages"),
OP( "gmbs",         B3SOIFD_GMBS,       IF_REAL,    "Gmb"),
OP( "gm",           B3SOIFD_GM,         IF_REAL,    "Gm"),
OP( "gm/ids",       B3SOIFD_GMID,       IF_REAL,    "Gm/Ids"),
OP( "gds",          B3SOIFD_GDS,        IF_REAL,    "Gds"),
OP( "vdsat",        B3SOIFD_VDSAT,      IF_REAL,    "Vdsat"),
OP( "vth",          B3SOIFD_VON,        IF_REAL,    "Vth"),
OP( "ids",          B3SOIFD_CD,         IF_REAL,    "Ids"),
OP( "vbs",          B3SOIFD_VBS,        IF_REAL,    "Vbs"),
OP( "vgs",          B3SOIFD_VGS,        IF_REAL,    "Vgs"),
OP( "vds",          B3SOIFD_VDS,        IF_REAL,    "Vds"),
OP( "ves",	    B3SOIFD_VES,	      IF_REAL,    "Ves"),
IOP( "bjtoff", B3SOIFD_BJTOFF,	      IF_INTEGER, "BJT on/off flag"),
IOP( "debug", B3SOIFD_DEBUG,	      IF_INTEGER, "BJT on/off flag"),
IOP( "rth0", B3SOIFD_RTH0,  IF_REAL,    "Instance Thermal Resistance"),
IOP( "cth0", B3SOIFD_CTH0,  IF_REAL,    "Instance Thermal Capacitance"),
IOP( "nrb", B3SOIFD_NRB,    IF_REAL,    "Number of squares in body"),
};

IFparm B3SOIFDmPTable[] = { /* model parameters */
IOP( "capmod", B3SOIFD_MOD_CAPMOD, IF_INTEGER, "Capacitance model selector"),
IOP( "mobmod", B3SOIFD_MOD_MOBMOD, IF_INTEGER, "Mobility model selector"),
IOP( "noimod", B3SOIFD_MOD_NOIMOD, IF_INTEGER, "Noise model selector"),
IOP( "paramchk", B3SOIFD_MOD_PARAMCHK, IF_INTEGER, "Model parameter checking selector"),
IOP( "binunit", B3SOIFD_MOD_BINUNIT, IF_INTEGER, "Bin  unit  selector"),
IOP( "version", B3SOIFD_MOD_VERSION, IF_REAL, " parameter for model version"),
IOP( "tox", B3SOIFD_MOD_TOX, IF_REAL, "Gate oxide thickness in meters"),

IOP( "cdsc", B3SOIFD_MOD_CDSC, IF_REAL, "Drain/Source and channel coupling capacitance"),
IOP( "cdscb", B3SOIFD_MOD_CDSCB, IF_REAL, "Body-bias dependence of cdsc"), 
IOP( "cdscd", B3SOIFD_MOD_CDSCD, IF_REAL, "Drain-bias dependence of cdsc"), 
IOP( "cit", B3SOIFD_MOD_CIT, IF_REAL, "Interface state capacitance"),
IOP( "nfactor", B3SOIFD_MOD_NFACTOR, IF_REAL, "Subthreshold swing Coefficient"),
IOP( "vsat", B3SOIFD_MOD_VSAT, IF_REAL, "Saturation velocity at tnom"),
IOP( "at", B3SOIFD_MOD_AT, IF_REAL, "Temperature coefficient of vsat"),
IOP( "a0", B3SOIFD_MOD_A0, IF_REAL, "Non-uniform depletion width effect coefficient."), 
IOP( "ags", B3SOIFD_MOD_AGS, IF_REAL, "Gate bias  coefficient of Abulk."), 
IOP( "a1", B3SOIFD_MOD_A1, IF_REAL, "Non-saturation effect coefficient"),
IOP( "a2", B3SOIFD_MOD_A2, IF_REAL, "Non-saturation effect coefficient"),
IOP( "keta", B3SOIFD_MOD_KETA, IF_REAL, "Body-bias coefficient of non-uniform depletion width effect."),
IOP( "nsub", B3SOIFD_MOD_NSUB, IF_REAL, "Substrate doping concentration with polarity"),
IOP( "nch", B3SOIFD_MOD_NPEAK, IF_REAL, "Channel doping concentration"),
IOP( "ngate", B3SOIFD_MOD_NGATE, IF_REAL, "Poly-gate doping concentration"),
IOP( "gamma1", B3SOIFD_MOD_GAMMA1, IF_REAL, "Vth body coefficient"),
IOP( "gamma2", B3SOIFD_MOD_GAMMA2, IF_REAL, "Vth body coefficient"),
IOP( "vbx", B3SOIFD_MOD_VBX, IF_REAL, "Vth transition body Voltage"),
IOP( "vbm", B3SOIFD_MOD_VBM, IF_REAL, "Maximum body voltage"),

IOP( "xt", B3SOIFD_MOD_XT, IF_REAL, "Doping depth"),
IOP( "k1", B3SOIFD_MOD_K1, IF_REAL, "Bulk effect coefficient 1"),
IOP( "kt1", B3SOIFD_MOD_KT1, IF_REAL, "Temperature coefficient of Vth"),
IOP( "kt1l", B3SOIFD_MOD_KT1L, IF_REAL, "Temperature coefficient of Vth"),
IOP( "kt2",  B3SOIFD_MOD_KT2, IF_REAL, "Body-coefficient of kt1"),
IOP( "k2",   B3SOIFD_MOD_K2,  IF_REAL, "Bulk effect coefficient 2"),
IOP( "k3",   B3SOIFD_MOD_K3,  IF_REAL, "Narrow width effect coefficient"),
IOP( "k3b",  B3SOIFD_MOD_K3B, IF_REAL, "Body effect coefficient of k3"),
IOP( "w0",   B3SOIFD_MOD_W0,  IF_REAL, "Narrow width effect parameter"),
IOP( "nlx",  B3SOIFD_MOD_NLX, IF_REAL, "Lateral non-uniform doping effect"),
IOP( "dvt0", B3SOIFD_MOD_DVT0, IF_REAL, "Short channel effect coeff. 0"),
IOP( "dvt1", B3SOIFD_MOD_DVT1, IF_REAL, "Short channel effect coeff. 1"),
IOP( "dvt2", B3SOIFD_MOD_DVT2, IF_REAL, "Short channel effect coeff. 2"),
IOP( "dvt0w", B3SOIFD_MOD_DVT0W, IF_REAL, "Narrow Width coeff. 0"),
IOP( "dvt1w", B3SOIFD_MOD_DVT1W, IF_REAL, "Narrow Width effect coeff. 1"),
IOP( "dvt2w", B3SOIFD_MOD_DVT2W, IF_REAL, "Narrow Width effect coeff. 2"),
IOP( "drout", B3SOIFD_MOD_DROUT, IF_REAL, "DIBL coefficient of output resistance"),
IOP( "dsub", B3SOIFD_MOD_DSUB, IF_REAL, "DIBL coefficient in the subthreshold region"),
IOP( "vth0", B3SOIFD_MOD_VTH0, IF_REAL,"Threshold voltage"),
IOPR( "vtho", B3SOIFD_MOD_VTH0, IF_REAL,"Threshold voltage"),
IOP( "ua", B3SOIFD_MOD_UA, IF_REAL, "Linear gate dependence of mobility"),
IOP( "ua1", B3SOIFD_MOD_UA1, IF_REAL, "Temperature coefficient of ua"),
IOP( "ub", B3SOIFD_MOD_UB, IF_REAL, "Quadratic gate dependence of mobility"),
IOP( "ub1", B3SOIFD_MOD_UB1, IF_REAL, "Temperature coefficient of ub"),
IOP( "uc", B3SOIFD_MOD_UC, IF_REAL, "Body-bias dependence of mobility"),
IOP( "uc1", B3SOIFD_MOD_UC1, IF_REAL, "Temperature coefficient of uc"),
IOP( "u0", B3SOIFD_MOD_U0, IF_REAL, "Low-field mobility at Tnom"),
IOP( "ute", B3SOIFD_MOD_UTE, IF_REAL, "Temperature coefficient of mobility"),
IOP( "voff", B3SOIFD_MOD_VOFF, IF_REAL, "Threshold voltage offset"),
IOP( "tnom", B3SOIFD_MOD_TNOM, IF_REAL, "Parameter measurement temperature"),
IOP( "cgso", B3SOIFD_MOD_CGSO, IF_REAL, "Gate-source overlap capacitance per width"),
IOP( "cgdo", B3SOIFD_MOD_CGDO, IF_REAL, "Gate-drain overlap capacitance per width"),
IOP( "cgeo", B3SOIFD_MOD_CGEO, IF_REAL, "Gate-substrate overlap capacitance"),
IOP( "xpart", B3SOIFD_MOD_XPART, IF_REAL, "Channel charge partitioning"),
IOP( "delta", B3SOIFD_MOD_DELTA, IF_REAL, "Effective Vds parameter"),
IOP( "rsh", B3SOIFD_MOD_RSH, IF_REAL, "Source-drain sheet resistance"),
IOP( "rdsw", B3SOIFD_MOD_RDSW, IF_REAL, "Source-drain resistance per width"),    

IOP( "prwg", B3SOIFD_MOD_PRWG, IF_REAL, "Gate-bias effect on parasitic resistance "),    
IOP( "prwb", B3SOIFD_MOD_PRWB, IF_REAL, "Body-effect on parasitic resistance "),    

IOP( "prt", B3SOIFD_MOD_PRT, IF_REAL, "Temperature coefficient of parasitic resistance "),    
IOP( "eta0", B3SOIFD_MOD_ETA0, IF_REAL, "Subthreshold region DIBL coefficient"),
IOP( "etab", B3SOIFD_MOD_ETAB, IF_REAL, "Subthreshold region DIBL coefficient"),
IOP( "pclm", B3SOIFD_MOD_PCLM, IF_REAL, "Channel length modulation Coefficient"),
IOP( "pdiblc1", B3SOIFD_MOD_PDIBL1, IF_REAL, "Drain-induced barrier lowering coefficient"),   
IOP( "pdiblc2", B3SOIFD_MOD_PDIBL2, IF_REAL, "Drain-induced barrier lowering coefficient"),   
IOP( "pdiblcb", B3SOIFD_MOD_PDIBLB, IF_REAL, "Body-effect on drain-induced barrier lowering"),   

IOP( "pvag", B3SOIFD_MOD_PVAG, IF_REAL, "Gate dependence of output resistance parameter"),   

IOP( "shmod", B3SOIFD_MOD_SHMOD, IF_INTEGER, "Self heating mode selector"),
IOP( "tbox", B3SOIFD_MOD_TBOX, IF_REAL, "Back gate oxide thickness in meters"),   
IOP( "tsi", B3SOIFD_MOD_TSI, IF_REAL, "Silicon-on-insulator thickness in meters"),   
IOP( "xj", B3SOIFD_MOD_XJ, IF_REAL, "Junction Depth"),   
IOP( "kb1", B3SOIFD_MOD_KB1, IF_REAL, "Backgate coupling coefficient at strong inversion"),   
IOP( "kb3", B3SOIFD_MOD_KB3, IF_REAL, "Backgate coupling coefficient at subthreshold"),   
IOP( "dvbd0", B3SOIFD_MOD_DVBD0, IF_REAL, "First coefficient of short-channel effect on Vbs0t"),   
IOP( "dvbd1", B3SOIFD_MOD_DVBD1, IF_REAL, "Second coefficient of short-channel effect on Vbs0t"),   
IOP( "vbsa", B3SOIFD_MOD_VBSA, IF_REAL, "Vbs0t offset voltage"),
IOP( "delp", B3SOIFD_MOD_DELP, IF_REAL, "Offset constant for limiting Vbseff to Phis"),
IOP( "rbody", B3SOIFD_MOD_RBODY, IF_REAL, "Intrinsic body contact sheet resistance"),   
IOP( "rbsh",  B3SOIFD_MOD_RBSH,  IF_REAL, "Extrinsic body contact sheet resistance"),
IOP( "adice0", B3SOIFD_MOD_ADICE0, IF_REAL, "DICE constant for bulk charge effect"),   
IOP( "abp", B3SOIFD_MOD_ABP, IF_REAL, "Gate bias coefficient for Xcsat calculation"),   
IOP( "mxc", B3SOIFD_MOD_MXC, IF_REAL, "A smoothing parameter for Xcsat calculation"),   
IOP( "rth0", B3SOIFD_MOD_RTH0, IF_REAL, "Self-heating thermal resistance"),   
IOP( "cth0", B3SOIFD_MOD_CTH0, IF_REAL, "Self-heating thermal capacitance"),
IOP( "aii", B3SOIFD_MOD_AII, IF_REAL, "1st Vdsatii parameter"),   
IOP( "bii", B3SOIFD_MOD_BII, IF_REAL, "2nd Vdsatii parameter"),   
IOP( "cii", B3SOIFD_MOD_CII, IF_REAL, "3rd Vdsatii parameter"),   
IOP( "dii", B3SOIFD_MOD_DII, IF_REAL, "4th Vdsatii parameter"),   
IOP( "ngidl", B3SOIFD_MOD_NGIDL, IF_REAL, "GIDL first parameter"),   
IOP( "agidl", B3SOIFD_MOD_AGIDL, IF_REAL, "GIDL second parameter"),   
IOP( "bgidl", B3SOIFD_MOD_BGIDL, IF_REAL, "GIDL third parameter"),   
IOP( "ndiode", B3SOIFD_MOD_NDIODE, IF_REAL, "Diode non-ideality factor"),   
IOP( "ntun", B3SOIFD_MOD_NTUN, IF_REAL, "Reverse tunneling non-ideality factor"),   
IOP( "isbjt", B3SOIFD_MOD_ISBJT, IF_REAL, "BJT emitter injection constant"),   
IOP( "isdif", B3SOIFD_MOD_ISDIF, IF_REAL, "Body to S/D injection constant"),   
IOP( "isrec", B3SOIFD_MOD_ISREC, IF_REAL, "Recombination in depletion constant"),   
IOP( "istun", B3SOIFD_MOD_ISTUN, IF_REAL, "Tunneling diode constant"),   
IOP( "xbjt", B3SOIFD_MOD_XBJT, IF_REAL, "Temperature coefficient for Isbjt"),   
IOP( "xdif", B3SOIFD_MOD_XBJT, IF_REAL, "Temperature coefficient for Isdif"),   
IOP( "xrec", B3SOIFD_MOD_XREC, IF_REAL, "Temperature coefficient for Isrec"),   
IOP( "xtun", B3SOIFD_MOD_XTUN, IF_REAL, "Temperature coefficient for Istun"),   
IOP( "edl", B3SOIFD_MOD_EDL, IF_REAL, "Electron diffusion length"),   
IOP( "kbjt1", B3SOIFD_MOD_KBJT1, IF_REAL, "Vds dependency on BJT base width"),   
IOP( "tt", B3SOIFD_MOD_TT, IF_REAL, "Diffusion capacitance transit time coefficient"),
IOP( "vsdth", B3SOIFD_MOD_VSDTH, IF_REAL, "Source/Drain diffusion threshold voltage"),
IOP( "vsdfb", B3SOIFD_MOD_VSDFB, IF_REAL, "Source/Drain diffusion flatband voltage"),
IOP( "csdmin", B3SOIFD_MOD_CSDMIN, IF_REAL, "Source/Drain diffusion bottom minimum capacitance"),
IOP( "asd", B3SOIFD_MOD_ASD, IF_REAL, "Source/Drain diffusion smoothing parameter"),

IOP( "pbswg", B3SOIFD_MOD_PBSWG, IF_REAL, "Source/drain (gate side) sidewall junction capacitance built in potential"),
IOP( "mjswg", B3SOIFD_MOD_MJSWG, IF_REAL, "Source/drain (gate side) sidewall junction capacitance grading coefficient"),

IOP( "cjswg", B3SOIFD_MOD_CJSWG, IF_REAL, "Source/drain (gate side) sidewall junction capacitance per unit width"),
IOP( "csdesw", B3SOIFD_MOD_CSDESW, IF_REAL, "Source/drain sidewall fringing constant"),
IOP( "lint", B3SOIFD_MOD_LINT, IF_REAL, "Length reduction parameter"),
IOP( "ll",   B3SOIFD_MOD_LL, IF_REAL, "Length reduction parameter"),
IOP( "lln",  B3SOIFD_MOD_LLN, IF_REAL, "Length reduction parameter"),
IOP( "lw",   B3SOIFD_MOD_LW,  IF_REAL, "Length reduction parameter"),
IOP( "lwn",  B3SOIFD_MOD_LWN, IF_REAL, "Length reduction parameter"),
IOP( "lwl",  B3SOIFD_MOD_LWL, IF_REAL, "Length reduction parameter"),

IOP( "wr",   B3SOIFD_MOD_WR, IF_REAL, "Width dependence of rds"),
IOP( "wint", B3SOIFD_MOD_WINT, IF_REAL, "Width reduction parameter"),
IOP( "dwg",  B3SOIFD_MOD_DWG, IF_REAL, "Width reduction parameter"),
IOP( "dwb",  B3SOIFD_MOD_DWB, IF_REAL, "Width reduction parameter"),

IOP( "wl",   B3SOIFD_MOD_WL, IF_REAL, "Width reduction parameter"),
IOP( "wln",  B3SOIFD_MOD_WLN, IF_REAL, "Width reduction parameter"),
IOP( "ww",   B3SOIFD_MOD_WW, IF_REAL, "Width reduction parameter"),
IOP( "wwn",  B3SOIFD_MOD_WWN, IF_REAL, "Width reduction parameter"),
IOP( "wwl",  B3SOIFD_MOD_WWL, IF_REAL, "Width reduction parameter"),

IOP( "b0",  B3SOIFD_MOD_B0, IF_REAL, "Abulk narrow width parameter"),
IOP( "b1",  B3SOIFD_MOD_B1, IF_REAL, "Abulk narrow width parameter"),

IOP( "cgsl", B3SOIFD_MOD_CGSL, IF_REAL, "New C-V model parameter"),
IOP( "cgdl", B3SOIFD_MOD_CGDL, IF_REAL, "New C-V model parameter"),
IOP( "ckappa", B3SOIFD_MOD_CKAPPA, IF_REAL, "New C-V model parameter"),
IOP( "cf",  B3SOIFD_MOD_CF, IF_REAL, "Fringe capacitance parameter"),
IOP( "clc", B3SOIFD_MOD_CLC, IF_REAL, "Vdsat parameter for C-V model"),
IOP( "cle", B3SOIFD_MOD_CLE, IF_REAL, "Vdsat parameter for C-V model"),
IOP( "dwc", B3SOIFD_MOD_DWC, IF_REAL, "Delta W for C-V model"),
IOP( "dlc", B3SOIFD_MOD_DLC, IF_REAL, "Delta L for C-V model"),

IOP( "alpha0", B3SOIFD_MOD_ALPHA0, IF_REAL, "substrate current model parameter"),
IOP( "alpha1", B3SOIFD_MOD_ALPHA1, IF_REAL, "substrate current model parameter"),
IOP( "beta0", B3SOIFD_MOD_BETA0, IF_REAL, "substrate current model parameter"),

IOP( "noia", B3SOIFD_MOD_NOIA, IF_REAL, "Flicker noise parameter"),
IOP( "noib", B3SOIFD_MOD_NOIB, IF_REAL, "Flicker noise parameter"),
IOP( "noic", B3SOIFD_MOD_NOIC, IF_REAL, "Flicker noise parameter"),
IOP( "em", B3SOIFD_MOD_EM, IF_REAL, "Flicker noise parameter"),
IOP( "ef", B3SOIFD_MOD_EF, IF_REAL, "Flicker noise frequency exponent"),
IOP( "af", B3SOIFD_MOD_AF, IF_REAL, "Flicker noise exponent"),
IOP( "kf", B3SOIFD_MOD_KF, IF_REAL, "Flicker noise coefficient"),
IOP( "noif", B3SOIFD_MOD_NOIF, IF_REAL, "Floating body excess noise ideality factor"),

/* Added for binning - START */
/* Length Dependence */
IOP( "lnch",  B3SOIFD_MOD_LNPEAK, IF_REAL, "Length dependence of nch"),
IOP( "lnsub", B3SOIFD_MOD_LNSUB, IF_REAL, "Length dependence of nsub"),
IOP( "lngate", B3SOIFD_MOD_LNGATE, IF_REAL, "Length dependence of ngate"),
IOP( "lvth0", B3SOIFD_MOD_LVTH0, IF_REAL,"Length dependence of vto"),
IOP( "lk1",   B3SOIFD_MOD_LK1,  IF_REAL, "Length dependence of k1"),
IOP( "lk2",   B3SOIFD_MOD_LK2,  IF_REAL, "Length dependence of k2"),
IOP( "lk3",   B3SOIFD_MOD_LK3,  IF_REAL, "Length dependence of k3"),
IOP( "lk3b",  B3SOIFD_MOD_LK3B, IF_REAL, "Length dependence of k3b"),
IOP( "lvbsa",  B3SOIFD_MOD_LVBSA, IF_REAL, "Length dependence of vbsa"),
IOP( "ldelp",  B3SOIFD_MOD_LDELP, IF_REAL, "Length dependence of delp"),
IOP( "lkb1",  B3SOIFD_MOD_LKB1, IF_REAL, "Length dependence of kb1"),
IOP( "lkb3",  B3SOIFD_MOD_LKB3, IF_REAL, "Length dependence of kb3"),
IOP( "ldvbd0",  B3SOIFD_MOD_LDVBD0, IF_REAL, "Length dependence of dvbd0"),
IOP( "ldvbd1",  B3SOIFD_MOD_LDVBD1, IF_REAL, "Length dependence of dvbd1"),
IOP( "lw0",   B3SOIFD_MOD_LW0,  IF_REAL, "Length dependence of w0"),
IOP( "lnlx",  B3SOIFD_MOD_LNLX, IF_REAL, "Length dependence of nlx"),
IOP( "ldvt0", B3SOIFD_MOD_LDVT0, IF_REAL, "Length dependence of dvt0"),
IOP( "ldvt1", B3SOIFD_MOD_LDVT1, IF_REAL, "Length dependence of dvt1"),
IOP( "ldvt2", B3SOIFD_MOD_LDVT2, IF_REAL, "Length dependence of dvt2"),
IOP( "ldvt0w", B3SOIFD_MOD_LDVT0W, IF_REAL, "Length dependence of dvt0w"),
IOP( "ldvt1w", B3SOIFD_MOD_LDVT1W, IF_REAL, "Length dependence of dvt1w"),
IOP( "ldvt2w", B3SOIFD_MOD_LDVT2W, IF_REAL, "Length dependence of dvt2w"),
IOP( "lu0",  B3SOIFD_MOD_LU0, IF_REAL, "Length dependence of u0"),
IOP( "lua",  B3SOIFD_MOD_LUA, IF_REAL, "Length dependence of ua"),
IOP( "lub", B3SOIFD_MOD_LUB, IF_REAL, "Length dependence of ub"),
IOP( "luc",  B3SOIFD_MOD_LUC, IF_REAL, "Length dependence of uc"),
IOP( "lvsat", B3SOIFD_MOD_LVSAT, IF_REAL, "Length dependence of vsat"),
IOP( "la0", B3SOIFD_MOD_LA0, IF_REAL, "Length dependence of a0"),
IOP( "lags", B3SOIFD_MOD_LAGS, IF_REAL, "Length dependence of ags"),
IOP( "lb0",  B3SOIFD_MOD_LB0, IF_REAL, "Length dependence of b0"),
IOP( "lb1",  B3SOIFD_MOD_LB1, IF_REAL, "Length dependence of b1"),
IOP( "lketa", B3SOIFD_MOD_LKETA, IF_REAL, "Length dependence of keta"),
IOP( "labp", B3SOIFD_MOD_LABP, IF_REAL, "Length dependence of abp"),
IOP( "lmxc", B3SOIFD_MOD_LMXC, IF_REAL, "Length dependence of mxc"),
IOP( "ladice0", B3SOIFD_MOD_LADICE0, IF_REAL, "Length dependence of adice0"),
IOP( "la1", B3SOIFD_MOD_LA1, IF_REAL, "Length dependence of a1"),
IOP( "la2", B3SOIFD_MOD_LA2, IF_REAL, "Length dependence of a2"),
IOP( "lrdsw", B3SOIFD_MOD_LRDSW,  IF_REAL, "Length dependence of rdsw "),
IOP( "lprwb", B3SOIFD_MOD_LPRWB,  IF_REAL, "Length dependence of prwb "),
IOP( "lprwg", B3SOIFD_MOD_LPRWG,  IF_REAL, "Length dependence of prwg "),
IOP( "lwr",  B3SOIFD_MOD_LWR, IF_REAL, "Length dependence of wr"),
IOP( "lnfactor", B3SOIFD_MOD_LNFACTOR, IF_REAL, "Length dependence of nfactor"),
IOP( "ldwg", B3SOIFD_MOD_LDWG, IF_REAL, "Length dependence of dwg"),
IOP( "ldwb", B3SOIFD_MOD_LDWB, IF_REAL, "Length dependence of dwb"),
IOP( "lvoff", B3SOIFD_MOD_LVOFF, IF_REAL, "Length dependence of voff"),
IOP( "leta0", B3SOIFD_MOD_LETA0, IF_REAL, "Length dependence of eta0"),
IOP( "letab", B3SOIFD_MOD_LETAB, IF_REAL, "Length dependence of etab"),
IOP( "ldsub", B3SOIFD_MOD_LDSUB, IF_REAL, "Length dependence of dsub"),
IOP( "lcit",   B3SOIFD_MOD_LCIT,  IF_REAL, "Length dependence of cit"),
IOP( "lcdsc",  B3SOIFD_MOD_LCDSC, IF_REAL, "Length dependence of cdsc"),
IOP( "lcdscb", B3SOIFD_MOD_LCDSCB, IF_REAL, "Length dependence of cdscb"),
IOP( "lcdscd", B3SOIFD_MOD_LCDSCD, IF_REAL, "Length dependence of cdscd"),
IOP( "lpclm", B3SOIFD_MOD_LPCLM, IF_REAL, "Length dependence of pclm"),
IOP( "lpdiblc1", B3SOIFD_MOD_LPDIBL1, IF_REAL, "Length dependence of pdiblc1"),
IOP( "lpdiblc2", B3SOIFD_MOD_LPDIBL2, IF_REAL, "Length dependence of pdiblc2"),
IOP( "lpdiblcb", B3SOIFD_MOD_LPDIBLB, IF_REAL, "Length dependence of pdiblcb"),
IOP( "ldrout", B3SOIFD_MOD_LDROUT, IF_REAL, "Length dependence of drout"),
IOP( "lpvag", B3SOIFD_MOD_LPVAG, IF_REAL, "Length dependence of pvag"),
IOP( "ldelta", B3SOIFD_MOD_LDELTA, IF_REAL, "Length dependence of delta"),
IOP( "laii", B3SOIFD_MOD_LAII, IF_REAL, "Length dependence of aii"),
IOP( "lbii", B3SOIFD_MOD_LBII, IF_REAL, "Length dependence of bii"),
IOP( "lcii", B3SOIFD_MOD_LCII, IF_REAL, "Length dependence of cii"),
IOP( "ldii", B3SOIFD_MOD_LDII, IF_REAL, "Length dependence of dii"),
IOP( "lalpha0", B3SOIFD_MOD_LALPHA0, IF_REAL, "Length dependence of alpha0"),
IOP( "lalpha1", B3SOIFD_MOD_LALPHA1, IF_REAL, "Length dependence of alpha1"),
IOP( "lbeta0", B3SOIFD_MOD_LBETA0, IF_REAL, "Length dependence of beta0"),
IOP( "lagidl", B3SOIFD_MOD_LAGIDL, IF_REAL, "Length dependence of agidl"),
IOP( "lbgidl", B3SOIFD_MOD_LBGIDL, IF_REAL, "Length dependence of bgidl"),
IOP( "lngidl", B3SOIFD_MOD_LNGIDL, IF_REAL, "Length dependence of ngidl"),
IOP( "lntun", B3SOIFD_MOD_LNTUN, IF_REAL, "Length dependence of ntun"),
IOP( "lndiode", B3SOIFD_MOD_LNDIODE, IF_REAL, "Length dependence of ndiode"),
IOP( "lisbjt", B3SOIFD_MOD_LISBJT, IF_REAL, "Length dependence of isbjt"),
IOP( "lisdif", B3SOIFD_MOD_LISDIF, IF_REAL, "Length dependence of isdif"),
IOP( "lisrec", B3SOIFD_MOD_LISREC, IF_REAL, "Length dependence of isrec"),
IOP( "listun", B3SOIFD_MOD_LISTUN, IF_REAL, "Length dependence of istun"),
IOP( "ledl", B3SOIFD_MOD_LEDL, IF_REAL, "Length dependence of edl"),
IOP( "lkbjt1", B3SOIFD_MOD_LKBJT1, IF_REAL, "Length dependence of kbjt1"),
IOP( "lvsdfb", B3SOIFD_MOD_LVSDFB, IF_REAL, "Length dependence of vsdfb"),
IOP( "lvsdth", B3SOIFD_MOD_LVSDTH, IF_REAL, "Length dependence of vsdth"),
/* Width Dependence */
IOP( "wnch",  B3SOIFD_MOD_WNPEAK, IF_REAL, "Width dependence of nch"),
IOP( "wnsub", B3SOIFD_MOD_WNSUB, IF_REAL, "Width dependence of nsub"),
IOP( "wngate", B3SOIFD_MOD_WNGATE, IF_REAL, "Width dependence of ngate"),
IOP( "wvth0", B3SOIFD_MOD_WVTH0, IF_REAL,"Width dependence of vto"),
IOP( "wk1",   B3SOIFD_MOD_WK1,  IF_REAL, "Width dependence of k1"),
IOP( "wk2",   B3SOIFD_MOD_WK2,  IF_REAL, "Width dependence of k2"),
IOP( "wk3",   B3SOIFD_MOD_WK3,  IF_REAL, "Width dependence of k3"),
IOP( "wk3b",  B3SOIFD_MOD_WK3B, IF_REAL, "Width dependence of k3b"),
IOP( "wvbsa",  B3SOIFD_MOD_WVBSA, IF_REAL, "Width dependence of vbsa"),
IOP( "wdelp",  B3SOIFD_MOD_WDELP, IF_REAL, "Width dependence of delp"),
IOP( "wkb1",  B3SOIFD_MOD_WKB1, IF_REAL, "Width dependence of kb1"),
IOP( "wkb3",  B3SOIFD_MOD_WKB3, IF_REAL, "Width dependence of kb3"),
IOP( "wdvbd0",  B3SOIFD_MOD_WDVBD0, IF_REAL, "Width dependence of dvbd0"),
IOP( "wdvbd1",  B3SOIFD_MOD_WDVBD1, IF_REAL, "Width dependence of dvbd1"),
IOP( "ww0",   B3SOIFD_MOD_WW0,  IF_REAL, "Width dependence of w0"),
IOP( "wnlx",  B3SOIFD_MOD_WNLX, IF_REAL, "Width dependence of nlx"),
IOP( "wdvt0", B3SOIFD_MOD_WDVT0, IF_REAL, "Width dependence of dvt0"),
IOP( "wdvt1", B3SOIFD_MOD_WDVT1, IF_REAL, "Width dependence of dvt1"),
IOP( "wdvt2", B3SOIFD_MOD_WDVT2, IF_REAL, "Width dependence of dvt2"),
IOP( "wdvt0w", B3SOIFD_MOD_WDVT0W, IF_REAL, "Width dependence of dvt0w"),
IOP( "wdvt1w", B3SOIFD_MOD_WDVT1W, IF_REAL, "Width dependence of dvt1w"),
IOP( "wdvt2w", B3SOIFD_MOD_WDVT2W, IF_REAL, "Width dependence of dvt2w"),
IOP( "wu0",  B3SOIFD_MOD_WU0, IF_REAL, "Width dependence of u0"),
IOP( "wua",  B3SOIFD_MOD_WUA, IF_REAL, "Width dependence of ua"),
IOP( "wub", B3SOIFD_MOD_WUB, IF_REAL, "Width dependence of ub"),
IOP( "wuc",  B3SOIFD_MOD_WUC, IF_REAL, "Width dependence of uc"),
IOP( "wvsat", B3SOIFD_MOD_WVSAT, IF_REAL, "Width dependence of vsat"),
IOP( "wa0", B3SOIFD_MOD_WA0, IF_REAL, "Width dependence of a0"),
IOP( "wags", B3SOIFD_MOD_WAGS, IF_REAL, "Width dependence of ags"),
IOP( "wb0",  B3SOIFD_MOD_WB0, IF_REAL, "Width dependence of b0"),
IOP( "wb1",  B3SOIFD_MOD_WB1, IF_REAL, "Width dependence of b1"),
IOP( "wketa", B3SOIFD_MOD_WKETA, IF_REAL, "Width dependence of keta"),
IOP( "wabp", B3SOIFD_MOD_WABP, IF_REAL, "Width dependence of abp"),
IOP( "wmxc", B3SOIFD_MOD_WMXC, IF_REAL, "Width dependence of mxc"),
IOP( "wadice0", B3SOIFD_MOD_WADICE0, IF_REAL, "Width dependence of adice0"),
IOP( "wa1", B3SOIFD_MOD_WA1, IF_REAL, "Width dependence of a1"),
IOP( "wa2", B3SOIFD_MOD_WA2, IF_REAL, "Width dependence of a2"),
IOP( "wrdsw", B3SOIFD_MOD_WRDSW,  IF_REAL, "Width dependence of rdsw "),
IOP( "wprwb", B3SOIFD_MOD_WPRWB,  IF_REAL, "Width dependence of prwb "),
IOP( "wprwg", B3SOIFD_MOD_WPRWG,  IF_REAL, "Width dependence of prwg "),
IOP( "wwr",  B3SOIFD_MOD_WWR, IF_REAL, "Width dependence of wr"),
IOP( "wnfactor", B3SOIFD_MOD_WNFACTOR, IF_REAL, "Width dependence of nfactor"),
IOP( "wdwg", B3SOIFD_MOD_WDWG, IF_REAL, "Width dependence of dwg"),
IOP( "wdwb", B3SOIFD_MOD_WDWB, IF_REAL, "Width dependence of dwb"),
IOP( "wvoff", B3SOIFD_MOD_WVOFF, IF_REAL, "Width dependence of voff"),
IOP( "weta0", B3SOIFD_MOD_WETA0, IF_REAL, "Width dependence of eta0"),
IOP( "wetab", B3SOIFD_MOD_WETAB, IF_REAL, "Width dependence of etab"),
IOP( "wdsub", B3SOIFD_MOD_WDSUB, IF_REAL, "Width dependence of dsub"),
IOP( "wcit",   B3SOIFD_MOD_WCIT,  IF_REAL, "Width dependence of cit"),
IOP( "wcdsc",  B3SOIFD_MOD_WCDSC, IF_REAL, "Width dependence of cdsc"),
IOP( "wcdscb", B3SOIFD_MOD_WCDSCB, IF_REAL, "Width dependence of cdscb"),
IOP( "wcdscd", B3SOIFD_MOD_WCDSCD, IF_REAL, "Width dependence of cdscd"),
IOP( "wpclm", B3SOIFD_MOD_WPCLM, IF_REAL, "Width dependence of pclm"),
IOP( "wpdiblc1", B3SOIFD_MOD_WPDIBL1, IF_REAL, "Width dependence of pdiblc1"),
IOP( "wpdiblc2", B3SOIFD_MOD_WPDIBL2, IF_REAL, "Width dependence of pdiblc2"),
IOP( "wpdiblcb", B3SOIFD_MOD_WPDIBLB, IF_REAL, "Width dependence of pdiblcb"),
IOP( "wdrout", B3SOIFD_MOD_WDROUT, IF_REAL, "Width dependence of drout"),
IOP( "wpvag", B3SOIFD_MOD_WPVAG, IF_REAL, "Width dependence of pvag"),
IOP( "wdelta", B3SOIFD_MOD_WDELTA, IF_REAL, "Width dependence of delta"),
IOP( "waii", B3SOIFD_MOD_WAII, IF_REAL, "Width dependence of aii"),
IOP( "wbii", B3SOIFD_MOD_WBII, IF_REAL, "Width dependence of bii"),
IOP( "wcii", B3SOIFD_MOD_WCII, IF_REAL, "Width dependence of cii"),
IOP( "wdii", B3SOIFD_MOD_WDII, IF_REAL, "Width dependence of dii"),
IOP( "walpha0", B3SOIFD_MOD_WALPHA0, IF_REAL, "Width dependence of alpha0"),
IOP( "walpha1", B3SOIFD_MOD_WALPHA1, IF_REAL, "Width dependence of alpha1"),
IOP( "wbeta0", B3SOIFD_MOD_WBETA0, IF_REAL, "Width dependence of beta0"),
IOP( "wagidl", B3SOIFD_MOD_WAGIDL, IF_REAL, "Width dependence of agidl"),
IOP( "wbgidl", B3SOIFD_MOD_WBGIDL, IF_REAL, "Width dependence of bgidl"),
IOP( "wngidl", B3SOIFD_MOD_WNGIDL, IF_REAL, "Width dependence of ngidl"),
IOP( "wntun", B3SOIFD_MOD_WNTUN, IF_REAL, "Width dependence of ntun"),
IOP( "wndiode", B3SOIFD_MOD_WNDIODE, IF_REAL, "Width dependence of ndiode"),
IOP( "wisbjt", B3SOIFD_MOD_WISBJT, IF_REAL, "Width dependence of isbjt"),
IOP( "wisdif", B3SOIFD_MOD_WISDIF, IF_REAL, "Width dependence of isdif"),
IOP( "wisrec", B3SOIFD_MOD_WISREC, IF_REAL, "Width dependence of isrec"),
IOP( "wistun", B3SOIFD_MOD_WISTUN, IF_REAL, "Width dependence of istun"),
IOP( "wedl", B3SOIFD_MOD_WEDL, IF_REAL, "Width dependence of edl"),
IOP( "wkbjt1", B3SOIFD_MOD_WKBJT1, IF_REAL, "Width dependence of kbjt1"),
IOP( "wvsdfb", B3SOIFD_MOD_WVSDFB, IF_REAL, "Width dependence of vsdfb"),
IOP( "wvsdth", B3SOIFD_MOD_WVSDTH, IF_REAL, "Width dependence of vsdth"),
/* Cross-term Dependence */
IOP( "pnch",  B3SOIFD_MOD_PNPEAK, IF_REAL, "Cross-term dependence of nch"),
IOP( "pnsub", B3SOIFD_MOD_PNSUB, IF_REAL, "Cross-term dependence of nsub"),
IOP( "pngate", B3SOIFD_MOD_PNGATE, IF_REAL, "Cross-term dependence of ngate"),
IOP( "pvth0", B3SOIFD_MOD_PVTH0, IF_REAL,"Cross-term dependence of vto"),
IOP( "pk1",   B3SOIFD_MOD_PK1,  IF_REAL, "Cross-term dependence of k1"),
IOP( "pk2",   B3SOIFD_MOD_PK2,  IF_REAL, "Cross-term dependence of k2"),
IOP( "pk3",   B3SOIFD_MOD_PK3,  IF_REAL, "Cross-term dependence of k3"),
IOP( "pk3b",  B3SOIFD_MOD_PK3B, IF_REAL, "Cross-term dependence of k3b"),
IOP( "pvbsa",  B3SOIFD_MOD_PVBSA, IF_REAL, "Cross-term dependence of vbsa"),
IOP( "pdelp",  B3SOIFD_MOD_PDELP, IF_REAL, "Cross-term dependence of delp"),
IOP( "pkb1",  B3SOIFD_MOD_PKB1, IF_REAL, "Cross-term dependence of kb1"),
IOP( "pkb3",  B3SOIFD_MOD_PKB3, IF_REAL, "Cross-term dependence of kb3"),
IOP( "pdvbd0",  B3SOIFD_MOD_PDVBD0, IF_REAL, "Cross-term dependence of dvbd0"),
IOP( "pdvbd1",  B3SOIFD_MOD_PDVBD1, IF_REAL, "Cross-term dependence of dvbd1"),
IOP( "pw0",   B3SOIFD_MOD_PW0,  IF_REAL, "Cross-term dependence of w0"),
IOP( "pnlx",  B3SOIFD_MOD_PNLX, IF_REAL, "Cross-term dependence of nlx"),
IOP( "pdvt0", B3SOIFD_MOD_PDVT0, IF_REAL, "Cross-term dependence of dvt0"),
IOP( "pdvt1", B3SOIFD_MOD_PDVT1, IF_REAL, "Cross-term dependence of dvt1"),
IOP( "pdvt2", B3SOIFD_MOD_PDVT2, IF_REAL, "Cross-term dependence of dvt2"),
IOP( "pdvt0w", B3SOIFD_MOD_PDVT0W, IF_REAL, "Cross-term dependence of dvt0w"),
IOP( "pdvt1w", B3SOIFD_MOD_PDVT1W, IF_REAL, "Cross-term dependence of dvt1w"),
IOP( "pdvt2w", B3SOIFD_MOD_PDVT2W, IF_REAL, "Cross-term dependence of dvt2w"),
IOP( "pu0",  B3SOIFD_MOD_PU0, IF_REAL, "Cross-term dependence of u0"),
IOP( "pua",  B3SOIFD_MOD_PUA, IF_REAL, "Cross-term dependence of ua"),
IOP( "pub", B3SOIFD_MOD_PUB, IF_REAL, "Cross-term dependence of ub"),
IOP( "puc",  B3SOIFD_MOD_PUC, IF_REAL, "Cross-term dependence of uc"),
IOP( "pvsat", B3SOIFD_MOD_PVSAT, IF_REAL, "Cross-term dependence of vsat"),
IOP( "pa0", B3SOIFD_MOD_PA0, IF_REAL, "Cross-term dependence of a0"),
IOP( "pags", B3SOIFD_MOD_PAGS, IF_REAL, "Cross-term dependence of ags"),
IOP( "pb0",  B3SOIFD_MOD_PB0, IF_REAL, "Cross-term dependence of b0"),
IOP( "pb1",  B3SOIFD_MOD_PB1, IF_REAL, "Cross-term dependence of b1"),
IOP( "pketa", B3SOIFD_MOD_PKETA, IF_REAL, "Cross-term dependence of keta"),
IOP( "pabp", B3SOIFD_MOD_PABP, IF_REAL, "Cross-term dependence of abp"),
IOP( "pmxc", B3SOIFD_MOD_PMXC, IF_REAL, "Cross-term dependence of mxc"),
IOP( "padice0", B3SOIFD_MOD_PADICE0, IF_REAL, "Cross-term dependence of adice0"),
IOP( "pa1", B3SOIFD_MOD_PA1, IF_REAL, "Cross-term dependence of a1"),
IOP( "pa2", B3SOIFD_MOD_PA2, IF_REAL, "Cross-term dependence of a2"),
IOP( "prdsw", B3SOIFD_MOD_PRDSW,  IF_REAL, "Cross-term dependence of rdsw "),
IOP( "pprwb", B3SOIFD_MOD_PPRWB,  IF_REAL, "Cross-term dependence of prwb "),
IOP( "pprwg", B3SOIFD_MOD_PPRWG,  IF_REAL, "Cross-term dependence of prwg "),
IOP( "pwr",  B3SOIFD_MOD_PWR, IF_REAL, "Cross-term dependence of wr"),
IOP( "pnfactor", B3SOIFD_MOD_PNFACTOR, IF_REAL, "Cross-term dependence of nfactor"),
IOP( "pdwg", B3SOIFD_MOD_PDWG, IF_REAL, "Cross-term dependence of dwg"),
IOP( "pdwb", B3SOIFD_MOD_PDWB, IF_REAL, "Cross-term dependence of dwb"),
IOP( "pvoff", B3SOIFD_MOD_PVOFF, IF_REAL, "Cross-term dependence of voff"),
IOP( "peta0", B3SOIFD_MOD_PETA0, IF_REAL, "Cross-term dependence of eta0"),
IOP( "petab", B3SOIFD_MOD_PETAB, IF_REAL, "Cross-term dependence of etab"),
IOP( "pdsub", B3SOIFD_MOD_PDSUB, IF_REAL, "Cross-term dependence of dsub"),
IOP( "pcit",   B3SOIFD_MOD_PCIT,  IF_REAL, "Cross-term dependence of cit"),
IOP( "pcdsc",  B3SOIFD_MOD_PCDSC, IF_REAL, "Cross-term dependence of cdsc"),
IOP( "pcdscb", B3SOIFD_MOD_PCDSCB, IF_REAL, "Cross-term dependence of cdscb"),
IOP( "pcdscd", B3SOIFD_MOD_PCDSCD, IF_REAL, "Cross-term dependence of cdscd"),
IOP( "ppclm", B3SOIFD_MOD_PPCLM, IF_REAL, "Cross-term dependence of pclm"),
IOP( "ppdiblc1", B3SOIFD_MOD_PPDIBL1, IF_REAL, "Cross-term dependence of pdiblc1"),
IOP( "ppdiblc2", B3SOIFD_MOD_PPDIBL2, IF_REAL, "Cross-term dependence of pdiblc2"),
IOP( "ppdiblcb", B3SOIFD_MOD_PPDIBLB, IF_REAL, "Cross-term dependence of pdiblcb"),
IOP( "pdrout", B3SOIFD_MOD_PDROUT, IF_REAL, "Cross-term dependence of drout"),
IOP( "ppvag", B3SOIFD_MOD_PPVAG, IF_REAL, "Cross-term dependence of pvag"),
IOP( "pdelta", B3SOIFD_MOD_PDELTA, IF_REAL, "Cross-term dependence of delta"),
IOP( "paii", B3SOIFD_MOD_PAII, IF_REAL, "Cross-term dependence of aii"),
IOP( "pbii", B3SOIFD_MOD_PBII, IF_REAL, "Cross-term dependence of bii"),
IOP( "pcii", B3SOIFD_MOD_PCII, IF_REAL, "Cross-term dependence of cii"),
IOP( "pdii", B3SOIFD_MOD_PDII, IF_REAL, "Cross-term dependence of dii"),
IOP( "palpha0", B3SOIFD_MOD_PALPHA0, IF_REAL, "Cross-term dependence of alpha0"),
IOP( "palpha1", B3SOIFD_MOD_PALPHA1, IF_REAL, "Cross-term dependence of alpha1"),
IOP( "pbeta0", B3SOIFD_MOD_PBETA0, IF_REAL, "Cross-term dependence of beta0"),
IOP( "pagidl", B3SOIFD_MOD_PAGIDL, IF_REAL, "Cross-term dependence of agidl"),
IOP( "pbgidl", B3SOIFD_MOD_PBGIDL, IF_REAL, "Cross-term dependence of bgidl"),
IOP( "pngidl", B3SOIFD_MOD_PNGIDL, IF_REAL, "Cross-term dependence of ngidl"),
IOP( "pntun", B3SOIFD_MOD_PNTUN, IF_REAL, "Cross-term dependence of ntun"),
IOP( "pndiode", B3SOIFD_MOD_PNDIODE, IF_REAL, "Cross-term dependence of ndiode"),
IOP( "pisbjt", B3SOIFD_MOD_PISBJT, IF_REAL, "Cross-term dependence of isbjt"),
IOP( "pisdif", B3SOIFD_MOD_PISDIF, IF_REAL, "Cross-term dependence of isdif"),
IOP( "pisrec", B3SOIFD_MOD_PISREC, IF_REAL, "Cross-term dependence of isrec"),
IOP( "pistun", B3SOIFD_MOD_PISTUN, IF_REAL, "Cross-term dependence of istun"),
IOP( "pedl", B3SOIFD_MOD_PEDL, IF_REAL, "Cross-term dependence of edl"),
IOP( "pkbjt1", B3SOIFD_MOD_PKBJT1, IF_REAL, "Cross-term dependence of kbjt1"),
IOP( "pvsdfb", B3SOIFD_MOD_PVSDFB, IF_REAL, "Cross-term dependence of vsdfb"),
IOP( "pvsdth", B3SOIFD_MOD_PVSDTH, IF_REAL, "Cross-term dependence of vsdth"),
/* Added for binning - END */

IP( "nmos", B3SOIFD_MOD_NMOS,  IF_FLAG, "Flag to indicate NMOS"),
IP( "pmos", B3SOIFD_MOD_PMOS,  IF_FLAG, "Flag to indicate PMOS"),
};

char *B3SOIFDnames[] = {
   "Drain",
   "Gate",
   "Source",
   "Backgate",
   "",
   "Body",
   "Temp",
   "Charge",
};

int	B3SOIFDnSize = NUMELEMS(B3SOIFDnames);
int	B3SOIFDpTSize = NUMELEMS(B3SOIFDpTable);
int	B3SOIFDmPTSize = NUMELEMS(B3SOIFDmPTable);
int	B3SOIFDiSize = sizeof(B3SOIFDinstance);
int	B3SOIFDmSize = sizeof(B3SOIFDmodel);


