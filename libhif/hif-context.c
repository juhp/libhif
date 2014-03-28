/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2014 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

/**
 * SECTION:hif-context
 * @short_description: High level interface to libhif.
 * @include: libhif.h
 * @stability: Stable
 *
 * This object is a high level interface that does not allow the the user
 * to use objects from librepo, rpm or hawkey directly.
 */

#include "config.h"

#include "hif-context.h"

typedef struct _HifContextPrivate	HifContextPrivate;
struct _HifContextPrivate
{
	gchar			*repo_dir;
};

G_DEFINE_TYPE_WITH_PRIVATE (HifContext, hif_context, G_TYPE_OBJECT)

#define GET_PRIVATE(o) (hif_context_get_instance_private (o))

/**
 * hif_context_finalize:
 **/
static void
hif_context_finalize (GObject *object)
{
	HifContext *context = HIF_CONTEXT (object);
	HifContextPrivate *priv = GET_PRIVATE (context);

	g_free (priv->repo_dir);

	G_OBJECT_CLASS (hif_context_parent_class)->finalize (object);
}

/**
 * hif_context_init:
 **/
static void
hif_context_init (HifContext *context)
{
}

/**
 * hif_context_class_init:
 **/
static void
hif_context_class_init (HifContextClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = hif_context_finalize;
}

/**
 * hif_context_get_repo_dir:
 * @context: a #HifContext instance.
 *
 * Gets the context ID.
 *
 * Returns: the context ID, e.g. "fedora-updates"
 *
 * Since: 0.1.0
 **/
const gchar *
hif_context_get_repo_dir (HifContext *context)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	return priv->repo_dir;
}

/**
 * hif_context_set_repo_dir:
 * @context: a #HifContext instance.
 * @repo_dir: the ID, e.g. "fedora-updates"
 *
 * Sets the context ID.
 *
 * Since: 0.1.0
 **/
void
hif_context_set_repo_dir (HifContext *context, const gchar *repo_dir)
{
	HifContextPrivate *priv = GET_PRIVATE (context);
	g_free (priv->repo_dir);
	priv->repo_dir = g_strdup (repo_dir);
}

/**
 * hif_context_new:
 *
 * Creates a new #HifContext.
 *
 * Returns: (transfer full): a #HifContext
 *
 * Since: 0.1.0
 **/
HifContext *
hif_context_new (void)
{
	HifContext *context;
	context = g_object_new (HIF_TYPE_CONTEXT, NULL);
	return HIF_CONTEXT (context);
}