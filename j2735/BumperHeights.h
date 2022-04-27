/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "../asn/J2735_201603DA_copyright_updated 12.2.ASN"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_BumperHeights_H_
#define	_BumperHeights_H_


#include <asn_application.h>

/* Including external dependencies */
#include "BumperHeight.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* BumperHeights */
typedef struct BumperHeights {
	BumperHeight_t	 front;
	BumperHeight_t	 rear;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BumperHeights_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BumperHeights;
extern asn_SEQUENCE_specifics_t asn_SPC_BumperHeights_specs_1;
extern asn_TYPE_member_t asn_MBR_BumperHeights_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _BumperHeights_H_ */
#include <asn_internal.h>
