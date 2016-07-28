////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     ISerializable.h (utilities)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ObjectDescription.h"
#include "Variant_def.h"
#include "TypeName.h"
#include "Serialization.h"

// stl
#include <string>
#include <ostream>
#include <type_traits>

namespace utilities
{
    /// <summary> ISerializable interface --- provides one function, GetDescription </summary>
    class ISerializable
    {
    public:
        virtual ~ISerializable() = default;

        virtual void Serialize(Serializer& serializer) const = 0;

        // begin serialize
        // serialize
        // end serialize

        // begin deserialize
        // deserialize
        // end deserialize
    };

    //template <typename ValueType>
    //using IsSerializable = typename std::enable_if_t<std::is_base_of<ISerializable, typename std::decay<ValueType>::type>::value, int>;

    //template <typename ValueType>
    //using IsNotSerializable = typename std::enable_if_t<(!std::is_base_of<ISerializable, typename std::decay<ValueType>::type>::value) && (std::is_fundamental<typename std::decay<ValueType>::type>::value), int>;

    class IDescribable
    {
    public:
        virtual ~IDescribable() = default;

        virtual ObjectDescription GetDescription() const = 0;
    };


    // // helper function
    // // See here for advice on overloading with function templates
    // // http://www.gotw.ca/publications/mill17.htm
    // template <typename ValueType>
    // class GetDescriptionHelper;

    // template <typename ValueType>
    // ObjectDescription GetDescription(ValueType&& obj)
    // {
    //     return GetDescriptionHelper<ValueType>::GetDescription(obj);
    // }

    // template <class ValueType>
    // {
    //     static ObjectDescription GetDescription(const ValueType& obj);
    // }

    template <typename ValueType, IsNotSerializable<ValueType> concept=0>
    ObjectDescription GetDescription(ValueType&& obj);

    template <typename ValueType, IsFundamental<ValueType> concept=0>
    ObjectDescription GetDescription(ValueType&& obj);

    ObjectDescription GetDescription(const ISerializable& obj);
    ObjectDescription GetDescription(const Variant& obj);

    //
    // Serializer class
    //
    class Serializer2
    {
    public:
        template <typename T>
        void Serialize(T&& obj);

    protected:
        virtual void SerializeFundamentalType(const Variant& variant) = 0;

        virtual void BeginSerializeType(const ObjectDescription& desc) = 0;
        virtual void SerializeField(std::string name, const Variant& variant) = 0;
        virtual void EndSerializeType(const ObjectDescription& desc) = 0;
    };

    class SimpleSerializer2 : public Serializer2
    {
    protected:
        virtual void SerializeFundamentalType(const Variant& variant) override;

        virtual void BeginSerializeType(const ObjectDescription& desc) override;
        virtual void SerializeField(std::string name, const Variant& variant) override;
        virtual void EndSerializeType(const ObjectDescription& desc) override;

    private:
        int _indent = 0;
    };
}

#include "Variant.h"
#include "../tcc/ISerializable.tcc"
