/**
 * @file
 * jTofu API
 */

#ifndef JTOFU_H
#define JTOFU_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@}***************************************************************//**
 * @defgroup version                                      Version Macros
 *
 * These macros represent the jTofu API version of compile-time.
 *
 * The jTofu API version of run-time can be obtained using the
 * `jtofu_query_jtofu_version()` function.
 ***************************************************************//**@{*/

/** jTofu API major version. */
#define JTOFU_VERSION_MAJOR 0
/** jTofu API minor version. */
#define JTOFU_VERSION_MINOR 0

/**@}***************************************************************//**
 * @defgroup typedef                                    Type Definitions
 ***************************************************************//**@{*/

/**
 * Job ID.
 *
 * A job ID is a 32-bit unsigned integer that identify a job.
 * A job is a set of processes launched at a time.
 * In the MPI world, a jTofu job corresponds to the group of `MPI_COMM_WORLD`.
 */
typedef uint32_t jtofu_job_id_t;

/**
 * Rank.
 *
 * A rank is a 32-bit unsigned integer that identify a process in a job.
 * Ranks in a job range from 0 to the number of processes in the job minus 1.
 */
typedef uint32_t jtofu_rank_t;

/**@}***************************************************************//**
 * @defgroup enum                                       Enumerated Types
 ***************************************************************//**@{*/

/**
 * Return codes.
 *
 * These enumeration constants are used for return values of almost all
 * functions of jTofu.
 */
enum jtofu_return_code {

    /** The operation has succeeded with no problems. */
    JTOFU_SUCCESS = 0,

    /** Error codes **/
    JTOFU_ERR_NOT_INITIALIZED = -1,
    JTOFU_ERR_NOT_IMPLEMENTED = -2,
    JTOFU_ERR_INVALID_ARG     = -3,
    JTOFU_ERR_INVALID_POINTER = -4,
    JTOFU_ERR_EXCESS_FINALIZE = -5,
    JTOFU_ERR_OUT_OF_MEMORY   = -6,
    JTOFU_ERR_INTERNAL        = -100,
};

/**@}***************************************************************//**
 * @defgroup struct                                    Structures/Unions
 ***************************************************************//**@{*/

union jtofu_phys_coords {
    struct {
        uint8_t x;
        uint8_t y;
        uint8_t z;
        uint8_t a;
        uint8_t b;
        uint8_t c;
    } s;
    uint8_t a[6];
};

union jtofu_log_coords {
    struct {
        uint32_t x;
        uint32_t y;
        uint32_t z;
    } s;
    uint32_t a[3];
};

union jtofu_path_coords {
    struct {
        uint8_t pa;
        uint8_t pb;
        uint8_t pc;
    } s;
    uint8_t a[3];
};

/**@}***************************************************************//**
 * @defgroup initfini              Initialization/Finalization Functions
 ***************************************************************//**@{*/

int jtofu_initialize(
    jtofu_job_id_t  job_id,
    jtofu_rank_t    rank,
    const void     *mapinfo);

int jtofu_finalize(void);

/**@}***************************************************************//**
 * @defgroup job                         Job Addition/Deletion Functions
 ***************************************************************//**@{*/

int jtofu_add_job(
    jtofu_job_id_t  job_id,
    const void     *mapinfo);

int jtofu_delete_job(
    jtofu_job_id_t job_id);

/**@}***************************************************************//**
 * @defgroup query                                       Query Functions
 ***************************************************************//**@{*/

int jtofu_query_sys_size(
    union jtofu_phys_coords *sys_size);

int jtofu_query_sys_torus(
    union jtofu_phys_coords *sys_torus);

int jtofu_query_ref_coords(
    union jtofu_phys_coords *ref_coords);

int jtofu_query_phys_size(
    union jtofu_phys_coords *phys_size);

int jtofu_query_log_size(
    union jtofu_log_coords *log_size);

int jtofu_query_phys_coords(
    jtofu_job_id_t           job_id,
    jtofu_rank_t             rank,
    union jtofu_phys_coords *phys_coords);

int jtofu_query_log_coords(
    jtofu_job_id_t          job_id,
    jtofu_rank_t            rank,
    union jtofu_log_coords *log_coords);

int jtofu_query_max_proc_per_node(void);

int jtofu_query_ranks_from_phys_coords(
    jtofu_job_id_t           job_id,
    union jtofu_phys_coords *phys_coords,
    size_t                   max_ranks,
    jtofu_rank_t            *ranks,
    size_t                  *num_ranks);

int jtofu_query_ranks_from_log_coords(
    jtofu_job_id_t          job_id,
    union jtofu_log_coords *log_coords,
    size_t                  max_ranks,
    jtofu_rank_t           *ranks,
    size_t                 *num_ranks);

int jtofu_query_onesided_paths(
    union jtofu_phys_coords *phys_coords,
    size_t                   max_paths,
    union jtofu_path_coords  path_coords[],
    size_t                  *num_paths);

int jtofu_query_barrier_paths(
    union jtofu_phys_coords *phys_coords,
    size_t                   max_paths,
    union jtofu_path_coords  path_coords[],
    size_t                  *num_paths);

int jtofu_query_onesided_hops(
    union jtofu_phys_coords *phys_coords,
    size_t                  *num_hops);

int jtofu_query_barrier_hops(
    union jtofu_phys_coords *phys_coords,
    size_t                  *num_hops);

/**@}***************************************************************//**
 * @defgroup supplement                             Supplement Functions
 ***************************************************************//**@{*/

/**
 * Query the version of jTofu run-time API.
 *
 * @param[out] major_ver Major version.
 * @param[out] minor_ver Minor version.
 */
extern void jtofu_query_jtofu_version(
    int *major_ver,
    int *minor_ver);

extern int jtofu_create_mapinfo_by_envvars(
    void         **mapinfo,
    size_t        *mapinfo_size,
    unsigned int  *num_proc);

#ifdef __cplusplus
}
#endif

#endif /* JTOFU_H */
