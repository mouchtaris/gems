#pragma once
namespace msg::input
{

    //! Read tag
    /// Indicates that a Selectable is of Read direction.
    struct Read;

    //! Write tag
    /// Indicates that a Selectable is of Write direction.
    struct Write;

    template <
        typename Direction
    >
    struct Selectable
    {
        int fd;
        bool ready;
    };

}
