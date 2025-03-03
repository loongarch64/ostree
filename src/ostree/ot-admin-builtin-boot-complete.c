/*
 * Copyright (C) 2022 Red Hat, Inc.
 *
 * SPDX-License-Identifier: LGPL-2.0+
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <https://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <stdlib.h>

#include "ot-main.h"
#include "ot-admin-builtins.h"
#include "ot-admin-functions.h"
#include "ostree.h"
#include "otutil.h"

#include "ostree-cmdprivate.h"

static GOptionEntry options[] = {
  { NULL }
};

gboolean
ot_admin_builtin_boot_complete (int argc, char **argv, OstreeCommandInvocation *invocation, GCancellable *cancellable, GError **error)
{
  /* Just a sanity check; we shouldn't be called outside of the service though.
   */
  struct stat stbuf;
  if (fstatat (AT_FDCWD, OSTREE_PATH_BOOTED, &stbuf, 0) < 0)
    return TRUE;
  // We must have been invoked via systemd which should have set up a mount namespace.
  g_assert (getenv ("INVOCATION_ID"));

  g_autoptr(GOptionContext) context = g_option_context_new ("");
  g_autoptr(OstreeSysroot) sysroot = NULL;
  if (!ostree_admin_option_context_parse (context, options, &argc, &argv,
                                          OSTREE_ADMIN_BUILTIN_FLAG_SUPERUSER,
                                          invocation, &sysroot, cancellable, error))
    return FALSE;

  if (!ostree_cmd__private__()->ostree_boot_complete (sysroot, cancellable, error))
    return FALSE;

  return TRUE;
}
