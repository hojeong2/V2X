/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "../asn/J2735_201603DA_copyright_updated 12.2.ASN"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RTCMmessage_H_
#define	_RTCMmessage_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RTCMmessage */
typedef OCTET_STRING_t	 RTCMmessage_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_RTCMmessage_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_RTCMmessage;
asn_struct_free_f RTCMmessage_free;
asn_struct_print_f RTCMmessage_print;
asn_constr_check_f RTCMmessage_constraint;
ber_type_decoder_f RTCMmessage_decode_ber;
der_type_encoder_f RTCMmessage_encode_der;
xer_type_decoder_f RTCMmessage_decode_xer;
xer_type_encoder_f RTCMmessage_encode_xer;
oer_type_decoder_f RTCMmessage_decode_oer;
oer_type_encoder_f RTCMmessage_encode_oer;
per_type_decoder_f RTCMmessage_decode_uper;
per_type_encoder_f RTCMmessage_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _RTCMmessage_H_ */
#include <asn_internal.h>
