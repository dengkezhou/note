#ifndef __DITH_H__
#define __DITH_H__

#define DIT_FSR				0x5c00
#define DIT_DCR				0x5c04
#define DIT_DMCO(x)			(0x5c08 + x * 4)


//DIT_FSR
#define DIT_FSR_VRES			(16)
#define DIT_FSR_HRES			(0)		
        
//DIT_DCR
#define DIT_DCR_RNB				(9)		
#define DIT_DCR_GNB				(6)		
#define DIT_DCR_BNB				(3)		
#define DIT_DCR_PASSBY			(2)	
#define DIT_DCR_TEMPO			(0)		
        
//DIT_DMCO0
#define DIT_DMCOx_DM00			(24)		
#define DIT_DMCOx_DM01			(16)	
#define DIT_DMCOx_DM02			(8)
#define DIT_DMCOx_DM03			(0)
        
enum dit_dmco {
	DIT_DMCO0,
	DIT_DMCO1,
	DIT_DMCO2,
	DIT_DMCO3,
	DIT_DMCO4,
	DIT_DMCO5,
	DIT_DMCO6,
	DIT_DMCO7,
	DIT_DMCO10,
	DIT_DMCO11,
	DIT_DMCO12,
	DIT_DMCO13,
	DIT_DMCO14,
	DIT_DMCO15,
	DIT_DMCO16,
	DIT_DMCO17,
	DIT_DMCO20,
	DIT_DMCO21,
	DIT_DMCO22,
	DIT_DMCO23,
	DIT_DMCO24,
	DIT_DMCO25,
	DIT_DMCO26,
	DIT_DMCO27,
	DIT_DMCO30,
	DIT_DMCO31,
	DIT_DMCO32,
	DIT_DMCO33,
	DIT_DMCO34,
	DIT_DMCO35,
	DIT_DMCO36,
	DIT_DMCO37,
};

#endif

