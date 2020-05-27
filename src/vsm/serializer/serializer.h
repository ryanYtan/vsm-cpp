#ifndef VSM_SERIALIZER_SERIALIZER_H_INCLUDED
#define VSM_SERIALIZER_SERIALIZER_H_INCLUDED
#include <ostream>
#include <istream>

namespace vsm
{
    template<typename T>
    class Serializer
    {
    public:
        using OStream = std::ostream;
        using IStream = std::istream;

        Serializer();

        virtual unsigned int serialize(T obj, OStream& output) = 0;
        virtual T deserialize(IStream& input) = 0;
    };

    template<typename T>
    Serializer<T>::Serializer() {}
}

#endif
