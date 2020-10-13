#include <stdio.h>
#include <pmix.h>
#include <jtofu.h>

int main(int argc, char **argv){
    pmix_proc_t this_proc;
    pmix_proc_t job_proc;
    int rc;
    pmix_value_t *kv;
    jtofu_job_id_t jobid;

    rc = PMIx_Init(&this_proc, NULL, 0);
    if(rc != PMIX_SUCCESS){
        fprintf(stderr, "PMIx_Init failed. rc = %d\n", rc);
        return -1;
    }

    strcpy(job_proc.nspace, this_proc.nspace);
    job_proc.rank = PMIX_RANK_WILDCARD;

    rc = PMIx_Get(&job_proc, "fjpmix.rankmap", NULL, 0, &kv);
    if(rc != PMIX_SUCCESS){
        fprintf(stderr, "PMIx_Get failed. rc = %d\n", rc);
        return -1;
    }

    jobid = 0;

    rc = jtofu_initialize(jobid,
                          this_proc.rank,
                          kv->data.bo.bytes);

    if(rc != JTOFU_SUCCESS){
        fprintf(stderr, "jtofu_initialize failed. rc = %d\n", rc);
        return -1;
    }

    /* do something */
    printf("my rank is %d\n", this_proc.rank);

    jtofu_finalize();

    PMIx_Finalize(NULL, 0);

    return 0;
}
