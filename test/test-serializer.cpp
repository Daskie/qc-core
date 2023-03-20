#include <qc-core/serializer.hpp>

#include <gtest/gtest.h>

#include <qc-core/list.hpp>
#include <qc-core/matrix.hpp>
#include <qc-core/quaternion.hpp>
#include <qc-core/span.hpp>
#include <qc-core/vector.hpp>

#include <qc-core/serializers/list-serializer.hpp>
#include <qc-core/serializers/std-map-serializer.hpp>
#include <qc-core/serializers/std-string-serializer.hpp>

using namespace qc::types;
using namespace qc::primitives;

enum CustomEnum { a, b, c };

struct CustomA
{
    SERIALIZABLE(2);

    ivec2 a;
    bool b;
};

struct CustomB
{
  public:

    SERIALIZABLE(3);

    CustomB() = default;

    CustomB(const CustomA & a, const CustomA & b, const double c) :
        _a{a},
        _b{b},
        _c{c}
    {}

    const CustomA & a() { return _a; }
    const CustomA & b() { return _b; }
    double c() { return _c; }

  private:

    CustomA _a;
    CustomA _b;
    double _c;
};

struct Blah {};
struct Wow : Blah { int x; };
static_assert(sizeof(Wow) == 4u);

const std::filesystem::path file{"qc-serializer-test.bin"};

