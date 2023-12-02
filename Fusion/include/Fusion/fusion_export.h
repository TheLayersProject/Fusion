/*
 * Copyright (C) 2023 The Layers Project
 *
 * This file is part of Fusion.
 *
 * Fusion is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fusion is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Fusion. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef FUSION_EXPORT_H
#define FUSION_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FUSION_LIB)
#  define FUSION_EXPORT Q_DECL_EXPORT
# else
#  define FUSION_EXPORT Q_DECL_IMPORT
# endif
#else
# define FUSION_EXPORT
#endif

#endif // FUSION_EXPORT_H
