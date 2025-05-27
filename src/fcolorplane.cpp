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

#include <Fusion/fcolorplane.h>

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <Layers/lstring.h>

using Layers::LAttribute;
using Layers::LString;
using Fusion::FColorPlane;
using Fusion::HSV;

FColorPlane::FColorPlane(QWidget* parent)
	: QWidget(parent)
{
	init_attributes();

	installEventFilter(this);
	setFixedSize(255, 255);

	m_cursor->setFixedSize(10, 10);
	m_cursor->move(width() - margin - (m_cursor->width() / 2), 0);

	connect(this, &FColorPlane::z_dimension_changed,
		this, &FColorPlane::update_z_axis);
}

LAttribute* FColorPlane::color()
{
	return m_color;
}

float FColorPlane::pos_as_ratio(int pos, int available_space)
{
	return
		float(pos - margin) /
			float(available_space - (margin * 2) - 1);
}

void FColorPlane::set_z_dimension(HSV z_dimension)
{
	m_z_dimension = z_dimension;

	QWidget::update();

	update_cursor_position();

	emit z_dimension_changed();
}

void FColorPlane::setFixedHeight(int h)
{
	QWidget::setFixedHeight(h);

	update_height_dependencies();
}

void FColorPlane::setFixedSize(const QSize& s)
{
	QWidget::setFixedSize(s);

	update_height_dependencies();
	update_width_dependencies();
}

void FColorPlane::setFixedSize(int w, int h)
{
	QWidget::setFixedSize(w, h);

	update_height_dependencies();
	update_width_dependencies();
}

void FColorPlane::setFixedWidth(int w)
{
	QWidget::setFixedWidth(w);

	update_width_dependencies();
}

LAttribute* FColorPlane::z_axis()
{
	return m_z_axis;
}

HSV FColorPlane::z_dimension() const
{
	return m_z_dimension;
}

bool FColorPlane::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		QPoint mouse_pos = mouse_event->pos();

		if (mouse_event->button() & Qt::LeftButton)
		{
			m_dragging = true;

			handle_mouse_event(mouse_pos);
		}
	}
	else if (event->type() == QEvent::MouseButtonRelease && m_dragging)
	{
		m_dragging = false;
	}
	else if (event->type() == QEvent::MouseMove && m_dragging)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		QPoint mouse_pos = mouse_event->pos();

		handle_mouse_event(mouse_pos);
	}

	return false;
}

void FColorPlane::paintEvent(QPaintEvent* event)
{
	QImage image;
	QColor paint_color;
	QPainter painter(this);

	switch (m_z_dimension)
	{
	case HSV::Hue:
	{
		image = QImage(MAX_SV + 1, MAX_SV + 1, QImage::Format_RGB32);

		int h = QColor(
			QString::fromStdString(m_color->as<LString>().c_str())).hue();

		for (int s = 0; s <= MAX_SV; s++) {
			for (int v = 0; v <= MAX_SV; v++) {
				paint_color.setHsv(h, s, v);
				image.setPixel(s, MAX_SV - v, paint_color.rgb());
			}
		}
		break;
	}
	case HSV::Saturation:
	{
		image = QImage(MAX_H + 1, MAX_SV + 1, QImage::Format_RGB32);

		int s = QColor(
			QString::fromStdString(m_color->as<LString>().c_str())).saturation();

		for (int h = 0; h <= MAX_H; h++) {
			for (int v = 0; v <= MAX_SV; v++) {
				paint_color.setHsv(h, s, v);
				image.setPixel(h, MAX_SV - v, paint_color.rgb());
			}
		}
		break;
	}
	case HSV::Value:
	{
		image = QImage(MAX_H + 1, MAX_SV + 1, QImage::Format_RGB32);

		int v = QColor(
			QString::fromStdString(m_color->as<LString>().c_str())).value();

		for (int h = 0; h <= MAX_H; h++) {
			for (int s = 0; s <= MAX_SV; s++) {
				paint_color.setHsv(h, s, v);
				image.setPixel(h, MAX_SV - s, paint_color.rgb());
			}
		}
		break;
	}
	}

	painter.drawImage(
		QRect(margin, margin, m_draw_width, m_draw_height),
		image);
}

