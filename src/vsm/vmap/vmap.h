#ifndef VSM_VECTOR_VECTORMAP_H_INCLUDED
#define VSM_VECTOR_VECTORMAP_H_INCLUDED

#include "util/maputil.h"
#include "util/funcutil.h"
#include <algorithm>
#include <map>
#include <cmath>
#include <ostream>
#include <set>
#include <vector>

namespace vsm
{
    template<class K>
    class VectorMap
    {
    private:
        VectorMap(std::map<K, double> _vecmap);
        std::map<K,double> _vecmap;

    public:
        template<typename InputIt, typename KeyOperator, typename ValueOperator>
        static VectorMap<K> vectorise(InputIt start, InputIt end,
                                      KeyOperator key_op = [](K key) {
                                          return key;
                                      },
                                      ValueOperator value_op = [](double val) {
                                          return val;
                                      }
        );

        void insert(const K& key);
        void insert(const K& key, double value_to_add);
        bool has(const K& key) const;
        double at(const K& key) const;
        double length() const noexcept;
        double dot(VectorMap<K> other) const noexcept;

        std::map<K, double> getmap();

        VectorMap<K> add(VectorMap<K> other) const;
        VectorMap<K> sub(VectorMap<K> other) const;
        VectorMap<K> add(double scalar) const;
        VectorMap<K> sub(double scalar) const;
        VectorMap<K> mul(double scalar) const;
        VectorMap<K> div(double scalar) const;

        template<class U>
        friend std::ostream& operator<<(std::ostream& o, const VectorMap<U>& vm);
    };

    template<class K>
    VectorMap<K>::VectorMap(std::map<K, double> vecmap) : _vecmap(vecmap)
    {}

    template<class K>
    template<typename InputIt, typename KeyOperator, typename ValueOperator>
    VectorMap<K> VectorMap<K>::vectorise(InputIt start, InputIt last,
                                         KeyOperator key_op,
                                         ValueOperator value_op)
    {
        std::map<K, double> counter;
        for (auto it = start; it != last; ++it) {
            auto key = key_op(*it);
            if (counter.find(key) == counter.end()) {
                counter[key] = 0.0;
            }
            counter[key] += 1.0;
        }

        for (auto& [key, value] : counter) {
            value = value_op(value);
        }

        return VectorMap<K>(counter);
    }

    template<class K>
    void VectorMap<K>::insert(const K& key)
    {
        insert(key, 0);
    }

    template<class K>
    void VectorMap<K>::insert(const K& key, double value_to_add)
    {
        _vecmap[key] += value_to_add;
    }

    template<class K>
    bool VectorMap<K>::has(const K& key) const
    {
        return _vecmap.count(key);
    }

    template<class K>
    double VectorMap<K>::at(const K& key) const
    {
        return _vecmap.at(key);
    }

    template<class K>
    double VectorMap<K>::length() const noexcept
    {
        std::vector<double> numbers;
        util::values(_vecmap, std::back_inserter(numbers));

        auto square = [](double d) { return d*d; };
        std::transform(numbers.begin(), numbers.end(), numbers.begin(), square);

        auto sum = [](double x, double y) { return x + y; };
        double sumsq = util::reduce(numbers.begin(), numbers.end(), sum);

        return sqrt(sumsq);
    }

    template<class K>
    double VectorMap<K>::dot(VectorMap<K> other) const noexcept
    {
        double ret = 0.0;
        auto common_keys = util::common_keys(_vecmap, other._vecmap);
        for (const K& key : common_keys) {
            ret += at(key) * other.at(key);
        }
        return ret;
    }

    template<class K>
    std::map<K, double> VectorMap<K>::getmap()
    {
        return _vecmap;
    }

    template<class K>
    VectorMap<K> VectorMap<K>::add(VectorMap<K> other) const
    {
        VectorMap<K> ret;
        std::set<K> all_keys = util::all_keys(_vecmap, other._vecmap);

        for (const K& key : all_keys) {
            if (has(key) && other.has(key)) {
                ret.add(key, at(key) + other.at(key));
            } else if (has(key)) {
                ret.add(key, at(key));
            } else {
                ret.add(key, other.at(key));
            }
        }
        return ret;
    }

    template<class K>
    VectorMap<K> VectorMap<K>::sub(VectorMap<K> other) const
    {
        VectorMap<K> ret;
        std::set<K> all_keys = util::all_keys(_vecmap, other._vecmap);

        for (const K& key : all_keys) {
            if (this->has(key) && other.has(key)) {
                ret.add(key, at(key) - other.at(key));
            } else if (this->has(key)) {
                ret.add(key, at(key));
            } else {
                ret.add(key, other.at(key));
            }
        }
        return ret;
    }

    template<class K>
    VectorMap<K> VectorMap<K>::mul(double scalar) const
    {
        VectorMap<K> ret;
        for (const auto [key, value] : _vecmap) {
            ret.add(key, value * scalar);
        }
        return ret;
    }

    template<class K>
    VectorMap<K> VectorMap<K>::div(double scalar) const
    {
        constexpr double EPSILON = 1e-10;
        if (-EPSILON < scalar && scalar < EPSILON) {
            throw std::runtime_error("attempted division by zero: " + std::to_string(scalar));
        }

        VectorMap<K> ret;
        for (const auto [key, value] : _vecmap) {
            ret.add(key, value / scalar);
        }
        return ret;
    }

    template<class U>
    std::ostream& operator<<(std::ostream& o, const VectorMap<U>& vm)
    {
        o << "{\n";
        for (const auto& [k, v] : vm._vecmap) {
            o << "\t" << k << ": " << v << "\n";
        }
        o << "}\n";
        return o;
    }
}

#endif
