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

#ifndef FCOLORPLANE_H
#define FCOLORPLANE_H

#include <Layers/lattribute.h>

#include "fusion_global.h"
#include "fusion_export.h"

#include <QLayers/qlcalculate.h>
#include <QLayers/qlwidget.h>

#include "fcolor.h"

FUSION_NAMESPACE_BEGIN
class FUSION_EXPORT FColorPlane : public QWidget, public QLayers::QLDefinable
{
	Q_OBJECT

signals:
	void z_dimension_changed();

public:
	FColorPlane(QWidget* parent = nullptr);

	Layers::LAttribute* color();

	void set_z_dimension(HSV z_dimension);

	void setFixedHeight(int h);

	void setFixedSize(const QSize& s);

	void setFixedSize(int w, int h);

	void setFixedWidth(int w);

	Layers::LAttribute* z_axis();

	HSV z_dimension() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private slots:
	void update_cursor_position();
	void update_z_axis();

private:
	void handle_mouse_event(QPoint& mouse_pos);

	void init_attributes();

	float pos_as_ratio(int pos, int available_space);

	void update_color(float x_pos_ratio, float y_pos_ratio);

	void update_height_dependencies();
	void update_width_dependencies();

	Layers::LAttribute* m_color
		{ new Layers::LAttribute("color", "#ff0000", this) };

	Layers::LAttribute* m_z_axis
		{ new Layers::LAttribute("z_axis", 0.0, this) };

	HSV m_z_dimension{ HSV::Hue };

	QLayers::QLWidget* m_cursor{ new QLayers::QLWidget(this) };

	int m_draw_height{ 245 };
	int m_draw_width{ 245 };

	const int margin{ 5 };

	bool m_dragging{ false };
};
FUSION_NAMESPACE_END

#endif // FCOLORPLANE_H