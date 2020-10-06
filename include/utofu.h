/**
 * uTofu API.
 */

#ifndef UTOFU_H
#define UTOFU_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 * Version Macros
 **********************************************************************/

#define UTOFU_VERSION_MAJOR 1
#define UTOFU_VERSION_MINOR 0

/***********************************************************************
 * Bit Flags for utofu_onesided_caps::flags
 **********************************************************************/

#define UTOFU_ONESIDED_CAP_FLAG_SESSION_MODE (1UL <<  0)
#define UTOFU_ONESIDED_CAP_FLAG_ARMW         (1UL <<  1)

/***********************************************************************
 * Bit Flags for utofu_onesided_caps::armw_ops
 **********************************************************************/

#define UTOFU_ONESIDED_CAP_ARMW_OP_CSWAP (1UL <<  0)
#define UTOFU_ONESIDED_CAP_ARMW_OP_SWAP  (1UL <<  1)
#define UTOFU_ONESIDED_CAP_ARMW_OP_ADD   (1UL <<  2)
#define UTOFU_ONESIDED_CAP_ARMW_OP_XOR   (1UL <<  3)
#define UTOFU_ONESIDED_CAP_ARMW_OP_AND   (1UL <<  4)
#define UTOFU_ONESIDED_CAP_ARMW_OP_OR    (1UL <<  5)

/***********************************************************************
 * Bit Flags for utofu_barrier_caps::flags
 **********************************************************************/

/***********************************************************************
 * Bit Flags for utofu_barrier_caps::reduce_ops
 **********************************************************************/

#define UTOFU_BARRIER_CAP_REDUCE_OP_BARRIER (1UL <<  1)
#define UTOFU_BARRIER_CAP_REDUCE_OP_BAND    (1UL <<  2)
#define UTOFU_BARRIER_CAP_REDUCE_OP_BOR     (1UL <<  3)
#define UTOFU_BARRIER_CAP_REDUCE_OP_BXOR    (1UL <<  4)
#define UTOFU_BARRIER_CAP_REDUCE_OP_MAX     (1UL <<  5)
#define UTOFU_BARRIER_CAP_REDUCE_OP_MAXLOC  (1UL <<  6)
#define UTOFU_BARRIER_CAP_REDUCE_OP_SUM     (1UL <<  7)
#define UTOFU_BARRIER_CAP_REDUCE_OP_BFPSUM  (1UL <<  8)

/***********************************************************************
 * Bit Flags for utofu_create_vcq::flags
 **********************************************************************/

#define UTOFU_VCQ_FLAG_THREAD_SAFE  (1UL <<  0)

#define UTOFU_VCQ_FLAG_EXCLUSIVE    (1UL <<  1)

#define UTOFU_VCQ_FLAG_SESSION_MODE (1UL <<  2)

/***********************************************************************
 * Bit Flags for utofu_alloc_vbg::flags
 **********************************************************************/

#define UTOFU_VBG_FLAG_THREAD_SAFE  (1UL <<  0)

/***********************************************************************
 * Bit Flags for utofu_reg_mem::flags
 **********************************************************************/

#define UTOFU_REG_MEM_FLAG_READ_ONLY (1UL <<  0)

/***********************************************************************
 * Bit Flags for utofu_dereg_mem::flags
 **********************************************************************/

/***********************************************************************
 * Bit Flags for utofu_put::flags etc.
 **********************************************************************/

#define UTOFU_ONESIDED_FLAG_STRONG_ORDER      (1UL <<  0)

#define UTOFU_ONESIDED_FLAG_PACKET_RESPONSE   (1UL <<  1)

#define UTOFU_ONESIDED_FLAG_REMOTE_MRQ_NOTICE (1UL <<  2)

#define UTOFU_ONESIDED_FLAG_PADDING           (1UL <<  3)

#define UTOFU_ONESIDED_FLAG_CACHE_INJECTION   (1UL <<  5)

#define UTOFU_ONESIDED_FLAG_DELAY_START       (1UL <<  8)

#define UTOFU_ONESIDED_FLAG_TCQ_NOTICE        (1UL << 14)

#define UTOFU_ONESIDED_FLAG_LOCAL_MRQ_NOTICE  (1UL << 15)

