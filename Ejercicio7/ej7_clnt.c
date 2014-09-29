/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "ej7.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

tiempo *
horasistema_1(void *argp, CLIENT *clnt)
{
	static tiempo clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, horaSistema,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_tiempo, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}