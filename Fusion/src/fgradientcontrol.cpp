/*
 * Copyright (C) 2024 The Layers Project
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

#include <Fusion/fgradientcontrol.h>

#include <QMouseEvent>
#include <Layers/lstring.h>
#include <Fusion/fgradientdialog.h>

using Layers::LString;
using Fusion::FGradientControl;

FGradientControl::FGradientControl(QWidget* parent) : QLWidget(parent)
{
	init_attributes();

	installEventFilter(this);
	setFixedSize(40, 40);
}

FGradientControl::~FGradientControl()
{
	delete m_fill;
}

bool FGradientControl::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress ||
		event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			FGradientDialog gradient_dialog(m_fill->as<std::vector<LString>>());

			center(&gradient_dialog, window());

			if (gradient_dialog.exec())
			{
				fill()->set_value(gradient_dialog.stops());

				emit gradient_changed();
			}
		}
	}

	return false;
}

void FGradientControl::init_attributes()
{
	// Remove control attribute
	m_fill->set_parent(nullptr);

	m_border_fill->set_value("#D6D6D6");
	m_border_thickness->set_value(2.0);
	m_corner_radii_top_left->set_value(5.0);
	m_corner_radii_top_right->set_value(5.0);
	m_corner_radii_bottom_left->set_value(5.0);
	m_corner_radii_bottom_right->set_value(5.0);
	m_margins_left->set_value(8.0);
	m_margins_top->set_value(8.0);
	m_margins_right->set_value(8.0);
	m_margins_bottom->set_value(8.0);

	m_fill->set_value(std::vector<LString>({ "0:#ffffff", "1:#000000" }));
}