#define UTOFU_ONESIDED_FLAG_PATH(path_id) \
    ((unsigned long int)path_id << 28)

#define UTOFU_ONESIDED_FLAG_SPS(sps) \
    ((unsigned long int)sps << 24)

/***********************************************************************
 * Bit Flags for utofu_barrier::flags etc.
 **********************************************************************/

/***********************************************************************
 * Bit Flags for utofu_poll_tcq::flags etc.
 **********************************************************************/

/***********************************************************************
 * Special values
 **********************************************************************/

#define UTOFU_VBG_ID_NULL ((utofu_vbg_id_t)-1)

#define UTOFU_PATH_COORD_NULL ((uint8_t)-1)

/***********************************************************************
 * Type Definitions
 **********************************************************************/

typedef uint16_t utofu_tni_id_t;

typedef uint16_t utofu_cq_id_t;

typedef uint16_t utofu_bg_id_t;

typedef uint16_t utofu_cmp_id_t;

typedef uintptr_t utofu_vcq_hdl_t;

typedef uint64_t utofu_vcq_id_t;

typedef uint64_t utofu_vbg_id_t;

typedef uint8_t  utofu_path_id_t;

typedef uint64_t utofu_stadd_t;

/***********************************************************************
 * Enumerated Types
 **********************************************************************/

enum utofu_return_code {

    UTOFU_SUCCESS              =    0,

    UTOFU_ERR_NOT_FOUND        =   -1,
    UTOFU_ERR_NOT_COMPLETED    =   -2,
    UTOFU_ERR_NOT_PROCESSED    =   -3,
    UTOFU_ERR_BUSY             =   -4,
    UTOFU_ERR_USED             =   -5,
    UTOFU_ERR_FULL             =   -6,
    UTOFU_ERR_NOT_AVAILABLE    =   -7,
    UTOFU_ERR_NOT_SUPPORTED    =   -8,

    UTOFU_ERR_TCQ_OTHER        = -128,
    UTOFU_ERR_TCQ_DESC         = -129,
    UTOFU_ERR_TCQ_MEMORY       = -130,
    UTOFU_ERR_TCQ_STADD        = -131,
    UTOFU_ERR_TCQ_LENGTH       = -132,

    UTOFU_ERR_MRQ_OTHER        = -192,
    UTOFU_ERR_MRQ_PEER         = -193,
    UTOFU_ERR_MRQ_LCL_MEMORY   = -194,
    UTOFU_ERR_MRQ_RMT_MEMORY   = -195,
    UTOFU_ERR_MRQ_LCL_STADD    = -196,
    UTOFU_ERR_MRQ_RMT_STADD    = -197,
    UTOFU_ERR_MRQ_LCL_LENGTH   = -198,
    UTOFU_ERR_MRQ_RMT_LENGTH   = -199,

    UTOFU_ERR_BARRIER_OTHER    = -256,
    UTOFU_ERR_BARRIER_MISMATCH = -257,

    UTOFU_ERR_INVALID_ARG      = -512,
    UTOFU_ERR_INVALID_POINTER  = -513,
    UTOFU_ERR_INVALID_FLAGS    = -514,
    UTOFU_ERR_INVALID_COORDS   = -515,
    UTOFU_ERR_INVALID_PATH     = -516,
    UTOFU_ERR_INVALID_TNI_ID   = -517,
    UTOFU_ERR_INVALID_CQ_ID    = -518,
    UTOFU_ERR_INVALID_BG_ID    = -519,
    UTOFU_ERR_INVALID_CMP_ID   = -520,
    UTOFU_ERR_INVALID_VCQ_HDL  = -521,
    UTOFU_ERR_INVALID_VCQ_ID   = -522,
    UTOFU_ERR_INVALID_VBG_ID   = -523,
    UTOFU_ERR_INVALID_PATH_ID  = -524,
    UTOFU_ERR_INVALID_STADD    = -525,
    UTOFU_ERR_INVALID_ADDRESS  = -526,
    UTOFU_ERR_INVALID_SIZE     = -527,
    UTOFU_ERR_INVALID_STAG     = -528,
    UTOFU_ERR_INVALID_EDATA    = -529,
    UTOFU_ERR_INVALID_NUMBER   = -530,
    UTOFU_ERR_INVALID_OP       = -531,
    UTOFU_ERR_INVALID_DESC     = -532,
    UTOFU_ERR_INVALID_DATA     = -533,

