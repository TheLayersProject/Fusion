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

#ifndef FFILLCONTROL_H
#define FFILLCONTROL_H

#include <Layers/lattribute.h>

#include "fusion_global.h"
#include "fusion_export.h"

#include <QLayers/qlwidget.h>

FUSION_NAMESPACE_BEGIN
class FFillDialog;

class FUSION_EXPORT FFillControl : public QLayers::QLWidget
{
	Q_OBJECT

public:
	FFillControl(QWidget* parent = nullptr);

	~FFillControl();

	void set_attribute(Layers::LAttribute* attribute);

protected:
	bool eventFilter(QObject* object, QEvent* event);

private:
	void init_attributes();
};
FUSION_NAMESPACE_END

#endif // FFILLCONTROL_H
