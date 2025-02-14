#ifndef __INFOTM_SCALER_H__
#define __INFOTM_SCALER_H__

struct scaler_case {
	int pos;
	int input_v;
	int input_h;
	int output_v;
	int output_h;
	int format;
};

#define SCALER_ZOOM_INIT(_pos, _input_v, _input_h, _output_v, _output_h, _format)	\
{ \
	.pos = _pos,	\
	.input_v = _input_v,    \
	.input_h = _input_h,    \
	.output_v = _output_v,    \
	.output_h = _output_h,    \
	.format = _format,    \
}

struct scaler_case scaler_rtl[] = {
	SCALER_ZOOM_INIT(     214,     580,     462,    1139,    1234,0x41ac3d94),
	SCALER_ZOOM_INIT(     429,     944,     270,    1442,      77,0xb8aaccad),
	SCALER_ZOOM_INIT(      13,     887,     819,    1584,    1351,0xcfddb4b8),
	SCALER_ZOOM_INIT(     883,       8,     397,    1036,     979,0x41a1820b),
	SCALER_ZOOM_INIT(     349,     836,      69,     567,    1952,0x82fd55d8),
	SCALER_ZOOM_INIT(     970,     132,      64,    1137,    1005,0x6359167c),
	SCALER_ZOOM_INIT(     398,     875,     263,    1175,    1926,0x8c2bd2b4),
	SCALER_ZOOM_INIT(     433,     998,     815,    1377,    1564,0x6039d2b0),
	SCALER_ZOOM_INIT(     581,     271,     298,     664,     875,0x44f64496),
	SCALER_ZOOM_INIT(     547,      72,     618,    1361,    1084,0xe6b0acad),
	SCALER_ZOOM_INIT(     885,     919,      28,    1103,    1500,0x4122c693),
	SCALER_ZOOM_INIT(     359,     896,     633,     158,    1660,0xac166f1b),
	SCALER_ZOOM_INIT(     284,     905,     341,    1992,    1388,0x01f335f1),
	SCALER_ZOOM_INIT(     699,     862,     297,    1652,     916,0x986920c2),
	SCALER_ZOOM_INIT(     120,     908,     666,    1633,    1141,0x6b8a61f3),
	SCALER_ZOOM_INIT(     487,     903,     291,     786,     952,0xcdedecac),
	SCALER_ZOOM_INIT(     686,     114,     274,    1221,      75,0xf35b4eaf),
	SCALER_ZOOM_INIT(     733,     965,     100,    1754,     493,0xbd3337ad),
	SCALER_ZOOM_INIT(     246,     441,     542,     956,     567,0xe8fa84be),
	SCALER_ZOOM_INIT(       0,     512,     512,    1024,    1024,0xc457e79e),
	SCALER_ZOOM_INIT(     425,     766,     418,    1847,     160,0xe48f81ad),
};

#endif