    UTOFU_ERR_OUT_OF_RESOURCE  = -640,
    UTOFU_ERR_OUT_OF_MEMORY    = -641,

    UTOFU_ERR_FATAL            = -768
};

enum utofu_armw_op {
    UTOFU_ARMW_OP_SWAP = 1,
    UTOFU_ARMW_OP_ADD  = 2,
    UTOFU_ARMW_OP_XOR  = 3,
    UTOFU_ARMW_OP_AND  = 4,
    UTOFU_ARMW_OP_OR   = 5
};

enum utofu_reduce_op {
    UTOFU_REDUCE_OP_BARRIER = 1,
    UTOFU_REDUCE_OP_BAND    = 2,
    UTOFU_REDUCE_OP_BOR     = 3,
    UTOFU_REDUCE_OP_BXOR    = 4,
    UTOFU_REDUCE_OP_MAX     = 5,
    UTOFU_REDUCE_OP_MAXLOC  = 6,
    UTOFU_REDUCE_OP_SUM     = 7,
    UTOFU_REDUCE_OP_BFPSUM  = 8
};

enum utofu_mrq_notice_type {
    UTOFU_MRQ_TYPE_LCL_PUT,
    UTOFU_MRQ_TYPE_RMT_PUT,
    UTOFU_MRQ_TYPE_LCL_GET,
    UTOFU_MRQ_TYPE_RMT_GET,
    UTOFU_MRQ_TYPE_LCL_ARMW,
    UTOFU_MRQ_TYPE_RMT_ARMW
};

/***********************************************************************
 * Structures
 **********************************************************************/

struct utofu_onesided_caps {
    unsigned long int flags;
    unsigned long int armw_ops;
    unsigned int      num_cmp_ids;
    unsigned int      num_reserved_stags;
    size_t            cache_line_size;
    size_t            stag_address_alignment;
    size_t            max_toq_desc_size;
    size_t            max_putget_size;
    size_t            max_piggyback_size;
    size_t            max_edata_size;
    size_t            max_mtu;
    size_t            max_gap;
};

struct utofu_barrier_caps {
    unsigned long int flags;
    unsigned long int reduce_ops;
    size_t            max_uint64_reduction;
    size_t            max_double_reduction;
};

struct utofu_vbg_setting {
    utofu_vbg_id_t vbg_id;
    utofu_vbg_id_t src_lcl_vbg_id;
    utofu_vbg_id_t src_rmt_vbg_id;
    utofu_vbg_id_t dst_lcl_vbg_id;
    utofu_vbg_id_t dst_rmt_vbg_id;
    uint8_t        dst_path_coords[3];
};

struct utofu_mrq_notice {
    uint8_t        notice_type;
    uint8_t        padding1[7];
    utofu_vcq_id_t vcq_id;
    uint64_t       edata;
    uint64_t       rmt_value;
    utofu_stadd_t  lcl_stadd;
    utofu_stadd_t  rmt_stadd;
    uint64_t       reserved[2];
};

/***********************************************************************
 * TNI Query Functions
 **********************************************************************/

extern int utofu_get_onesided_tnis(
    utofu_tni_id_t **tni_ids,
    size_t          *num_tnis);

extern int utofu_get_barrier_tnis(
    utofu_tni_id_t **tni_ids,
    size_t          *num_tnis);

extern int utofu_query_onesided_caps(
    utofu_tni_id_t               tni_id,
    struct utofu_onesided_caps **tni_caps);

extern int utofu_query_barrier_caps(
    utofu_tni_id_t              tni_id,
    struct utofu_barrier_caps **tni_caps);

/***********************************************************************
 * VCQ Management Functions
 **********************************************************************/

extern int utofu_create_vcq(
    utofu_tni_id_t     tni_id,
    unsigned long int  flags,
    utofu_vcq_hdl_t   *vcq_hdl);

extern int utofu_create_vcq_with_cmp_id(
    utofu_tni_id_t     tni_id,
    utofu_cmp_id_t     cmp_id,
    unsigned long int  flags,
    utofu_vcq_hdl_t   *vcq_hdl);

extern int utofu_free_vcq(
    utofu_vcq_hdl_t vcq_hdl);

