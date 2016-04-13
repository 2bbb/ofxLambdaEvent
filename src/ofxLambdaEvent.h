//
//  ofxLambdaEvent.h
//
//  Created by ISHII 2bit on 2016/04/14.
//
//

#pragma once

#include <functional>
#include <tuple>

#include "ofEvent.h"
#include "ofEvents.h"
#include "ofEventUtils.h"

namespace ofxLambdaEvent {
    template <typename T>
    using get_type = typename T::type;
    
    template <typename T>
    struct function_info : public function_info<decltype(&T::operator())>  {};
    
    template <typename U, typename ret, typename ... arguments>
    struct function_info<ret(U::*)(arguments ...) const> {
        static constexpr bool is_function = true;
        static constexpr std::size_t arity = sizeof...(arguments);
        using result_type = ret;
        using arguments_types_tuple = std::tuple<arguments ...>;
        template <std::size_t index>
        using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
        using function_type = std::function<result_type(arguments ...)>;
    };
    
    template <typename U, typename ret, typename ... arguments>
    struct function_info<ret(U::*)(arguments ...)> {
        static constexpr bool is_function = true;
        static constexpr std::size_t arity = sizeof...(arguments);
        using result_type = ret;
        using arguments_types_tuple = std::tuple<arguments ...>;
        template <std::size_t index>
        using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
        using function_type = std::function<result_type(arguments ...)>;
    };
    
    template <typename ret, typename ... arguments>
    struct function_info<ret(*)(arguments ...)> {
        static constexpr bool is_function = true;
        static constexpr std::size_t arity = sizeof...(arguments);
        using result_type = ret;
        using arguments_types_tuple = std::tuple<arguments ...>;
        template <std::size_t index>
        using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
        using function_type = std::function<result_type(arguments ...)>;
    };
    
    template <typename ret, typename ... arguments>
    struct function_info<ret(arguments ...)> {
        static constexpr bool is_function = true;
        static constexpr std::size_t arity = sizeof...(arguments);
        using result_type = ret;
        using arguments_types_tuple = std::tuple<arguments ...>;
        template <std::size_t index>
        using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
        using function_type = std::function<result_type(arguments ...)>;
    };
}

template <
    typename EventType,
    typename Lambda,
    typename info = ofxLambdaEvent::function_info<Lambda>
>
auto ofxAddLambdaListener(EventType &event,
                          Lambda callback,
                          int priority = OF_EVENT_ORDER_AFTER_APP)
-> typename std::enable_if<info::is_function>::type
{
    ofAddListener(event, static_cast<typename info::result_type(*)(typename info::template argument_type<0> &)>(callback), priority);
}
