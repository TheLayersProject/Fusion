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

#ifndef FGRADIENTEDITORITEM
#define FGRADIENTEDITORITEM

#include <QGradientStop>

#include <Fusion/fusion_global.h>

#include <Fusion/fcolorcontrol.h>

FUSION_NAMESPACE_BEGIN

struct FGradientEditorItem
{
	QGradientStop stop;
	FColorControl* control;
};

inline bool compare_items(
	FGradientEditorItem* left, FGradientEditorItem* right)
{
	return left->control->x() < right->control->x();
}

FUSION_NAMESPACE_END

#endif // FGRADIENTEDITORITEM