TEST(Serializer, primitives)
{
    {
        qc::Serializer serializer{file};
        ASSERT_TRUE(serializer);
        serializer << u8{1u} << u16{2u} << u32{3u} << u64{4u};
        serializer << s8{1} << s16{2} << s32{3} << s64{4};
        serializer << 1.0f << 2.0;
        serializer << true;
        serializer << CustomEnum::b;
        serializer << ucvec2{1u, 2u} << ucvec3{3u, 4u, 5u} << ucvec4{6u, 7u, 8u, 9u};
        serializer << usvec2{1u, 2u} << usvec3{3u, 4u, 5u} << usvec4{6u, 7u, 8u, 9u};
        serializer << uivec2{1u, 2u} << uivec3{3u, 4u, 5u} << uivec4{6u, 7u, 8u, 9u};
        serializer << ulvec2{1u, 2u} << ulvec3{3u, 4u, 5u} << ulvec4{6u, 7u, 8u, 9u};
        serializer << cvec2{1, 2} << cvec3{3, 4, 5} << cvec4{6, 7, 8, 9};
        serializer << svec2{1, 2} << svec3{3, 4, 5} << svec4{6, 7, 8, 9};
        serializer << ivec2{1, 2} << ivec3{3, 4, 5} << ivec4{6, 7, 8, 9};
        serializer << lvec2{1, 2} << lvec3{3, 4, 5} << lvec4{6, 7, 8, 9};
        serializer << fvec2{1.0f, 2.0f} << fvec3{3.0f, 4.0f, 5.0f} << fvec4{6.0f, 7.0f, 8.0f, 9.0f};
        serializer << dvec2{1.0, 2.0} << dvec3{3.0, 4.0, 5.0} << dvec4{6.0, 7.0, 8.0, 9.0};
        serializer << bvec2{true, false} << bvec3{true, false, true} << bvec4{false, true, false, true};
        serializer << fmat2{1.0f, 2.0f, 3.0f, 4.0f};
        serializer << fmat3{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        serializer << fmat4{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
        serializer << dmat2{1.0, 2.0, 3.0, 4.0};
        serializer << dmat3{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
        serializer << dmat4{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
        serializer << fquat{fvec3{1.0f, 2.0f, 3.0f}, 4.0f};
        serializer << dquat{dvec3{1.0, 2.0, 3.0}, 4.0};
        serializer << ispan1{1, 2} << ispan2{ivec2{3, 4}, ivec2{5, 6}} << ispan3{ivec3{7, 8, 9}, ivec3{10, 11, 12}} << ispan4{ivec4{13, 14, 15, 16}, ivec4{17, 18, 19, 20}};
        ASSERT_TRUE(serializer.close());
    }
    {
        qc::Deserializer deserializer{file};
        ASSERT_TRUE(deserializer);
        {
            u8 v1; u16 v2; u32 v3; u64 v4;
            deserializer >> v1 >> v2 >> v3 >> v4;
            ASSERT_EQ(v1, 1u);
            ASSERT_EQ(v2, 2u);
            ASSERT_EQ(v3, 3u);
            ASSERT_EQ(v4, 4u);
        }
        {
            s8 v1; s16 v2; s32 v3; s64 v4;
            deserializer >> v1 >> v2 >> v3 >> v4;
            ASSERT_EQ(v1, 1);
            ASSERT_EQ(v2, 2);
            ASSERT_EQ(v3, 3);
            ASSERT_EQ(v4, 4);
        }
        {
            float v1; double v2;
            deserializer >> v1 >> v2;
            ASSERT_EQ(v1, 1.0f);
            ASSERT_EQ(v2, 2.0);
        }
        {
            bool v;
            deserializer >> v;
            ASSERT_EQ(v, true);
        }
        {
            CustomEnum v;
            deserializer >> v;
            ASSERT_EQ(v, CustomEnum::b);
        }
        {
            ucvec2 v1; ucvec3 v2; ucvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (ucvec2{1u, 2u}));
            ASSERT_EQ(v2, (ucvec3{3u, 4u, 5u}));
            ASSERT_EQ(v3, (ucvec4{6u, 7u, 8u, 9u}));
        }
        {
            usvec2 v1; usvec3 v2; usvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (usvec2{1u, 2u}));
            ASSERT_EQ(v2, (usvec3{3u, 4u, 5u}));
            ASSERT_EQ(v3, (usvec4{6u, 7u, 8u, 9u}));
        }
        {
            uivec2 v1; uivec3 v2; uivec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (uivec2{1u, 2u}));
            ASSERT_EQ(v2, (uivec3{3u, 4u, 5u}));
            ASSERT_EQ(v3, (uivec4{6u, 7u, 8u, 9u}));
        }
        {
            ulvec2 v1; ulvec3 v2; ulvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (ulvec2{1u, 2u}));
            ASSERT_EQ(v2, (ulvec3{3u, 4u, 5u}));
            ASSERT_EQ(v3, (ulvec4{6u, 7u, 8u, 9u}));
        }
        {
            cvec2 v1; cvec3 v2; cvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (cvec2{1, 2}));
            ASSERT_EQ(v2, (cvec3{3, 4, 5}));
            ASSERT_EQ(v3, (cvec4{6, 7, 8, 9}));
        }
        {
            svec2 v1; svec3 v2; svec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (svec2{1, 2}));
            ASSERT_EQ(v2, (svec3{3, 4, 5}));
            ASSERT_EQ(v3, (svec4{6, 7, 8, 9}));
        }
        {
            ivec2 v1; ivec3 v2; ivec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (ivec2{1, 2}));
            ASSERT_EQ(v2, (ivec3{3, 4, 5}));
            ASSERT_EQ(v3, (ivec4{6, 7, 8, 9}));
        }
        {
            lvec2 v1; lvec3 v2; lvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (lvec2{1, 2}));
            ASSERT_EQ(v2, (lvec3{3, 4, 5}));
            ASSERT_EQ(v3, (lvec4{6, 7, 8, 9}));
        }
        {
            fvec2 v1; fvec3 v2; fvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (fvec2{1.0f, 2.0f}));
            ASSERT_EQ(v2, (fvec3{3.0f, 4.0f, 5.0f}));
            ASSERT_EQ(v3, (fvec4{6.0f, 7.0f, 8.0f, 9.0f}));
        }
        {
            dvec2 v1; dvec3 v2; dvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (dvec2{1.0, 2.0}));
            ASSERT_EQ(v2, (dvec3{3.0, 4.0, 5.0}));
            ASSERT_EQ(v3, (dvec4{6.0, 7.0, 8.0, 9.0}));
        }
        {
            bvec2 v1; bvec3 v2; bvec4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (bvec2{true, false}));
            ASSERT_EQ(v2, (bvec3{true, false, true}));
            ASSERT_EQ(v3, (bvec4{false, true, false, true}));
        }
        {
            fmat2 v1; fmat3 v2; fmat4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (fmat2{1.0f, 2.0f, 3.0f, 4.0f}));
            ASSERT_EQ(v2, (fmat3{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f}));
            ASSERT_EQ(v3, (fmat4{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f}));
        }
        {
            dmat2 v1; dmat3 v2; dmat4 v3;
            deserializer >> v1 >> v2 >> v3;
            ASSERT_EQ(v1, (dmat2{1.0, 2.0, 3.0, 4.0}));
            ASSERT_EQ(v2, (dmat3{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}));
            ASSERT_EQ(v3, (dmat4{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0}));
        }
        {
            fquat v;
            deserializer >> v;
            ASSERT_EQ(v, (fquat{fvec3{1.0f, 2.0f, 3.0f}, 4.0f}));
        }
        {
            dquat v;
            deserializer >> v;
            ASSERT_EQ(v, (dquat{dvec3{1.0, 2.0, 3.0}, 4.0}));
        }
        {
            ispan1 v1; ispan2 v2; ispan3 v3; ispan4 v4;
            deserializer >> v1 >> v2 >> v3 >> v4;
            ASSERT_EQ(v1, (ispan1{1, 2}));
            ASSERT_EQ(v2, (ispan2{ivec2{3, 4}, ivec2{5, 6}}));
            ASSERT_EQ(v3, (ispan3{ivec3{7, 8, 9}, ivec3{10, 11, 12}}));
            ASSERT_EQ(v4, (ispan4{ivec4{13, 14, 15, 16}, ivec4{17, 18, 19, 20}}));
        }
        ASSERT_TRUE(deserializer.close());
    }
}

