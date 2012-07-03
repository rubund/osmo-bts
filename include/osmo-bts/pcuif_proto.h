#ifndef _PCUIF_PROTO_H
#define _PCUIF_PROTO_H

/* msg_type */
#define PCU_IF_MSG_DATA_REQ	0x00	/* send data to given channel */
#define PCU_IF_MSG_DATA_IND	0x02	/* receive data from given channel */	
#define PCU_IF_MSG_RTS_REQ	0x10	/* ready to send data to given chan. */
#define PCU_IF_MSG_RACH_IND	0x22	/* receive rach */
#define PCU_IF_MSG_INFO_IND	0x32	/* retrieve BTS info */
#define PCU_IF_MSG_ACT_REQ	0x40	/* activate/deactivate PDCH */
#define PCU_IF_MSG_TIME_IND	0x52	/* gsm time indication */

/* sapi */
#define PCU_IF_SAPI_RACH	0x01	/* channel request on CCCH */
#define PCU_IF_SAPI_AGCH	0x02	/* assignment on CCCH */
#define PCU_IF_SAPI_PAGCH	0x03	/* paging request on CCCH */
#define PCU_IF_SAPI_BCCH	0x04	/* SI on BCCH */
#define PCU_IF_SAPI_PDTCH	0x05	/* packet data/control/ccch block */
#define PCU_IF_SAPI_PRACH	0x06	/* packet random access channel */
#define PCU_IF_SAPI_PTCCH	0x07	/* packet TA control channel */

/* flags */
#define PCU_IF_FLAG_ACTIVE	(1 << 0)/* BTS is active */
#define PCU_IF_FLAG_SYSMO	(1 << 1)/* access PDCH of sysmoBTS directly */

struct gsm_pcu_if_data {
	uint8_t		sapi;
	uint8_t		len;
	uint8_t		data[162];
	uint32_t	fn;
	uint16_t	arfcn;
	uint8_t		trx_nr;
	uint8_t		ts_nr;
	uint8_t		block_nr;
} __attribute__ ((packed));

struct gsm_pcu_if_rts_req {
	uint8_t		sapi;
	uint8_t		spare[3];
	uint32_t	fn;
	uint16_t	arfcn;
	uint8_t		trx_nr;
	uint8_t		ts_nr;
	uint8_t		block_nr;
} __attribute__ ((packed));

struct gsm_pcu_if_rach_ind {
	uint8_t		sapi;
	uint8_t		ra;
	int16_t		qta;
	uint32_t	fn;
	uint16_t	arfcn;
} __attribute__ ((packed));

struct gsm_pcu_if_info_trx {
	uint16_t	arfcn;
	uint8_t		pdch_mask;		/* PDCH channels per TS */
	uint8_t		spare;
	uint8_t		tsc[8];			/* TSC per channel */
} __attribute__ ((packed));

struct gsm_pcu_if_info_ind {
	uint32_t	flags;
	struct gsm_pcu_if_info_trx trx[8];	/* TRX infos per BTS */
} __attribute__ ((packed));

struct gsm_pcu_if_act_req {
	uint8_t		activate;
	uint8_t		trx_nr;
	uint8_t		ts_nr;
	uint8_t		spare;
} __attribute__ ((packed));

struct gsm_pcu_if_time_ind {
	uint32_t	fn;
} __attribute__ ((packed));

struct gsm_pcu_if {
	/* context based information */
	uint8_t		msg_type;	/* message type */
	uint8_t		bts_nr;		/* bts number */
	uint8_t		spare[2];

	union {
		struct gsm_pcu_if_data		data_req;
		struct gsm_pcu_if_data		data_ind;
		struct gsm_pcu_if_rts_req	rts_req;
		struct gsm_pcu_if_rach_ind	rach_ind;
		struct gsm_pcu_if_info_ind	info_ind;
		struct gsm_pcu_if_act_req	act_req;
		struct gsm_pcu_if_time_ind	time_ind;
	} u;
} __attribute__ ((packed));

#endif /* _PCUIF_PROTO_H */
