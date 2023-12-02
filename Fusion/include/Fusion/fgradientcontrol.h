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

#ifndef FGRADIENTCONTROL_H
#define FGRADIENTCONTROL_H

#include <QLayers/qlwidget.h>

#include "fusion_global.h"
#include "fusion_export.h"

FUSION_NAMESPACE_BEGIN
class FUSION_EXPORT FGradientControl : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void gradient_changed();

public:
	FGradientControl(QWidget* parent = nullptr);

	~FGradientControl();

protected:
	bool eventFilter(QObject* object, QEvent* event);

private:
	void init_attributes();
};
FUSION_NAMESPACE_END

#endif // FGRADIENTCONTROL_H
