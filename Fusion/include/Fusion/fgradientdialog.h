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

#ifndef FGRADIENTDIALOG_H
#define FGRADIENTDIALOG_H

#include <QTimer>

#include <Layers/lstring.h>

#include <QLayers/qlbutton.h>
#include <QLayers/qldialog.h>

#include "fusion_global.h"
#include "fusion_export.h"

#include "fcolorcontrol.h"
#include "fgradienteditor.h"

FUSION_NAMESPACE_BEGIN
class FUSION_EXPORT FGradientDialog : public QLayers::QLDialog
{
	Q_OBJECT

public:
	FGradientDialog(std::vector<Layers::LString> stops, QWidget* parent = nullptr);

	std::vector<Layers::LString> stops() const;

private:
	void init_layout();

	FGradientEditor* m_gradient_editor;

	QLayers::QLButton* m_apply_button{
		new QLayers::QLButton(
			QLayers::QLGraphic(":/images/check.svg", QSize(16, 13)), "Apply") };
};
FUSION_NAMESPACE_END

#endif // FGRADIENTDIALOG_H
