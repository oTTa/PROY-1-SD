/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _EJ3B2_H_RPCGEN
#define _EJ3B2_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct entrada {
	u_long datos1[256];
	u_long datos2[256];
};
typedef struct entrada entrada;

struct salida {
	u_long datos[512];
};
typedef struct salida salida;

#define ej3b1 0x20000001
#define ej3b1v1 1

#if defined(__STDC__) || defined(__cplusplus)
#define ejecutartarea 1
extern  salida * ejecutartarea_1(entrada *, CLIENT *);
extern  salida * ejecutartarea_1_svc(entrada *, struct svc_req *);
extern int ej3b1_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ejecutartarea 1
extern  salida * ejecutartarea_1();
extern  salida * ejecutartarea_1_svc();
extern int ej3b1_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_entrada (XDR *, entrada*);
extern  bool_t xdr_salida (XDR *, salida*);

#else /* K&R C */
extern bool_t xdr_entrada ();
extern bool_t xdr_salida ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_EJ3B2_H_RPCGEN */