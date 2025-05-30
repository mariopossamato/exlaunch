/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <nn/nn_common.hpp>
#include "impl/os_internal_critical_section.hpp"
#include "impl/os_internal_condition_variable.hpp"

namespace nn::os {

    namespace impl {

        class MultiWaitObjectList;

    }

    struct MessageQueueType {
        enum State {
            State_NotInitialized = 0,
            State_Initialized    = 1,
        };

        /* Intrusive list nodes, but I'm lazy. */
        util::AlignedStorage<0x10, 8>::Type waitlist_not_full;
        util::AlignedStorage<0x10, 8>::Type waitlist_not_empty;
        uintptr_t *buffer;
        s32 capacity;
        s32 count;
        s32 offset;
        u8 state;

        mutable detail::InternalCriticalSectionStorage cs_queue;
        mutable detail::InternalConditionVariableStorage cv_not_full;
        mutable detail::InternalConditionVariableStorage cv_not_empty;
    };
    static_assert(sizeof(MessageQueueType) == 0x48);
}
