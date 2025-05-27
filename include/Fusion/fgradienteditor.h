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

#ifndef FGRADIENTEDITOR
#define FGRADIENTEDITOR

#include <Layers/lstring.h>

#include <QLayers/qlbutton.h>
#include <QLayers/qlwidget.h>

#include "fusion_global.h"
#include "fusion_export.h"

#include "fcolorcontrol.h"

FUSION_NAMESPACE_BEGIN
class FGradientEditorItem;

class FUSION_EXPORT FGradientEditor : public QLayers::QLWidget
{
	Q_OBJECT

public:
	FGradientEditor(std::vector<Layers::LString> stops, QWidget* parent = nullptr);

	~FGradientEditor();

	std::vector<Layers::LString> stops() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	FGradientEditorItem* create_item(const Layers::LString& stop);

	void init_attributes(const std::vector<Layers::LString>& stops);
	void init_items(const std::vector<Layers::LString>& stops);
	void init_add_stop_buttons();

	void update_gradient();
	void update_indexes();
	void update_positions();

	QList<FGradientEditorItem*> m_items;
	QList<QLayers::QLButton*> m_add_stop_buttons;

	FGradientEditorItem* m_drag_item{ nullptr };
	FGradientEditorItem* m_replace_item{ nullptr };

	int m_drag_ctrl_initial_x{ 0 };
	QPoint m_click_pos;
};
FUSION_NAMESPACE_END

#endif // FGRADIENTEDITOR
