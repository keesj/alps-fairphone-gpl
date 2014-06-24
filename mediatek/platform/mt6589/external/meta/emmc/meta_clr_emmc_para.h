/*****************************************************************************
 *
 * Filename:
 * ---------
 *   meta_fm.h
 *
 * Project:
 * --------
 *   YUSU
 *
 * Description:
 * ------------
 *   FM meta data struct define.
 *
 * Author:
 * -------
 *  LiChunhui (MTK80143)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * 07 03 2012 vend_am00076
 * [ALPS00269605] [MP Feature Patch Back]Shared sdcard feature support
 * shared sdcard --meta mode
 *
 * 03 12 2012 vend_am00076
 * [ALPS00251394] [Patch Request]
 * .
 *
 * 03 02 2012 vend_am00076
 * NULL
 * .
 *
 * 12 03 2010 hongcheng.xia
 * [ALPS00136616] [Need Patch] [Volunteer Patch]FM Meta bugs Fix
 * .
 *
 * 11 18 2010 hongcheng.xia
 * [ALPS00135614] [Need Patch] [Volunteer Patch]MT6620 FM Radio code check in
 * .
 *
 * 08 28 2010 chunhui.li
 * [ALPS00123709] [Bluetooth] meta mode check in
 * for FM meta enable

 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by CC/CQ. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef __META_CLR_EMMC_H_
#define __META_CLR_EMMC_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
     FT_EMMC_OP_CLEAR = 0,
     FT_EMMC_OP_FORMAT_TCARD,
     FT_EMMC_OP_CLEAR_WITHOUT_TCARD,
     FT_EMMC_END
}FT_EMMC_OP;

typedef struct {       
    unsigned char   status;   // The operation whether success , 1 means success
} EMMC_CLEAR_CNF;

typedef struct {
    unsigned char status;
}EMMC_CLEAR_WITHOUT_TCARD_CNF;

typedef struct
{       
  unsigned char   status;   // The operation whether success , 1 means success
} EMMC_FORMAT_TCARD_CNF;

typedef union {
  EMMC_CLEAR_CNF     clear_cnf;
  EMMC_FORMAT_TCARD_CNF   form_tcard_cnf;
  EMMC_CLEAR_WITHOUT_TCARD_CNF clear_without_tcard_cnf;
} FT_EMMC_RESULT;

typedef struct {       
    unsigned char   sign;   // No means
} EMMC_CLEAR_REQ;

typedef struct
{
  unsigned char   sign;   // No means
} EMMC_FORMAT_TCARD_REQ;

typedef struct {
    unsigned char   sign;
} EMMC_CLEAR_WITHOUT_TCARD_REQ;

typedef union {
  EMMC_CLEAR_REQ     clear_req;
  EMMC_FORMAT_TCARD_REQ   format_tcard_req;
  EMMC_CLEAR_WITHOUT_TCARD_REQ clear_without_tcard_req;
} FT_EMMC_CMD;

typedef struct {
    FT_H	       header;  
    FT_EMMC_OP	       op;
    FT_EMMC_CMD  cmd;
} FT_EMMC_REQ;

typedef struct {
     FT_H	    header;
     FT_EMMC_OP	    op;
     unsigned char  m_status;   // The data frame state, 0 means normal
     FT_EMMC_RESULT  result;
} FT_EMMC_CNF;

bool META_CLR_EMMC_init();
void META_CLR_EMMC_deinit();
void META_CLR_EMMC_OP(FT_EMMC_REQ *req) ;

#ifdef __cplusplus
};
#endif

#endif

