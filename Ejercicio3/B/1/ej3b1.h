/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _EJ3B1_H_RPCGEN
#define _EJ3B1_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define ej3b1 0x20000001
#define ej3b1v1 1

#if defined(__STDC__) || defined(__cplusplus)
#define ejecutartarea 1
extern  u_long * ejecutartarea_1(u_long *, CLIENT *);
extern  u_long * ejecutartarea_1_svc(u_long *, struct svc_req *);
extern int ej3b1_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ejecutartarea 1
extern  u_long * ejecutartarea_1();
extern  u_long * ejecutartarea_1_svc();
extern int ej3b1_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_EJ3B1_H_RPCGEN */
