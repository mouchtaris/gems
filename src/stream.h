#pragma once
#include <cstdint>
#include <utility>
#include <functional>
#include "stdx.h"
namespace stream
{
    //! Sink contract
    template <
        typename T,
        typename In
    >
    using push_t = decltype(
        push(
            std::declval<T&&>(),
            std::declval<In&&>()
        )
    );

    //! Stage contract
    template <
        typename T,
        typename Val,
        typename Sink
    >
    using on_push_t = decltype(
        on_push(
            std::declval<T&&>(),
            std::declval<Val&&>(),
            std::declval<Sink&&>()
        )
    );



    //! Sink from function
    template <
        typename F
    >
    struct sink_from_function
    {
        F f;
    };

    template <
        typename F,
        typename Val
    >
    void push(sink_from_function<F>&& sink, Val&& val)
    {
        std::move(sink.f)(std::forward<Val>(val));
    }

    static_assert(std::is_detected_v<push_t, sink_from_function<std::function<void(int)>>, int>);


    //! Stage from function
    template <
        typename F
    >
    struct stage_from_function
    {
        F f;
    };

    template <
        typename F,
        typename Val,
        typename Sink
    >
    decltype(auto) on_push(
        stage_from_function<F>&& stage,
        Val&& val,
        Sink&& sink)
    {
        return push(std::forward<Sink&&>(sink), stage.f(std::forward<Val&&>(val)));
    }

    static_assert(std::is_detected_v<
        on_push_t,
        stage_from_function<std::function<int (int)>>,
        int,
        sink_from_function<std::function<void (int)>>
    >);


    //! Connect a stage to a sink. The result is a sink.
    template <
        typename Stage,
        typename Sink
    >
    struct to
    {
        Stage stage;
        Sink sink;
    };
    template <
        typename Stage,
        typename Sink
    >
    to(Stage&&, Sink&&) -> to<Stage, Sink>;

    template <
        typename Stage,
        typename Sink,
        typename Val
    >
    decltype(auto) push(to<Stage, Sink>&& stage, Val&& val)
    {
        return on_push(
            std::move(stage.stage),
            std::forward<Val>(val),
            std::move(stage.sink)
        );
    }

    static_assert(std::is_detected_v<
        push_t,
        to<
            stage_from_function<std::function<int (int)>>,
            sink_from_function<std::function<void (int)>>
        >,
        int
    >);


    //! Connect two stages. The result is a stage.
    template <typename A, typename B>
    struct via { A a; B b; };

    template <
        typename A,
        typename B,
        typename Val,
        typename Sink
    >
    decltype(auto) on_push(via<A, B>&& stage, Val&& val, Sink&& sink)
    {
        return on_push(
            std::move(stage.a),
            std::forward<Val>(val),
            to {
                std::move(stage.b),
                std::forward<Sink&&>(sink),
            }
        );
    }

    static_assert(std::is_detected_v<
        on_push_t,
        via<
            stage_from_function<std::function<float (int)>>,
            stage_from_function<std::function<int (float)>>
        >,
        int,
        sink_from_function<std::function<void (int)>>
    >);
    static_assert(std::is_same_v<
        on_push_t<
            via<
                stage_from_function<std::function<float (int)>>,
                stage_from_function<std::function<int (float)>>
            >,
            int,
            sink_from_function<std::function<void (int)>>
        >,
        void
    >);
}
