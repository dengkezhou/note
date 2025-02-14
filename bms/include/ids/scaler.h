#ifndef __OSD_SCALER_H__
#define __OSD_SCALER_H__

#define SCALER_INPUT_ADDR       0
#define SCALER_OUTPUT_ADDR      1

struct scaler_resolution {
	uint32_t vertical;    
	uint32_t horizontal;  
};

#define SCALER_RESOLUTION_INIT(_horizontal, _vertical)  \
{ \
	.vertical = _vertical,                              \
	.horizontal = _horizontal,                          \
}   

enum zoom_mode {            
	ZOOMIN,                 
	ZOOMOUT,                
};                          

enum zoom_type {            
	AVERAGE_VARIABLE,       
	AVERAGE_4_4,            
	SPLINE_0_5,             
	SPLINE_1_0,             
	BILINEAR,               
};                          

struct zoom_cfg {           
	enum zoom_mode mode;    
	enum zoom_type type;    
	uint32_t coe_interp[64];
};                          

struct scaler_module {
	int bypass;
	struct scaler_resolution out_resolute;
	struct scaler_resolution in_resolute;
};

#endif
