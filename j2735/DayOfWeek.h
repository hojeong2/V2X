/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AddGrpB"
 * 	found in "../asn/J2735_201603DA_copyright_updated 12.2.ASN"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_DayOfWeek_H_
#define	_DayOfWeek_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DayOfWeek {
	DayOfWeek_unknown	= 0,
	DayOfWeek_monday	= 1,
	DayOfWeek_tuesday	= 2,
	DayOfWeek_wednesday	= 3,
	DayOfWeek_thursday	= 4,
	DayOfWeek_friday	= 5,
	DayOfWeek_saturday	= 6,
	DayOfWeek_sunday	= 7
} e_DayOfWeek;

/* DayOfWeek */
typedef long	 DayOfWeek_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_DayOfWeek_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_DayOfWeek;
extern const asn_INTEGER_specifics_t asn_SPC_DayOfWeek_specs_1;
asn_struct_free_f DayOfWeek_free;
asn_struct_print_f DayOfWeek_print;
asn_constr_check_f DayOfWeek_constraint;
ber_type_decoder_f DayOfWeek_decode_ber;
der_type_encoder_f DayOfWeek_encode_der;
xer_type_decoder_f DayOfWeek_decode_xer;
xer_type_encoder_f DayOfWeek_encode_xer;
oer_type_decoder_f DayOfWeek_decode_oer;
oer_type_encoder_f DayOfWeek_encode_oer;
per_type_decoder_f DayOfWeek_decode_uper;
per_type_encoder_f DayOfWeek_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _DayOfWeek_H_ */
#include <asn_internal.h>