TEST(Serializer, fieldN)
{
    static_assert(qc::HasSerializableN<CustomA>);

    {
        qc::Serializer serializer{file};
        ASSERT_TRUE(serializer);
        serializer << CustomB{CustomA{ivec2{1, 2}, true}, CustomA{ivec2{3, 4}, false}, 5.0};
        ASSERT_TRUE(serializer.close());
    }
    {
        qc::Deserializer deserializer{file};
        ASSERT_TRUE(deserializer);
        {
            CustomB v;
            deserializer >> v;
            ASSERT_EQ(v.a().a, (ivec2{1, 2}));
            ASSERT_EQ(v.a().b, true);
            ASSERT_EQ(v.b().a, (ivec2{3, 4}));
            ASSERT_EQ(v.b().b, false);
            ASSERT_EQ(v.c(), 5.0);
        }
        ASSERT_TRUE(deserializer.close());
    }
}

TEST(Serializer, stdString)
{
    {
        qc::Serializer serializer{file};
        ASSERT_TRUE(serializer);
        serializer << std::string{"oh wow, super cool"};
        ASSERT_TRUE(serializer.close());
    }
    {
        qc::Deserializer deserializer{file};
        ASSERT_TRUE(deserializer);
        {
            std::string v;
            deserializer >> v;
            ASSERT_EQ(v, "oh wow, super cool");
        }
        ASSERT_TRUE(deserializer.close());
    }
}

TEST(Serializer, stdMap)
{
    {
        qc::Serializer serializer{file};
        ASSERT_TRUE(serializer);
        serializer << std::map<std::string, int>{{"a", 1}, {"b", 2}, {"c", 3}};
        ASSERT_TRUE(serializer.close());
    }
    {
        qc::Deserializer deserializer{file};
        ASSERT_TRUE(deserializer);
        {
            std::map<std::string, int> v;
            deserializer >> v;
            ASSERT_EQ(v, (std::map<std::string, int>{{"a", 1}, {"b", 2}, {"c", 3}}));
        }
        ASSERT_TRUE(deserializer.close());
    }
}

TEST(Serializer, list)
{
    {
        qc::Serializer serializer{file};
        ASSERT_TRUE(serializer);
        serializer << qc::List<int>{1, 2, 3};
        serializer << qc::List<std::string>{"1", "2", "3"};
        ASSERT_TRUE(serializer.close());
    }
    {
        qc::Deserializer deserializer{file};
        ASSERT_TRUE(deserializer);
        {
            qc::List<int> v1;
            qc::List<std::string> v2;
            deserializer >> v1 >> v2;
            ASSERT_EQ(v1, (qc::List<int>{1, 2, 3}));
            ASSERT_EQ(v2, (qc::List<std::string>{"1", "2", "3"}));
        }
        ASSERT_TRUE(deserializer.close());
    }
}

template <typename T> concept Serializable = requires(T v, qc::Serializer s) { s << v; };
template <typename T> concept Deserializable = requires(T v, qc::Deserializer ds) { ds >> v; };
template <typename T> concept Unserializable = !Serializable<T> && !Deserializable<T>;

TEST(Serializer, fails)
{
    static_assert(Unserializable<char *>);
    static_assert(Unserializable<const char *>);

    static_assert(Unserializable<int *>);
    static_assert(Unserializable<const int *>);

    static_assert(Unserializable<void *>);
    static_assert(Unserializable<const void *>);
}