extern int utofu_query_vcq_id(
    utofu_vcq_hdl_t  vcq_hdl,
    utofu_vcq_id_t  *vcq_id);

extern int utofu_construct_vcq_id(
    uint8_t         coords[],
    utofu_tni_id_t  tni_id,
    utofu_cq_id_t   cq_id,
    utofu_cmp_id_t  cmp_id,
    utofu_vcq_id_t *vcq_id);

extern int utofu_set_vcq_id_path(
    utofu_vcq_id_t *vcq_id,
    uint8_t         path_coords[]);

extern int utofu_query_vcq_info(
    utofu_vcq_id_t  vcq_id,
    uint8_t         coords[],
    utofu_tni_id_t *tni_id,
    utofu_cq_id_t  *cq_id,
    uint16_t       *extra_val);

/***********************************************************************
 * VBG Management Functions
 **********************************************************************/

extern int utofu_alloc_vbg(
    utofu_tni_id_t    tni_id,
    size_t            num_vbgs,
    unsigned long int flags,
    utofu_vbg_id_t    vbg_ids[]);

extern int utofu_free_vbg(
    utofu_vbg_id_t vbg_ids[],
    size_t         num_vbgs);

extern int utofu_set_vbg(
    struct utofu_vbg_setting vbg_settings[],
    size_t                   num_vbg_settings);

extern int utofu_query_vbg_info(
    utofu_vbg_id_t  vbg_id,
    uint8_t         coords[],
    utofu_tni_id_t *tni_id,
    utofu_bg_id_t  *bg_id,
    uint16_t       *extra_val);

/***********************************************************************
 * Communication Path Management Functions
 **********************************************************************/

extern int utofu_get_path_id(
    utofu_vcq_id_t   vcq_id,
    uint8_t          path_coords[],
    utofu_path_id_t *path_id);

extern int utofu_get_path_coords(
    utofu_vcq_id_t  vcq_id,
    utofu_path_id_t path_id,
    uint8_t         path_coords[]);

/***********************************************************************
 * STADD Management Functions
 **********************************************************************/

extern int utofu_reg_mem(
    utofu_vcq_hdl_t    vcq_hdl,
    void              *addr,
    size_t             size,
    unsigned long int  flags,
    utofu_stadd_t     *stadd);

extern int utofu_reg_mem_with_stag(
    utofu_vcq_hdl_t    vcq_hdl,
    void              *addr,
    size_t             size,
    unsigned int       stag,
    unsigned long int  flags,
    utofu_stadd_t     *stadd);

extern int utofu_query_stadd(
    utofu_vcq_id_t  vcq_id,
    unsigned int    stag,
    utofu_stadd_t  *stadd);

extern int utofu_dereg_mem(
    utofu_vcq_hdl_t   vcq_hdl,
    utofu_stadd_t     stadd,
    unsigned long int flags);

/***********************************************************************
 * One-sided Communication Execution Functions
 **********************************************************************/

extern int utofu_put(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_put_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *cbdata);

extern int utofu_put_stride(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_put_stride_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *cbdata);

