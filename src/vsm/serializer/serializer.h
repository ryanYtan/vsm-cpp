#include <ostream>
#include <istream>

namespace vsm
{
    template<typename T>
    class Serializer
    {
    public:
        Serializer();
        virtual ~Serializer();

        virtual void serialize(T obj, std::ostream& output);
        virtual T deserialize(std::istream& input);
    };
}
