// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifdef JET_USE_CUDA

#ifndef INCLUDE_JET_CUDA_TEXTURE_H_
#define INCLUDE_JET_CUDA_TEXTURE_H_

#include <jet/cuda_array_view1.h>
#include <jet/cuda_array_view2.h>
#include <jet/cuda_array_view3.h>

#include <cuda_runtime.h>

namespace jet {

template <typename T, size_t N, typename Derived>
class CudaTexture {
 public:
    static_assert(N >= 1 || N <= 3,
                  "Not implemented - N should be either 1, 2 or 3.");

    virtual ~CudaTexture();

    void clear();

    void set(const ConstArrayView<T, N>& view);

    void set(const ConstCudaArrayView<T, N>& view);

    void set(const Derived& other);

    cudaTextureObject_t textureObject() const;

 protected:
    Size<N> _size;
    cudaArray_t _array = nullptr;
    cudaTextureObject_t _tex = 0;

    CudaTexture();

    CudaTexture(const ConstArrayView<T, N>& view);

    CudaTexture(const ConstCudaArrayView<T, N>& view);

    CudaTexture(const CudaTexture& other);

    CudaTexture(CudaTexture&& other);

    CudaTexture& operator=(const CudaTexture& other);

    CudaTexture& operator=(CudaTexture&& other) = delete;

    static cudaTextureObject_t createTexture(
        cudaArray_t array,
        cudaTextureFilterMode filterMode = cudaFilterModeLinear,
        bool shouldNormalizeCoords = false);
};

template <typename T>
class CudaTexture1 final : public CudaTexture<T, 1, CudaTexture1<T>> {
 public:
    typedef CudaTexture<T, 1, CudaTexture1<T>> Base;
    using Base::textureObject;
    using Base::operator=;

    CudaTexture1();

    CudaTexture1(const ConstArrayView<T, 1>& view);

    CudaTexture1(const ConstCudaArrayView<T, 1>& view);

    CudaTexture1(const CudaTexture1& other);

    CudaTexture1(CudaTexture1&& other);

    size_t size() const;

    CudaTexture1& operator=(CudaTexture1&& other);

 private:
    friend class Base;

    void resize(const Size<1>& size);

    template <typename View>
    void _set(const View& view, cudaMemcpyKind memcpyKind);

    void _set(const CudaTexture1& other);
};

template <typename T>
class CudaTexture2 final : public CudaTexture<T, 2, CudaTexture2<T>> {
 public:
    typedef CudaTexture<T, 2, CudaTexture2<T>> Base;
    using Base::textureObject;
    using Base::operator=;

    CudaTexture2();

    CudaTexture2(const ConstArrayView<T, 2>& view);

    CudaTexture2(const ConstCudaArrayView<T, 2>& view);

    CudaTexture2(const CudaTexture2& other);

    CudaTexture2(CudaTexture2&& other);

    Size2 size() const;

    size_t width() const;

    size_t height() const;

    CudaTexture2& operator=(CudaTexture2&& other);

 private:
    friend class Base;

    void resize(const Size<2>& size);

    template <typename View>
    void _set(const View& view, cudaMemcpyKind memcpyKind);

    void _set(const CudaTexture2& other);
};

template <typename T>
class CudaTexture3 final : public CudaTexture<T, 3, CudaTexture3<T>> {
 public:
    typedef CudaTexture<T, 3, CudaTexture3<T>> Base;
    using Base::textureObject;
    using Base::operator=;

    CudaTexture3();

    CudaTexture3(const ConstArrayView<T, 3>& view);

    CudaTexture3(const ConstCudaArrayView<T, 3>& view);

    CudaTexture3(const CudaTexture3& other);

    CudaTexture3(CudaTexture3&& other);

    Size3 size() const;

    size_t width() const;

    size_t height() const;

    size_t depth() const;

    CudaTexture3& operator=(CudaTexture3&& other);

 private:
    friend class Base;

    void resize(const Size<3>& size);

    template <typename View>
    void _set(const View& view, cudaMemcpyKind memcpyKind);

    void _set(const CudaTexture3& other);
};

}  // namespace jet

#include "detail/cuda_texture-inl.h"

#endif  // INCLUDE_JET_CUDA_TEXTURE_H_

#endif  // JET_USE_CUDA