void FColorPlane::update_cursor_position()
{
	QColor c = QColor(QString::fromStdString(m_color->as<LString>().c_str()));

	float w_ratio = 1.f / float(width() - (margin * 2) - 1);
	float h_ratio = 1.f / float(height() - (margin * 2) - 1);

	QPoint new_cursor_location;

	switch (m_z_dimension)
	{
	case HSV::Hue:
		new_cursor_location = QPoint(
			c.saturationF() / w_ratio, (1.f - c.valueF()) / h_ratio);
		break;
	case HSV::Saturation:
		new_cursor_location = QPoint(
			c.hueF() / w_ratio, (1.f - c.valueF()) / h_ratio);
		break;
	case HSV::Value:
		new_cursor_location = QPoint(
			c.hueF() / w_ratio, (1.f - c.saturationF()) / h_ratio);
		break;
	}

	new_cursor_location += QPoint(margin, margin);
	new_cursor_location -=
		QPoint(m_cursor->width() / 2, m_cursor->height() / 2);
	m_cursor->move(new_cursor_location);
}

void FColorPlane::update_z_axis()
{
	switch (m_z_dimension)
	{
	case HSV::Hue:
		m_z_axis->set_value(double(QColor(
			QString::fromStdString(m_color->as<LString>().c_str())).hue()));
		break;
	case HSV::Saturation:
		m_z_axis->set_value(double(QColor(
			QString::fromStdString(m_color->as<LString>().c_str())).saturation()));
		break;
	case HSV::Value:
		m_z_axis->set_value(double(QColor(
			QString::fromStdString(m_color->as<LString>().c_str())).value()));
		break;
	}
}

void FColorPlane::handle_mouse_event(QPoint& mouse_pos)
{
	float x_pos_ratio = 0.f;
	float y_pos_ratio = 0.f;

	// Handle X
	if (mouse_pos.x() < margin)
		x_pos_ratio = 0.f;
	else if (mouse_pos.x() >= width() - margin)
		x_pos_ratio = 1.f;
	else
		x_pos_ratio = pos_as_ratio(mouse_pos.x(), width());

	// Handle Y
	if (mouse_pos.y() < margin)
		y_pos_ratio = 0.f;
	else if (mouse_pos.y() >= height() - margin)
		y_pos_ratio = 1.f;
	else
		y_pos_ratio = pos_as_ratio(mouse_pos.y(), height());

	// Update color
	update_color(x_pos_ratio, y_pos_ratio);
}

void FColorPlane::init_attributes()
{
	m_z_axis->on_change(
		[this] {
			QColor c = QColor(QString::fromStdString(m_color->as<LString>().c_str()));

			switch (m_z_dimension)
			{
			case HSV::Hue:
				c.setHsv(m_z_axis->as<double>(), c.saturation(), c.value());
				break;
			case HSV::Saturation:
				c.setHsv(c.hue(), m_z_axis->as<double>(), c.value());
				break;
			case HSV::Value:
				c.setHsv(c.hue(), c.saturation(), m_z_axis->as<double>());
				break;
			}

			m_color->set_value(c.name().toStdString().c_str());
		}
	);

	m_color->on_change(
		[this] {
			update_cursor_position();
			//update_z_axis();
			QWidget::update();
		}
	);

	m_cursor->fill()->create_link(m_color);
	m_cursor->border_fill()->set_value("#c0c0c0");
	m_cursor->border_thickness()->set_value(2.0);
	m_cursor->corner_radii_top_left()->set_value(2.0);
	m_cursor->corner_radii_top_right()->set_value(2.0);
	m_cursor->corner_radii_bottom_left()->set_value(2.0);
	m_cursor->corner_radii_bottom_right()->set_value(2.0);
}

void FColorPlane::update_color(float x_pos_ratio, float y_pos_ratio)
{
	QColor c = QColor(QString::fromStdString(m_color->as<LString>().c_str()));

	switch (m_z_dimension)
	{
	case HSV::Hue:
		c.setHsvF(c.hueF(), x_pos_ratio, 1.f - y_pos_ratio);
		break;
	case HSV::Saturation:
		c.setHsvF(x_pos_ratio, c.saturationF(), 1.f - y_pos_ratio);
		break;
	case HSV::Value:
		c.setHsvF(x_pos_ratio, 1.f - y_pos_ratio, c.valueF());
		break;
	}

	m_color->set_value(c.name().toStdString().c_str());
}

void FColorPlane::update_height_dependencies()
{
	m_draw_height = height() - (margin * 2);

	update_cursor_position();
}

void FColorPlane::update_width_dependencies()
{
	m_draw_width = width() - (margin * 2);

	update_cursor_position();
}
