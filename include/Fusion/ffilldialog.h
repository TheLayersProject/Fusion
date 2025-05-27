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

#ifndef FFILLDIALOG_H
#define FFILLDIALOG_H

#include <QGraphicsOpacityEffect>
#include <Layers/lattribute.h>
#include <Layers/lstring.h>
#include <QLayers/qldialog.h>
#include <QLayers/qltoggleswitch.h>

#include "fusion_global.h"
#include "fusion_export.h"

#include "fcolorcontrol.h"
#include "fgradientcontrol.h"

FUSION_NAMESPACE_BEGIN
class FUSION_EXPORT FFillDialog : public QLayers::QLDialog
{
	Q_OBJECT

public:
	FFillDialog(QWidget* parent = nullptr);

	void set_attribute(Layers::LAttribute* attribute);

private:
	void init_attributes();
	void init_layout();

	QLayers::QLToggleSwitch* m_fill_type_toggle{ new QLayers::QLToggleSwitch(true) };

	QGraphicsOpacityEffect* m_color_label_opacity
		{ new QGraphicsOpacityEffect };
	QGraphicsOpacityEffect* m_gradient_label_opacity
		{ new QGraphicsOpacityEffect };

	QLayers::QLLabel* m_color_label{ new QLayers::QLLabel("Color") };
	QLayers::QLLabel* m_gradient_label{ new QLayers::QLLabel("Gradient") };

	FColorControl* m_color_control{ new FColorControl };
	FGradientControl* m_gradient_control{ new FGradientControl };

	Layers::LString m_previous_color{ "#f0f0f0" };
	std::vector<Layers::LString> m_previous_gradient{ "0:#f0f0f0", "0:#0f0f0f" };
};
FUSION_NAMESPACE_END

#endif // FFILLDIALOG_H
