/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _EJ7_H_RPCGEN
#define _EJ7_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct tiempo {
	u_long seconds;
	u_long useconds;
};
typedef struct tiempo tiempo;

#define ej7 0x20000001
#define ej7v1 1

#if defined(__STDC__) || defined(__cplusplus)
#define horaSistema 1
extern  tiempo * horasistema_1(void *, CLIENT *);
extern  tiempo * horasistema_1_svc(void *, struct svc_req *);
extern int ej7_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define horaSistema 1
extern  tiempo * horasistema_1();
extern  tiempo * horasistema_1_svc();
extern int ej7_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_tiempo (XDR *, tiempo*);

#else /* K&R C */
extern bool_t xdr_tiempo ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_EJ7_H_RPCGEN */
