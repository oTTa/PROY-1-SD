/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "ej3b1.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

u_long *
ejecutartarea_1(u_long *argp, CLIENT *clnt)
{
	static u_long clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ejecutartarea,
		(xdrproc_t) xdr_u_long, (caddr_t) argp,
		(xdrproc_t) xdr_u_long, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}