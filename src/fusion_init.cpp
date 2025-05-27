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

#include <Fusion/fusion_init.h>
#include <Fusion/fusion_global.h>

#include <QDebug>

#include <Layers/lstring.h>
#include <Layers/lcontroller.h>

namespace Layers {
    namespace Resources {
        extern void initResources_definitions();
    }
}

void initialize_resources()
{
    // Initialize Layers resources
    Layers::Resources::initResources_definitions();
}

FUSION_NAMESPACE_BEGIN

Initializer::Initializer()
{
    initialize_resources();

    lController.include_internal("/definitions/fusion");
    qDebug() << "Fusion: Loaded Definitions";
}

static Initializer fusion_initializer;

FUSION_NAMESPACE_END
