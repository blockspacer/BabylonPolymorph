/********************************************************
*                                                       *
*   Copyright (C) Microsoft. All rights reserved.       *
*                                                       *
********************************************************/

#pragma once

#include <memory>

namespace Babylon
{
    namespace Utils
    {
        // Runtime check that the passed instance is of type TTest
        template<typename TTest, typename TInput>
        bool Babylon_is_type(const TInput& input)
        {
            static_assert(std::is_base_of<TInput, TTest>::value, "Template parameter TTest must derive from TInput");
            return dynamic_cast<const TTest*>(&input) != nullptr;
        }

        // Babylon_safe_cast is used where the input is known (by design) to be of the correct type,
        // so that only a static_cast<> is required for efficiency.
        //
        // In debug builds, this a full dynamic_cast is used to assert the precondition.
        template<typename Output, typename Input>
        Output* Babylon_safe_cast(Input* input)
        {
            BabylonAssert(input && Babylon_is_type<Output>(*input));
            return static_cast<Output*>(input);
        }

        // Babylon_safe_pointer_cast is used where the input is known (by design) to be of the correct type,
        // so that only a static_pointer_cast<> is required for efficiency.
        //
        // In debug builds, this a full dynamic_cast is used to assert the precondition.
        template<typename Output, typename Input>
        std::shared_ptr<Output> Babylon_safe_pointer_cast(std::shared_ptr<Input> input)
        {
            BabylonAssert(input && Babylon_is_type<Output>(*input));
            return std::static_pointer_cast<Output>(input);
        }
    }
}
