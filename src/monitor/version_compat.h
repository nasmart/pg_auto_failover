/*-------------------------------------------------------------------------
 *
 * src/monitor/version_compat.h
 *	  Compatibility macros for writing code agnostic to PostgreSQL versions
 *
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the PostgreSQL License.
 *
 *-------------------------------------------------------------------------
 */

#ifndef VERSION_COMPAT_H
#define VERSION_COMPAT_H

#include "postgres.h"

/* we only support Postgres versions 10, 11, and 12. */
#if (PG_VERSION_NUM < 100000 || PG_VERSION_NUM >= 130000)
#error "Unknown or unsupported postgresql version"
#endif

#if (PG_VERSION_NUM < 110000)

#include "postmaster/bgworker.h"
#include "utils/memutils.h"

#define DEFAULT_XLOG_SEG_SIZE XLOG_SEG_SIZE

#define BackgroundWorkerInitializeConnection(dbname, username, flags) \
	BackgroundWorkerInitializeConnection(dbname, username)

#define BackgroundWorkerInitializeConnectionByOid(dboid, useroid, flags) \
	BackgroundWorkerInitializeConnectionByOid(dboid, useroid)

#endif

#if (PG_VERSION_NUM < 120000)

#define table_beginscan_catalog heap_beginscan_catalog
#define TableScanDesc HeapScanDesc

#endif

#if (PG_VERSION_NUM >= 120000)

#include "access/htup_details.h"
#include "catalog/pg_database.h"

static inline Oid HeapTupleGetOid(HeapTuple tuple)
{
	Form_pg_database dbForm = (Form_pg_database) GETSTRUCT(tuple);
	return dbForm->oid;
}

#endif

#endif   /* VERSION_COMPAT_H */