extern int utofu_put_piggyback(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    void              *lcl_data,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_put_piggyback8(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    uint64_t           lcl_data,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_get(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_get_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *cbdata);

extern int utofu_get_stride(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_get_stride_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *cbdata);

extern int utofu_armw4(
    utofu_vcq_hdl_t     vcq_hdl,
    utofu_vcq_id_t      rmt_vcq_id,
    enum utofu_armw_op  armw_op,
    uint32_t            op_value,
    utofu_stadd_t       rmt_stadd,
    uint64_t            edata,
    unsigned long int   flags,
    void               *cbdata);

extern int utofu_armw8(
    utofu_vcq_hdl_t     vcq_hdl,
    utofu_vcq_id_t      rmt_vcq_id,
    enum utofu_armw_op  armw_op,
    uint64_t            op_value,
    utofu_stadd_t       rmt_stadd,
    uint64_t            edata,
    unsigned long int   flags,
    void               *cbdata);

extern int utofu_cswap4(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    uint32_t           old_value,
    uint32_t           new_value,
    utofu_stadd_t      rmt_stadd,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_cswap8(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    uint64_t           old_value,
    uint64_t           new_value,
    utofu_stadd_t      rmt_stadd,
    uint64_t           edata,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_nop(
    utofu_vcq_hdl_t    vcq_hdl,
    unsigned long int  flags,
    void              *cbdata);

extern int utofu_prepare_put(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_put_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_put_stride(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_put_stride_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_put_piggyback(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    void              *lcl_data,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_put_piggyback8(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    uint64_t           lcl_data,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_get(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_get_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_get_stride(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_get_stride_gap(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    utofu_stadd_t      lcl_stadd,
    utofu_stadd_t      rmt_stadd,
    size_t             length,
    size_t             stride,
    size_t             num_blocks,
    uint64_t           edata,
    unsigned long int  flags,
    size_t             mtu,
    size_t             gap,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_armw4(
    utofu_vcq_hdl_t     vcq_hdl,
    utofu_vcq_id_t      rmt_vcq_id,
    enum utofu_armw_op  armw_op,
    uint32_t            op_value,
    utofu_stadd_t       rmt_stadd,
    uint64_t            edata,
    unsigned long int   flags,
    void               *desc,
    size_t             *desc_size);

extern int utofu_prepare_armw8(
    utofu_vcq_hdl_t     vcq_hdl,
    utofu_vcq_id_t      rmt_vcq_id,
    enum utofu_armw_op  armw_op,
    uint64_t            op_value,
    utofu_stadd_t       rmt_stadd,
    uint64_t            edata,
    unsigned long int   flags,
    void               *desc,
    size_t             *desc_size);

extern int utofu_prepare_cswap4(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    uint32_t           old_value,
    uint32_t           new_value,
    utofu_stadd_t      rmt_stadd,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_cswap8(
    utofu_vcq_hdl_t    vcq_hdl,
    utofu_vcq_id_t     rmt_vcq_id,
    uint64_t           old_value,
    uint64_t           new_value,
    utofu_stadd_t      rmt_stadd,
    uint64_t           edata,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_prepare_nop(
    utofu_vcq_hdl_t    vcq_hdl,
    unsigned long int  flags,
    void              *desc,
    size_t            *desc_size);

extern int utofu_post_toq(
    utofu_vcq_hdl_t  vcq_hdl,
    void            *desc,
    size_t           desc_size,
    void            *cbdata);

extern int utofu_poll_tcq(
    utofu_vcq_hdl_t     vcq_hdl,
    unsigned long int   flags,
    void              **cbdata);

extern int utofu_poll_mrq(
    utofu_vcq_hdl_t          vcq_hdl,
    unsigned long int        flags,
    struct utofu_mrq_notice *notice);

extern int utofu_query_num_unread_tcq(
    utofu_vcq_hdl_t  vcq_hdl,
    size_t          *count);

extern int utofu_query_num_unread_mrq(
    utofu_vcq_hdl_t  vcq_hdl,
    size_t          *count);

/***********************************************************************
 * Barrier Communication Execution Functions
 **********************************************************************/

extern int utofu_barrier(
    utofu_vbg_id_t    vbg_id,
    unsigned long int flags);

extern int utofu_reduce_uint64(
    utofu_vbg_id_t       vbg_id,
    enum utofu_reduce_op op,
    uint64_t             data[],
    size_t               num_data,
    unsigned long int    flags);

extern int utofu_reduce_double(
    utofu_vbg_id_t       vbg_id,
    enum utofu_reduce_op op,
    double               data[],
    size_t               num_data,
    unsigned long int    flags);

extern int utofu_poll_barrier(
    utofu_vbg_id_t    vbg_id,
    unsigned long int flags);

extern int utofu_poll_reduce_uint64(
    utofu_vbg_id_t    vbg_id,
    unsigned long int flags,
    uint64_t          data[]);

extern int utofu_poll_reduce_double(
    utofu_vbg_id_t    vbg_id,
    unsigned long int flags,
    double            data[]);

/***********************************************************************
 * Supplemental Feature Functions
 **********************************************************************/

extern void utofu_query_tofu_version(
    int *major_ver,
    int *minor_ver);

extern void utofu_query_utofu_version(
    int *major_ver,
    int *minor_ver);

extern int utofu_query_my_coords(
    uint8_t coords[]);

/**********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* UTOFU_H */
