/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "ej7.h"

bool_t
xdr_tiempo (XDR *xdrs, tiempo *objp)
{
	register int32_t *buf;

	 if (!xdr_u_long (xdrs, &objp->seconds))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->useconds))
		 return FALSE;
	return TRUE;
}
