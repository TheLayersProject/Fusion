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

#ifndef FCOLORCONTROL_H
#define FCOLORCONTROL_H

#include "fusion_global.h"
#include "fusion_export.h"

#include <QLayers/qlwidget.h>

FUSION_NAMESPACE_BEGIN
class FUSION_EXPORT FColorControl : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void color_changed();

public:
	FColorControl(QWidget* parent = nullptr);

	~FColorControl();

	void click();

	void disable_clicking(bool cond = true);

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_attributes();

	bool clicking_disabled{ false };
	bool open_on_release{ false };

	QStringList m_attribute_states;
};
FUSION_NAMESPACE_END

#endif // FCOLORCONTROL_H
