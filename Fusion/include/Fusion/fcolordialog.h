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

#ifndef FCOLORDIALOG_H
#define FCOLORDIALOG_H

#include <Layers/lattribute.h>

#include "fusion_global.h"
#include "fusion_export.h"

#include <QLayers/qlcombobox.h>
#include <QLayers/qldialog.h>
#include <QLayers/qllineeditor.h>
#include <QLayers/qlradiobutton.h>
#include <QLayers/qlradiobuttonpool.h>
#include <QLayers/qlslider.h>

#include "fcolor.h"
#include "fcolorplane.h"

FUSION_NAMESPACE_BEGIN
class FUSION_EXPORT FColorDialog : public QLayers::QLDialog
{
	Q_OBJECT

public:
	FColorDialog(QWidget* parent = nullptr);

	~FColorDialog();

	Layers::LAttribute* color() const;

private slots:
	void hsv_changed();

private:
	void init_attributes();
	void init_layout();

	QLayers::QLButton* m_apply_button{
		new QLayers::QLButton(
			QLayers::QLGraphic(
				":/images/check.svg", QSize(16, 13)), "Apply") };

	QLayers::QLLabel* m_color_unit_label{ new QLayers::QLLabel("#")};

	QLayers::QLLineEditor* m_color_name_editor{ new QLayers::QLLineEditor };

	FColorPlane* m_color_plane{ new FColorPlane };

	QLayers::QLSlider* m_z_slider{ new QLayers::QLSlider(MAX_H) };

	Layers::LAttribute* m_color
		{ new Layers::LAttribute("color", "#000000")};

	QLayers::QLRadioButton* m_radio_button_hue{ new QLayers::QLRadioButton };
	QLayers::QLRadioButton* m_radio_button_sat{ new QLayers::QLRadioButton };
	QLayers::QLRadioButton* m_radio_button_val{ new QLayers::QLRadioButton };

	QLayers::QLRadioButtonPool m_hsv_radio_button_pool{
		QLayers::QLRadioButtonPool({
			m_radio_button_hue,
			m_radio_button_sat,
			m_radio_button_val
			}) };

	QLayers::QLLabel* m_label_hue{ new QLayers::QLLabel("H:") };
	QLayers::QLLabel* m_label_hue_unit{ new QLayers::QLLabel("°") };
	QLayers::QLLabel* m_label_sat{ new QLayers::QLLabel("S:") };
	QLayers::QLLabel* m_label_sat_unit{ new QLayers::QLLabel("%") };
	QLayers::QLLabel* m_label_val{ new QLayers::QLLabel("V:") };
	QLayers::QLLabel* m_label_val_unit{ new QLayers::QLLabel("%") };

	QLayers::QLLineEditor* m_line_editor_hue{ new QLayers::QLLineEditor };
	QLayers::QLLineEditor* m_line_editor_sat{ new QLayers::QLLineEditor };
	QLayers::QLLineEditor* m_line_editor_val{ new QLayers::QLLineEditor };
};
FUSION_NAMESPACE_END

#endif // FCOLORDIALOG_H
