#pragma once
namespace util::seri
{
template <typename... Tags> struct TagIndex
{
    template <typename Tag> using add = TagIndex<Tags..., Tag>;
};
}
