/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "ej3b2.h"

bool_t
xdr_entrada (XDR *xdrs, entrada *objp)
{
	register int32_t *buf;

	int i;

	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, ( 256  + 256 ) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_vector (xdrs, (char *)objp->datos1, 256,
				sizeof (u_long), (xdrproc_t) xdr_u_long))
				 return FALSE;
			 if (!xdr_vector (xdrs, (char *)objp->datos2, 256,
				sizeof (u_long), (xdrproc_t) xdr_u_long))
				 return FALSE;
		} else {
			{
				register u_long *genp;

				for (i = 0, genp = objp->datos1;
					i < 256; ++i) {
					IXDR_PUT_U_LONG(buf, *genp++);
				}
			}
			{
				register u_long *genp;

				for (i = 0, genp = objp->datos2;
					i < 256; ++i) {
					IXDR_PUT_U_LONG(buf, *genp++);
				}
			}
		}
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, ( 256  + 256 ) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_vector (xdrs, (char *)objp->datos1, 256,
				sizeof (u_long), (xdrproc_t) xdr_u_long))
				 return FALSE;
			 if (!xdr_vector (xdrs, (char *)objp->datos2, 256,
				sizeof (u_long), (xdrproc_t) xdr_u_long))
				 return FALSE;
		} else {
			{
				register u_long *genp;

				for (i = 0, genp = objp->datos1;
					i < 256; ++i) {
					*genp++ = IXDR_GET_U_LONG(buf);
				}
			}
			{
				register u_long *genp;

				for (i = 0, genp = objp->datos2;
					i < 256; ++i) {
					*genp++ = IXDR_GET_U_LONG(buf);
				}
			}
		}
	 return TRUE;
	}

	 if (!xdr_vector (xdrs, (char *)objp->datos1, 256,
		sizeof (u_long), (xdrproc_t) xdr_u_long))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->datos2, 256,
		sizeof (u_long), (xdrproc_t) xdr_u_long))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_salida (XDR *xdrs, salida *objp)
{
	register int32_t *buf;

	int i;

	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, ( 512 ) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_vector (xdrs, (char *)objp->datos, 512,
				sizeof (u_long), (xdrproc_t) xdr_u_long))
				 return FALSE;
		} else {
			{
				register u_long *genp;

				for (i = 0, genp = objp->datos;
					i < 512; ++i) {
					IXDR_PUT_U_LONG(buf, *genp++);
				}
			}
		}
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, ( 512 ) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_vector (xdrs, (char *)objp->datos, 512,
				sizeof (u_long), (xdrproc_t) xdr_u_long))
				 return FALSE;
		} else {
			{
				register u_long *genp;

				for (i = 0, genp = objp->datos;
					i < 512; ++i) {
					*genp++ = IXDR_GET_U_LONG(buf);
				}
			}
		}
	 return TRUE;
	}

	 if (!xdr_vector (xdrs, (char *)objp->datos, 512,
		sizeof (u_long), (xdrproc_t) xdr_u_long))
		 return FALSE;
	return TRUE;
}